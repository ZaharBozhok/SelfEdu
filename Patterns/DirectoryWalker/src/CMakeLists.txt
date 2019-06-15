cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

#SET(VERSION "0.1" CACHE STRING "Option")

project("DirWalker")
message(STATUS "Name: ${PROJECT_NAME}")
#message(STATUS "Version: ${PROJECT_VERSION}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O0")

#libs
add_subdirectory(FileSystem)

#bins
add_subdirectory(DirectoryWalker)