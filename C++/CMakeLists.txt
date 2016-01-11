cmake_minimum_required(VERSION 3.3)
project(WaveletTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp WaveletTree.cpp WaveletTree.h WaveletNode.cpp WaveletNode.h)
add_executable(WaveletTree ${SOURCE_FILES})