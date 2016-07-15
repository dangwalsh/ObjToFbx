#include <sstream>
#include <algorithm>
#include <iterator>
#include "StringTools.h"

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