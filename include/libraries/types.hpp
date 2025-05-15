#ifndef TYPES_HPP
#define TYPES_HPP
#include <set>
#include <string>

const std::set<std::string> dataTypes = {"int", "float", "string", "bool"};

bool isDataType(std::string data) {
  if (dataTypes.find(data) != dataTypes.end()) {
    return true;
  }
  return false;
}

#endif
