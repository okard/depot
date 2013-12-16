#!/usr/bin/env bash

# Check for build directory
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# enter build directory
cd build

# CMAKE Debug Option
#-DCMAKE_BUILD_TYPE=Debug

# make or ninja build
if command -v ninja >/dev/null 2>&1; then
	cmake -G "Ninja" .. -DCMAKE_BUILD_TYPE=Debug
	ninja
else
	cmake -G "Unix Makefiles" ..
	make
fi



