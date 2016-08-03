#include "ObjScene.h"
#include <iterator>
#include "../Utilities/StringTools.h"
#include "../Io/MtlReader.h"

using namespace std;

/* Public Memebers - Constructors */
ObjScene::ObjScene(string& pString)
{
    mVertices = new vector<FbxVector4>;
    mNormals = new vector<FbxVector4>;
    mTexCoords = new vector<FbxVector2>;
    mGroups = new vector<ObjGroup*>;
    mMtlLib = new vector<ObjMaterial*>;
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
#ifdef WIN32
				if (lItor == lEnd) break;
#endif
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

const vector<ObjMaterial*>* ObjScene::GetMtlLib() const
{
    return mMtlLib;
}


/* Protected Members */
void ObjScene::AddMtlLib(vector<string>& pTokens)
{
    MtlReader lReader;
    lReader.FileOpen(pTokens.at(1).c_str());
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

vector<string>::iterator ObjScene::AddObjGroup(vector<string>& pTokens,
                                               vector<string>::iterator pItor,
                                               vector<string>::iterator pEnd)
{
	ObjGroup* lGroup = new ObjGroup(this, pTokens.at(1));
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

const ObjMaterial* ObjScene::GetMaterial(size_t pIndex) const
{
    return NULL;
}

void ObjScene::CreateMaterials(string &pString)
{
    vector<string> lLines = Tokenize(pString, '\n');
    for (vector<string>::iterator itor = lLines.begin(); itor < lLines.end(); ++itor)
    {
        vector<string> lTokens = Tokenize(*itor);
        if(!lTokens.empty()) {
            string lType = lTokens[0];
            if (lType == "newmtl") {
                ObjMaterial* lMaterial = new ObjMaterial(this, lTokens.at(1));
                mMtlLib->push_back(lMaterial);
                for (++itor; itor != lLines.end(); ++itor)
                {
                    lTokens = Tokenize(*itor);
                    if (!lTokens.empty()) {
                        lType = lTokens[0];
                        if (lType == "Ka") {
                            lMaterial->SetKa(ConvertVector(lTokens));
                        } else if (lType == "Kd") {
                            lMaterial->SetKd(ConvertVector(lTokens));
                        } else if (lType == "Ks") {
                            lMaterial->SetKs(ConvertVector(lTokens));
                        } else if (lType == "Ns") {
                            lMaterial->SetNs(ConvertValue(lTokens));
                        } else if (lType == "map_Ka") {
                            lMaterial->SetMap_Ka(lTokens.at(1));
                        } else if (lType == "map_Kd") {
                            lMaterial->SetMap_Kd(lTokens.at(1));
                        } else if (lType == "map_Ks") {
                            lMaterial->SetMap_Ks(lTokens.at(1));
                        } else if (lType == "map_bump") {
                            lMaterial->SetMap_Bump(lTokens.at(1));
                        } else if (lType == "d") {
                            lMaterial->SetD(ConvertValue(lTokens));
                        } else if (lType == "illum") {
                            lMaterial->SetIllum(ConvertValue(lTokens));
                        } else if (lType == "newmtl") {
                            --itor;
                            break;
                        }
                    }
                }
            }
        }
    }
}

double* ObjScene::ConvertValue(vector<string> &pTokens)
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
