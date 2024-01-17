#pragma once

typedef int esp_err_t;
typedef int esp_ota_handle_t;
typedef int esp_partition_type_t;
typedef int esp_partition_subtype_t;
typedef struct {
    void* flash_chip;                   /*!< SPI flash chip on which the partition resides */
    esp_partition_type_t type;          /*!< partition type (app/data) */
    esp_partition_subtype_t subtype;    /*!< partition subtype */
    uint32_t address;                   /*!< starting address of the partition in flash */
    uint32_t size;                      /*!< size of the partition, in bytes */
    char label[17];                     /*!< partition label, zero-terminated ASCII string */
    bool encrypted;                     /*!< flag is set to true if partition is encrypted */
} esp_partition_t;

#define esp_ota_get_running_partition(p) 0
#define esp_ota_get_next_update_partition(p) 0
#define esp_ota_set_boot_partition(p) 0
#define esp_ota_write(a,b,c) 0
#define esp_ota_begin(a,b,c) 0
#define esp_restart()
#define esp_reset_reason() 0
#define ESP_OK 0
#define ESP_RST_SW 1
#define esp_ota_get_boot_partition() 0
#define esp_ota_get_app_partition_count() 0
