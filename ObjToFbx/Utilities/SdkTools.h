#ifndef SDKTOOLS_H
#define SDKTOOLS_H

#include <fbxsdk.h>
#include <string>

void InitializeSdkObjects(FbxManager *&pManager, FbxScene *&pScene);
void DestroySdkObjects(FbxManager* pManager, bool pExitStatus);
char* GetDirectory(char* pFileName);
void ChangeExtension(char* pPath);
char* CreatFileName(char* pPath);
const char* CreateRelativePath(const char* pAbsolute, const char* pRelative);
bool SaveScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename, int pFileFormat = -1, bool pEmbedMedia = false);

#endif // SDKTOOLS_H
