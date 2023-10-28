#pragma once

#include <cstdlib>
#include <cstdint>

class Stream {
    public:
    virtual ~Stream() {}
    virtual int available() = 0;
    virtual int read() = 0;
    virtual size_t write(uint8_t) = 0;
    virtual int readBytes(uint8_t *buffer, int len);
};
