#include <iostream>
#include <File.h>
#include <RecursiveDirectoryIterator.h>
#include <StraightDirectoryIterator.h>
#include "DirectoryWalker.h"
#include "StreamWrapper.h"
#include "SocketWrapper.h"
#include <vector>
#include <fstream>
#include <memory>
#include "WritablesFactory.h"
#include "DirectoryIteratorFactory.h"

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
DirectoryIteratorFactory::IteratorType GetIterator(int argc, char* argv[])
{
    if(argc >= 3)
    {
        char i = 0;
        i = argv[2][0];
        if(i == 's')
        {
            return DirectoryIteratorFactory::IteratorType::STRAIGHT;
        }
        else if(i == 'r')
        {
            return DirectoryIteratorFactory::IteratorType::RECURSIVE;
        }
        else
        {
            throw std::runtime_error("Unknown iterrator type");
        }
    }
    return DirectoryIteratorFactory::IteratorType::STRAIGHT;
}

WritablesFactory::WritableType GetWritable(int argc, char* argv[])
{
    if(argc >= 4)
    {
        switch (argv[3][0])
        {
        case 's':
            return WritablesFactory::WritableType::STDOUT;
            break;
        case 'f':
            return WritablesFactory::WritableType::FILE;
            break;
        case 'u':
            return WritablesFactory::WritableType::UNIXDOMAINSOCKET;
            break;
        default:
            throw std::runtime_error("Unknown writable type");
            break;
        }
    }
    return WritablesFactory::WritableType::STDOUT;
}
};

int main(int argc, char* argv[])
{
    try
    {
        std::unique_ptr<fs::DirectoryIterator> dirIter(DirectoryIteratorFactory::CreateIterator(GetIterator(argc,argv), GetPath(argc, argv)));
        std::unique_ptr<Writable> writable(WritablesFactory::CreateWritable(GetWritable(argc,argv)));

        DirectoryWalker directoryWalker(dirIter.get(),
                                        [&writable](const fs::File& file)
        {
            std::vector<char> buff(file.Name().cbegin(), file.Name().cend());
            buff.push_back('\n');
            writable->Write(buff);
        }
                                       );
        directoryWalker.Walk();
        return 0;
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return -1;

}