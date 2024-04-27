#pragma once

#include <climits>
#include <cstdint>
#include <thread>

// RTOS
typedef uint64_t TickType_t;
typedef int BaseType_t;

#define pdPASS 1

typedef void TaskFunction_t(void *);
typedef void *TaskHandle_t;
typedef void *QueueHandle_t;
typedef std::thread *TimerHandle_t;
typedef void *SemaphoreHandle_t;
extern BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, void *const pvParameters, int uxPriority, TaskHandle_t *const pvCreatedTask);
extern BaseType_t xTaskCreatePinnedToCore(TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, void *const pvParameters, int uxPriority, TaskHandle_t *const pvCreatedTask, const int xCoreID);
extern void vTaskDelay(int);
extern TickType_t xTaskGetTickCountFromISR();
#define xPortGetCoreID() 0
#define vTaskDelete(n)
#define xTaskGetCurrentTaskHandle() 0
#define vTaskResume(n)
#define xSemaphoreCreateMutex() 0
#define xTimerDelete(a,b)
#define xTimerStart(a,b)
#define vQueueDelete(a)
#define vSemaphoreDelete(a)
#define xQueueCreate(a,b) 0
#define xQueueSendToFront(a,b,c)
#define xQueueSendToBack(a,b,c)
#define xTaskAbortDelay(a)
#define uxQueueMessagesWaiting(q) 0
#define xQueueReceive(a,b,c)
#define xQueueReset(q)
