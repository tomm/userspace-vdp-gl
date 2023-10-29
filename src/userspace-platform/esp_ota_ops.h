#pragma once

typedef int esp_err_t;
typedef int esp_ota_handle_t;
typedef int esp_partition_t;

#define esp_ota_get_running_partition(p) 0
#define esp_ota_get_next_update_partition(p) 0
#define esp_ota_set_boot_partition(p) 0
#define esp_ota_write(a,b,c) 0
#define esp_ota_begin(a,b,c) 0
#define esp_restart()
#define esp_reset_reason() 0
#define ESP_OK 0
#define ESP_RST_SW 1
