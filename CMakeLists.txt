cmake_minimum_required(VERSION 3.12)
project(setservostik)
set(CMAKE_CXX_STANDARD 14)

add_executable(setservostik setservostik.cpp)
target_link_libraries(setservostik usb-1.0)

install(TARGETS setservostik DESTINATION bin)