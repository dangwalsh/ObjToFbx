#ifndef SDKEXCEPTION_H
#define SDKEXCEPTION_H

#include <exception>

class SdkException: public std::exception
{
public:
	SdkException(const char* pMessage);
	virtual const char* Message() const throw();
};



#endif // !SDKEXCEPTION_H