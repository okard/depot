#!/usr/bin/env bash
premake4 gmake
cd build
make $@
cd ..

