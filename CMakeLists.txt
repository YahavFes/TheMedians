cmake_minimum_required(VERSION 3.7)
project(TheMedians)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Parser.cpp)
add_executable(TheMedians ${SOURCE_FILES})