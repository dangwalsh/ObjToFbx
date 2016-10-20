//
// Created by Daniel Walsh on 7/29/16.
//

#ifndef OBJTOFBX_MTLREADER_H
#define OBJTOFBX_MTLREADER_H

#include <fbxsdk.h>
#include <string>

class MtlReader
{
public:
    MtlReader(const char* pDirectory);
    virtual ~MtlReader();
    
    virtual bool FileOpen(const char* pFileName);
    virtual bool FileOpenRelative(const char* pFileName);
    virtual std::string* FileRead();
    virtual bool FileClose();

protected:
    FILE*           mFilePointer;
    const char*     mDirectory;
};


#endif //OBJTOFBX_MTLREADER_H
