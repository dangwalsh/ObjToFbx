#ifndef STRINGHELP_H
#define STRINGHELP_H

#include <vector>
#include <string>


const std::vector<std::string> Tokenize(std::string& pInput);
const std::vector<std::string> Tokenize(std::string& pInput, char pChar);

#endif // STRINGHELP_H