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
	lResult = lImporter->Import(lScene);
    
	DestroySdkObjects(lSdkManager, lResult);

	return 0;
}
