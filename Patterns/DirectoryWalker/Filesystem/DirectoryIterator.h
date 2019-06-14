#ifndef DIRECTORYITERATOR_H
#define DIRECTORYITERATOR_H

namespace FileSystem
{
    class File;
};

namespace FileSystem
{

class DirectoryIterator
{
public:
    virtual ~DirectoryIterator() {}
    virtual File& operator*() = 0;
    virtual File* operator->() = 0;
};

};
#endif //DIRECTORYITERATOR_H
