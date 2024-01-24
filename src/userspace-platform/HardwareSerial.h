#pragma once

#include <cstring>
#include <stdint.h>
#include <deque>
#include <mutex>
#include "Stream.h"

struct HardwareSerial: public Stream {
    HardwareSerial() {}
    HardwareSerial(int) {}

    int available() override;
    int read() override;
    size_t write(uint8_t) override;
    inline size_t write (uint8_t* buffer, size_t len)
    {
        for (int i=0;i<len;i++)
            write(buffer[i]);
        return len;
    }
    inline size_t write(const char * s)
    {
        return write((uint8_t*) s, strlen(s));
    }
    void end() {}
    void setRxBufferSize(int) {}
    void setHwFlowCtrlMode(uint8_t mode, uint8_t threshold = 64) {}   // 64 is half FIFO Length
    void begin(int, int, int, int) {}
    void setPins(int, int, int, int) {}
    void print(const char *) {}
    int availableForWrite() { return 1; }

    void writeToInQueue(uint8_t b);
    bool readFromOutQueue(uint8_t *out);
    

private:
    std::deque<uint8_t> m_buf_in;
    std::deque<uint8_t> m_buf_out;
    std::mutex m_lock_in;
    std::mutex m_lock_out;
};
