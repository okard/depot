# ShellNG - libshellng CMake
cmake_minimum_required(VERSION 2.8) 

project(libshellng)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

# Set up executable
file(GLOB_RECURSE LIBSHELLNG_SOURCES src/*.cpp)


# lexer gen via re2c
add_custom_target(re2c_lexer COMMAND re2c -o ${CMAKE_CURRENT_LIST_DIR}/src/Lexer_re2c.inc ${CMAKE_CURRENT_LIST_DIR}/src/Lexer.re WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
# parser gen via lemon
add_custom_target(lemon_parser COMMAND lemon -q ${CMAKE_CURRENT_LIST_DIR}/src/Parser.yy  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})


include_directories(include)
add_library(libshellng ${LIBSHELLNG_SOURCES})
add_dependencies(libshellng re2c_lexer lemon_parser) #lemon_parser
target_link_libraries(libshellng "uv")