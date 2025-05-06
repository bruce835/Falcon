#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <cctype>

int lineNumber = 1;
char ch;
std::string tokenType = "Type";

struct Token {
	std::string type;
	std::string value;
	int line;
};

std::vector<Token> tokenize(std::vector<Token>& tokens, std::vector<char>& buf, std::ifstream& src) {
	std::string value(buf.begin(), buf.end());
	tokens.push_back({tokenType, value, lineNumber});
	buf.clear();
	return tokens;
}

int main(int argc, char *argv[]) {
	std::vector<Token> tokens;
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
				tokenize(tokens, buf, src);
			}
			
			else {
				buf.push_back(ch);
			}
		}

		else if (ch == '\"') {
			if (tokenType != "String") {
				tokenType = "String";
				buf.push_back(ch);
				tokenize(tokens, buf, src);
			}

			else {
				buf.pop_back();
				tokenize(tokens, buf, src);
				tokenType = "Type";
			}
		}
		
		else if (tokenType != "String") {
			if (ch == '(') {
				tokenType = "(";
				buf.push_back(ch);
				tokenize(tokens, buf, src);
			}

			else if (ch == ')') {
				tokenType = ")";
				buf.push_back(ch);
				tokenize(tokens, buf, src);
			}
			
			else if (ch == '{') {
				tokenType = "{";
				buf.push_back(ch);
				tokenize(tokens, buf, src);
			}

			else {
				buf.push_back(ch);
			}
		}
	}

	for (const Token& token : tokens) {
		std::cout << "\n\nType: " << token.type;
		std::cout << "\nValue: " << token.value;
		std::cout << "\nLine: " << token.line;
	}

	return 0;
}
