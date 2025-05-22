#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <string>
#include <vector>
#include "libraries/abstractions.hpp"
#include "lexer_main.h"

int processKeyword();
std::vector<parameter> checkKeyword (std::vector<Token>& funcTokens, const std::string& newInstruction);
#endif
