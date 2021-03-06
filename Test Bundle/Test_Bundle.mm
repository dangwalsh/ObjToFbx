//
//  Test_Bundle.m
//  Test Bundle
//
//  Created by Daniel Walsh on 7/17/16.
//  Copyright © 2016 Daniel Walsh. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <fbxsdk.h>
#import "../ObjToFbx/Geometry/ObjFace.h"
#include "../ObjToFbx/Io/ObjReaderFacade.h"
#include "../ObjToFbx/Utilities/SdkTools.h"

@interface Test_Bundle : XCTestCase

@end

@implementation Test_Bundle

int          gRegisteredCount;
int          gPluginId;
const char*  gFileName = "texture_test.xobj";
FbxManager*  gSdkManager = NULL;
FbxScene*    gScene = NULL;

void sdkInit() {
    InitializeSdkObjects(gSdkManager, gScene);
    gSdkManager->GetIOPluginRegistry()->RegisterReader(CreateObjReader, GetObjReaderInfo, gPluginId, gRegisteredCount, FillObjReaderIOSettings);
}

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    XCTAssert(YES, @"Well this is awkward.");
}

- (void)testImportInit {
    sdkInit();
    FbxImporter* lImporter = FbxImporter::Create(gSdkManager, "");
    XCTAssertTrue(lImporter->Initialize(gFileName, -1, gSdkManager->GetIOSettings()));
}

- (void)testImport {
    sdkInit();
    FbxImporter* lImporter = FbxImporter::Create(gSdkManager, "");
    lImporter->Initialize(gFileName, -1, gSdkManager->GetIOSettings());
    XCTAssertTrue(lImporter->Import(gScene));
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
