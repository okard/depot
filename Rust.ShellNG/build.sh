#!/usr/bin/env bash


#rustnoise
gcc -Wall -W -Os -g -c -o linenoise.o src/rustnoise/linenoise.c
ar rs liblinenoise.a linenoise.o
rustc -g src/rustnoise/lib.rs

if [ $? -ne 0 ]; then
    exit
fi

#lib shellng
rustc -g -L . --crate-type=lib src/libshellng/lib.rs 

if [ $? -ne 0 ]; then
    exit
fi

#shellng
rustc -g -L . -o shellng src/shellng/main.rs

if [ $? -ne 0 ]; then
    exit
fi
