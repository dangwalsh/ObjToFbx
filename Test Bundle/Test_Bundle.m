//
//  Test_Bundle.m
//  Test Bundle
//
//  Created by Daniel Walsh on 7/17/16.
//  Copyright © 2016 Daniel Walsh. All rights reserved.
//

#import <XCTest/XCTest.h>

@interface Test_Bundle : XCTestCase

@end

@implementation Test_Bundle

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

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
