//
//  ObjFaceTest.cpp
//  ObjToFbx
//
//  Created by Daniel Walsh on 7/17/16.
//  Copyright © 2016 Daniel Walsh. All rights reserved.
//

#include <string>
#include <gtest/gtest.h>
#include "Geometry/ObjFace.h"

TEST(ObjFace, BasicTest) {
    std::string s = ObjFace::GetString();
    EXPECT_EQ("Hello Test!\n", s);
}
