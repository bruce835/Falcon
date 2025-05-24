#include "libraries/abstractions.hpp"
#include "lexer_main.h"
#include "functions.h"
#include <string>
#include <vector>
#include <iostream>


int processKeyword (std::string& currentKeyword, func& print, std::vector<parameter>& params) {
  if (currentKeyword == "print") {
    if (params.size() > print.paramCount) {
      std::cerr << "Function provided with more parameters than expected.\n";
      exit(0);
    }
  }
  return 0;
}

std::vector<parameter> checkKeyword (std::vector<Token>& funcTokens, const std::string& newInstruction) {  
  func print;
  //TODO: make this an array and actually use it
  parameter printParameter;
  func returnFunc;
  printParameter.type = "String";
  print.paramCount = 1;
  returnFunc.paramCount = 0; 
  std::vector<parameter> params;
  std::string currentKeyword;

  params.clear();
  for (auto& token : funcTokens) {
    if (token.type == "Keyword") {
      currentKeyword = token.value;
    }

    else if (token.type != ";" && token.type != "," && token.type != "\"" && token.type != "(" && token.type != ")") { 
     parameter param;
     param.value = token.value;
     param.type = token.type;
     params.push_back(param);
   } 
  } 

  processKeyword(currentKeyword, print, params);
  std::vector<parameter> paramsClone = params;
  params.clear();
  return paramsClone;
}
