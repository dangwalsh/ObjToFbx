#include "ObjScene.h"
#include <iterator>
#include "../Utilities/StringTools.h"

using namespace std;

/* Public Memebers - Constructors */
ObjScene::ObjScene(string& pString)
{
    mVertices = new vector<FbxVector4>;
    mNormals = new vector<FbxVector4>;
    mTexCoords = new vector<FbxVector2>;
    mGroups = new vector<ObjGroup*>;
	vector<string> lLines = Tokenize(pString, '\n');
	vector<string>::iterator lItor;
	vector<string>::iterator lBegin = lLines.begin();
	vector<string>::iterator lEnd = lLines.end();
	for (lItor = lBegin; lItor < lEnd; ++lItor)
	{
		vector<string> lTokens = Tokenize(*lItor);
        if (!lTokens.empty()) {
            string lType = lTokens[0];
            if (lType == "mtllib") {
                AddMtlLib(lTokens);
            } else if (lType == "v") {
                AddVertex(lTokens);
            } else if (lType == "vn") {
                AddNormal(lTokens);
            } else if (lType == "vt") {
                AddTexCoord(lTokens);
            } else if (lType == "usemtl") {
                lItor = AddObjGroup(lTokens, lItor, lEnd);
            }
        }
	}
}

ObjScene::~ObjScene()
{
    delete mMtlLib;
    delete mVertices;
    delete mNormals;
    delete mTexCoords;
    delete mGroups;
}



/* Public Members - Accessors */
std::vector<FbxVector4>* ObjScene::GetVertices() const
{
    return mVertices;
}

std::vector<FbxVector4>* ObjScene::GetNormals() const
{
    return mNormals;
}

std::vector<FbxVector2>* ObjScene::GetTexCoords() const
{
    return mTexCoords;
}

std::vector<ObjGroup*>* ObjScene::GetGroups() const
{
    return mGroups;
}

FbxVector4& ObjScene::GetVertex(size_t index) const
{
    return mVertices->at(index);
}


/* Protected Members */
void ObjScene::AddMtlLib(vector<string>& pTokens)
{
	mMtlLib = new string(pTokens.at(1));
}

void ObjScene::AddVertex(vector<string>& pTokens)
{
    string::size_type sz;
	double v1 = stod(pTokens.at(1), &sz);
	double v2 = stod(pTokens.at(2), &sz);
	double v3 = stod(pTokens.at(3), &sz);
	FbxVector4 vertex(v1, v2, v3);
	mVertices->push_back(vertex);
}

void ObjScene::AddNormal(vector<string>& pTokens)
{
    string::size_type sz;
	double v1 = stod(pTokens.at(1), &sz);
	double v2 = stod(pTokens.at(2), &sz);
	double v3 = stod(pTokens.at(3), &sz);
	FbxVector4 vertex(v1, v2, v3);
	mNormals->push_back(vertex);
}

void ObjScene::AddTexCoord(vector<string>& pTokens)
{
    string::size_type sz;
	double v1 = stod(pTokens.at(1), &sz);
	double v2 = stod(pTokens.at(2), &sz);
//	double v3 = stod(pTokens.at(3), &sz);
	FbxVector2 vertex(v1, v2);
	mTexCoords->push_back(vertex);
}

vector<string>::iterator ObjScene::AddObjGroup(vector<string>& pTokens,
                                               vector<string>::iterator pItor,
                                               vector<string>::iterator pEnd)
{
	ObjGroup* lGroup = new ObjGroup(this, pTokens.at(1).c_str());
    mGroups->push_back(lGroup);
	for(++pItor; pItor < pEnd; ++pItor)
	{
		vector<string> lTokens = Tokenize(*pItor);
        if (!lTokens.empty()) {
            string lType = lTokens[0];
            if (lType == "f") {
                ObjFace* lFace = new ObjFace(this, lTokens);
                lGroup->AddFace(lFace);
            } else if (lType == "g") {
                string* lString = new string(lTokens.at(1));
                lGroup->AddName(lString);
            } else if (lType == "usemtl") {
                return pItor;
            }
        } else {
            return pItor;
        }
	}
	return pItor;
}
