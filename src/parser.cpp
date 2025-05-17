#include <iostream>
#include <vector>
#include <string>
#include "../include/parser.h"
#include "../include/compiler.h"
#include "../include/libraries/functions.hpp"

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
    } 

    else {
        std::cout << indent << "    |-- No Parameters\n";
    }

    if (!newFunc.instructions.empty()) {
      std::cout << indent << "    |-- Instructions:\n";
      for (const std::string& instr : newFunc.instructions) {
        std::cout << indent << "        |-- " << instr << "\n";
      }
    }

    else {
      std::cout << indent << "    |-- No Instructions\n";
    }
}

int parseFunc(Token& token, auto& tokenIterator, int& funcStep, func& newFunc) {
  tokenIterator++;
  if (tokenIterator != tokens.end() && tokenIterator != tokens.begin()) {
    token = *tokenIterator;
  }
   auto nextTokenIt = std::next(tokenIterator, 1);

  if(nextTokenIt != tokens.end() && nextTokenIt != tokens.begin()) {
    Token nextToken = *nextTokenIt;
 if (funcStep == 2) {
    if (token.type != "("){
      std::cerr << "p_01: Expected \"(\".";
       exit(0);
    } 
    else {
      paramDepth++;
    }
 }

 else if (funcStep == 3) {  
   std::string paramType = "";
   std::string paramValue = "";
   --tokenIterator;
   --nextTokenIt;
   token = *tokenIterator;
   nextToken = *nextTokenIt;
   for (int i = 0; i < 100; i++) {
     ++tokenIterator;
     ++nextTokenIt;
     token = *tokenIterator;
     nextToken = *nextTokenIt;

      bool invalidParamToken = (token.type == "," || token.type == "\"");

     if (token.type == ")") {
        if (paramDepth <= 0) {
         std::cerr << "p_02: Expected \"(\" before \")\".";
         exit(0);
        }
      else {
        paramDepth--;
      }
     }

     else if (token.type == "{") {
       if (paramDepth > 0) {
         std::cerr << "Expected ')' before '{'\n";
         exit(0);
       }
       return 0;
     }
     
     else if (token.type == "(") {
       std::cout << "at (:\n";
       paramDepth++;
     }

     else if (!invalidParamToken){
       parameter newParam;
       newParam.type = token.type;
        paramType = newParam.type;
       newParam.value = token.value;
        paramValue = newParam.value;
        std::cout << paramType << " " << paramValue << std::endl;
       newFunc.parameters.push_back(newParam);
     }
   }
  if (paramDepth > 0) {
    std::cerr << "p_03: Missing ')'.\n";
    exit(0);
  }

  else if (paramDepth < 0) {
    std:: cerr << "p_04: Missing ')'.\n";
    exit(0);
  }
 }

  else if (funcStep == 4) { 
    tokenIterator = tokens.begin();
    nextTokenIt = next(tokenIterator, 1);
   token = *tokenIterator;
   nextToken = *nextTokenIt;
   while(true) {
     if(tokenIterator == tokens.end()) {
       std::cerr << "tokens.end() reached";
     }
     if(tokenIterator != tokens.end()) {
      ++tokenIterator;
     }
     ++nextTokenIt;
     if (tokenIterator != tokens.end()) {
      token = *tokenIterator;
     }
     if (nextTokenIt != tokens.end()) {
      nextToken = *nextTokenIt;
     }

     if (token.type == "Keyword") {
       std::string newInstruction = token.value; 
       newFunc.instructions.push_back(newInstruction);

       std::vector<Token> funcTokens;
       
       int functionIterator = 0;
       while (true) {
       token = *tokenIterator;
       nextToken = *nextTokenIt;       
        if (token.value == ";") {
          break;
        }
        
        else if (token.type == "Keyword" && functionIterator > 0) {
          std::cerr << "Expected ';'";
          exit (0);
        }

        else {
          funcTokens.push_back(token);
        }

       ++tokenIterator;
       ++nextTokenIt;
       ++functionIterator;
       }
        functions functionsLocal;
       functionsLocal.checkKeyword(funcTokens, newInstruction);
     }

     else if (token.value == "}") {
       std::cout << "\nEnd of Func\n";
       return 0;
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
      for(int funcStep = 1; funcStep <=4; funcStep++) {
    parseFunc(token, tokenIterator, funcStep, newFunc);
  } 
      printParseTree(newFunc, 0);
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
