//
// Created by Daniel Walsh on 7/29/16.
//

#include "MtlReader.h"

using namespace std;

MtlReader::MtlReader():
mFilePointer(NULL)
{
    
}

MtlReader::~MtlReader()
{
    
}

bool MtlReader::FileOpen(const char* pFileName)
{
    if (mFilePointer != NULL)
        FileClose();
    FBXSDK_fopen(mFilePointer, pFileName, "r");
    if (mFilePointer == NULL)
        return false;
    return true;
}

string* MtlReader::FileRead()
{
    long lSize;
    char* lBuffer = NULL;
    string* lString = NULL;
    
    if(mFilePointer != NULL)
    {
        fseek (mFilePointer , 0 , SEEK_END);
        lSize = ftell (mFilePointer);
        rewind (mFilePointer);
        
        lBuffer = (char*) malloc (sizeof(char)*lSize + 1);
        size_t lRead = fread(lBuffer, 1, lSize, mFilePointer);
        lBuffer[lRead]='\0';
        
        lString = new string(lBuffer);
        
        free(lBuffer);
    }
    
    return lString;
}

bool MtlReader::FileClose()
{
    if (mFilePointer != NULL)
        fclose(mFilePointer);
    return true;
}