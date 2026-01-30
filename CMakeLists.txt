cmake_minimum_required(VERSION 4.1)
project(ipc_library)

set(CMAKE_CXX_STANDARD 20)

add_library(ipc_library SHARED library.cpp)

target_include_directories(ipc_library PRIVATE /usr/x86_64-w64-mingw32/include)
target_include_directories(ipc_library PRIVATE /usr/lib/jvm/java-25-temurin/include)
target_include_directories(ipc_library PRIVATE /usr/lib/jvm/java-25-temurin/include/linux)