#include "HardwareSerial.h"
#include <stdio.h>
#include <mutex>
#include <chrono>
#include "freertos/FreeRTOS.h"

HardwareSerial Serial2;

int HardwareSerial::available() {
	std::unique_lock<std::mutex> lock(m_lock_in);
	return m_buf_in.size();
}
int HardwareSerial::read() {
	std::unique_lock<std::mutex> lock(m_lock_in);
	if (m_buf_in.empty())
		return -1;
	uint8_t v = m_buf_in.front();
	m_buf_in.pop_front();
	return v;
}
int HardwareSerial::peek() {
	std::unique_lock<std::mutex> lock(m_lock_in);
	if (m_buf_in.empty())
		return -1;
	uint8_t v = m_buf_in.front();
	return v;
}
bool HardwareSerial::readFromOutQueue(uint8_t *out) {
	std::unique_lock<std::mutex> lock(m_lock_out);
	if (m_buf_out.size()) {
		*out = m_buf_out.front();
		m_buf_out.pop_front();
		return true;
	} else {
		return false;
	}
}
int HardwareSerial::readBytes(uint8_t *buffer, int len) {
	//auto start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	for (int i=0; i<len; i++) {
		while (!this->available()) {
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
	std::unique_lock<std::mutex> lock(m_lock_out);
	m_buf_out.push_back(c);
	return 1;
}
void HardwareSerial::writeToInQueue(uint8_t c) {
	std::unique_lock<std::mutex> lock(m_lock_in);
	// hard buffer limit of 16
	if (m_buf_in.size() < 16) {
		m_buf_in.push_back(c);
	}
}
