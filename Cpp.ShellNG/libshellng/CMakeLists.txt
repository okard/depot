# ShellNG - libshellng CMake
cmake_minimum_required(VERSION 2.8) 

project(libshellng)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

# Set up sources
file(GLOB_RECURSE LIBSHELLNG_SOURCES src/*.cpp)


#include dir
include_directories(include)

# set up the static library
add_library(libshellng STATIC ${LIBSHELLNG_SOURCES})
set_target_properties(libshellng PROPERTIES OUTPUT_NAME "shellng")
target_link_libraries(libshellng "uv")

# set up dynamic library
#add_library(libshellng SHARED ${LIBSHELLNG_SOURCES})

# copy lib to folder
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib/)
get_target_property(LIBSHELLNG_LIB libshellng LOCATION)
add_custom_command(TARGET libshellng POST_BUILD COMMAND cp ARGS ${LIBSHELLNG_LIB} ${CMAKE_CURRENT_LIST_DIR}/lib/)

