#include "ObjMaterial.h"

using namespace std;

ObjMaterial::ObjMaterial(ObjScene* pScene, const char* pString)
{
	mScene = pScene;
    mName = pString;
}

ObjMaterial::~ObjMaterial()
{

}


/* Public Members - Accessors */

const char* ObjMaterial::GetName() const
{
    return mName;
}