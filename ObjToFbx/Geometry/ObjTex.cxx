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
#include "../Utilities/StringTools.h"

using namespace std;

ObjTex::ObjTex(vector<string>& pTokens)
{
    mScale = new double[3] { 1.0, 1.0, 1.0 };
    mOrigin = new double[3] { 0.0, 0.0, 0.0 };
    mTurbulence = new double[3] { 0.0, 0.0, 0.0 };

    size_t lCount = pTokens.size();

    //switch (lCount) {
    //    case 2:
    //    {
    //        mPath = pTokens[1];
    //        break;
    //    }
    //    case 6:
    //    {
    //        SetTransforms(pTokens);
    //        mPath = pTokens[5];
    //        break;
    //    }
    //    case 10:
    //    {
    //        SetTransforms(pTokens);
    //        mPath = pTokens[9];
    //        break;
    //    }
    //    case 14:
    //    {
    //        SetTransforms(pTokens);
    //        mPath = pTokens[13];
    //        break;
    //    }
    //    default:
    //        // TODO: throw an exception
    //        break;
    //}

	vector<string>::iterator lItor = pTokens.begin();
	++lItor;
	while (lItor != pTokens.end())
	{
		if((*lItor)[0] == '-')
		{
			switch(lItor->at(1))
			{
			case 'o':
				lItor = SetOrigin(++lItor);
				break;
			case 's':
				lItor = SetScale(++lItor);
				break;
			case 't':
				lItor = SetTurbulence(++lItor);
				break;
			default:
				// TODO: throw an exception
				break;
			}
		}
		else
		{
			string lPath = *lItor++;
			while (lItor != pTokens.end())
			{
				lPath += " " + *lItor++;
			}
			mPath = lPath;
		}
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

double* ObjTex::GetOrigin()
{
	return mOrigin;
}

double* ObjTex::GetScale()
{
    return mScale;
}

double* ObjTex::GetTurbulence()
{
    return mTurbulence;
}


/* Protected Members */

//void ObjTex::SetTransforms(vector<string>& pTokens)
//{
//    string lOptions[3] = { "-s", "-o", "-t" };
//    double** lMembers = new double*[3] { mScale, mOrigin, mTurbulence };
//    vector<string>::iterator lBegin = pTokens.begin();
//    vector<string>::iterator lEnd = pTokens.end();
//    vector<string>::iterator lToken;
//
//    for (size_t i = 0; i < 3; ++i)
//    {
//        lToken = find(lBegin, lEnd, lOptions[i]);
//        if (lToken != lEnd) {
//            double* lArray = CreateArray(++lToken);
//            for (size_t j = 0; j < 3; ++j)
//                lMembers[i][j] = lArray[j];
//        }
//    }
//}

double* ObjTex::CreateArray(vector<string>::iterator& pItor)
{
    double* lArray = new double[3];

    for (size_t i = 0; i < 3; ++i)
        lArray[i] = stod(*pItor++);

    return lArray;
}

vector<string>::iterator ObjTex::SetOrigin(vector<string>::iterator& pItor)
{
	mOrigin = CreateArray(pItor);
	return pItor;
}

vector<string>::iterator ObjTex::SetScale(vector<string>::iterator& pItor)
{
	mScale = CreateArray(pItor);
	return pItor;
}

vector<string>::iterator ObjTex::SetTurbulence(vector<string>::iterator& pItor)
{
	mTurbulence = CreateArray(pItor);
	return pItor;
}
