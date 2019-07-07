#include "DirectoryWalker.h"
#include <File.h>
#include <DirectoryIterator.h>

DirectoryWalker::DirectoryWalker(fs::DirectoryIterator* iterator, const std::function<void(const fs::File&)>& handler)
    : m_iterator(iterator)
    , m_handler(handler)
{

}

void DirectoryWalker::Walk()
{
    while (*m_iterator)
    {
        if (m_handler)
        {
            m_handler(*(*m_iterator));
        }
        ++(*m_iterator);
    }
}
