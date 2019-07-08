#ifndef STRINGTOITERATORADAPTER_H
#define STRINGTOITERATORADAPTER_H

#include "DirectoryIteratorFactory.h"

DirectoryIteratorFactory::IteratorType GetIterator(int argc, char* argv[])
{
    if (argc >= 3)
    {
        char i = 0;
        i = argv[2][0];
        if (i == 's')
        {
            return DirectoryIteratorFactory::IteratorType::STRAIGHT;
        }
        else if (i == 'r')
        {
            return DirectoryIteratorFactory::IteratorType::RECURSIVE;
        }
        else
        {
            throw std::runtime_error("Unknown iterrator type");
        }
    }
    return DirectoryIteratorFactory::IteratorType::STRAIGHT;
}

#endif //STRINGTOITERATORADAPTER_H