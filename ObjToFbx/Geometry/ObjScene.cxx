#include "ObjScene.h"
#include <iterator>
#include "../Utilities/StringTools.h"

using namespace std;

ObjScene::ObjScene()
{
    
}

ObjScene::ObjScene(string& pString)
{
	vector<string> lLines = Tokenize(pString, '\n');
	vector<string>::iterator lItor;
	vector<string>::iterator lBegin;
	vector<string>::iterator lEnd;
	for (lItor = lBegin; lItor < lEnd; ++lItor)
	{
		vector<string> lTokens = Tokenize(*lItor);
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
			lItor = AddObjGroup(lItor, lEnd);
		} else {
			FBXSDK_printf("Error: Unrecognized node type\n");
			exit(1);
		}
	}
}

ObjScene::~ObjScene()
{
    delete mMatLib;
    delete mVertices;
    delete mNormals;
    delete mTexCoord;
    delete mElements;
}

void ObjScene::AddMtlLib(vector< string >& pTokens)
{
	mMatLib = &pTokens.at(1);
}

void ObjScene::AddVertex(vector< string >& pTokens)
{
    string::size_type sz;
	double v1 = stod(pTokens.at(1), &sz);
	double v2 = stod(pTokens.at(2), &sz);
	double v3 = stod(pTokens.at(3), &sz);
	FbxVector4 vertex(v1, v2, v3);
	mVertices->push_back(vertex);
}

void ObjScene::AddNormal(vector< string >& pTokens)
{
    string::size_type sz;
	double v1 = stod(pTokens.at(1), &sz);
	double v2 = stod(pTokens.at(2), &sz);
	double v3 = stod(pTokens.at(3), &sz);
	FbxVector4 vertex(v1, v2, v3);
	mNormals->push_back(vertex);
}

void ObjScene::AddTexCoord(vector< string >& pTokens)
{
    string::size_type sz;
	double v1 = stod(pTokens.at(1), &sz);
	double v2 = stod(pTokens.at(2), &sz);
	double v3 = stod(pTokens.at(3), &sz);
	FbxVector4 vertex(v1, v2, v3);
	mTexCoord->push_back(vertex);
}

vector<string>::iterator ObjScene::AddObjGroup(vector<string>::iterator pItor, vector<string>::iterator pEnd)
{
	ObjGroup* lGroup = new ObjGroup(*pItor, this);
	++pItor;
	for(; pItor < pEnd; ++pItor)
	{
		vector<string> lTokens = Tokenize(*pItor);
		string lType = lTokens[0];
		if (lType == "f")
		{
            ObjFace lFace(lTokens);
            lGroup->AddFace(lFace);
		} else if (lType == "g") {
			// TODO: add a group to the element
		} else if (lType == "usemtl") {
			return pItor;
		}
	}
	return pItor;
}
