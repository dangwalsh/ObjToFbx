//
//  GeometryTools.cpp
//  ObjToFbx
//
//  Created by Daniel Walsh on 7/25/16.
//  Copyright © 2016 Daniel Walsh. All rights reserved.
//

#include "GeometryTools.h"

FbxVector4 CalculateNormal(FbxVector4& a, FbxVector4& b, FbxVector4& c)
{
    FbxVector4 norm = (b-a).CrossProduct(c-a);
    norm.Normalize();
    return norm;
}
