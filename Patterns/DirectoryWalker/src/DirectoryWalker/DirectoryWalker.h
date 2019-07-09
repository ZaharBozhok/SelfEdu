#ifndef DIRECTORYWALKER_H
#define DIRECTORYWALKER_H

#include <functional>

namespace FileSystem
{
    class File;
    class DirectoryIterator;
};

namespace fs = FileSystem;

class DirectoryWalker
{
    public:
        DirectoryWalker(fs::DirectoryIterator* iterator, const std::function<void(fs::File&)>& handler);
        void Walk();
    private:
        fs::DirectoryIterator* m_iterator;
        std::function<void(fs::File&)> m_handler;
};



#endif //DIRECTORYWALKER_H