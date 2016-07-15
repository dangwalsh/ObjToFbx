#ifndef OBJMATERIAL_H
#define OBJMATERIAL_H

#include <string>
#include "ObjScene.h"

class ObjScene;

class ObjMaterial
{
public:
    ObjMaterial(ObjScene* pScene, std::string* pString);
    virtual ~ObjMaterial();

protected:
    std::string*    mName;
	ObjScene*       mScene;
	
};


#endif // !OBJMATERIAL_H