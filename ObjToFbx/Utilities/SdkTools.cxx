#include "SdkTools.h"
#include "StringTools.h"
#include <exception>

#ifdef IOS_REF
	#undef  IOS_REF
	#define IOS_REF (*(pManager->GetIOSettings()))
#endif

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
	try
	{
		if (pManager) pManager->Destroy();
	}
	catch (std::exception ex)
	{
		FBXSDK_printf(ex.what());
		exit(1);
	}	
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

char* GetDirectory(char* pPath)
{
	int lSize = strlen(pPath);
	char *lBuffer = new char[lSize];
	strcpy(lBuffer, pPath);
    char *lPtr;
#ifdef WIN32
    char lSeparator = '\\';
#else
    char lSeparator = '/';
#endif

	for (lPtr = (lBuffer + lSize - 1); *lPtr != lSeparator; --lPtr) { }

	*++lPtr = '\0';
	return lBuffer;
}

const char* CreateRelativePath(const char* pAbsolute, const char* pRelative)
{
    return StringConcat(pAbsolute, pRelative);
}

bool SaveScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename, int pFileFormat, bool pEmbedMedia)
{
	int lMajor, lMinor, lRevision;
	bool lStatus = true;
	
	FbxExporter* lExporter = FbxExporter::Create(pManager, "");

	if(pFileFormat == 0)
	{
		pEmbedMedia = true;
	}
	//  if( pFileFormat < 0 || pFileFormat >= pManager->GetIOPluginRegistry()->GetWriterFormatCount() )
	//  {
	//      pFileFormat = pManager->GetIOPluginRegistry()->GetNativeWriterFormat();
	//      pFileFormat = pManager->GetIOPluginRegistry()->FindWriterIDByDescription("FBX binary (*.fbx)");
	//	    pFileFormat = pManager->GetIOPluginRegistry()->FindWriterIDByDescription("FBX ascii (*.fbx)");
	//      int lFormatIndex, lFormatCount = pManager->GetIOPluginRegistry()->GetWriterFormatCount();
	//  }

	IOS_REF.SetBoolProp(EXP_FBX_MATERIAL, true);
	IOS_REF.SetBoolProp(EXP_FBX_TEXTURE, true);
	IOS_REF.SetBoolProp(EXP_FBX_EMBEDDED, pEmbedMedia);
	IOS_REF.SetBoolProp(EXP_FBX_SHAPE, true);
	IOS_REF.SetBoolProp(EXP_FBX_GOBO, true);
	IOS_REF.SetBoolProp(EXP_FBX_ANIMATION, true);
	IOS_REF.SetBoolProp(EXP_FBX_GLOBAL_SETTINGS, true);

	if (lExporter->Initialize(pFilename, pFileFormat, pManager->GetIOSettings()) == false)
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



