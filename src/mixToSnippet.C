//Author: Mr. Man Brother (2020.09.04)
//Contact at mr.man.brother@gmail.com or MrManBrother on github for bugs

//c+cpp
#include <cmath>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

//Local
#include "include/checkMakeDir.h"
#include "include/configParser.h"
#include "include/stringUtil.h"

int mixToSnippet(std::string inConfigFileName)
{  
  checkMakeDir check;
  if(!check.checkFileExt(inConfigFileName, ".config")) return 1;

  configParser config(inConfigFileName);
  std::vector<std::string> reqParams = {"INFILENAME",
					"NLINES",
					"DOLINEBREAKS",
					"DOTITLE"};

  if(!config.ContainsParamSet(reqParams)) return 1;

  const std::string inFileName = config.GetConfigVal("INFILENAME");
  const int nLines = std::stoi(config.GetConfigVal("NLINES"));
  const bool doLineBreaks = std::stoi(config.GetConfigVal("DOLINEBREAKS"));
  const int linesPerBreak = std::stoi(config.GetConfigVal("LINESPERBREAK"));
  const bool doTitle = std::stoi(config.GetConfigVal("DOTITLE"));
  
  if(!check.checkFileExt(inFileName, ".txt")) return 1;
  
  std::vector<std::string> lines;
  std::ifstream inFile(inFileName.c_str());
  std::string tempStr;
  while(std::getline(inFile, tempStr)){
    if(tempStr.size() == 0) continue;

    lines.push_back(tempStr);
  }
  inFile.close();

  unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator;
  generator.seed(seed1);
  std::uniform_int_distribution<int> distribution(0,lines.size()-1);
  std::map<int, int> values;
  for(unsigned int i = 0; i < lines.size(); ++i){
    values[i] = 0;
  }

  const int nPullsTot = std::min(nLines, (int)lines.size());
  int nPulls = 0;
  std::cout << std::endl;

  std::string titleStr = "";
  if(doTitle){    
    while(nPulls < 1){
      int lineNum = distribution(generator);
      if(values[lineNum] > 0) continue;
      
      titleStr = lines[lineNum];
      ++(values[lineNum]);
      
      ++nPulls;
    }
    nPulls = 0;
  }

  std::vector<std::string> selectLines;
  while(nPulls < nPullsTot){
    int lineNum = distribution(generator);
    if(values[lineNum] > 0) continue;
    
    
    selectLines.push_back(lines[lineNum]);
    ++(values[lineNum]);
    
    ++nPulls;
  }

  if(doTitle){
    titleStr = returnAllCapsSentence(titleStr);
    std::cout << "'" << titleStr << "'" << std::endl;
    std::cout << std::endl;
  }
 
  for(unsigned int sI = 0; sI < selectLines.size(); ++sI){
    std::cout << selectLines[sI] << std::endl;
    
    if(doLineBreaks && sI != selectLines.size()-1 && (sI+1)%linesPerBreak == 0) std::cout << std::endl;
  }
  std::cout << std::endl;
  
  std::cout << "MIXTOSNIPPET COMPLETE. return 0." << std::endl;
  return 0;
}

int main(int argc, char* argv[])
{
  if(argc != 2){
    std::cout << "Usage: ./bin/mixToSnippet.exe <inConfigFileName>" << std::endl;
    std::cout << "TO DEBUG:" << std::endl;
    std::cout << " export DOGLOBALDEBUGROOT=1 #from command line" << std::endl;
    std::cout << "TO TURN OFF DEBUG:" << std::endl;
    std::cout << " export DOGLOBALDEBUGROOT=0 #from command line" << std::endl;
    std::cout << "return 1." << std::endl;
    return 1;
  }
 
  int retVal = 0;
  retVal += mixToSnippet(argv[1]);
  return retVal;
}
