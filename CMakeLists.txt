cmake_minimum_required(VERSION 3.5.0)

project(setservostik LANGUAGES CXX)
# The version number.
set (SETSERVOSTICK_MAJOR 1)
set (SETSERVOSTICK_MINOR 0)
set (SETSERVOSTICK_PATCH 1)

set(CMAKE_CXX_STANDARD 14)

# Use customized cmake macros
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
find_package(LibUSB REQUIRED)


# configure a header file to pass some of the CMake settings to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/SetServoConfig.h.in"
        "${PROJECT_BINARY_DIR}/SetServoConfig.h"
)
# add the binary tree to the search path for include files so that we will find SetServoConfig.h
include_directories("${PROJECT_BINARY_DIR}")


add_subdirectory(src)
