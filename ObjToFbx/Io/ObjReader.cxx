#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include "ObjReader.h"
#include "../Geometry/ObjScene.h"

using namespace std;

ObjReader::ObjReader(FbxManager &pManager, int pID):
FbxReader(pManager, pID, FbxStatusGlobal::GetRef()),
mFilePointer(NULL),
mManager(&pManager)
{
}

ObjReader::~ObjReader() 
{
	FileClose();
}

void ObjReader::GetVersion(int& pMajor, int& pMinor, int& pRevision) 
{
	pMajor = 1;
	pMinor = 0;
	pRevision = 0;
}

bool ObjReader::FileOpen(char* pFileName) 
{
	if (mFilePointer != NULL)
		FileClose();
	FBXSDK_fopen(mFilePointer, pFileName, "r");
	if (mFilePointer == NULL)
		return false;
	return true;
}

bool ObjReader::FileClose() 
{
	if (mFilePointer != NULL)
		fclose(mFilePointer);
	return true;
}

bool ObjReader::IsFileOpen() 
{
	if (mFilePointer != NULL)
		return true;
	return false;
}

bool ObjReader::GetReadOptions(bool /*pParseFileAsNeeded*/) 
{
	return true;
}

bool ObjReader::Read(FbxDocument* pDocument) 
{
	if (!pDocument)
	{
		GetStatus().SetCode(FbxStatus::eFailure, "Invalid document handle");
		return false;
	}
	FbxScene*       lScene = FbxCast<FbxScene>(pDocument);
	bool            lIsAScene = (lScene != NULL);
	bool            lResult = false;
    ObjScene*       lObjScene = NULL;
    
	if(lIsAScene)
	{
//		FbxNode* lRootNode = lScene->GetRootNode();
//		FbxNodeAttribute * lRootNodeAttribute = FbxNull::Create(lScene,"");
//		lRootNode->SetNodeAttribute(lRootNodeAttribute);

		long lSize;
		char* lBuffer = NULL;    
		if(mFilePointer != NULL)
		{
			fseek (mFilePointer , 0 , SEEK_END);
			lSize = ftell (mFilePointer);
			rewind (mFilePointer);

			lBuffer = (char*) malloc (sizeof(char)*lSize + 1);
			size_t lRead = fread(lBuffer, 1, lSize, mFilePointer);
			lBuffer[lRead]='\0';
			string lString(lBuffer);

			lObjScene = new ObjScene(lString);
            
			free(lBuffer);
		}
        
        CreateFbxScene(lScene, lObjScene);
        
		lResult = true;
	}
	return lResult;
}

void ObjReader::CreateFbxScene(FbxScene* pScene, ObjScene* pObjScene)
{
    FbxNode* lRootNode = pScene->GetRootNode();
    FbxNodeAttribute * lRootNodeAttribute = FbxNull::Create(pScene,"");
    lRootNode->SetNodeAttribute(lRootNodeAttribute);
    vector<ObjGroup*>::iterator itor;
    vector<ObjGroup*>* lGroups = pObjScene->GetGroups();
    for(itor = lGroups->begin(); itor < lGroups->end(); ++itor) {
        CreateMesh(pScene, pObjScene, *itor++);
    }
    
}

void ObjReader::CreateMesh(FbxScene* pScene, ObjScene* pObjScene, ObjGroup* pGroup)
{
    const char* lName = pGroup->GetName()->c_str();
    FbxMesh* lMesh = FbxMesh::Create(pScene, lName);
    
    size_t lNbFaces = pGroup->GetFaces()->size();
    size_t lNbPoints = pGroup->GetFaces(0)->Size();
    lMesh->InitControlPoints(lNbPoints * lNbFaces);
    
    FbxVector4* lControlPoints = lMesh->GetControlPoints();
    const vector<FbxVector4>* lVertices = pObjScene->GetVertices();
    
    for (size_t i = 0; i < lNbFaces; ++i) {
        const ObjFace* lFace = pGroup->GetFaces(i);
        for (size_t j = 0; j < lNbPoints; ++j) {
            *lControlPoints = lVertices->at(lFace->GetXYZ(j));
            ++lControlPoints;
        }
    }
    
    FbxNode* lNode = FbxNode::Create(pScene,lName);
    lNode->SetNodeAttribute(lMesh);
    
//    TODO: incorporate materials
//    lNode->AddMaterial(fbxsdk::FbxSurfaceMaterial *pMaterial);
//    lNode->SetShadingMode(FbxNode::eTextureShading);
    
    pScene->GetRootNode()->AddChild(lNode);
}
