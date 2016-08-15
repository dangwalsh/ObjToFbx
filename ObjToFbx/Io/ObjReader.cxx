#include <sstream>
#include <vector>
#include "ObjReader.h"

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
            CreateFbxScene(lScene, lObjScene);

			free(lBuffer);
		}
		lResult = true;
	}
	return lResult;
}

void ObjReader::CreateFbxScene(FbxScene* pScene, ObjScene* pObjScene)
{
    for (ObjGroup* &lGroup : *pObjScene->GetGroups())
    {
        FbxNode* lNode = CreateMesh(pScene, pObjScene, lGroup);
        if(!lNode)
            continue;
        ApplyMaterial(pScene, lNode, lGroup);
        pScene->GetRootNode()->AddChild(lNode);
    }
}

FbxNode* ObjReader::CreateMesh(FbxScene* pScene, ObjScene* pObjScene, ObjGroup* pGroup)
{
    FbxMesh* lMesh = FbxMesh::Create(pScene, pGroup->GetName()->c_str());
    vector<FbxVector4>* lVertices = pObjScene->GetVertices();

    lMesh->InitControlPoints(static_cast<unsigned int>(lVertices->size()));
    FbxVector4* lControlPoints = lMesh->GetControlPoints();

    for (FbxVector4 &lVertex : *lVertices)
        *lControlPoints++ = lVertex;

    FbxGeometryElementUV* lUVDiffuseElement = lMesh->CreateElementUV("DiffuseUV");
    FBX_ASSERT( lUVDiffuseElement != NULL);
    lUVDiffuseElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
    lUVDiffuseElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);

    vector<FbxVector2>* lTexCoords = pObjScene->GetTexCoords();

//    FbxLayer* lLayer = lMesh->GetLayer(0);
//    if(lLayer == NULL){
//        lMesh->CreateLayer();
//        lLayer = lMesh->GetLayer(0);
//    }
//
    FbxLayerElementNormal* lLayerElementNormal= FbxLayerElementNormal::Create(lMesh, "");
    lLayerElementNormal->SetMappingMode(FbxLayerElement::eByPolygon);
    lLayerElementNormal->SetReferenceMode(FbxLayerElement::eDirect);

    for (FbxVector2 & lTexCoord : *lTexCoords)
        lUVDiffuseElement->GetDirectArray().Add(lTexCoord);
//    int count =static_cast<int>(lTexCoords->size());
//    lUVDiffuseElement->GetIndexArray().SetCount(count);

    for (ObjFace* &lFace : *pGroup->GetFaces())
    {
        lMesh->BeginPolygon();
        const vector<unsigned int>* lVertInd = lFace->GetXYZ();
        const vector<unsigned int>* lTexInd = lFace->GetUVW();
        for (size_t i = 0; i < lFace->Size(); ++i)
        {
            lMesh->AddPolygon(lVertInd->at(i));
            lUVDiffuseElement->GetIndexArray().Add(lTexInd->at(i));
        }
        lMesh->EndPolygon ();
        lLayerElementNormal->GetDirectArray().Add(*lFace->GetNormal());
    }

//    lLayer->SetNormals(lLayerElementNormal);
    FbxNode* lNode = FbxNode::Create(pScene, "");
    lNode->SetNodeAttribute(lMesh);
    lNode->SetShadingMode(FbxNode::eTextureShading);

    return lNode;
}



void ObjReader::ApplyMaterial(FbxScene* pScene, FbxNode* pNode, ObjGroup* pGroup)
{
    FbxMesh* lMesh = pNode->GetMesh();
    FbxGeometryElementMaterial* lMaterialElement = lMesh->CreateElementMaterial();
    lMaterialElement->SetMappingMode(FbxGeometryElement::eByPolygon);
    lMaterialElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);
    if (!lMesh->GetElementMaterial(0))
        return;

    FbxSurfaceMaterial* lMaterial = CreateMaterial(pScene, pGroup->GetMaterial());
    pNode->AddMaterial(lMaterial);

    lMaterialElement->GetIndexArray().SetCount(lMesh->GetPolygonCount());

    for (int i = 0; i<lMesh->GetPolygonCount(); ++i)
        lMaterialElement->GetIndexArray().SetAt(i,0);

    return;
}

FbxSurfaceMaterial* ObjReader::CreateMaterial(FbxScene* pScene, ObjMaterial* pObjMaterial)
{
    // TODO: check illum value to determine which shading model
    
    FbxString lShadingName = "Phong";
    FbxString lMaterialName = pObjMaterial->GetName().c_str();
    FbxSurfacePhong* lMaterial = FbxSurfacePhong::Create(pScene, lMaterialName.Buffer());

    lMaterial->ShadingModel.Set(lShadingName);
    lMaterial->Ambient.Set(pObjMaterial->GetAmbient());
    lMaterial->Ambient.ConnectSrcObject(CreateTexture(pScene, lMaterial, pObjMaterial->GetAmbientTex()));
    lMaterial->Diffuse.Set(pObjMaterial->GetDiffuse());
    lMaterial->Diffuse.ConnectSrcObject(CreateTexture(pScene, lMaterial, pObjMaterial->GetDiffuseTex()));
    lMaterial->Specular.Set(pObjMaterial->GetSpecular());
    lMaterial->Specular.ConnectSrcObject(CreateTexture(pScene, lMaterial, pObjMaterial->GetSpecularTex()));
    lMaterial->TransparencyFactor.Set(1.0 - pObjMaterial->GetDissolve());
    lMaterial->Shininess.Set(pObjMaterial->GetHilight());

    return lMaterial;
}

FbxFileTexture* ObjReader::CreateTexture(FbxScene *pScene, FbxSurfacePhong *pFbxMaterial, ObjTex* pObjTex)
{
    if(pObjTex == NULL)
        return NULL;

    FbxFileTexture* lTexture = FbxFileTexture::Create(pScene, "Diffuse Texture");

    lTexture->SetFileName(pObjTex->GetPath().c_str());
    lTexture->SetTextureUse(FbxTexture::eStandard);
    lTexture->SetMappingType(FbxTexture::eUV);
    lTexture->SetMaterialUse(FbxFileTexture::eModelMaterial);
    lTexture->SetSwapUV(false);
    lTexture->SetTranslation(pObjTex->GetOrigin()[0], pObjTex->GetOrigin()[1]);
    lTexture->SetScale(pObjTex->GetScale()[0], pObjTex->GetScale()[1]);
    lTexture->SetRotation(pObjTex->GetRotation()[0], pObjTex->GetOrigin()[1]);

    return lTexture;

}
