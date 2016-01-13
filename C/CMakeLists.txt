cmake_minimum_required(VERSION 3.2)
project(c)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -O2")

set(SOURCE_FILES main.c main.c WaveletTree.h BitVector.h Basic.h Utils.h WaveletTree.c BitVector.c Utils.c Tester.h Tester.c Timer.h Timer.c BatchTester.h BatchTester.c)
add_executable(c-wavelet-tree ${SOURCE_FILES})