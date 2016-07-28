project(ObjToFbx_Tests)

include_directories(../Vendor/googletest/include ../Vendor/googletest)

add_executable(runBasicTests BasicTest.cpp)

target_link_libraries(runBasicTests gtest gtest_main)
