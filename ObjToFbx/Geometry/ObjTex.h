#ifndef ObjTex_hpp
#define ObjTex_hpp

#include <string>
#include <vector>

class ObjTex
{
public:
	
    ObjTex(std::vector<std::string>& pTokens);
    ~ObjTex();

    virtual std::string GetPath();
    virtual double* GetScale();
    virtual double* GetOrigin();
    virtual double* GetTurbulence();
    
protected:
    std::string mPath;
	double*     mOrigin;    
	double*     mScale;
    double*     mTurbulence;

	void ParseTokens(std::vector<std::basic_string<char>>& pTokens);
    
	virtual void SetOrigin(std::vector<std::string>::iterator& pItor);
	virtual void SetScale(std::vector<std::string>::iterator& pItor);
	virtual void SetTurbulence(std::vector<std::string>::iterator& pItor);
	virtual double* ConvertToDoubleArray(std::vector<std::string>::iterator& pItor);
};

#endif /* OBJTEX_H */
