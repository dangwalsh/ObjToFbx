#include <fbxsdk.h>
#include <boost/filesystem.hpp>
#include "Io/ObjReaderFacade.h"
#include "Utilities/SdkTools.h"
#include "Utilities/ClTools.h"

using namespace std;

int main(int argc, char** argv)
{
	bool lResult;
	int lRegisteredCount;
	int lPluginId;

	FbxManager* lSdkManager = NULL;
	FbxScene* lScene = NULL;
	ClParser lParser(argc, argv);

	string lInput = lParser.InPath();
	string lOutput = lParser.OutPath();
	int8_t lOptions = lParser.FileFormat();

    InitializeSdkObjects(lSdkManager, lScene);

	lSdkManager->GetIOPluginRegistry()->RegisterReader(CreateObjReader, GetObjReaderInfo, lPluginId, lRegisteredCount, FillObjReaderIOSettings);

	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

	lResult = lImporter->Initialize(lInput.c_str(), -1, lSdkManager->GetIOSettings() );
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

    lResult = SaveScene(lSdkManager, lScene, lOutput.c_str(), lOptions);
	DestroySdkObjects(lSdkManager, lResult);

	return 0;
}
