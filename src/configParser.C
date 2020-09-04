//Author: Mr. Man Brother (2020.01.24)

//cpp
#include <iostream>

//Local
#include "include/configParser.h"

configParser::configParser(std::string inConfigFileName)
{
  Init(inConfigFileName);
  return;
}

bool configParser::Init(std::string inConfigFileName)
{
  Clean(); //Make sure all is reset in-case we forget a Clean call before invoking Init

  m_configFileName = inConfigFileName;
  if(!check.checkFile(m_configFileName)){
    std::cout << "configParser::Init - Given inConfigFileName \'" << inConfigFileName << "\' is invalid. Init failed, return false" << std::endl;
    Clean();
    return false;
  }
  
  m_configFile = new std::ifstream(m_configFileName.c_str());//Process our config file
  std::string tempStr;
  std::vector<std::string> tempVect;
  while(std::getline(*m_configFile, tempStr)){
    //    while(tempStr.find(" ") != std::string::npos){tempStr.replace(tempStr.find(" "),1,"");}
    if(tempStr.size()==0) continue;
    if(tempStr.substr(0,1).find("#") != std::string::npos) continue;//# is comment

    if(tempStr.find(":") == std::string::npos) continue;
    
    tempVect.push_back(tempStr.substr(0, tempStr.find(":")));
    tempStr.replace(0, tempStr.find(":")+1, "");
    std::vector<std::string> tempVect2 = commaSepStringToVect(tempStr);//We need to parse string list
    tempVect.insert(std::end(tempVect), std::begin(tempVect2), std::end(tempVect2));

    
    
    if(tempVect.size() < 2){
      std::cout << "configParser::Init - Given inConfigFileName \'" << inConfigFileName << "\' contains invalid line \'" << tempStr << "\'. Please fix (At least 2 items, comma sep). Clean and return false." << std::endl;
      Clean();
      return false;
    }
    std::string valStr = tempVect[1];
    for(unsigned int tI = 2; tI < tempVect.size(); ++tI){
      valStr = valStr + "," + tempVect[tI];
    }

    while(valStr.size() > 0){
      if(valStr.substr(0, 1).find(" ") != std::string::npos){
	valStr.replace(0,1,"");
      }
      else break;
    }
    
    m_configVals[tempVect[0]] = valStr;
    tempVect.clear();
  }
  
  return true;
}

bool configParser::ContainsParam(std::string inStr, bool doSilent)
{

  if(m_configVals.count(inStr) == 0){
    if(!doSilent) std::cout << "configParser::ContainsParam - Given inStr \'" << inStr << "\' not found. Please define in given config \'" << m_configFileName << "\'. return false" << std::endl;
    return false;
  }
  return true;
}

bool configParser::ContainsParamSet(std::vector<std::string> inParamVect)
{
  bool retVal = true;
  for(auto const & param : inParamVect){
    retVal = retVal && ContainsParam(param);
  }
  return retVal;
}

std::string configParser::GetConfigVal(std::string inStr)
{
  if(m_configVals.count(inStr) == 0){
    std::cout << "configParser::GetConfigVal - Given inStr \'" << inStr << "\' is not found. Please define in given config \'" << m_configFileName << "\'. return empty string." << std::endl;
    return "";
  }
  return m_configVals[inStr];
}

std::string configParser::GetDefinitionVal(std::string inStr)
{
  if(m_definitionVals.count(inStr) == 0){
    std::cout << "configParser::GetDefinitionVal - Given inStr \'" << inStr << "\' is not found. Please define in given config \'" << m_configFileName << "\'. return empty string." << std::endl;
    return "";
  }
  return m_definitionVals[inStr];
}

std::map<std::string, std::string> configParser::GetConfigMap(){return m_configVals;}

void configParser::Clean()
{
  m_configFileName = "";
  if(m_configFile != nullptr){
    m_configFile->close();
    delete m_configFile;
    m_configFile = nullptr;
  }
  m_configVals.clear();
  m_definitionVals.clear();
  
  return;
}

void configParser::SetConfigVal(std::string inStrParam, std::string inStrVal)
{
  if(m_configVals.count(inStrParam) != 0){
    std::cout << "CONFIGPARSER WARNING - SetConfigVal called to override, \'" << inStrParam << "\' with new value \'" << inStrVal << "\'" << std::endl;
  }
  m_configVals[inStrParam] = inStrVal;
  return;
}
