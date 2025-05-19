#ifndef TYPES_HPP
#define TYPES_HPP
#include <set>
#include <string>

const std::set<std::string> dataTypes = {"int", "float", "string", "bool"};
bool isDataType(std::string bufString) {
  if (dataTypes.find(bufString) != dataTypes.end()) {
    return true;
  }
  return false;
}

const std::set<std::string> keywords = {"print", "return"};
bool isKeyword(std::string bufString) {
 if (keywords.find(bufString) != keywords.end()) {
   return true;
 } 
  return false;
}

#endif
