#include <fbxsdk.h>
#include "Io/ObjReaderFacade.h"
#include "Utilities/SdkTools.h"

int main(int argc, char** argv) 
{
	bool lResult;
	int lRegisteredCount;
	int lPluginId;
	const char* lFileName = "texture_test.xobj";
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
    
	DestroySdkObjects(lSdkManager, lResult);

	return 0;
}
