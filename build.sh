#!/bin/bash
set -e

BUILD_DIR=build
TARGET=Windows
ARCH=x86_64
JDK_PATH="/usr/lib/jvm/java-25-temurin"

mkdir -p $BUILD_DIR

cmake -S . -B $BUILD_DIR \
    -DCMAKE_SYSTEM_NAME=${TARGET} \
    -DCMAKE_C_COMPILER=${ARCH}-w64-mingw32-gcc \
    -DCMAKE_CXX_COMPILER=${ARCH}-w64-mingw32-g++ \
    -DJAVA_INCLUDE_PATH=${JDK_PATH}/include \
    -DJAVA_INCLUDE_PATH2=${JDK_PATH}/include/linux \
    -DCMAKE_BUILD_TYPE=Release

cmake --build $BUILD_DIR --config Release