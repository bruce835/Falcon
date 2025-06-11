#ifndef ABSTRACTIONS_HPP
#define ABSTRACTIONS_HPP
#include <string>
#include <vector>
#include <optional>

// Functions
struct parameter {
  std::string type;
  std::string value;
};

struct instruction {
  std::vector<parameter> parameters;
  std::string keyword;
};

struct func {
  std::vector<instruction> instructions;
  std::vector<parameter> parameters; 
  std::string returnType;
  std::vector<std::string> returnValues;
  std::string identifier;
  int paramCount;
};

// Variables
struct variable {
  std::string type;
  std::string value;
};
#endif
