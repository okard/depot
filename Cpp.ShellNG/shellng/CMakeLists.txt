# ShellNG - shellng executable CMake
cmake_minimum_required(VERSION 2.8) 

project(shellng)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

# Set up executable
file(GLOB_RECURSE SHELLNG_SOURCES src/*.cpp)


include_directories(${CMAKE_SOURCE_DIR}/deps/linenoise)
set(LINENOISE_SOURCES ${CMAKE_SOURCE_DIR}/deps/linenoise/linenoise.c)

include_directories(${CMAKE_SOURCE_DIR}/libshellng/include)
add_executable(shellng ${SHELLNG_SOURCES} ${LINENOISE_SOURCES})
target_link_libraries(shellng libshellng)