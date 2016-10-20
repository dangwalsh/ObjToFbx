#ifndef VECTOREXCEPTION_H
#define VECTOREXCEPTION_H

#include <exception>

class VectorException : public std::exception
{
public:
	VectorException(const char* pMessage);
    virtual const char* what() const throw();
private:
    const char* mMessage;
};



#endif // !VECTOREXCEPTION_H
