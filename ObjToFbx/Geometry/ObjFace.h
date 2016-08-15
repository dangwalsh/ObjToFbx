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
    
    virtual size_t Size() const;
    virtual const std::vector<unsigned int>* GetXYZ();
    virtual const std::vector<unsigned int>* GetNrm();
    virtual const std::vector<unsigned int>* GetUVW();
    virtual unsigned int GetXYZ(unsigned int index) const;
    virtual unsigned int GetNrm(unsigned int index) const;
    virtual unsigned int GetUVW(unsigned int index) const;
    virtual const FbxVector4* GetNormal();

protected:
    std::vector<unsigned int>*  mVertexIndex;
    std::vector<unsigned int>*  mNormalIndex;
    std::vector<unsigned int>*  mTextureIndex;
    FbxVector4*                 mNormal;
    ObjScene*                   mScene;
};

#endif // OBJFACE_H