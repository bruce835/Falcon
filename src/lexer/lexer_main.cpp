#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <cctype>
#include <chrono>
#include "../../include/parser.h"
#include "../../include/compiler.h"
#include "../../include/lexer_main.h"
#include "../../include/libraries/types.hpp"
#include "../../include/tokenProcessor.h"

int lineNumber = 1;
char ch;
std::string tokenType = "Type";
std::vector<Token> tokens;
std::string fileName = "";
std::chrono::time_point<std::chrono::high_resolution_clock> initialTime = std::chrono::high_resolution_clock::now();

std::string checkType(std::vector<char>& buf) {
	std::string bufString(buf.begin(), buf.end());
	bool isDeclarator = (isDataType(bufString));
	bool hasKeyOrInvalidSymbol = false;
	bool isIdentifier = (tokenType == "Declarator" && isalpha(buf[0]) && !hasKeyOrInvalidSymbol);
  bool is_Keyword = (isKeyword(bufString));
	
	for (const char& bufChar : buf) {
		if (!isalnum(bufChar) && bufChar != '-' && bufChar != '_') {
			hasKeyOrInvalidSymbol = true;
		}
	}

	if (isDeclarator) {
		tokenType = "Declarator";
	}

	else if (isIdentifier) {
		tokenType = "Identifier";
	}
		
	else if (is_Keyword) {
		tokenType = "Keyword"; 
	}

	return tokenType;
}

std::vector<Token> tokenize(std::vector<Token>& tokens, std::vector<char>& buf, std::ifstream& src) {
  if (buf.empty()) {
    return tokens;
  }

	std::string value(buf.begin(), buf.end());
	tokens.push_back({checkType(buf), value, lineNumber});
	buf.clear();
	return tokens;
}

std::vector<Token> readTokens(const std::string& srcPath) {
	std::ifstream src(srcPath);
	std::vector<char> buf;

	if (!src) {
		std::cerr << "Source file not found. Exiting.";
		exit(0);
	}
  
  while(src.get(ch)) {
    processTokens(buf, ch, src);
  }

  return tokens;
}

int main(int argc, char *argv[]) {
	std::string srcPath = argv[1];

  for (const char& ch : srcPath) {
    if (ch == '/') {
      fileName.clear();
    } 
    else {
      fileName.push_back(ch);
    }
  }

  for (char& ch : fileName) {
    if (ch == '.') {
      while (true) {
        if (fileName.back() == '.') {
          fileName.pop_back();
          break;
        }
        fileName.pop_back();
        
        if (fileName.empty()) {
          break;
        }
      }
    }
  }

  tokens = readTokens(srcPath);
  
  for (auto token : tokens) {
    std::cout << token.value;
  }
  parse(tokens, fileName);
  return 0;
}
