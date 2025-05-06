#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <cctype>

int lineNumber = 1;
char ch;

struct Token {
	std::string type;
	std::string value;
	int line;
};

std::vector<Token> tokenize(std::vector<char>& buf, std::ifstream& src) {
	std::vector<Token> tokens;
	std::string value(buf.begin(), buf.end());
	tokens.push_back({"Type", value, lineNumber});
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
		for (const Token& token : tokenize(buf, src)) {
			std::cout << "\nType: " << token.type << std::endl;
			std::cout << "Value: " << token.value;
			std::cout <<"\nLine Number: " << token.line;
		}
			buf.clear();
		}

		else {
			buf.push_back(ch);
		}
	}

	return 0;
}
