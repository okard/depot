
cmake_minimum_required(VERSION 2.8)
project(runner)


# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

# Set up executable
file(GLOB_RECURSE RUNNER_SOURCES src/*.cpp)
add_executable(runner ${RUNNER_SOURCES})
target_link_libraries(runner "sfml-system" "sfml-window" "sfml-graphics" "sfml-audio" )

