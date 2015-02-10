#!/usr/bin/env bash


gcc -Wall -W -Os -g -c -o $OUT_DIR/linenoise.o src/linenoise.c
ar rs $OUT_DIR/liblinenoise.a $OUT_DIR/linenoise.o

