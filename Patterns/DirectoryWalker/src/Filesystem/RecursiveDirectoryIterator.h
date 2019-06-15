#ifndef RECURSIVEDIRECTORYITERATOR_H
#define RECURSIVEDIRECTORYITERATOR_H

#include <stack>
#include "DirectoryIterator.h"
#include "StraightDirectoryIterator.h"

namespace FileSystem
{
class RecursiveDirectoryIterator : public DirectoryIterator
{
public:
    RecursiveDirectoryIterator(const File& root);
    File& operator*() override;
    File* operator->() override;
    explicit operator bool() const override;
    DirectoryIterator& operator++() override;
    bool operator==(const RecursiveDirectoryIterator& val) const;
    bool operator!=(const RecursiveDirectoryIterator& val) const;
public:
    static const RecursiveDirectoryIterator& end();
private:
    RecursiveDirectoryIterator();
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