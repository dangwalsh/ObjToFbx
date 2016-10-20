#include "VectorException.h"

VectorException::VectorException(const char* pMessage)
    : mMessage(pMessage)
{
    
}

const char* VectorException::what() const throw()
{
    return mMessage;
}
