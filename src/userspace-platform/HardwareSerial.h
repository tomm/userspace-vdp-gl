#pragma once

#include <cstring>
#include <stdint.h>
#include "SPSCQueue.h"
#include <algorithm>
#include "Stream.h"

struct HardwareSerial: public Stream {
    HardwareSerial():
        timeout_ms(0),
        m_buf_in(512),
        m_buf_out(512)
    {}
    HardwareSerial(int):
        timeout_ms(0),
        m_buf_in(512),
        m_buf_out(512)
    {}

    int available() override;
    int read() override;
    int peek() override;
    size_t write(uint8_t) override;
    int readBytes(uint8_t *buffer, int len) override;
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
    void setTimeout(int t) { timeout_ms = t; }
    void setRxBufferSize(int) {}
    void setHwFlowCtrlMode(uint8_t mode, uint8_t threshold = 64) {
        m_cts_threshold = std::min((int)threshold, 128);
    }
    void begin(int, int, int, int) {}
    void setPins(int, int, int, int) {}
    void print(const char *) {}
    int availableForWrite() { return m_buf_out.size() < m_buf_out.capacity() ? 1 : 0; }

    void writeToInQueue(uint8_t b);
    bool readFromOutQueue(uint8_t *out);
    bool isReadyToReceive() { return available() < m_cts_threshold; }

private:
    rigtorp::SPSCQueue<uint8_t> m_buf_in;
    rigtorp::SPSCQueue<uint8_t> m_buf_out;
    int timeout_ms;
    int m_cts_threshold;
};
