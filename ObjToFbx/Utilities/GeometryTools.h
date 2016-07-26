//
//  GeometryTools.hpp
//  ObjToFbx
//
//  Created by Daniel Walsh on 7/25/16.
//  Copyright © 2016 Daniel Walsh. All rights reserved.
//

#ifndef GeometryTools_h
#define GeometryTools_h

#include <fbxsdk.h>
#include "../Geometry/ObjFace.h"

class ObjFace;

FbxVector4 CalculateNormal(FbxVector4& a, FbxVector4& b, FbxVector4& c);

#endif /* GeometryTools_h */
