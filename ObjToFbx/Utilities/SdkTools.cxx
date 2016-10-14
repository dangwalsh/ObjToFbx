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

void ChangeExtension(char* pPath)
{
	char* lExt = new char[5]{ '.','f','b','x','\0' };
	char* lPtr = strchr(pPath, '.');

	while (*lExt != '\0')
	{
		++lPtr;
		++lExt;
		*lPtr = *lExt;
	}
}

char* CreatFileName(char* pPath)
{
	char* lExt = new char[5]{ '.','f','b','x','\0' };
	int lSize = strlen(pPath);
	char *lBuffer = new char[lSize];
	strcpy(lBuffer, pPath);
	char *lPtr = strchr(lBuffer, '.');
	
	while (*lExt != '\0')
	{
		++lPtr;
		++lExt;
		*lPtr = *lExt;
	}

	return lBuffer;
}

char * GetDirectory(char* pPath)
{
	int lSize = strlen(pPath);
	char *lBuffer = new char[lSize];
	strcpy(lBuffer, pPath);
	char *lPtr; 

	for (lPtr = lBuffer + lSize; *lPtr != '\\'; --lPtr) { }

	*lPtr = '\0';
	return lBuffer;
}