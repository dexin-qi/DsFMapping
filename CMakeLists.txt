cmake_minimum_required(VERSION 3.2)
project(dsfmapping)

set(DsFM_VERSION_MAJOR  1)
set(DsFM_VERSION_MINOR  0)
set(DsFM_VERSION_PATCH  0)
set(DsFM_VERSION ${DsFM_VERSION_MAJOR}.${DsFM_VERSION_MINOR}.${DsFM_VERSION_PATCH})

option(BUILD_TEST "build DsFMapping test" true)

find_package(Abseil REQUIRED)
find_package(PCL REQUIRED QUIET COMPONENTS common)
find_package(Boost REQUIRED QUIET)
find_package(Ceres REQUIRED QUIET COMPONENTS SuiteSparse)
find_package(Eigen3 REQUIRED QUIET)
find_package(LuaGoogle REQUIRED QUIET)
find_package(Protobuf 3.0.0 REQUIRED QUIET)
find_package(OpenCV 3.2 REQUIRED QUIET)

