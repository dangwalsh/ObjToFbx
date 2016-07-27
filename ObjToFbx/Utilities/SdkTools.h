#ifndef SDKTOOLS_H
#define SDKTOOLS_H

#include <fbxsdk.h>

void InitializeSdkObjects(FbxManager *&pManager, FbxScene *&pScene);
void DestroySdkObjects(FbxManager* pManager, bool pExitStatus);

#endif // SDKTOOLS_H