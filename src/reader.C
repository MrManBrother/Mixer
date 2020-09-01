//Author: Mr. Man Brother (2020.08.28)
//Contact at mr.man.brother@gmail.com or MrManBrother github for bugs

//Local
#include "include/reader.h"
#include "include/stringUtil.h"

//c+cpp
#include <cmath>
#include <iostream>
#include <fstream>

reader::reader(std::string in_inFileName, unsigned int in_edgeWordsToSkip)
{
  Init(in_inFileName, in_edgeWordsToSkip);
  return;
}
 
reader::~reader()
{
  Clean();
  return;
}

bool reader::Init(std::string in_inFileName, unsigned int in_edgeWordsToSkip)
{
  m_inFileName = in_inFileName;

  std::ifstream inFile(m_inFileName);
  std::string tempStr = "";

  m_edgeWordsToSkip = std::max(in_edgeWordsToSkip, (unsigned int)0);
  
  while(std::getline(inFile, tempStr)){    
    if(tempStr.size() == 0) continue;
    while(tempStr.substr(0, 1).find(" ") != std::string::npos){
      tempStr.replace(0,1,"");
      if(tempStr.size() == 0) break;
    }
    if(tempStr.size() == 0) continue;

    std::vector<std::string> words = spaceSepStringToVect(tempStr);
    std::string frontLine = "";
    std::string mainLine = "";
    std::string backLine = "";

    for(unsigned int wI = 0; wI < words.size(); ++wI){
      if(wI < in_edgeWordsToSkip) frontLine = frontLine + words [wI] + " ";
      else if(wI > words.size() - 1 - in_edgeWordsToSkip) backLine = backLine + words [wI] + " ";
      else mainLine = mainLine + words [wI] + " ";
    }

    if(frontLine.size() != 0) frontLine.replace(frontLine.size()-1, 1, "");
    if(backLine.size() != 0) backLine.replace(backLine.size()-1, 1, "");
    if(mainLine.size() != 0) mainLine.replace(mainLine.size()-1, 1, "");
    
    m_lines.push_back(mainLine);
    m_frontLines.push_back(frontLine);
    m_backLines.push_back(backLine);
  }
  inFile.close();

  for(unsigned int lI = 0; lI < m_lines.size(); ++lI){
    std::vector<std::string> words = spaceSepStringToVect(m_lines[lI]);

    for(auto const & word : words){
      if(m_wordToLinesMap.count(word) == 0) m_wordToLinesMap[word] = {lI};
      else m_wordToLinesMap[word].push_back(lI);
    }      
  }
  
  return true;
}
 
  
void reader::Clean()
{
  m_inFileName = "";

  m_lines.clear();
  m_linesLower.clear();
  m_wordToLinesMap.clear();
  
  return;
}

void reader::Print()
{
  std::cout << "PRINTING CURRENT STORED TXT:" << std::endl;
  std::cout << "LINE-BY-LINE:" << std::endl;
  for(auto const & line : m_lines){
    std::cout << " " << line << std::endl;
  }
  std::cout << "WORDS:" << std::endl;
  for(auto const & word : m_wordToLinesMap){
    std::cout << " " << word.first << ": " << word.second.size() << std::endl;
  }

  
  std::cout << "PRINTING STORED TXT COMPLETE !" << std::endl;
}

std::vector<std::string> reader::GetReaderMix(reader* external_p)
{
  std::vector<std::string> mixLines;

  for(auto const & word : m_wordToLinesMap){
    if(external_p->ReaderContainsWord(word.first)){
      std::vector<std::string> externalLines = external_p->GetLinesWithWord(word.first);
      std::vector<std::string> externalFrontLines = external_p->GetFrontLinesWithWord(word.first);
      std::vector<std::string> externalBackLines = external_p->GetBackLinesWithWord(word.first);
      
      for(unsigned int wI = 0; wI < word.second.size(); ++wI){
	for(unsigned int wI2 = 0; wI2 < externalLines.size(); ++wI2){
	  for(unsigned int i = 0; i < 2; ++i){
	    std::string frontLine, backLine;
	    std::string frontMainLine, backMainLine;
	    if(i == 0){
	      frontLine = m_frontLines[word.second[wI]];
	      frontMainLine = m_lines[word.second[wI]];
	      backMainLine = externalLines[wI2];
	      backLine = externalBackLines[wI2];
	    }
	    else{
	      backLine = m_backLines[word.second[wI]];
	      backMainLine = m_lines[word.second[wI]];
	      frontMainLine = externalLines[wI2];
	      frontLine = externalFrontLines[wI2];
	    }
	    
	    frontMainLine.replace(frontMainLine.find(word.first), frontMainLine.size(), "");
	    backMainLine.replace(0, backMainLine.find(word.first), "");
	    mixLines.push_back(frontLine + " " + frontMainLine + backMainLine + " " + backLine);
	  }
	}
      }      
    }
  }

  return mixLines;
}

bool reader::ReaderContainsWord(std::string inWord)
{
  return m_wordToLinesMap[inWord].size() > 0;
}


std::vector<std::string> reader::GetLinesWithWord(std::string inWord)
{
  std::vector<std::string> lines;
  std::vector<unsigned int> lineNumbers = m_wordToLinesMap[inWord];
  for(auto const & number : lineNumbers){
    lines.push_back(m_lines[number]);
  }
  return lines;
}

std::vector<std::string> reader::GetFrontLinesWithWord(std::string inWord)
{
  std::vector<std::string> lines;
  std::vector<unsigned int> lineNumbers = m_wordToLinesMap[inWord];
  for(auto const & number : lineNumbers){
    lines.push_back(m_frontLines[number]);
  }
  return lines;
}

std::vector<std::string> reader::GetBackLinesWithWord(std::string inWord)
{
  std::vector<std::string> lines;
  std::vector<unsigned int> lineNumbers = m_wordToLinesMap[inWord];
  for(auto const & number : lineNumbers){
    lines.push_back(m_backLines[number]);
  }
  return lines;
}
