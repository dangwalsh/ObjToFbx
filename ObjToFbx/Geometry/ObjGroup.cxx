#include "ObjGroup.h"
#include "../Utilities/StringTools.h"

using namespace std;


/* Public Members - Constructors */

ObjGroup::ObjGroup(ObjScene* pScene)
{
    mScene = pScene;
    mFaces = new vector<ObjFace*>;
}

ObjGroup::ObjGroup(ObjScene* pScene, string& pString)
{
    mScene = pScene;
    mFaces = new vector<ObjFace*>;
    mMaterial = pScene->GetMaterial(pString);
}

ObjGroup::~ObjGroup()
{
    delete mFaces;
    delete mMaterial;
}



/* Public Members - Mutators */

void ObjGroup::AddFace(ObjFace* pFace)
{
    mFaces->push_back(pFace);
}

void ObjGroup::AddName(string* pString)
{
    mName = pString;
}

void ObjGroup::AddMaterial(ObjMaterial* pMaterial)
{
    mMaterial = pMaterial;
}


/* Public Members - Accessors */

const std::string* ObjGroup::GetName()
{
    return mName;
}

vector<ObjFace*>* ObjGroup::GetFaces()
{
    return mFaces;
}

const ObjFace* ObjGroup::GetFaces(size_t index)
{
    return mFaces->at(index);
}

ObjMaterial* ObjGroup::GetMaterial()
{
    return mMaterial;
}
