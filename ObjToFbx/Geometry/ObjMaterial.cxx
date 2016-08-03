#include "ObjMaterial.h"
#include "../Utilities/StringTools.h"

using namespace std;

ObjMaterial::ObjMaterial(ObjScene* pScene, string& pString)
{
	mScene = pScene;
    mName = pString.c_str();
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
    mKa = pValues;
}

void ObjMaterial::SetKd(double pValues[3])
{
    mKd = pValues;
}

void ObjMaterial::SetKs(double pValues[3])
{
    mKs = pValues;
}

void ObjMaterial::SetD(double* pValue)
{
    mD = pValue;
}

void ObjMaterial::SetNs(double* pValue)
{
    mNs = pValue;
}

void ObjMaterial::SetIllum(double* pValue)
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

const char* ObjMaterial::GetName() const
{
    return mName;
}



/* Protected Members */









