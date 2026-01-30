#!/bin/bash
set -e
BUILD_DIR=build
mkdir -p $BUILD_DIR
cmake -S . -B $BUILD_DIR -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++
cmake --build $BUILD_DIR