#ifndef STRINGTOWRITABLEADAPTER_H
#define STRINGTOWRITABLEADAPTER_H

#include "WritablesFactory.h"

WritablesFactory::WritableType GetWritable(int argc, char* argv[])
{
    if (argc >= 4)
    {
        switch (argv[3][0])
        {
            case 's':
                return WritablesFactory::WritableType::STDOUT;
                break;
            case 'f':
                return WritablesFactory::WritableType::FILE;
                break;
            case 'u':
                return WritablesFactory::WritableType::UNIXDOMAINSOCKET;
                break;
            default:
                throw std::runtime_error("Unknown writable type");
                break;
        }
    }
    return WritablesFactory::WritableType::STDOUT;
}

#endif //STRINGTOWRITABLEADAPTER_H