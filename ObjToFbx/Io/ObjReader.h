#ifndef OBJREADER_H
#define OBJREADER_H

#include <fbxsdk.h>

class ObjReader : public FbxReader
{
public:
	ObjReader(FbxManager &pManager, int pID);
	virtual ~ObjReader();

	virtual void GetVersion(int& pMajor, int& pMinor, int& pRevision);
	virtual bool FileOpen(char* pFileName);
	virtual bool FileClose();
	virtual bool IsFileOpen();

	virtual bool GetReadOptions(bool pParseFileAsNeeded = true);
	virtual bool Read(FbxDocument* pDocument);

private:
	FILE*		mFilePointer;
	FbxManager*	mManager;
};



#endif // OBJREADER_H