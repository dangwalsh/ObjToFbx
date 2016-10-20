#include "SdkException.h"
#include "../Utilities/StringTools.h"

SdkException::SdkException(const char* pMessage)
	: mMessage(pMessage)
{

}

SdkException::SdkException(const char* pMessage, const char* pData)
    : mMessage(pMessage), mData(pData)
{
    
}

const char* SdkException::what() const throw()
{
	return StringConcat(mMessage, mData);
}
