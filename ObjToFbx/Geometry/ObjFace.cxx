#include "ObjFace.h"
#include "../Io/ObjReader.h"
#include "../Utilities/StringTools.h"

ObjFace::ObjFace()
{
    
}

ObjFace::ObjFace(vector<string>& pTokens)
{
	size_t lCount = pTokens.size();
    mXYZ = new size_t[lCount];
    mNrm = new size_t[lCount];
    mUVW = new size_t[lCount];
	for (size_t i = 1; i < lCount; i++)
	{
		string::size_type sz;
		vector<string> lIndices = Tokenize(pTokens.at(i), '/');
		switch(lIndices.size())
		{
			case 1:
				mXYZ[i] = stoi(lIndices[0], &sz);
				break;
			case 2:
				mXYZ[i] = stoi(lIndices[0], &sz);
				mUVW[i] = stoi(lIndices[1], &sz);
				break;
			case 3:
				mXYZ[i] = stoi(lIndices[0], &sz);
				mNrm[i] = stoi(lIndices[1], &sz);
				mUVW[i] = stoi(lIndices[2], &sz);
				break;
		}
	}
}

ObjFace::~ObjFace()
{
    delete [] mXYZ;
    delete [] mNrm;
    delete [] mUVW;
}