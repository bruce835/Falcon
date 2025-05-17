#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "abstractions.hpp"
#include "../lexer.h"
#include <string>
#include <vector>
#include <iostream>

class functions { 
  // Keywords
  public:
  func print;
  parameter printParameter;

  functions() {
    printParameter.type = "String";
    print.paramCount = 1;
  }

    std::vector<parameter> params;
    std::string currentKeyword;

  int processKeyword () {
    if (currentKeyword == "print") {
      if (params.size() > print.paramCount) {
        std::cerr << "Function provided with more parameters than expected.\n";
        exit(0);
      }
    }
    return 0;
  }

  int checkKeyword (std::vector<Token>& funcTokens, const std::string& newInstruction) {  
    for (auto& token : funcTokens) {
      if (token.type == "Keyword") {
        currentKeyword = token.value;
      }

      else if (token.type != "," && token.type != "\"" && token.type != "(" && token.type != ")") { 
       parameter param;
       param.value = token.value;
       param.type = token.type;
       params.push_back(param);
     } 
    } 

    processKeyword();
    return 0;
  }
};
#endif
