#!/usr/bin/env bash

#rustnoise
gcc -Wall -W -Os -g -c -o linenoise.o src/rustnoise/linenoise.c
ar rs liblinenoise.a linenoise.o
rustc -g src/rustnoise/lib.rs

if [ $? -ne 0 ]; then
    exit
fi

rustc -g -L . src/rustnoise/example.rs -o rustnoise_example.bin
if [ $? -ne 0 ]; then
    exit
fi


rustc -g -L . --test src/libshellng/lib.rs -o libshellng_tests.bin
if [ $? -ne 0 ]; then
    exit
fi

./libshellng_tests.bin
