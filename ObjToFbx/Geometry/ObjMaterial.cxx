#include "ObjMaterial.h"
#include "../Utilities/StringTools.h"

using namespace std;

ObjMaterial::ObjMaterial(ObjScene* pScene, string& pString)
{
	mScene = pScene;
    mName = pString;
}

ObjMaterial::~ObjMaterial()
{
    delete mNs;
    delete mD;
    delete mKs;
    delete mKd;
    delete mKa;
    delete mIllum;
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
    mD = pValue;
}

void ObjMaterial::SetNs(double* pValue)
{
    mNs = pValue;
}

void ObjMaterial::SetIllum(int* pValue)
{
    mIllum = pValue;
}

void ObjMaterial::SetMap_Bump(string &pString)
{
    mMap_Bump = pString;
}

void ObjMaterial::SetMap_Ka(string &pString)
{
    mMap_Ka = pString;
}

void ObjMaterial::SetMap_Kd(string &pString)
{
    mMap_Kd = pString;
}

void ObjMaterial::SetMap_Ks(string &pString)
{
    mMap_Ks = pString;
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

/* Protected Members */
