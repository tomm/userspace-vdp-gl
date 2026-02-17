#include "HardwareSerial.h"
#include <chrono>
#include "freertos/FreeRTOS.h"

HardwareSerial Serial2;

// rust_glue.cpp
extern bool is_fabgl_terminating;

int HardwareSerial::available() {
	return m_buf_in.size();
}
int HardwareSerial::read() {
	if (m_buf_in.empty())
		return -1;
	uint8_t v = *m_buf_in.front();
	m_buf_in.pop();
	return v;
}
int HardwareSerial::peek() {
	if (m_buf_in.empty())
		return -1;
	return *m_buf_in.front();
}
bool HardwareSerial::readFromOutQueue(uint8_t *out) {
	if (m_buf_out.size()) {
		*out = *m_buf_out.front();
		m_buf_out.pop();
		return true;
	} else {
		return false;
	}
}
int HardwareSerial::readBytes(uint8_t *buffer, int len) {
	//auto start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	for (int i=0; i<len && !is_fabgl_terminating; i++) {
		while (!this->available()) {
			// Icky that this busy-waits, but let's break one thing at a time, eh
			//std::this_thread::sleep_for(std::chrono::microseconds(10));

			// if timeout
			//if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - start_time >= timeout_ms) {
				//return len;
			//}
		}
		buffer[i] = read();
	}
	return len;
}
size_t HardwareSerial::write(uint8_t c) {
	m_buf_out.push(c);
	return 1;
}
void HardwareSerial::writeToInQueue(uint8_t c) {
	// hard buffer limit of 2 x m_cts_threshold
	if (m_buf_in.size() < 2*m_cts_threshold) {
		m_buf_in.push(c);
	}
}
