#include "ObjMaterial.h"

using namespace std;

ObjMaterial::ObjMaterial()
{
    
}

ObjMaterial::ObjMaterial(string& pString, ObjScene* pScene)
{
	mName = &pString;
	mScene = pScene;
}

ObjMaterial::~ObjMaterial()
{
    delete mName;
    delete mScene;
}