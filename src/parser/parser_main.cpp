#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <sys/wait.h>
#include "lexer_main.h"
#include "parser_main.h"
#include "compiler.h"
#include "functions.h"

std::string abstractionType = "null";
int paramDepth = 0;
std::vector<parameter> newInstructionParams; 

compiler comp;


void compileForLinux(const std::string& fileName) {
    std::vector<std::vector<std::string>> commands = {
        {"nasm", "-f", "elf64", "asm/" + fileName + ".asm", "-o", "object/" + fileName + ".o"},
        {"ld", "object/" + fileName + ".o", "-o", "exampleBuilds/" + fileName}
    };

    for (const auto& cmd : commands) {
        std::vector<char*> args;
        for (const auto& str : cmd) {
            args.push_back(const_cast<char*>(str.c_str()));
        }
        args.push_back(nullptr);

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args.data());
            std::cerr << "execvp failed for " << args[0] << "\n";
            exit(EXIT_FAILURE);
        }

        else if (pid > 0) {
          int status;
          waitpid(pid, &status, 0);
        }

        else if (pid < 0) {
            std::cerr << "Fork failed!\n";
            exit(EXIT_FAILURE);
        }
    }
}

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

      for (const auto& instr : newFunc.instructions) {
        std::cout << indent << "        |-- " << instr.keyword << "\n";
        std::cout << indent << "            |-- Parameters: \n";

        for (auto& param : newInstructionParams) {
          std::cout << indent << "                |--" << param.type << ": " << param.value << std::endl;
        } 
      }
    }

    else {
      std::cout << indent << "    |-- No Instructions\n";
    }
}

int parseFunc(Token& token, auto& tokenIterator, int& funcStep, func& newFunc) {
  std::vector<Token> funcTokens;
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

     else if (!invalidParamToken) {
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
       std::string newInstructionKeyword = token.value; 

       while (true) {
         int functionIterator = 0;
       token = *tokenIterator;
       nextToken = *nextTokenIt;       

        if (token.value == ";") {
          newInstructionParams = checkKeyword(funcTokens, newInstructionKeyword);
          funcTokens.clear();
          instruction newInstruction; 
          newInstruction.keyword = newInstructionKeyword;
          newInstruction.parameters = newInstructionParams;
          newFunc.instructions.push_back(newInstruction);
          break;
        }

        else if (token.value == "return") {
          if (newFunc.returnType == "int") {
              for (const char& ch : nextToken.value) {
                if (ch != ';' && !isdigit(ch)) {
                  std::cerr << "Expected numerical value.";
                  exit(0);
                }
            }
              if (nextToken.value != ";") {
                newFunc.returnValues.push_back(nextToken.value); 
                funcTokens.push_back(nextToken);
              }
          }
          funcTokens.push_back(token);
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
     }

     else if (token.value == "}") {
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

        comp.toAssembly_function(newFunc);
      //  printParseTree(newFunc, 0);
      } 
  }
}

  return 0;
}

int parse(std::vector<Token>& tokens, std::string& fileName) {
  comp.asmClear();

  for (std::vector<Token>::iterator tokenIterator = tokens.begin(); tokenIterator != tokens.end(); tokenIterator++) {
    scan(*tokenIterator, tokenIterator);
  }
  
  if (usingLinux) {
    compileForLinux(fileName);
  }

  auto exitTime = std::chrono::high_resolution_clock::now();
  auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(exitTime - initialTime);
  std::cout << "Elapsed Time: " << elapsedTime.count() << "ms\n";
  return 0;
}
