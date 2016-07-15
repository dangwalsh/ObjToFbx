#include "SdkException.h"

const char* SdkException::Message() const throw()
{
	return "There was a problem with the SDK";
}