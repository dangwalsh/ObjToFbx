#ifndef OBJFACE_H
#define OBJFACE_H

#include <fbxsdk.h>
#include <string>
#include <vector>
#include "Objscene.h"

class ObjScene;

class ObjFace
{
public:
    ObjFace(ObjScene* pScene, std::vector<std::string>& pTokens);
	virtual ~ObjFace();

protected:
    std::vector<size_t>*    mXYZ;
    std::vector<size_t>*    mNrm;
    std::vector<size_t>*    mUVW;
    ObjScene*               mScene;
};

#endif // OBJFACE_H