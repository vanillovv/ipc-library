#!/bin/bash
INCLUDE_DIR="/usr/lib/jvm/java-25-temurin/include"
x86_64-w64-mingw32-g++ -shared -I"$INCLUDE_DIR" -I"$INCLUDE_DIR/linux" -o library.dll library.cpp -static-libgcc -static-libstdc++ -Wl,--add-stdcall-alias