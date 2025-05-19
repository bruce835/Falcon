#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

struct Token {
	std::string type;
	std::string value;
	int line;
};

extern std::vector<Token> tokens;
extern std::string fileName;
#endif
