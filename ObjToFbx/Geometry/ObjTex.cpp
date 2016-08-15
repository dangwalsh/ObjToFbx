//
//  ObjTex.cpp
//  ObjToFbx
//
//  Created by Daniel Walsh on 8/13/16.
//  Copyright © 2016 Daniel Walsh. All rights reserved.
//

#include "ObjTex.h"
#include <iterator>
#include <algorithm>

using namespace std;

ObjTex::ObjTex(vector<string>& pTokens)
{
    mScale = new double[3] { 1.0, 1.0, 1.0 };
    mOrigin = new double[3] { 0.0, 0.0, 0.0 };
    mRotation = new double[3] { 0.0, 0.0, 0.0 };

    size_t lCount = pTokens.size();

    switch (lCount) {
        case 2:
        {
            mPath = pTokens[1];
            break;
        }
        case 6:
        {
            SetTransforms(pTokens);
            mPath = pTokens[5];
            break;
        }
        case 10:
        {
            SetTransforms(pTokens);
            mPath = pTokens[9];
            break;
        }
        case 14:
        {
            SetTransforms(pTokens);
            mPath = pTokens[13];
            break;
        }
        default:
            // TODO: throw an exception
            break;
    }
}

ObjTex::~ObjTex()
{
    
}


/* Public Members - Accessors */

string ObjTex::GetPath()
{
    return mPath;
}

double* ObjTex::GetScale()
{
    return mScale;
}

double* ObjTex::GetOrigin()
{
    return mOrigin;
}

double* ObjTex::GetRotation()
{
    return mRotation;
}


/* Protected Members */

void ObjTex::SetTransforms(vector<string>& pTokens)
{
    string lOptions[3] = { "-s", "-o", "-r" };
    double** lMembers = new double*[3] { mScale, mOrigin, mRotation };
    vector<string>::iterator lBegin = pTokens.begin();
    vector<string>::iterator lEnd = pTokens.end();
    vector<string>::iterator lToken;

    for (size_t i = 0; i < 3; ++i)
    {
        lToken = find(lBegin, lEnd, lOptions[i]);
        if (lToken != lEnd) {
            double* lArray = CreateArray(++lToken);
            for (size_t j = 0; j < 3; ++j)
                lMembers[i][j] = lArray[j];
        }
    }
}

double* ObjTex::CreateArray(vector<string>::iterator& pItor)
{
    double* lArray = new double[3];

    for (size_t i = 0; i < 3; ++i)
        lArray[i] = stod(*pItor);

    return lArray;
}