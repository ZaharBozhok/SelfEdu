#ifndef FILEWRAPPER_H
#define FILEWRAPPER_H

#include "Writable.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>

class FileWrapper : public Writable
{
    public:
        FileWrapper(const std::string& path)
        {
            m_fd = open(path.c_str(), O_WRONLY | O_CREAT);
            if (-1 == m_fd)
            {
                throw std::runtime_error("Can't open file");
            }
        }
        bool Write(const std::vector<char>& data) override
        {
            ssize_t size = write(m_fd, data.data(), data.size());
            if (-1 == size)
            {
                return false;
            }
            return true;
        }
        bool Write(const std::string& str) override
        {
            ssize_t size = write(m_fd, str.data(), str.size());
            if (-1 == size)
            {
                return false;
            }
            return true;
        }
    private:
        int m_fd;
};

#endif //FILEWRAPPER_H