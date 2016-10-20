#ifndef OBJSCENE_H
#define OBJSCENE_H

#include <fbxsdk.h>
#include <string>
#include "ObjGroup.h"
#include "ObjMaterial.h"

class ObjGroup;
class ObjMaterial;

class ObjScene
{
public:
	ObjScene(std::string& pString);
    ObjScene(const char* pDirectory, std::string& pContent);
	virtual ~ObjScene();
    
    virtual std::vector<FbxVector4>* GetVertices() const;
    virtual std::vector<FbxVector4>* GetNormals() const;
    virtual std::vector<FbxVector2>* GetTexCoords() const;
    virtual std::vector<ObjGroup*>* GetGroups() const;
    virtual FbxVector4& GetVertex(size_t pIndex) const;
    virtual const std::vector<ObjMaterial*>* GetMtlLib() const;
    virtual const ObjMaterial* GetMaterial(size_t pIndex) const;
	virtual ObjMaterial* GetMaterial(std::string) const;
	virtual FbxVector4& GetNormal(size_t pIndex) const;

protected:
    std::vector<ObjMaterial*>*  mMtlLib;
	std::vector<FbxVector4>*    mVertices;
	std::vector<FbxVector4>*    mNormals;
	std::vector<FbxVector2>*    mTexCoords;
    std::vector<ObjGroup*>*     mGroups;
    const char*                 mDirectory;

	virtual void AddMtlLib(std::vector<std::string>& pTokens);
	virtual void AddVertex(std::vector<std::string>& pTokens);
	virtual void AddNormal(std::vector<std::string>& pTokens);
	virtual void AddTexCoord(std::vector<std::string>& pTokens);
    virtual std::vector<std::string>::iterator AddObjGroup(std::vector<std::string>& pTokens,
                                                           std::vector<std::string>::iterator pItor,
                                                           std::vector<std::string>::iterator pEnd);
    virtual void CreateMaterials(std::string &pString);
    virtual int* ConvertInt(std::vector<std::string> &pTokens);
    virtual double* ConvertDouble(std::vector<std::string> &pTokens);
    virtual double* ConvertVector(std::vector<std::string> &pTokens);

};

#endif // OBJSCENE_H
