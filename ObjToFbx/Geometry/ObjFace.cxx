#include "ObjFace.h"
#include "../Io/ObjReader.h"
#include "../Utilities/StringTools.h"

ObjFace::ObjFace(ObjScene* pScene, vector<string>& pTokens)
{
    mScene = pScene;
    mXYZ = new vector<size_t>;
    mNrm = new vector<size_t>;
    mUVW = new vector<size_t>;
    pTokens.erase(pTokens.begin());
	size_t lCount = pTokens.size();
	for (size_t i = 0; i < lCount; i++)
	{
		string::size_type sz;
		vector<string> lIndices = Tokenize(pTokens.at(i), '/');
		switch(lIndices.size())
		{
			case 1:
				mXYZ->push_back(stoi(lIndices[0], &sz));
				break;
			case 2:
				mXYZ->push_back(stoi(lIndices[0], &sz));
				mUVW->push_back(stoi(lIndices[1], &sz));
				break;
			case 3:
				mXYZ->push_back(stoi(lIndices[0], &sz));
				mNrm->push_back(stoi(lIndices[1], &sz));
				mUVW->push_back(stoi(lIndices[2], &sz));
				break;
		}
	}
}

ObjFace::~ObjFace()
{
    delete mScene;
    delete mXYZ;
    delete mNrm;
    delete mUVW;
}

string ObjFace::GetString()
{
    return "Hello Test!\n";
}