#ifndef OBJSCENE_H
#define OBJSCENE_H

#include <fbxsdk.h>
#include "ObjGroup.h"

class ObjGroup;

class ObjScene
{
public:
	ObjScene(std::string& pString);
	virtual ~ObjScene();
    
    virtual std::vector<FbxVector4>* GetVertices() const;
    virtual std::vector<FbxVector4>* GetNormals() const;
    virtual std::vector<FbxVector2>* GetTexCoords() const;
    virtual std::vector<ObjGroup*>* GetGroups() const;
    virtual FbxVector4& GetVertex(size_t index) const;
    virtual const std::string* GetMtlLib() const;

protected:
    std::string*                mMtlLib;
	std::vector<FbxVector4>*    mVertices;
	std::vector<FbxVector4>*    mNormals;
	std::vector<FbxVector2>*    mTexCoords;
    std::vector<ObjGroup*>*     mGroups;

	virtual void AddMtlLib(std::vector<std::string>& pTokens);
	virtual void AddVertex(std::vector<std::string>& pTokens);
	virtual void AddNormal(std::vector<std::string>& pTokens);
	virtual void AddTexCoord(std::vector<std::string>& pTokens);
    virtual std::vector<std::string>::iterator AddObjGroup(std::vector<std::string>& pTokens,
                                                           std::vector<std::string>::iterator pItor,
                                                           std::vector<std::string>::iterator pEnd);

};

#endif // OBJSCENE_H