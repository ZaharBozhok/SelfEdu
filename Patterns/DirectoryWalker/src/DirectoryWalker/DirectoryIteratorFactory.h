#ifndef DIRECTORYITERATORFACTORY
#define DIRECTORYITERATORFACTORY

#include "DirectoryIterator.h"
#include "StraightDirectoryIterator.h"
#include "RecursiveDirectoryIterator.h"
#include "File.h"

class DirectoryIteratorFactory
{
    public:
    enum class IteratorType : char
    {
        STRAIGHT = 's',
        RECURSIVE = 'r'
    };
    public:
    static FileSystem::DirectoryIterator* CreateIterator(const IteratorType& type, const std::string& path)
    {
        switch (type)
        {
        case IteratorType::STRAIGHT:
            return new FileSystem::StraightDirectoryIterator(FileSystem::File(path));
            break;
        case IteratorType::RECURSIVE:
            return new FileSystem::RecursiveDirectoryIterator(FileSystem::File(path));
            break;
        default:
        throw std::runtime_error("Can't create iterator of that type");
            break;
        }
    }
};

#endif //DIRECTORYITERATORFACTORY