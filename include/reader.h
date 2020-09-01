//Author: Mr. Man Brother (2020.08.28)
//Contact at mr.man.brother@gmail.com or MrManBrother on github for bugs

#ifndef READER_H
#define READER_H

//c+cpp
#include <map>
#include <string>
#include <vector>
 
class reader{
 public:
  reader(){};
  reader(std::string in_inFileName, unsigned int in_edgeWordsToSkip = 0);
  ~reader();

  bool Init(std::string in_inFileName, unsigned int in_edgeWordsToSkip = 0);
  void Clean();
  void Print();
  std::vector<std::string> GetReaderMix(reader* external_p);
  bool ReaderContainsWord(std::string inWord);
  std::vector<std::string> GetLinesWithWord(std::string inWord);
  std::vector<std::string> GetFrontLinesWithWord(std::string inWord);
  std::vector<std::string> GetBackLinesWithWord(std::string inWord);
  
 private:
  std::string m_inFileName;

  int m_edgeWordsToSkip;
  
  std::vector<std::string> m_lines;
  std::vector<std::string> m_linesLower;
  std::vector<std::string> m_frontLines;
  std::vector<std::string> m_backLines;
  std::map<std::string, std::vector<unsigned int> > m_wordToLinesMap;
};

#endif
