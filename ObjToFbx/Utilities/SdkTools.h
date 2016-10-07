#ifndef SDKTOOLS_H
#define SDKTOOLS_H

#include <fbxsdk.h>

void InitializeSdkObjects(FbxManager *&pManager, FbxScene *&pScene);
void DestroySdkObjects(FbxManager* pManager, bool pExitStatus);
char* GetDirectory(char* pFileName);

#endif // SDKTOOLS_H