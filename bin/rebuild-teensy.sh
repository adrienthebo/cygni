#!/bin/bash

rm -rf build
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/teensy-arm.toolchain.cmake ..
make
