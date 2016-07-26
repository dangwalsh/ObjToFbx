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
    vector<ObjGroup*>::iterator itor;
    vector<ObjGroup*>* lGroups = pObjScene->GetGroups();
    for(itor = lGroups->begin(); itor < lGroups->end(); ++itor) {
        CreateMesh(pScene, pObjScene, *itor++);
    }
    
}

void ObjReader::CreateMesh(FbxScene* pScene, ObjScene* pObjScene, ObjGroup* pGroup)
{    
    FbxMesh* lMesh = FbxMesh::Create(pScene, "");
    vector<FbxVector4>* lVertices = pObjScene->GetVertices();
    int lNbPoints = static_cast<unsigned int>(lVertices->size());
    lMesh->InitControlPoints(lNbPoints);
    FbxVector4* lControlPoints = lMesh->GetControlPoints();
    
    for (vector<FbxVector4>::iterator itor = lVertices->begin(); itor < lVertices->end(); ++itor) {
        *lControlPoints++ = *itor;
    }
    
    // TODO: normals and UVs
    
    for(ObjGroup* & group : *pObjScene->GetGroups()) {
        for (ObjFace* & face : *group->GetFaces()) {
            vector<size_t> lVerts = *face->GetXYZ();
            lMesh->BeginPolygon();
            for (vector<size_t>::iterator itor = lVerts.begin(); itor < lVerts.end(); ++itor) {
                lMesh->AddPolygon(static_cast<unsigned int>(*itor));
                
                // TODO: update the index array of the UVs
            }
            lMesh->EndPolygon ();
        }
    }
    
    FbxNode* lNode = FbxNode::Create(pScene, "");
    lNode->SetNodeAttribute(lMesh);
    pScene->GetRootNode()->AddChild(lNode);
}
