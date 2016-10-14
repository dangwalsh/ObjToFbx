#ifndef VECTOREXCEPTION_H
#define VECTOREXCEPTION_H

#include <exception>

class VectorException : public std::exception
{
public:
	VectorException(const char* pMessage);
	virtual const char* Message() const throw();
};



#endif // !VECTOREXCEPTION_H