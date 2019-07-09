#ifndef WRITABLE_H
#define WRITABLE_H

#include <vector>

struct Writable
{
    virtual bool Write(const std::vector<char>& data) = 0;
    virtual bool Write(const std::string& str) = 0;
};

#endif //WRITABLE_H