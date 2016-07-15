#ifndef OBJMATERIAL_H
#define OBJMATERIAL_H

#include <string>
#include "ObjScene.h"

class ObjScene;

class ObjMaterial
{
public:
    ObjMaterial();
    ObjMaterial(std::string& pString, ObjScene* pScene);
    virtual ~ObjMaterial();

protected:
    std::string*    mName;
	ObjScene*       mScene;
	
};


#endif // !OBJMATERIAL_H