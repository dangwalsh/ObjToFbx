#include "VectorException.h"

VectorException::VectorException(const char* pMessage)
	: exception(pMessage)
{

}

const char* VectorException::Message() const throw()
{
	return what();
}
