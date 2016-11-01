#include "ObjScene.h"
#include "ObjTex.h"
#include "../Utilities/StringTools.h"
#include "../Utilities/SdkTools.h"
#include "../Io/MtlReader.h"
#include <iterator>
#include "../Exceptions/SdkException.h"
#include "../Exceptions/VectorException.h"


using namespace std;

/* Public Memebers - Constructors */
ObjScene::ObjScene(const char* pDirectory, std::string& pContent)
{
	mVertices = new vector<FbxVector4>;
	mNormals = new vector<FbxVector4>;
	mTexCoords = new vector<FbxVector2>;
	mGroups = new vector<ObjGroup*>;
	mMtlLib = new vector<ObjMaterial*>;
	mDirectory = pDirectory;

	ParseTokens(pContent);
}


ObjScene::~ObjScene()
{
    delete mMtlLib;
    delete mVertices;
    delete mNormals;
    delete mTexCoords;
    delete mGroups;
    delete mDirectory;
}



/* Public Members - Accessors */
vector<FbxVector4>* ObjScene::GetVertices() const
{
    return mVertices;
}

vector<FbxVector4>* ObjScene::GetNormals() const
{
    return mNormals;
}

vector<FbxVector2>* ObjScene::GetTexCoords() const
{
    return mTexCoords;
}

vector<ObjGroup*>* ObjScene::GetGroups() const
{
    return mGroups;
}

FbxVector4& ObjScene::GetVertex(size_t index) const
{
    return mVertices->at(index);
}

const vector<ObjMaterial*>* ObjScene::GetMtlLib() const
{
    return mMtlLib;
}

ObjMaterial* ObjScene::GetMaterial(string pString) const
{
    for(ObjMaterial* lMaterial : *mMtlLib)
    {
        if(lMaterial->GetName() == pString) return lMaterial;
    }
    return NULL;
}

FbxVector4& ObjScene::GetNormal(size_t pIndex) const
{
	return mNormals->at(pIndex);
}



/* Protected Members */
void ObjScene::ParseTokens(std::string& pContent)
{
	vector<string> lLines = Tokenize(pContent, '\n');
	vector<string>::iterator lItor;
	vector<string>::iterator lBegin = lLines.begin();
	vector<string>::iterator lEnd = lLines.end();

	ObjMaterial* lMaterial = NULL;
	ObjGroup* lGroup = NULL;

	for (lItor = lBegin; lItor < lEnd; ++lItor)
	{
		vector<string> lTokens = Tokenize(*lItor);
		if (!lTokens.empty())
		{
			string lType = lTokens[0];
			if (lType == "mtllib")
			{
				AddMtlLib(lTokens);
			}
			else if (lType == "v")
			{
				AddVertex(lTokens);
			}
			else if (lType == "vn")
			{
				AddNormal(lTokens);
			}
			else if (lType == "vt")
			{
				AddTexCoord(lTokens);
			}
			else if (lType == "usemtl")
			{
				AddMaterial(lTokens, &lMaterial, &lGroup);
			}
			else if (lType == "g")
			{
				AddGroup(lTokens, &lMaterial, &lGroup);
			}
			else if (lType == "f")
			{
				AddFace(lTokens, lGroup);
			}
		}
	}
}

