#ifndef STRINGHELP_H
#define STRINGHELP_H

#include <vector>
#include <string>

using namespace std;

const vector<string> Tokenize(string& pInput);
const vector<string> Tokenize(string& pInput, char pChar);

#endif // STRINGHELP_H