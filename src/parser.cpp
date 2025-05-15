#include <iostream>
#include <vector>
#include <string>
#include "../include/parser.h"
#include "../include/compiler.h"
#include "../include/libraries/abstractions.hpp"

std::string abstractionType = "null";
int paramDepth = 0;

void printParseTree(const func& newFunc, int depth = 0) {
    std::string indent(depth * 4, ' '); // Creates indentation for hierarchy
    std::cout << indent << "|-- Function: " << newFunc.identifier << "\n";
    std::cout << indent << "    |-- Return Type: " << newFunc.returnType << "\n";
    if (!newFunc.parameters.empty()) {
        std::cout << indent << "    |-- Parameters:\n";
        for (const auto& param : newFunc.parameters) {
            std::cout << indent << "        |-- " << param.type << ": " << param.value << "\n";
        }
    } else {
        std::cout << indent << "    |-- No Parameters\n";
    }
}

int parseFunc(Token& token, auto& tokenIterator, int& funcStep, func& newFunc) {
  tokenIterator++;
  if (tokenIterator != tokens.end()) {
    token = *tokenIterator;
  }
  auto nextTokenIt = std::next(tokenIterator, 1);

  if(nextTokenIt != tokens.end()) {
    Token nextToken = *nextTokenIt;
 if (funcStep == 2) {
    if (token.type != "("){
      std::cerr << "p_01: Expected \"(\".";
    } 
 }

 else if (funcStep == 3) {  
   std::string paramType = "";
   std::string paramValue = "";
   for (int i = 0; i < 100; i++) {
     std::cout << token.type << " " << token.value << std::endl;
     if (token.type == ")") {
       std::cout << "\n" << paramDepth;
       break;
     }
     
     else if (token.type == "(") {
       ++tokenIterator;
       ++nextTokenIt;
       token = *tokenIterator;
       nextToken = *nextTokenIt;
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
       ++nextTokenIt;
       nextToken = *nextTokenIt;
     }
   }
 }
    if (token.type == "(") {
      paramDepth++;
     }

    else if (token.type == ")") {
      if (paramDepth == 0) {
        std::cerr << "p_02: Expected \"(\" before \")\".";
      }
      paramDepth--;
    }

if (paramDepth > 0) {
  std::cerr << "p_03: Missing ')'.\n";
}

else if (paramDepth <0) {
  std:: cerr << "p_04: Missing ')'.\n";
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
      for(int funcStep = 1; funcStep <=3; funcStep++) {
    parseFunc(token, tokenIterator, funcStep, newFunc);
  } 
      //printParseTree(newFunc, 0);
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
