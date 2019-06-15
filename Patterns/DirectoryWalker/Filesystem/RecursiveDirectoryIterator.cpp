#include "RecursiveDirectoryIterator.h"

using namespace FileSystem;
#define topIt m_iterFrames.top()

RecursiveDirectoryIterator::RecursiveDirectoryIterator(): m_currentFile(nullptr), m_freshDir(nullptr)
{
}

const RecursiveDirectoryIterator& RecursiveDirectoryIterator::end()
{
    static RecursiveDirectoryIterator _end;
    return _end;
}

RecursiveDirectoryIterator::RecursiveDirectoryIterator(const File& root) : m_currentFile(nullptr), m_freshDir(nullptr)
{
    m_iterFrames.push(StraightDirectoryIterator(root));
    if(topIt != topIt.end())
    {
        getNextAtomic();
    }
    else
    {
        chopchop();
    }
}

File& RecursiveDirectoryIterator::operator*()
{
    return *m_currentFile;
}
File* RecursiveDirectoryIterator::operator->()
{
    return m_currentFile;
}

RecursiveDirectoryIterator::operator bool() const
{
    return (*this != end());
}

bool RecursiveDirectoryIterator::operator==(const RecursiveDirectoryIterator& val) const
{
    return m_iterFrames == val.m_iterFrames;
}
bool RecursiveDirectoryIterator::operator!=(const RecursiveDirectoryIterator& val) const
{
    return !(*this == val);
}
DirectoryIterator& RecursiveDirectoryIterator::operator++()
{
    getNext();
    return *this;
}

void RecursiveDirectoryIterator::chopchop()
{
    while (topIt == topIt.end())
    {
        m_iterFrames.pop();
        if(m_iterFrames.empty())
        {
            *this = end();
            return;
        }
        ++topIt;
    }
}

void RecursiveDirectoryIterator::getNextAtomic()
{
    if(*this != end())
    {
        m_currentFile = &(*topIt);
        if(File::IsDirectory(*m_currentFile))
        {
            m_iterFrames.push(*m_currentFile);
            m_freshDir = &(*topIt);
        }
    }
}

void RecursiveDirectoryIterator::getNext()
{
    if(nullptr != m_freshDir)
    {
        m_freshDir = nullptr;
        if(topIt != topIt.end())
        {
            getNextAtomic();
        }
        else
        {
            chopchop();
            getNextAtomic();
        }
    }
    else
    {
        ++topIt;
        if(topIt != topIt.end())
        {
            getNextAtomic();
        }
        else if(!m_iterFrames.empty())
        {
            chopchop();
            getNextAtomic();
        }
    }
}

#undef topIt