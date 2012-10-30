
# nlogin CMake
cmake_minimum_required(VERSION 2.8)

project(nlogin)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

# Set up executable
file(GLOB_RECURSE NLOGIN_SOURCES src/*.cpp)

# add liblmng to include dir
include_directories(${CMAKE_SOURCE_DIR}/liblmng/include)

# executable and link 
add_executable(nlogin ${NLOGIN_SOURCES})
target_link_libraries(nlogin lmng "ncurses")
