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
    virtual double* GetRotation();
    
protected:
    std::string mPath;
    double*     mScale;
    double*     mOrigin;
    double*     mRotation;

    virtual void SetTransforms(std::vector<std::string>& pTokens);
    virtual double* CreateArray(std::vector<std::string>::iterator& pItor);
};

#endif /* ObjTex_hpp */
