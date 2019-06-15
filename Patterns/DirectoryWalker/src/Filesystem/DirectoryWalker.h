#ifndef DIRECTORYWALKER_H
#define DIRECTORYWALKER_H

#include <functional>

namespace FileSystem
{

class File;
class DirectoryIterator;

class DirectoryWalker
{
public:
    DirectoryWalker(DirectoryIterator* iterator, const std::function<void(const File&)>& handler);
    void Walk();
private:
    DirectoryIterator* m_iterator;
    std::function<void(const File&)> m_handler;
};

};

#endif //DIRECTORYWALKER_H