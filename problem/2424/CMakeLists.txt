cmake_minimum_required(VERSION 3.5.0)
project(main)
set(CMAKE_CXX_STANDARD 11)


set(CMAKE_BUILD_TYPE Debug)
include_directories(${CMAKE_SOURCE_DIR})
add_executable(main main.cpp)

