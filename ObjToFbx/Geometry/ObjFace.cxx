#include "ObjFace.h"
#include "../Io/ObjReader.h"
#include "../Utilities/StringTools.h"


/* Public Members - Constructors */

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


/* Test Function - TODO: Delete */

string ObjFace::GetString()
{
    return "Hello Test!\n";
}


/* Public Members - Accessors */

size_t ObjFace::Size() const
{
    return mXYZ->size();
}

const vector<size_t>* ObjFace::GetXYZ()
{
    return mXYZ;
}

const vector<size_t>* ObjFace::GetNrm()
{
    return mNrm;
}

const vector<size_t>* ObjFace::GetUVW()
{
    return mUVW;
}

size_t ObjFace::GetXYZ(size_t index) const
{
    return mXYZ->at(index);
}

size_t ObjFace::GetNrm(size_t index) const
{
    return mNrm->at(index);
}

size_t ObjFace::GetUVW(size_t index) const
{
    return mUVW->at(index);
}