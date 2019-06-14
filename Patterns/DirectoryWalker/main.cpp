#include <iostream>
#include "Filesystem/File.h"
#include "Filesystem/RecursiveDirectoryIterator.h"
#include "Filesystem/StraightDirectoryIterator.h"

int main(int argc, char* argv[])
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
    
    FileSystem::File file(path);
    FileSystem::RecursiveDirectoryIterator iter(file);
    
    while(iter != iter.end())
    {
        std::cout << iter->Path() << std::endl;
        ++iter;
    }
    return 0;
}