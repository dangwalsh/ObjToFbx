#include "ObjMaterial.h"

using namespace std;

ObjMaterial::ObjMaterial(ObjScene* pScene, string* pString)
{
	mScene = pScene;
    mName = pString;
}

ObjMaterial::~ObjMaterial()
{

}