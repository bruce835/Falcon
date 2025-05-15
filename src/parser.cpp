#include <iostream>
#include <vector>
#include <string>
#include "../include/parser.h"
#include "../include/compiler.h"
#include "../include/libraries/abstractions.hpp"

std::string abstractionType = "null";

int parseFunc(Token& token, auto& tokenIterator, int& funcStep, func& newFunc) {
  tokenIterator++;
  if (tokenIterator != tokens.end()) {
    token = *tokenIterator;
  }
  auto nextTokenIt = std::next(tokenIterator, 1);

  if(nextTokenIt != tokens.end()) {
    Token nextToken = *nextTokenIt;
 if (funcStep == 2) {
    if (token.type == "(") {
        std::cout << "\nParameters:";
    }
    else {
      std::cerr << "p_01: Expected \"(\".";
    } 
 }

 else if (funcStep == 3) {  
   std::string paramType = "";
   std::string paramValue = "";
   int paramCount = 0;
   for (int i = 0; i < 5; i++) {
     if (token.type == ")") {
       break;
     }
     else if (token.value == ",") {
       ++tokenIterator;
       ++nextTokenIt;
       token = *tokenIterator;
       nextToken = *nextTokenIt;
     }
     else if (token.value == "\"") {
       ++tokenIterator;
       ++nextTokenIt;
       token = *tokenIterator;
       nextToken = *nextTokenIt;
     }
     else {
       parameter newParam;
       newParam.type = token.type;
        paramType = newParam.type;
       newParam.value = token.value;
        paramValue = newParam.value;
       newFunc.parameters.push_back(newParam);
       ++tokenIterator;
       token = *tokenIterator;
       nextToken = *nextTokenIt;
       ++nextTokenIt;
     }
    paramCount = i;
   }
   if (paramCount == 0) {
     std::cout << "none";
   }
   else {
   for (parameter& param : newFunc.parameters) {
     std::cout << param.value << ";";
   }
   }
 }
}
 return 0;
}

int scan(Token& token, std::vector<Token>::iterator& tokenIterator) {
  std::string nextTokenType = "null";
  std::string nextTokenValue = "null";
  std::vector<Token>::iterator nextTokenIt = std::next(tokenIterator, 1);

  if (nextTokenIt != tokens.end()) {
    Token nextToken = *nextTokenIt;
    nextTokenType = nextToken.type;
    nextTokenValue = nextToken.value;
    if (token.type == "Declarator") {
    if (nextTokenType == "Identifier") {
     abstractionType = "Function";
     func newFunc;
     newFunc.returnType = token.value;
     newFunc.identifier = nextTokenValue;
     std::cout << "Function " << newFunc.identifier << ":\nReturn Type: " << newFunc.returnType << std::endl; 
      for(int funcStep = 1; funcStep <=3; funcStep++) {
    parseFunc(token, tokenIterator, funcStep, newFunc);
  } 
   } 
  }
}

  return 0;
}

int parse(std::vector<Token>& tokens) {
  for (std::vector<Token>::iterator tokenIterator = tokens.begin(); tokenIterator != tokens.end(); tokenIterator++) {
    scan(*tokenIterator, tokenIterator);
  }

  toAssembly(tokens);
  return 0;
}


