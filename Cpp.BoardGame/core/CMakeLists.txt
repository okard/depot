#########################################
# Main cmake file
#########################################
cmake_minimum_required(VERSION 2.8)

project(core)

include_directories(include)

set(core_src
    src/Token.cpp
    src/Board.cpp
    src/Game.cpp
    src/Player.cpp
)


add_library(core ${core_src})