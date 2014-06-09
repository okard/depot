#!/usr/bin/env bash

rustc -g --test src/libshellng/lib.rs -o libshellng_tests.bin
if [ $? -ne 0 ]; then
    exit
fi

./libshellng_tests.bin
