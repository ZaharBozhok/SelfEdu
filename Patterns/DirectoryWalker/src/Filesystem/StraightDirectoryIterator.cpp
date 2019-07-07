#include "StraightDirectoryIterator.h"
#include <string.h>

using namespace FileSystem;

StraightDirectoryIterator::StraightDirectoryIterator() : m_dir(nullptr), m_dirent(nullptr)
{

}

StraightDirectoryIterator::operator bool() const
{
    return (*this != end());
}

bool StraightDirectoryIterator::operator==(const StraightDirectoryIterator& val) const
{
    return  m_iterableDir.Path() ==  val.m_iterableDir.Path() &&
            m_currentFile.Path() == val.m_currentFile.Path() &&
            m_dir == val.m_dir &&
            m_dirent == val.m_dirent;
}
bool StraightDirectoryIterator::operator!=(const StraightDirectoryIterator& val) const
{
    return !(*this == val);
}
File* StraightDirectoryIterator::operator->()
{
    return &m_currentFile;
}

StraightDirectoryIterator StraightDirectoryIterator::end()
{
    static StraightDirectoryIterator _end;
    return _end;
}

StraightDirectoryIterator::StraightDirectoryIterator(const File& file) : m_iterableDir(file), m_dir(nullptr), m_dirent(nullptr)
{
    openDir();
    skipDots();
    getNext();
}

File& StraightDirectoryIterator::operator*()
{
    return m_currentFile;
}

DirectoryIterator& StraightDirectoryIterator::operator++()
{
    getNext();
    return *this;
}

void StraightDirectoryIterator::openDir()
{
    m_dir = opendir(m_iterableDir.Path().c_str());
    if (NULL == m_dir)
    {
        throw std::runtime_error("Can't opendir");
    }
}

void StraightDirectoryIterator::skipDots()
{
    m_dirent = readdir(m_dir);
    m_dirent = readdir(m_dir);
}

void StraightDirectoryIterator::getNext()
{
    m_dirent = readdir(m_dir);
    if (NULL == m_dirent)
    {
        *this = end();
        return;
    }
    std::string pathToFile = m_iterableDir.Path() + "/" + m_dirent->d_name;
    if (m_dirent->d_type & DT_DIR)
    {
        m_currentFile = File(pathToFile, S_IFDIR);
    }
    else
    {
        m_currentFile = File(pathToFile);
    }
}