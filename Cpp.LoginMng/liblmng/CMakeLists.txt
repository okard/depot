# liblmng cmake
cmake_minimum_required(VERSION 2.8)

project(nlogin)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

# set up sources
file(GLOB_RECURSE LIBLMNG_SOURCES src/*.cpp)

# add include dir
include_directories("include")

# create library
add_library(lmng ${LIBLMNG_SOURCES})
#target_link_libraries()
