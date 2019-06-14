#ifndef RECURSIVEDIRECTORYITERATOR_H
#define RECURSIVEDIRECTORYITERATOR_H

#include <stack>
#include "DirectoryIterator.h"
#include "StraightDirectoryIterator.h"

namespace FileSystem
{
class RecursiveDirectoryIterator : public DirectoryIterator
{
private:
    RecursiveDirectoryIterator();
public:
    RecursiveDirectoryIterator(const File& root);
    File& operator*() override;
    File* operator->() override;
    bool operator==(const RecursiveDirectoryIterator& val) const;
    bool operator!=(const RecursiveDirectoryIterator& val) const;
    RecursiveDirectoryIterator& operator++();
public:
    static const RecursiveDirectoryIterator& end();
private:
    void getNext();
    void getNextAtomic();
    void chopchop();
private:
    File* m_currentFile;
    File* m_freshDir;
    std::stack<FileSystem::StraightDirectoryIterator> m_iterFrames;
};
};



#endif //RECURSIVEDIRECTORYITERATOR_H