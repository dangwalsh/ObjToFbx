#include "ObjFace.h"
#include "../Io/ObjReader.h"
#include "../Utilities/StringTools.h"
#include "../Utilities/GeometryTools.h"

using namespace std;

/* Public Members - Constructors */

ObjFace::ObjFace(ObjScene* pScene, vector<string>& pTokens)
{
    mScene = pScene;
    mVertexIndex = new vector<unsigned int>;
    mNormalIndex = new vector<unsigned int>;
    mTextureIndex = new vector<unsigned int>;
    
    pTokens.erase(pTokens.begin());
	size_t lCount = pTokens.size();
	for (unsigned int i = 0; i < lCount; i++)
	{
		string::size_type sz;
		vector<string> lIndices = Tokenize(pTokens.at(i), '/');
		switch(lIndices.size())
		{
			case 1:
				mVertexIndex->push_back((stoi(lIndices[0], &sz)) - 1);
				break;
			case 2:
				mVertexIndex->push_back((stoi(lIndices[0], &sz)) - 1);
				mTextureIndex->push_back((stoi(lIndices[1], &sz)) - 1);
				break;
			case 3:
				mVertexIndex->push_back((stoi(lIndices[0], &sz)) - 1);
				mNormalIndex->push_back((stoi(lIndices[1], &sz)) - 1);
				mTextureIndex->push_back((stoi(lIndices[2], &sz)) - 1);
				break;
		}
	}
    if (mNormalIndex->size()==0)
    {
        mNormal = new FbxVector4;
        FbxVector4 &v1 = mScene->GetVertex(this->GetXYZ(0));
        FbxVector4 &v2 = mScene->GetVertex(this->GetXYZ(1));
        FbxVector4 &v3 = mScene->GetVertex(this->GetXYZ(2));
        *mNormal = CalculateNormal(v1, v2, v3);
    }
}

ObjFace::~ObjFace()
{
    delete mScene;
    delete mVertexIndex;
    delete mNormalIndex;
    delete mTextureIndex;
    delete mNormal;
}


/* Public Members - Accessors */

size_t ObjFace::Size() const
{
    return mVertexIndex->size();
}

const vector<unsigned int>* ObjFace::GetXYZ()
{
    return mVertexIndex;
}

const vector<unsigned int>* ObjFace::GetNrm()
{
    return mNormalIndex;
}

const vector<unsigned int>* ObjFace::GetUVW()
{
    return mTextureIndex;
}

unsigned int ObjFace::GetXYZ(unsigned int index) const
{
    return mVertexIndex->at(index);
}

unsigned int ObjFace::GetNrm(unsigned int index) const
{
    return mNormalIndex->at(index);
}

unsigned int ObjFace::GetUVW(unsigned int index) const
{
    return mTextureIndex->at(index);
}

const FbxVector4* ObjFace::GetNormal()
{
    return mNormal;
}