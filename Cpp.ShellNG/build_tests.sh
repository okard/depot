#!/usr/bin/env bash

./build.sh


# mkdir tests/bin/

#-Llibshellng/lib -lshellng
g++ -std=c++11 -Ilibshellng/include -Llibshellng/lib -lshellng -o tests/lexer tests/libshellng/lexer.cpp
