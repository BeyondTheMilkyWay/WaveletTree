cmake_minimum_required(VERSION 3.3)
project(WaveletTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp WaveletTree.cpp WaveletTree.h WaveletNode.cpp WaveletNode.h BitArray.cpp BitArray.h NullableObject.cpp NullableObject.h WaveletNodeNull.cpp WaveletNodeNull.h tests.cpp tests.h FastaParser.cpp FastaParser.h)
add_executable(WaveletTree ${SOURCE_FILES})