#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <chrono>
#include <fstream>

struct Token {
	std::string type;
	std::string value;
	int line;
};

std::vector<Token> tokenize(std::vector<Token>& tokens, std::vector<char>& buf, std::ifstream& src);

extern std::vector<Token> tokens;
extern std::string fileName;
extern int lineNumber;

extern std::ifstream src;

extern std::chrono::time_point<std::chrono::high_resolution_clock> initialTime;
#endif
