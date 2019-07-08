cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("DirWalker")
message(STATUS "Name: ${PROJECT_NAME}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O0 -ggdb")

#libs
add_subdirectory(Filesystem)

#bins
add_subdirectory(DirectoryWalker)
add_subdirectory(SocketCreator)