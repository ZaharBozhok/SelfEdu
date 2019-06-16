#ifndef WRITABLESFACTORY_H
#define WRITABLESFACTORY_H

#include "Writable.h"
#include "StreamWrapper.h"
#include "SocketWrapper.h"
#include "FileWrapper.h"

class WritablesFactory
{
    public:
    enum class WritableType : char 
    {
        STDOUT = 's',
        FILE = 'f',
        UNIXDOMAINSOCKET = 'u'
    };
    public:
    WritablesFactory() = default;
    static Writable* CreateWritable(const WritableType& type)
    {
        switch (type)
        {
        case WritableType::STDOUT:
            return new StreamWrapper(std::cout);
            break;
        case WritableType::FILE:
            return new FileWrapper("./DirectoryWalker.txt");
            break;
        case WritableType::UNIXDOMAINSOCKET:
            return new SocketWrapper("/tmp/directorywalker.socket");
            break;
        default:
            throw std::runtime_error("No such type of writale");
            break;
        }
    }
};

#endif //WRITABLESFACTORY_H
