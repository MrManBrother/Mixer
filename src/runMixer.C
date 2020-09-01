//Author: Man Brother (2020.08.27)
//Contact at mr.man.brother@gmail.com or MrManBrother on github for bugs

//c+cpp
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//Local includes
#include "include/checkMakeDir.h"
#include "include/configParser.h"
#include "include/reader.h"
#include "include/stringUtil.h"

int runMixer(std::string inConfigFileName)
{
  std::srand( unsigned ( 382712956 ) );

  checkMakeDir check;
  if(!check.checkFileExt(inConfigFileName, ".config")) return 1;

  const std::string dateStr = getDateStr();
  const std::string timeStr = getTimeStr();

  check.doCheckMakeDir("output");
  check.doCheckMakeDir("output/" + dateStr);
  
  configParser config(inConfigFileName);
  std::vector<std::string> reqParams = {"FILE.0",
					"FILE.1",
					"EDGEWORDSTOSKIP"}; 
  if(!config.ContainsParamSet(reqParams)) return 1;

  const unsigned int edgeWordsToSkip = std::stoi(config.GetConfigVal("EDGEWORDSTOSKIP"));
  std::vector<std::string> fileNames;

  for(unsigned int i = 0; i < 100; ++i){
    if(config.ContainsParam("FILE." + std::to_string(i), true)){
      std::string fileName = config.GetConfigVal("FILE." + std::to_string(i));
      while(fileName.substr(0, 1).find(" ") != std::string::npos){fileName.replace(0, 1, "");}
      fileNames.push_back(fileName);
    }
  }

  std::vector<std::string> allMixLines, tempMixLines;
  for(unsigned int fI = 0; fI < fileNames.size(); ++fI){
    reader baseReader(fileNames[fI], edgeWordsToSkip);

    for(unsigned int fI2 = fI+1; fI2 < fileNames.size(); ++fI2){
      reader subReader(fileNames[fI2], edgeWordsToSkip);

      tempMixLines = subReader.GetReaderMix(&baseReader);
      
      for(unsigned int tI = 0; tI < tempMixLines.size(); ++tI){
	if(!vectContainsStr(tempMixLines[tI], &allMixLines)) allMixLines.push_back(tempMixLines[tI]);
      }
    }
  }

  std::random_shuffle(allMixLines.begin(), allMixLines.end());

  std::ofstream outFile(("output/" + dateStr + "/mixed_" + dateStr + "_" + timeStr + ".txt").c_str());

  for(auto const & line : allMixLines){
    outFile << line << std::endl;
  }
  outFile.close();
  
  std::cout << "RUNMIXER COMPLETE. return 0." << std::endl;
  return 0;      
}

int main(int argc, char* argv[])
{
  if(argc != 2){
    std::cout << "Usage: ./bin/runMixer.exe <inConfigFileName>" << std::endl;
    std::cout << "TO DEBUG:" << std::endl;
    std::cout << " export DOGLOBALDEBUGROOT=1 #from command line" << std::endl;
    std::cout << "TO TURN OFF DEBUG:" << std::endl;
    std::cout << " export DOGLOBALDEBUGROOT=0 #from command line" << std::endl;
    std::cout << "return 1." << std::endl;
    return 1;
  }
 
  int retVal = 0;
  retVal += runMixer(argv[1]);
  return retVal;
}
