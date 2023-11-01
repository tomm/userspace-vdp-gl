#pragma once

#include "freertos/FreeRTOS.h"
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "HardwareSerial.h"

extern void init_userspace_fabgl();
extern void init_esp_ram();
extern void malloc_wrapper_dump_stats();

typedef uint8_t byte;
typedef uint16_t word;
typedef int lldesc_t;;
typedef void (*esp_timer_handle_t);
typedef int gpio_num_t;
typedef int gpio_mode_t;
#define GPIO_MAX 64
#define GPIO_NUM_33 0
#define GPIO_NUM_32 0
#define GPIO_NUM_26 0
#define GPIO_NUM_27 0
#define GPIO_NUM_MAX 64
typedef void(*intr_handler_t)(void *);
typedef void(*intr_handle_t)();
#define REG_WRITE(n,m)
#define REG_READ(n) 0
#define portMAX_DELAY 0
#define pdMS_TO_TICKS(n) (n)
#define xSemaphoreTake(n,m)
#define xSemaphoreGive(n)
#define portTICK_PERIOD_MS 1

#define GPIO_MODE_DISABLE 0
#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT 0
#define GPIO_MODE_OUTPUT_OD 0
#define GPIO_MODE_INPUT_OUTPUT_OD 0
#define GPIO_MODE_INPUT_OUTPUT 0

#define MALLOC_CAP_8BIT 1
#define MALLOC_CAP_32BIT 2
#define MALLOC_CAP_INTERNAL 4
#define MALLOC_CAP_DMA 8
#define MALLOC_CAP_SPIRAM 16
void *heap_caps_malloc(size_t, int);
//void *heap_caps_realloc(void *, size_t, int);
void *heap_caps_free(void *);
size_t heap_caps_get_largest_free_block(int);
int heap_caps_get_free_size(int);
#define gpio_get_level(n) 0
#define disableCore0WDT()
#define disableCore1WDT()
inline bool psramInit() { return true; }
inline void *ps_malloc(size_t sz) { return heap_caps_malloc(sz, MALLOC_CAP_8BIT); }

extern int64_t esp_timer_get_time();

// RTOS
typedef int TickType_t;

// ESP32
#define LOW 0
#define HIGH 1
void digitalWrite(int, int);

// ESP32Tim;
unsigned long millis();

// FABGL

// Integer square root by Halleck's method, with Legalize's speedup
int sqrt(int x);

#define SERIAL_8N1 0
#define HW_FLOWCTRL_RTS 0
extern struct HardwareSerial Serial2;

// New stuff for userspace vdp
extern "C" void z80_send_to_vdp(uint8_t b);

