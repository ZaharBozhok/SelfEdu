add_executable(DirectoryWalker
    main.cpp
    DirectoryWalker.cpp
)

target_link_libraries(DirectoryWalker
    PRIVATE FileSystemLib
)