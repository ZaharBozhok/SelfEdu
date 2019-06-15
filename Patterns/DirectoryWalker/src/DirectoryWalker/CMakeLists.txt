add_executable(DirectoryWalker
    main.cpp
)

target_link_libraries(DirectoryWalker
    PRIVATE FileSystemLib
)