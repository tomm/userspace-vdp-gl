#include "Stream.h"
#include "freertos/FreeRTOS.h"

int Stream::readBytes(uint8_t *buffer, int len) {
	for (int i=0; i<len; i++) {
		while (!this->available()) {
			vTaskDelay(1);
		}
		buffer[i] = read();
	}
	return len;
}
