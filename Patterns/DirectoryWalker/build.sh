#!/bin/bash

BUILD_DIR="bin"
CORES=$(grep -c ^processor /proc/cpuinfo)

mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR}
cmake -D CMAKE_C_COMPILER=gcc-8 -D CMAKE_CXX_COMPILER=g++-8 ../src/
make "-j$CORES" 
