#include "ObjMaterial.h"
#include "../Utilities/StringTools.h"

using namespace std;

ObjMaterial::ObjMaterial(ObjScene* pScene, string& pString)
{
	mScene = pScene;
    mName = pString;
	mKa = new FbxDouble3;
	mKd = new FbxDouble3;
	mKs = new FbxDouble3;
	mD = new FbxDouble;
	mNs = new FbxDouble;
	mIllum = new FbxInt;
    mTex_Ka = NULL;
    mTex_Kd = NULL;
    mTex_Ks = NULL;
    mTex_Bump = NULL;
}

ObjMaterial::~ObjMaterial()
{
    delete mNs;
    delete mD;
    delete mKs;
    delete mKd;
    delete mKa;
    delete mIllum;
    delete mTex_Ka;
    delete mTex_Kd;
    delete mTex_Ks;
    delete mTex_Bump;
}



/* Public Members - Mutators */

void ObjMaterial::SetKa(double pValues[3])
{
    FbxDouble3 *lArray = new FbxDouble3(pValues[0], pValues[1], pValues[2]);
    mKa = lArray;
}

void ObjMaterial::SetKd(double pValues[3])
{
    FbxDouble3 *lArray = new FbxDouble3(pValues[0], pValues[1], pValues[2]);
    mKd = lArray;
}

void ObjMaterial::SetKs(double pValues[3])
{
    FbxDouble3 *lArray = new FbxDouble3(pValues[0], pValues[1], pValues[2]);
    mKs = lArray;
}

void ObjMaterial::SetD(double* pValue)
{
    mD = new FbxDouble(*pValue);
}

void ObjMaterial::SetNs(double* pValue)
{
    mNs = new FbxDouble(*pValue);
}

void ObjMaterial::SetIllum(int* pValue)
{
    mIllum = new FbxInt(*pValue);
}

void ObjMaterial::SetTex_Ka(ObjTex* pTexture)
{
    mTex_Ka = pTexture;
}

void ObjMaterial::SetTex_Kd(ObjTex* pTexture)
{
    mTex_Kd = pTexture;
}

void ObjMaterial::SetTex_Ks(ObjTex* pTexture)
{
    mTex_Ks = pTexture;
}

void ObjMaterial::SetTex_Bump(ObjTex* pTexture)
{
    mTex_Bump = pTexture;
}



/* Public Members - Accessors */

const string ObjMaterial::GetName() const
{
    return mName;
}

FbxDouble3& ObjMaterial::GetAmbient()
{
    return *mKa;
}

FbxDouble3& ObjMaterial::GetDiffuse()
{
    return *mKd;
}

FbxDouble3& ObjMaterial::GetSpecular()
{
    return *mKs;
}

FbxDouble& ObjMaterial::GetDissolve()
{
    return *mD;
}

FbxDouble& ObjMaterial::GetHilight()
{
    return *mNs;
}

FbxInt& ObjMaterial::GetIllumModel()
{
    return *mIllum;
}

ObjTex* ObjMaterial::GetAmbientTex()
{
    return mTex_Ka;
}

ObjTex* ObjMaterial::GetDiffuseTex()
{
    return mTex_Kd;
}

ObjTex* ObjMaterial::GetSpecularTex()
{
    return mTex_Ks;
}

ObjTex* ObjMaterial::GetBumpTex()
{
    return mTex_Bump;
}

/* Protected Members */
