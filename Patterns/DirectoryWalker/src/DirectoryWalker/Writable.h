#ifndef WRITABLE_H
#define WRITABLE_H

#include <vector>

struct Writable
{
    virtual bool Write(const std::vector<char>& data) = 0;
};

#endif //WRITABLE_H