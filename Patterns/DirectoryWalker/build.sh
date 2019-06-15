#!/bin/bash

BUILD_DIR="bin"

mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR}
cmake ../src/
make -j2 
