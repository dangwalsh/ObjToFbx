#include "SdkException.h"

SdkException::SdkException(const char* pMessage)
	: exception(pMessage)
{

}

const char* SdkException::Message() const throw()
{
	return what();
}
