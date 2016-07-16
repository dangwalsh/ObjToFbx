#ifndef OBJGROUP_H
#define OBJGROUP_H

#include <string>
#include <vector>
#include "ObjFace.h"
#include "ObjScene.h"
#include "ObjMaterial.h"


class ObjFace;
class ObjScene;
class ObjMaterial;


class ObjGroup
{
public:
    ObjGroup(ObjScene* pScene);
    ObjGroup(ObjScene* pScene, std::string* pString);
    virtual ~ObjGroup();
    
    virtual void AddName(std::string* pString);
    virtual void AddFace(ObjFace* pFace);
    virtual void AddMaterial(ObjMaterial* pMaterial);

protected:
    std::string*            mName;
    std::vector<ObjFace*>*  mFaces;
	ObjMaterial*            mMaterial;
    ObjScene*               mScene;

};


#endif // OBJGROUP_H