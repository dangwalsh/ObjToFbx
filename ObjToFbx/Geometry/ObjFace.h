#ifndef OBJFACE_H
#define OBJFACE_H

#include <fbxsdk.h>
#include <string>
#include <vector>

class ObjFace
{
public:
    ObjFace(std::vector<std::string>& pTokens);
	ObjFace(FbxString& pString);
	virtual ~ObjFace();

protected:
	size_t*  mXYZ;
	size_t*  mNrm;
    size_t*  mUVW;

};

#endif // OBJFACE_H