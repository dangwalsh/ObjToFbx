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
    FbxNode* lNode = CreateMesh(pScene, pObjScene);
    pScene->GetRootNode()->AddChild(lNode);
}

FbxNode* ObjReader::CreateMesh(FbxScene* pScene, ObjScene* pObjScene)
{
    FbxMesh* lMesh = FbxMesh::Create(pScene, "");
    vector<FbxVector4>* lVertices = pObjScene->GetVertices();

    lMesh->InitControlPoints(static_cast<unsigned int>(lVertices->size()));
    FbxVector4* lControlPoints = lMesh->GetControlPoints();
    
    for (FbxVector4 &lVertex : *lVertices) {
        *lControlPoints++ = lVertex;
    }
    
    FbxGeometryElementUV* lUVDiffuseElement = lMesh->CreateElementUV( "DiffuseUV");
    FBX_ASSERT( lUVDiffuseElement != NULL);
    lUVDiffuseElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
    lUVDiffuseElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);
    
    vector<FbxVector2>* lTexCoords = pObjScene->GetTexCoords();
    
    for (FbxVector2 & lTexCoord : *lTexCoords) {
        lUVDiffuseElement->GetDirectArray().Add(lTexCoord);
    }
    
    lUVDiffuseElement->GetIndexArray().SetCount(static_cast<unsigned int>(lTexCoords->size()));
    
    for(ObjGroup* &lGroup : *pObjScene->GetGroups()) {
        for (ObjFace* &lFace : *lGroup->GetFaces()) {
            lMesh->BeginPolygon();
            const vector<size_t>* lVertInd = lFace->GetXYZ();
            const vector<size_t>* lTexInd = lFace->GetUVW();
            for (size_t i = 0; i < lFace->Size(); ++i) {
                lMesh->AddPolygon(static_cast<unsigned int>(lVertInd->at(i)));
                lUVDiffuseElement->GetIndexArray().Add(static_cast<unsigned int>(lTexInd->at(i)));
            }
            lMesh->EndPolygon ();
        }
    }
    
    FbxNode* lNode = FbxNode::Create(pScene, "");
    lNode->SetNodeAttribute(lMesh);
    lNode->SetShadingMode(FbxNode::eTextureShading);
    
    FbxGeometryElementMaterial* lMaterialElement = lMesh->CreateElementMaterial();
    lMaterialElement->SetMappingMode(FbxGeometryElement::eByPolygon);
    lMaterialElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);
    if( !lMesh->GetElementMaterial( 0))
        return NULL;
    
    FbxString lMaterialName = "material_for_plane";
    FbxString lShadingName  = "Phong";
    FbxSurfacePhong* lMaterial = FbxSurfacePhong::Create(pScene, lMaterialName.Buffer());
    
    lMaterial->Diffuse.Set(FbxDouble3(1.0, 1.0, 0));
    lMaterial->DiffuseFactor.Set(1.);
    
    lNode->AddMaterial(lMaterial);
    
    lMaterialElement->GetIndexArray().SetCount(lMesh->GetPolygonCount());
    
    for(int i = 0; i<lMesh->GetPolygonCount(); ++i)
        lMaterialElement->GetIndexArray().SetAt(i,0);
    
    return lNode;
}
