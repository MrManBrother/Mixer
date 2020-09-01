//Author: Mr. Man Brother (2020.08.31)
//Contact at mr.man.brother@gmail.com or MrManBrother on github for bugs

//c+cpp
#include <iostream>
#include <string>

//Local
#include "include/checkMakeDir.h"
#include "include/reader.h"

int testReader(std::string inFileName)
{
  checkMakeDir check;
  if(!check.checkFileExt(inFileName, ".txt")) return 1;

  reader testReader(inFileName);

  std::cout << "Checking print..." << std::endl;
  testReader.Print();
  std::cout << "Print check complete." << std::endl;
  
  
  std::cout << "TESTREADER COMPLETE. return 0." << std::endl;
  return 0;
}

int main(int argc, char* argv[])
{
  if(argc != 2){
    std::cout << "Usage: ./bin/testReader.exe <inFileName>" << std::endl;
    std::cout << "TO DEBUG:" << std::endl;
    std::cout << " export DOGLOBALDEBUGROOT=1 #from command line" << std::endl;
    std::cout << "TO TURN OFF DEBUG:" << std::endl;
    std::cout << " export DOGLOBALDEBUGROOT=0 #from command line" << std::endl;
    std::cout << "return 1." << std::endl;
    return 1;
  }
 
  int retVal = 0;
  retVal += testReader(argv[1]);
  return retVal;
}
