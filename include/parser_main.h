#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
#include "lexer_main.h"
#include "compiler.h"

int parse(std::vector<Token>& tokens, std::string& fileName);

#endif
