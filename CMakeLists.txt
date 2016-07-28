cmake_minimum_required(VERSION 3.5)
project(ObjToFbx)

find_library(CARBON_LIBRARY Carbon)
find_library(SYSTEMCONFIGURATION_LIBRARY SystemConfiguration)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(INCLUDES /usr/local/include ObjToFbx ObjToFbx_Tests Vendor/googletest)
set(LIBRARIES /usr/local/lib/libfbxsdk.dylib)
set(FRAMEWORKS ${CARBON_LIBRARY} ${SYSTEMCONFIGURATION_LIBRARY})

set(SOURCE_FILES
    ObjToFbx/Exceptions/SdkException.cxx
    ObjToFbx/Exceptions/SdkException.h
    ObjToFbx/Geometry/ObjFace.cxx
    ObjToFbx/Geometry/ObjFace.h
    ObjToFbx/Geometry/ObjGroup.cxx
    ObjToFbx/Geometry/ObjGroup.h
    ObjToFbx/Geometry/ObjMaterial.cxx
    ObjToFbx/Geometry/ObjMaterial.h
    ObjToFbx/Geometry/ObjScene.cxx
    ObjToFbx/Geometry/ObjScene.h
    ObjToFbx/Io/ObjReader.cxx
    ObjToFbx/Io/ObjReader.h
    ObjToFbx/Io/ObjReaderFacade.cxx
    ObjToFbx/Io/ObjReaderFacade.h
    ObjToFbx/Utilities/GeometryTools.cxx
    ObjToFbx/Utilities/GeometryTools.h
    ObjToFbx/Utilities/SdkTools.cxx
    ObjToFbx/Utilities/SdkTools.h
    ObjToFbx/Utilities/StringTools.cxx
    ObjToFbx/Utilities/StringTools.h
    ObjToFbx/main.cxx
    Google\ Test/gtest-all.cc
    ObjToFbx_Tests/BasicTest.cpp)

add_executable(ObjToFbx ${SOURCE_FILES})
include_directories(${INCLUDES})

add_subdirectory(Vendor/googletest)
add_subdirectory(ObjToFbx_Tests)

target_link_libraries(ObjToFbx ${LIBRARIES} ${FRAMEWORKS})