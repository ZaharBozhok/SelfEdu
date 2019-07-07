#!/bin/bash

BUILD_DIR="bin"
CORES=$(grep -c ^processor /proc/cpuinfo)

mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR}
cmake ../src/
make "-j$CORES" 
