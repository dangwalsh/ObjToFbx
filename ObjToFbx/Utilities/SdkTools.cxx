#include "SdkTools.h"

void InitializeSdkObjects(FbxManager *&pManager, FbxScene *&pScene)
{
	pManager = FbxManager::Create();
	if( !pManager )
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		exit(1);
	}
	else FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());

	FbxIOSettings* lIos = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(lIos);

	pScene = FbxScene::Create(pManager, "My Scene");
	if( !pScene ) 
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		exit(1);
	}
}

void DestroySdkObjects(FbxManager* pManager, bool pExitStatus)
{
	if( pManager ) pManager->Destroy();
	if( pExitStatus ) FBXSDK_printf("Program Success!\n");
}