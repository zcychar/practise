cmake_minimum_required(VERSION 3.10)
project(code)

set(CMAKE_CXX_STANDARD 17)

# 自动添加所有的源文件
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
