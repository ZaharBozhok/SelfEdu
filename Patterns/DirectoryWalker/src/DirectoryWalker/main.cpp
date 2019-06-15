#include <iostream>
#include <File.h>
#include <RecursiveDirectoryIterator.h>
#include <StraightDirectoryIterator.h>
#include <DirectoryWalker.h>

namespace fs = FileSystem;

namespace
{
std::string GetPath(int argc, char* argv[])
{
    std::string path;
    if(argc == 1)
    {
        path = argv[0];
        auto pos = path.rfind('/');
        if(pos != std::string::npos)
        {
            path = path.substr(0, pos);
        }
    }
    else
    {
        path = argv[1];
    }
    return path;
}
};

int main(int argc, char* argv[])
{
    std::string path = GetPath(argc, argv);

    fs::File file(path);
    fs::RecursiveDirectoryIterator recursiveIter(file);
    fs::StraightDirectoryIterator straightIter(file);

    fs::DirectoryWalker directoryWalker(&straightIter,
        [](const fs::File& file)
        {
            std::cout << file.Name() << std::endl;
        }
    );
    directoryWalker.Walk();

    return 0;
}