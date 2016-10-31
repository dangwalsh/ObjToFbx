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
#include "../Exceptions/VectorException.h"

using namespace std;

/* Public Members - Constructors */

ObjTex::ObjTex(vector<string>& pTokens)
{
    mScale = new double[3] { 1.0, 1.0, 1.0 };
    mOrigin = new double[3] { 0.0, 0.0, 0.0 };
	mTurbulence = new double[3]{ 0.0, 0.0, 0.0 };

	ParseTokens(pTokens);
}

ObjTex::~ObjTex()
{
	delete mOrigin;
	delete mScale;
	delete mTurbulence;
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

void ObjTex::ParseTokens(vector<string>& pTokens)
{
	vector<string>::iterator lItor = pTokens.begin() + 1;

	while (lItor != pTokens.end())
	{
		if ((*lItor)[0] == '-')
		{
			switch (lItor->at(1))
			{
			case 'o':
				SetOrigin(++lItor);
				break;
			case 's':
				SetScale(++lItor);
				break;
			case 't':
				SetTurbulence(++lItor);
				break;
			default:
				string error = "Texture option '" + *lItor + "' not specified.";
				throw new VectorException(error.c_str());
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

void ObjTex::SetOrigin(vector<string>::iterator& pItor)
{
	mOrigin = ConvertToDoubleArray(pItor);
}

void ObjTex::SetScale(vector<string>::iterator& pItor)
{
	mScale = ConvertToDoubleArray(pItor);
}

void ObjTex::SetTurbulence(vector<string>::iterator& pItor)
{
	mTurbulence = ConvertToDoubleArray(pItor);
}

double* ObjTex::ConvertToDoubleArray(vector<string>::iterator& pItor)
{
	double* lArray = new double[3];

	for (size_t i = 0; i < 3; ++i)
		lArray[i] = stod(*pItor++);

	return lArray;
}
