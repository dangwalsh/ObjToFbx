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
    ObjGroup(ObjScene* pScene, const char* pString);
    virtual ~ObjGroup();

    virtual void AddName(std::string* pString);
    virtual void AddFace(ObjFace* pFace);
    virtual void AddMaterial(ObjMaterial* pMaterial);
    
    virtual const std::string *GetName();
    virtual std::vector<ObjFace*>* GetFaces();
    virtual const ObjFace* GetFaces(size_t index);
    virtual const ObjMaterial* GetMaterial();

protected:
    std::string*            mName;
    std::vector<ObjFace*>*  mFaces;
	ObjMaterial*            mMaterial;
    ObjScene*               mScene;

};


#endif // OBJGROUP_H