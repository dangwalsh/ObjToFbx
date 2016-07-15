#ifndef OBJREADERFACADE_H
#define OBJREADERFACADE_H

#include <fbxsdk.h>

FbxReader* CreateObjReader(FbxManager& pManager, FbxImporter& pImporter, int pSubID, int pPluginID);
void* GetObjReaderInfo(FbxReader::EInfoRequest pRequest, int pId);
void FillObjReaderIOSettings(FbxIOSettings& pIOS);

#endif // OBJREADERFACADE_H