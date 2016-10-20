#ifndef SDKEXCEPTION_H
#define SDKEXCEPTION_H

#include <exception>

class SdkException: public std::exception
{
public:
	SdkException(const char* pMessage);
    SdkException(const char* pMessage, const char* pData);
	virtual const char* what() const throw();
private:
    const char* mMessage;
    const char* mData;
};



#endif // !SDKEXCEPTION_H
