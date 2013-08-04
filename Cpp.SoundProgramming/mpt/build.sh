#!/usr/bin/env bash

# Check for build directory
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

#enter build directory
cd build

# debug

# clang
#export CC=/usr/bin/clang
#export CXX=/usr/bin/clang++


# make or ninja build
if command -v ninja >/dev/null 2>&1; then
	cmake -DCMAKE_BUILD_TYPE=Debug  -G "Ninja" ..
	ninja
else
	cmake -DCMAKE_BUILD_TYPE=Debug  -G "Unix Makefiles" ..
	make
fi




