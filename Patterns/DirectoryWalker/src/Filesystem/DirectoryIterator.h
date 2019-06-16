#ifndef DIRECTORYITERATOR_H
#define DIRECTORYITERATOR_H

namespace FileSystem
{
class File;
};

namespace FileSystem
{

struct DirectoryIterator
{
    virtual ~DirectoryIterator() {}
    virtual File& operator*() = 0;
    virtual File* operator->() = 0;
    explicit virtual operator bool() const = 0;
    virtual DirectoryIterator& operator++() = 0;
};

};
#endif //DIRECTORYITERATOR_H
