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

}


/* Public Members - Accessors */

const char* ObjMaterial::GetName() const
{
    return mName;
}


/* Protected Members */









