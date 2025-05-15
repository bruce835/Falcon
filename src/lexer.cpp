#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <cctype>
#include "../include/parser.h"
#include "../include/compiler.h"
#include "../include/lexer.h"
#include "../include/libraries/types.hpp"

int lineNumber = 1;
char ch;
std::string tokenType = "Type";
std::vector<Token> tokens;

std::string checkType(std::vector<char>& buf) {
	std::string bufString(buf.begin(), buf.end());
	bool isDeclarator = (isDataType(bufString));
	bool hasKeyOrInvalidSymbol = false;
	bool isIdentifier = (tokenType == "Declarator" && isalpha(buf[0]) && !hasKeyOrInvalidSymbol);
	
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
		
	else if (bufString == "print") {
		tokenType = "Keyword"; 
	}

	return tokenType;
}

std::vector<Token> tokenize(std::vector<Token>& tokens, std::vector<char>& buf, std::ifstream& src) {
	std::string value(buf.begin(), buf.end());
	tokens.push_back({checkType(buf), value, lineNumber});
	buf.clear();
	return tokens;
}

int main(int argc, char *argv[]) {
	std::ifstream src;
	std::string srcPath = argv[1];
	src.open(srcPath);
	std::cout << srcPath << std::endl;
	std::vector<char> buf;
	if (!src) {
		std::cerr << "Source file not found. Exiting.";
		exit(0);
	}

	while (src.get(ch)) {
		if (std::isspace(ch)) {
			if (ch == '\n') {
				lineNumber++;
			}

			if (tokenType != "String") {
				if (!buf.empty()) {
					tokenize(tokens, buf, src);
				}
				continue;
			}
			
			else {
				buf.push_back(ch);
			}
		}

    else if (ch == ',') {
      if (tokenType != "String") { 
      tokenize(tokens, buf, src);
      if (buf.empty()) {
        tokenType = ",";
        buf.push_back(ch);
        tokenize(tokens, buf, src);
      }
      }
      
      else {
        buf.push_back(ch);
      }
    }

		else if (ch == '\"') {
			if (tokenType != "String") {
				if (!buf.empty()) {
					tokenize(tokens, buf, src);
				}

				tokenType = "\"";
				buf.push_back(ch);
				tokenize(tokens, buf, src);
				tokenType = "String";
			}

			else {
					tokenize(tokens, buf, src);
					buf.push_back(ch);
					tokenType = "\"";
					tokenize(tokens, buf, src);
			}
		}
		
		else if (tokenType != "String") {

		 if (ch == '(' || ch == ')') {
			if (!buf.empty()) {
				tokenize(tokens, buf, src);
			}

			tokenType = std::string(1, ch);
			buf.push_back(ch);
			tokenize(tokens, buf, src);
		}
			
			else if (ch == '{' || ch == '}') {
				if (!buf.empty()) {
					tokenize(tokens, buf, src);
				}

				tokenType = std::string(1, ch);
				buf.push_back(ch);
				tokenize(tokens, buf, src);
			}

			else if (ch == ';') {
			 if (!buf.empty()) {
				 tokenize(tokens, buf, src);
				}
			 tokenType = ";";
			 buf.push_back(ch);
			 tokenize(tokens, buf, src);
			}

			else {
				buf.push_back(ch);
			}
		}
		
		else if (tokenType == "String") {
			buf.push_back(ch);
		}
	}

	std::cout << std::endl;
  	for (const Token& token : tokens) {
		std::cout << "\nType: " << token.type;
		std::cout << "\nValue: " << token.value;
		std::cout << "\nLine: " << token.line << std::endl;
    
	} 

  parse(tokens);
  return 0;
}
