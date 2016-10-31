//
//  ObjTex.hpp
//  ObjToFbx
//
//  Created by Daniel Walsh on 8/13/16.
//  Copyright © 2016 Daniel Walsh. All rights reserved.
//

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

    //virtual void SetTransforms(std::vector<std::string>& pTokens);
    virtual double* CreateArray(std::vector<std::string>::iterator& pItor);
	virtual std::vector<std::string>::iterator SetOrigin(std::vector<std::string>::iterator& pItor);
	virtual std::vector<std::string>::iterator SetScale(std::vector<std::string>::iterator& pItor);
	virtual std::vector<std::string>::iterator SetTurbulence(std::vector<std::string>::iterator& pItor);
};

#endif /* ObjTex_hpp */
