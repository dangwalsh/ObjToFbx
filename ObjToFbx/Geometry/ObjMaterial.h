#ifndef OBJMATERIAL_H
#define OBJMATERIAL_H

#include "ObjScene.h"

class ObjScene;

class ObjMaterial
{
public:
    ObjMaterial(ObjScene* pScene, std::string& pString);
    virtual ~ObjMaterial();
    
    virtual const char* GetName() const;


protected:
    const char*     mName;
	ObjScene*       mScene;
    
};


#endif // !OBJMATERIAL_H