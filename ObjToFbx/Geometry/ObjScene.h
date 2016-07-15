#ifndef OBJSCENE_H
#define OBJSCENE_H

#include <fbxsdk.h>
#include "ObjGroup.h"

class ObjGroup;

class ObjScene
{
public:
    ObjScene();
	ObjScene(std::string& pString);
	virtual ~ObjScene();

protected:
	std::string*             mMatLib;
	std::vector<FbxVector4>* mVertices;
	std::vector<FbxVector4>* mNormals;
	std::vector<FbxVector4>* mTexCoord;
    std::vector<ObjGroup>* mElements;

	void AddMtlLib(std::vector<std::string>& pTokens);
	void AddVertex(std::vector<std::string>& pTokens);
	void AddNormal(std::vector<std::string>& pTokens);
	void AddTexCoord(std::vector<std::string>& pTokens);
	std::vector<std::string>::iterator AddObjGroup(std::vector<std::string>::iterator pItor,
                                                     std::vector<std::string>::iterator pEnd);

};

#endif // OBJSCENE_H