add_library(FileSystemLib STATIC
    File.cpp
    StraightDirectoryIterator.cpp
    RecursiveDirectoryIterator.cpp
    DirectoryWalker.cpp
)

target_include_directories(FileSystemLib
    PUBLIC .
)