#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include "Writable.h"
#include <string>

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define UNIX_PATH_MAX 4096

class SocketWrapper : public Writable
{
    public:
        SocketWrapper(const std::string& pathToSocket) : m_address({}), m_socketFd(-1)
        {
            m_socketFd = socket(PF_UNIX, SOCK_STREAM, 0);
            if (m_socketFd < 0)
            {
                throw std::runtime_error("Can't create socket");
            }
            m_address.sun_family = AF_UNIX;
            strcpy(m_address.sun_path, pathToSocket.c_str());
            if (connect(m_socketFd, (sockaddr*)&m_address, sizeof(sockaddr_un)) != 0)
            {
                throw std::runtime_error("Can't connect to socket");
            }
        }
        bool Write(const std::vector<char>& data) override
        {
            if (-1 == write(m_socketFd, data.data(), data.size()))
            {
                return false;
            }
            return true;
        }
        bool Write(const std::string& str) override
        {
            if (-1 == write(m_socketFd, str.data(), str.size()))
            {
                return false;
            }
            return true;
        }
        ~SocketWrapper()
        {
            close(m_socketFd);
        }
    private:
        sockaddr_un m_address;
        int m_socketFd;
};

#endif //SOCKETWRAPPER_H