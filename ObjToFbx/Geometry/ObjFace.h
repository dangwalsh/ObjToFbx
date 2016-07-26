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
    virtual const std::vector<size_t>* GetXYZ();
    virtual const std::vector<size_t>* GetNrm();
    virtual const std::vector<size_t>* GetUVW();
    virtual size_t GetXYZ(size_t index) const;
    virtual size_t GetNrm(size_t index) const;
    virtual size_t GetUVW(size_t index) const;
    virtual const FbxVector4* GetNormal();

protected:
    std::vector<size_t>*    mVertexIndex;
    std::vector<size_t>*    mNormalIndex;
    std::vector<size_t>*    mTextureIndex;
    FbxVector4*             mNormal;
    ObjScene*               mScene;
};

#endif // OBJFACE_H