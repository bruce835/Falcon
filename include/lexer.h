#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <chrono>

struct Token {
	std::string type;
	std::string value;
	int line;
};

extern std::vector<Token> tokens;
extern std::string fileName;

extern std::chrono::time_point<std::chrono::high_resolution_clock> initialTime;
#endif
