#ifndef STRINGHELP_H
#define STRINGHELP_H

#include <vector>
#include <string>


const std::vector<std::string> Tokenize(std::string& pInput);
const std::vector<std::string> Tokenize(std::string& pInput, char pChar);
const char* StringConcat(const char* pOne, const char* pTwo);

#endif // STRINGHELP_H
