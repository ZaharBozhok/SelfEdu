#ifndef STREAMWRAPPER_H
#define STREAMWRAPPER_H

#include "Writable.h"
#include <ostream>
#include <vector>

class StreamWrapper : public Writable
{
    public:
        StreamWrapper(std::ostream& stream) : m_stream(stream)
        {

        }
        bool Write(const std::vector<char>& data) override
        {
            m_stream.write(data.data(), data.size());
            //checking badbit failbit
            return true;
        }
    private:
        std::ostream& m_stream;
};

#endif //STREAMWRAPPER_H