void ObjScene::AddMtlLib(vector<string>& pTokens)
{
    MtlReader lReader(mDirectory);
	const char* lChar = pTokens.at(1).c_str();

    if (lReader.FileOpen(lChar) == false)
    {
        if(lReader.FileOpenRelative(lChar) == false)
        {
            throw new SdkException("ObjToFbx failed to open MTL file at path: ", lChar);
        }
    }

    string* lString = lReader.FileRead();
    CreateMaterials(*lString);
    lReader.FileClose();
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

void ObjScene::AddMaterial(vector<string>& pTokens, ObjMaterial** pMaterial, ObjGroup** pGroup)
{
	*pGroup = NULL;
	*pMaterial = NULL;
	string* lName = AssembleString(pTokens);

	for (auto & lMatPtr : *mMtlLib)
	{
		if (lMatPtr->GetName() == *lName)
		{
			*pMaterial = lMatPtr;
		}
	}
}

void ObjScene::AddGroup(vector<string>& pTokens, ObjMaterial** pMaterial, ObjGroup** pGroup)
{
	if (*pGroup != NULL)
	{
		throw new VectorException("Something went wrong");
	}

	string* lName = AssembleString(pTokens);

	for (auto & lGroupPtr : *mGroups)
	{
		if (*lGroupPtr->GetName() == *lName)
		{
			*pGroup = lGroupPtr;
		}
	}

	if (*pGroup == NULL)
	{
		*pGroup = new ObjGroup(this, lName, *pMaterial);
		mGroups->push_back(*pGroup);
	}
}

void ObjScene::AddFace(vector<string>& pTokens, ObjGroup* pGroup)
{
	ObjFace* lFace = new ObjFace(this, pTokens);
	pGroup->AddFace(lFace);
}

//vector<string>::iterator ObjScene::AddObjGroup(vector<string>& pTokens,
//                                               vector<string>::iterator pItor,
//                                               vector<string>::iterator pEnd)
//{
//	ObjGroup* lGroup = NULL;
//	vector<string>::iterator lGroupLine = pItor + 1;
//	vector<string> lGroupTokens = Tokenize(*lGroupLine);
//	string* lGroupName = new string(lGroupTokens.at(1));
//	string* lMaterialName = new string(pTokens.at(1));
//
//	for (vector<ObjGroup*>::iterator lItor = mGroups->begin(); lItor != mGroups->end(); ++lItor)
//	{
//		ObjGroup* lTemp = *lItor;
//		string lTempName = (*lTemp).GetName();
//		if (lTempName == *lGroupName) 
//		{
//			lGroup = lTemp;
//			break;
//		}
//	}
//
//	if (lGroup == NULL)
//	{
//		lGroup = new ObjGroup(this, lMaterialName);
//		mGroups->push_back(lGroup);
//	}
//
//	for(++pItor; pItor < pEnd; ++pItor)
//	{
//		vector<string> lTokens = Tokenize(*pItor);
//        if (!lTokens.empty()) {
//            string lType = lTokens[0];
//            if (lType == "f") {
//                ObjFace* lFace = new ObjFace(this, lTokens);
//                lGroup->AddFace(lFace);
//            } else if (lType == "g") {
//                string* lString = new string(lTokens.at(1));
//                lGroup->AddName(lString);
//            } else if (lType == "usemtl") {
//                return pItor;
//            }
//        } else {
//            return pItor;
//        }
//	}
//	return pItor;
//}

void ObjScene::CreateMaterials(string &pString)
{
    vector<string> lLines = Tokenize(pString, '\n');
    for (vector<string>::iterator itor = lLines.begin(); itor < lLines.end(); ++itor)
    {
        vector<string> lTokens = Tokenize(*itor);
        if(!lTokens.empty()) {
            string lType = lTokens[0];
            if (lType == "newmtl") {
                ObjMaterial* lMaterial = new ObjMaterial(this, AssembleString(lTokens));
                mMtlLib->push_back(lMaterial);
                for (++itor; itor != lLines.end(); ++itor)
                {
						lTokens = Tokenize(*itor);
						if (!lTokens.empty()) {
							lType = lTokens[0];
							if (lType == "Ka") {
								lMaterial->SetKa(ConvertVector(lTokens));
							}
							else if (lType == "Kd") {
								lMaterial->SetKd(ConvertVector(lTokens));
							}
							else if (lType == "Ks") {
								lMaterial->SetKs(ConvertVector(lTokens));
							}
							else if (lType == "Ns") {
								lMaterial->SetNs(ConvertDouble(lTokens));
							}
							else if (lType == "map_Ka") {
								ObjTex *lTexture = new ObjTex(lTokens);
								lMaterial->SetTex_Ka(lTexture);
							}
							else if (lType == "map_Kd") {
								ObjTex *lTexture2 = new ObjTex(lTokens);
								lMaterial->SetTex_Kd(lTexture2);
							}
							else if (lType == "map_Ks") {
								ObjTex *lTexture3 = new ObjTex(lTokens);
								lMaterial->SetTex_Ks(lTexture3);
							}
							else if (lType == "map_bump") {
								ObjTex *lTexture4 = new ObjTex(lTokens);
								lMaterial->SetTex_Bump(lTexture4);
							}
							else if (lType == "d") {
								lMaterial->SetD(ConvertDouble(lTokens));
							}
							else if (lType == "illum") {
								lMaterial->SetIllum(ConvertInt(lTokens));
							}
							else if (lType == "newmtl") {
								--itor;
								break;
							}
					}   
                }
				if (itor == lLines.end()) break;
            }
        }
    }
}

int* ObjScene::ConvertInt(vector<string> &pTokens)
{
    string::size_type sz;
    int* lValue = new int;
    *lValue = stoi(pTokens.at(1), &sz);
    return lValue;
}

double* ObjScene::ConvertDouble(vector<string> &pTokens)
{
    string::size_type sz;
    double* lValue = new double;
    *lValue = stod(pTokens.at(1), &sz);
    return lValue;
}

double* ObjScene::ConvertVector(vector<string> &pTokens)
{
    string::size_type sz;
    double* lValues = new double[3];
    lValues[0] = stod(pTokens.at(1), &sz);
    lValues[1] = stod(pTokens.at(2), &sz);
    lValues[2] = stod(pTokens.at(3), &sz);
    return lValues;
}

string* ObjScene::AssembleString(vector<string>& pTokens)
{
	vector<string>::iterator lItor = pTokens.begin() + 1;
	string* lString = new string(*lItor++);

	while (lItor != pTokens.end())
	{
		*lString += " " + *lItor++;
	}

	return lString;
}
