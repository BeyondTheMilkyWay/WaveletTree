cmake_minimum_required(VERSION 3.3)
project(C)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c main.c wavelet-tree.h)
add_executable(C ${SOURCE_FILES})