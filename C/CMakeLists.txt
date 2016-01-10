cmake_minimum_required(VERSION 3.2)
project(C)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c main.c WaveletTree.h BitVector.h Basic.h Utils.h WaveletTree.c BitVector.c Utils.c Tester.h Tester.c)
add_executable(C ${SOURCE_FILES})