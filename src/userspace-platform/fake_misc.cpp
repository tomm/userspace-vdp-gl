#include "fake_fabgl.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <unordered_map>

//#define LIMIT_ESP32_RAM

bool is_fabgl_terminating = false;

// a guess, and does not consider memory types
#define HEAP_SIZE 220632

static size_t _s_total_allocd = 0;
static std::unordered_map<void *, size_t> _s_allocs;

static void dump_mem_stats()
{
	printf("Heap used: %ld, remaining %ld of %ld\n", _s_total_allocd, HEAP_SIZE - _s_total_allocd, (long)HEAP_SIZE);
}

void *heap_caps_malloc(size_t sz, int) {
	void *p = malloc(sz);
#ifdef LIMIT_ESP32_RAM
	_s_total_allocd += sz;
	_s_allocs[p] = sz;
	dump_mem_stats();
#endif /* LIMIT_ESP32_RAM */
	return p;
}
/*
void *heap_caps_realloc(void *ptr, size_t sz, int) {
	return realloc(ptr, sz);
}
*/
void *heap_caps_free(void *ptr) {
#ifdef LIMIT_ESP32_RAM
	auto iter = _s_allocs.find(ptr);
	if (iter != _s_allocs.end()) {
		_s_total_allocd -= iter->second;
		_s_allocs.erase(iter);
	}
	dump_mem_stats();
#endif /* LIMIT_ESP32_RAM */
	free(ptr);
	return ptr;
}
size_t heap_caps_get_largest_free_block(int sz) {
	return sz;
}
int heap_caps_get_free_size(int) {
	return 1024*1024;
}

int esp_timer_get_time() {
	return 0;
}

/* Arduino.h */
void delay(int ms) {
	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	} while (is_fabgl_terminating);
}

unsigned long millis() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int sqrt(int x) {
	return (int)sqrtf((float)x);
}

void digitalWrite(int, int) {}

/* FreeRTOS */
int xTaskCreatePinnedToCore(TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, void *const pvParameters, int uxPriority, TaskHandle_t *const pvCreatedTask, const int xCoreID)
{
	return xTaskCreate(pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pvCreatedTask);
}

int xTaskCreate(TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, void *const pvParameters, int uxPriority, TaskHandle_t *const pvCreatedTask)
{
	//printf("Spawning thread %s...\n", pcName);
	auto t = std::thread(pvTaskCode, pvParameters);
	t.detach();

	// XXX A horrible workaround. pvParameters can be a pointer to
	// local vars in the caller, which will be GONE by the time std::thread starts.
	// So wait around a bit in the hope that the thread gets going
	// before we wipe its arguments... :wince:
	delay(1);

	return 0;
}

void vTaskDelay(int n)
{
	// n isn't ms, but whatever
	delay(n);
}
