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
    
//    static std::string GetString();
    
    virtual size_t Size() const;
    virtual const std::vector<size_t>* GetXYZ();
    virtual const std::vector<size_t>* GetNrm();
    virtual const std::vector<size_t>* GetUVW();
    virtual size_t GetXYZ(size_t index) const;
    virtual size_t GetNrm(size_t index) const;
    virtual size_t GetUVW(size_t index) const;

protected:
    std::vector<size_t>*    mXYZ;
    std::vector<size_t>*    mNrm;
    std::vector<size_t>*    mUVW;
    ObjScene*               mScene;
};

#endif // OBJFACE_H