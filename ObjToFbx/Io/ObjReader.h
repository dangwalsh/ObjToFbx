#ifndef OBJREADER_H
#define OBJREADER_H

#include <fbxsdk.h>
#include <vector>
#include "../Geometry/ObjScene.h"
#include "../Geometry/ObjGroup.h"
#include "../Geometry/ObjMaterial.h"
#include "../Geometry/ObjTex.h"

class ObjScene;
class ObjGroup;
class ObjMaterial;
class ObjTexture;

class ObjReader : public FbxReader
{
public:
	ObjReader(FbxManager &pManager, int pID);
	virtual ~ObjReader();

	virtual void GetVersion(int& pMajor, int& pMinor, int& pRevision);
	virtual bool FileOpen(char* pFileName);
	virtual bool FileClose();
	virtual bool IsFileOpen();

	virtual bool GetReadOptions(bool pParseFileAsNeeded = true);
	virtual bool Read(FbxDocument* pDocument);
    virtual void CreateFbxScene(FbxScene* pScene, ObjScene* pObjScene);
    virtual FbxNode* CreateMesh(FbxScene* pScene, ObjScene* pObjScene, ObjGroup* pGroup);
    virtual void ApplyMaterial(FbxScene* pScene, FbxNode* pNode, ObjGroup* pGroup);
    virtual FbxSurfaceMaterial* CreateMaterial(FbxScene* pScene, ObjMaterial* pMaterial);
    virtual FbxFileTexture* CreateTexture(FbxScene* pScene, FbxSurfacePhong* pFbxMaterial, ObjTex* pObjMaterial);

private:
	FILE*		mFilePointer;
	FbxManager*	mManager;
	char*		mDirectory;
    std::vector<FbxSurfaceMaterial*> mMaterials;
};



#endif // OBJREADER_H
