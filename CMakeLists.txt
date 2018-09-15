cmake_minimum_required(VERSION 3.5.0)

project(setservostik LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

# Use customized cmake macros
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
find_package(LibUSB REQUIRED)

# find_program(
#   CLANG_TIDY_EXE
#   NAMES "clang-tidy"
#   DOC "Path to clang-tidy executable"
# )
# if(NOT CLANG_TIDY_EXE)
#   message(STATUS "clang-tidy not found.")
# else()
#   message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
#   set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*;-warnings-as-errors=*")
# endif()

add_subdirectory(src)

