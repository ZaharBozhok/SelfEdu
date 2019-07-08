#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils
{
    static std::string GetPath(int argc, char* argv[])
    {
        std::string path;
        if (argc == 1)
        {
            path = argv[0];
            auto pos = path.rfind('/');
            if (pos != std::string::npos)
            {
                path = path.substr(0, pos);
            }
        }
        else
        {
            path = argv[1];
        }
        return path;
    }
};

#endif //UTILS_H