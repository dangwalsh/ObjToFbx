#include "ObjGroup.h"
#include "../Utilities/StringTools.h"

using namespace std;

ObjGroup::ObjGroup(ObjScene* pScene)
{
    mScene = pScene;
}

ObjGroup::~ObjGroup()
{
    delete mName;
    delete mMaterial;
    delete mFaces;
    delete mScene;
}

void ObjGroup::AddFace(ObjFace& pFace)
{
    mFaces->push_back(pFace);
}

void ObjGroup::AddName(string& pString)
{
    mName = &pString;
}

void ObjGroup::AddMaterial(ObjMaterial &pMaterial)
{
    mMaterial = &pMaterial;
}