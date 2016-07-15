#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include "ObjReader.h"
#include "../Geometry/ObjScene.h"

using namespace std;

ObjReader::ObjReader(FbxManager &pManager, int pID):
FbxReader(pManager, pID, FbxStatusGlobal::GetRef()),
mFilePointer(NULL),
mManager(&pManager)
{
}

ObjReader::~ObjReader() 
{
	FileClose();
}

void ObjReader::GetVersion(int& pMajor, int& pMinor, int& pRevision) 
{
	pMajor = 1;
	pMinor = 0;
	pRevision = 0;
}

bool ObjReader::FileOpen(char* pFileName) 
{
	if (mFilePointer != NULL)
		FileClose();
	FBXSDK_fopen(mFilePointer, pFileName, "r");
	if (mFilePointer == NULL)
		return false;
	return true;
}

bool ObjReader::FileClose() 
{
	if (mFilePointer != NULL)
		fclose(mFilePointer);
	return true;
}

bool ObjReader::IsFileOpen() 
{
	if (mFilePointer != NULL)
		return true;
	return false;
}

bool ObjReader::GetReadOptions(bool /*pParseFileAsNeeded*/) 
{
	return true;
}

bool ObjReader::Read(FbxDocument* pDocument) 
{
	if (!pDocument)
	{
		GetStatus().SetCode(FbxStatus::eFailure, "Invalid document handle");
		return false;
	}
	FbxScene*       lScene = FbxCast<FbxScene>(pDocument);
	bool            lIsAScene = (lScene != NULL);
	bool            lResult = false;

	if(lIsAScene)
	{
		FbxNode* lRootNode = lScene->GetRootNode();
		FbxNodeAttribute * lRootNodeAttribute = FbxNull::Create(lScene,"");
		lRootNode->SetNodeAttribute(lRootNodeAttribute);

		long lSize;
		char* lBuffer = NULL;    
		if(mFilePointer != NULL)
		{
			//To obtain file size
			fseek (mFilePointer , 0 , SEEK_END);
			lSize = ftell (mFilePointer);
			rewind (mFilePointer);

			//Read file content to a string.
			lBuffer = (char*) malloc (sizeof(char)*lSize + 1);
			size_t lRead = fread(lBuffer, 1, lSize, mFilePointer);
			lBuffer[lRead]='\0';
			string lString(lBuffer);

			auto lObjScene = ObjScene(lString);

			//Parse the string to get the node types and values. 
			// FbxNodeAttribute* lNodeAttribute;

			// size_t lEndTokenCount = lString.GetTokenCount("\n");

			// string lMatLib;
			// vector< FbxVector4 > lVertices;
			// vector< FbxVector4 > lVertNorms;
			// vector< FbxVector4 > lTexCoords;

			// for (int i = 0; i < lEndTokenCount; i++)
			// {
			// 	string lSubString(lString.GetToken(i,"\n"));
			// 	vector<string> lTokens = ObjReader::Parse(lSubString);
			// 	string lTokenType = lTokens.at(0);
			// 	string::size_type sz;

			// 	if (lTokenType == "v")
			// 	{
			// 		double v1 = stod(lTokens.at(1), &sz);
			// 		double v2 = stod(lTokens.at(2), &sz);
			// 		double v3 = stod(lTokens.at(3), &sz);
			// 		FbxVector4 vertex(v1, v2, v3);
			// 		lVertices.push_back(vertex);
			// 	}
			// 	else if (lTokenType == "vt")
			// 	{
			// 		double v1 = stod(lTokens.at(1), &sz);
			// 		double v2 = stod(lTokens.at(2), &sz);
			// 		double v3 = stod(lTokens.at(3), &sz);
			// 		FbxVector4 vertex(v1, v2, v3);
			// 		lTexCoords.push_back(vertex);
			// 	}
			// 	else if (lTokenType == "usemtl")
			// 	{
			// 		if (lTokenType == "f")
			// 		{

			// 		}
			// 		else if (lTokenType == "g")
			// 		{
						
			// 		}
			// 	}
			// 	else if (lTokenType == "mtllib")
			// 	{
			// 		lMatLib = lTokens.at(1);
			// 	}
			// 	else
			// 	{
			// 		FBXSDK_printf("Error: Unrecognized node type\n");
			// 		exit(1);
			// 	}
			
			// }
			free(lBuffer);
		}
		lResult = true;
	}
	return lResult;
}
