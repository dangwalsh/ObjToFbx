#include <sstream>
#include <algorithm>
#include <iterator>
#include "StringTools.h"

using namespace std;

const vector<string> Tokenize(string& pInput)
{
	istringstream lStream(pInput);
	vector<string> lTokens;
	copy(istream_iterator<string>(lStream),istream_iterator<string>(),back_inserter(lTokens));
	return lTokens;
}

const vector<string> Tokenize(string& pInput, char pChar)
{
	istringstream lStream(pInput);
	string lToken;
	vector<string> lTokens;
	while(getline(lStream, lToken, pChar))
	{
		lTokens.push_back(lToken);
	}
	return lTokens;
}

const char* StringConcat(const char* pOne, const char* pTwo)
{
    size_t lLengthOne = strlen(pOne);
    size_t lLengthTwo = strlen(pTwo);
    
    char* lCombined = new char[lLengthOne + lLengthTwo + 1]();
    if (!lCombined) abort();

    memcpy(lCombined, pOne, lLengthOne);
    memcpy(lCombined + lLengthOne, pTwo, lLengthTwo);
    lCombined[lLengthOne + lLengthTwo] = '\0';
    return lCombined;
}
