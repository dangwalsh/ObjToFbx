#include "ObjReaderFacade.h"
#include "ObjReader.h"

FbxReader* CreateObjReader(FbxManager& pManager, FbxImporter& pImporter, int pSubID, int pPluginID)
{
	return FbxNew<ObjReader>(pManager, pPluginID);
}

void* GetObjReaderInfo(FbxReader::EInfoRequest pRequest, int pId)
{
	static const char* sExt[] = 
	{
		"xobj",
		0
	};

	static const char* sDesc[] = 
	{
		"Extended OBJ FileFormat (*.xobj)",
		0
	};

    switch (pRequest)
    {
    case FbxReader::eInfoExtension:
        return sExt;
    case FbxReader::eInfoDescriptions:
        return sDesc;
    default:
        return 0;
    }
}

void FillObjReaderIOSettings(FbxIOSettings& pIOS)
{
	// TODO: add custom IOSettings
}