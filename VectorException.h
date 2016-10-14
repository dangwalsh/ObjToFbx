#pragma once
#include <exception>

class VectorException : public std::exception
{
public:
	VectorException(const char* pMessage);
	virtual const char* Message() const throw();
};
