#include <fbxsdk.h>
#include "Io/ObjReaderFacade.h"
#include "Utilities/SdkTools.h"

#ifdef IOS_REF
    #undef  IOS_REF
    #define IOS_REF (*(pManager->GetIOSettings()))
#endif

bool SaveScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename, int pFileFormat=-1, bool pEmbedMedia=false);


int main(int argc, char** argv) 
{
	bool lResult;
	int lRegisteredCount;
	int lPluginId;
	const char* lFileName = "/Library/ObjToFbx/texture_test.xobj";
	FbxManager* lSdkManager = NULL;
	FbxScene* lScene = NULL;

    InitializeSdkObjects(lSdkManager, lScene);
    
	lSdkManager->GetIOPluginRegistry()->RegisterReader(CreateObjReader, GetObjReaderInfo, lPluginId, lRegisteredCount, FillObjReaderIOSettings);

	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

	lResult = lImporter->Initialize(lFileName, -1, lSdkManager->GetIOSettings() );
    if(lResult == false)
    {
        FBXSDK_printf("Call to FbxExporter::Initialize() failed.\n");
        FBXSDK_printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
        DestroySdkObjects(lSdkManager, false);
        return 1;
    }
    
	lResult = lImporter->Import(lScene);
    if(lResult == false)
    {
        FBXSDK_printf("Error in write of our custom writer\n");
        DestroySdkObjects(lSdkManager, lResult);
        return 1;
    }

    lResult = SaveScene(lSdkManager, lScene, "texture_test.fbx");
    
	DestroySdkObjects(lSdkManager, lResult);

	return 0;
}


bool SaveScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename, int pFileFormat, bool pEmbedMedia)
{
    int lMajor, lMinor, lRevision;
    bool lStatus = true;
    
    FbxExporter* lExporter = FbxExporter::Create(pManager, "");
    
    if( pFileFormat < 0 || pFileFormat >= pManager->GetIOPluginRegistry()->GetWriterFormatCount() )
    {
        pFileFormat = pManager->GetIOPluginRegistry()->GetNativeWriterFormat();
        int lFormatIndex, lFormatCount = pManager->GetIOPluginRegistry()->GetWriterFormatCount();
        
        for (lFormatIndex=0; lFormatIndex<lFormatCount; lFormatIndex++)
        {
            if (pManager->GetIOPluginRegistry()->WriterIsFBX(lFormatIndex))
            {
                FbxString lDesc =pManager->GetIOPluginRegistry()->GetWriterFormatDescription(lFormatIndex);
                const char *lASCII = "ascii";
                if (lDesc.Find(lASCII)>=0)
                {
                    pFileFormat = lFormatIndex;
                    break;
                }
            }
        }
    }
    
    IOS_REF.SetBoolProp(EXP_FBX_MATERIAL,        true);
    IOS_REF.SetBoolProp(EXP_FBX_TEXTURE,         true);
    IOS_REF.SetBoolProp(EXP_FBX_EMBEDDED,        pEmbedMedia);
    IOS_REF.SetBoolProp(EXP_FBX_SHAPE,           true);
    IOS_REF.SetBoolProp(EXP_FBX_GOBO,            true);
    IOS_REF.SetBoolProp(EXP_FBX_ANIMATION,       true);
    IOS_REF.SetBoolProp(EXP_FBX_GLOBAL_SETTINGS, true);
    
    if(lExporter->Initialize(pFilename, pFileFormat, pManager->GetIOSettings()) == false)
    {
        FBXSDK_printf("Call to FbxExporter::Initialize() failed.\n");
        FBXSDK_printf("Error returned: %s\n\n", lExporter->GetStatus().GetErrorString());
        return false;
    }
    
    FbxManager::GetFileFormatVersion(lMajor, lMinor, lRevision);
    FBXSDK_printf("FBX file format version %d.%d.%d\n\n", lMajor, lMinor, lRevision);
    
    lStatus = lExporter->Export(pScene);
    
    lExporter->Destroy();
    return lStatus;
}