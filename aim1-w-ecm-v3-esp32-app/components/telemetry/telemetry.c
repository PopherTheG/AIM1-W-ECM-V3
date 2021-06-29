#include <string.h>
#include <time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_log.h"

#include "telemetry_protocol.h"
#include "telemetry_encoder.h"
#include "telemetry.h"
#include "cloud_api.h"
#include "cloud_mqtt.h"
#include "sgp40_voc_index_task.h"

#define TELEMETRY_STACK 3072
#define TELEMETRY_PRIORITY 2
#define TELEMETRY_QUEUE_LEN 10

#define TAG "telemetry"
#define TELEMETRY_LOCK(_mutex) xSemaphoreTake(_mutex, portMAX_DELAY)
#define TELEMETRY_UNLOCK(_mutex) xSemaphoreGive(_mutex)
#define SCALE_10X(__float_num) (__float_num * 10) s

static uint16_t reqNo = 1;
static SemaphoreHandle_t xTelemetryGuard;
static QueueHandle_t xTelemetryQueue = NULL;
static TaskHandle_t xTelemetryTask;
static SemaphoreHandle_t xTelemetrySemph;
static TimerHandle_t xSgp40sht4xTimer = NULL;

static uint64_t telemetry_id;

static const uint16_t crc_table[256] = {0x0000, 0x1021, 0x2042, 0x3063, 0x4084,
                                        0x50a5, 0x60c6, 0x70e7, 0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad,
                                        0xe1ce, 0xf1ef, 0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7,
                                        0x62d6, 0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
                                        0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 0xa56a,
                                        0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 0x3653, 0x2672,
                                        0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 0xb75b, 0xa77a, 0x9719,
                                        0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 0x48c4, 0x58e5, 0x6886, 0x78a7,
                                        0x0840, 0x1861, 0x2802, 0x3823, 0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948,
                                        0x9969, 0xa90a, 0xb92b, 0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50,
                                        0x3a33, 0x2a12, 0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b,
                                        0xab1a, 0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
                                        0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 0x7e97,
                                        0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 0xff9f, 0xefbe,
                                        0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 0x9188, 0x81a9, 0xb1ca,
                                        0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 0x1080, 0x00a1, 0x30c2, 0x20e3,
                                        0x5004, 0x4025, 0x7046, 0x6067, 0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d,
                                        0xd31c, 0xe37f, 0xf35e, 0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214,
                                        0x6277, 0x7256, 0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c,
                                        0xc50d, 0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
                                        0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 0x26d3,
                                        0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 0xd94c, 0xc96d,
                                        0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 0x5844, 0x4865, 0x7806,
                                        0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e,
                                        0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1,
                                        0x1ad0, 0x2ab3, 0x3a92, 0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b,
                                        0x9de8, 0x8dc9, 0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0,
                                        0x0cc1, 0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
                                        0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0};

static uint16_t _CRC16(const uint8_t *data, size_t length, uint16_t seed, uint16_t final)
{
    size_t count;
    unsigned int crc = seed;
    unsigned int temp;
    for (count = 0; count < length; ++count)
    {
        temp = (*data++ ^ (crc >> 8)) & 0xff;
        crc = crc_table[temp] ^ (crc << 8);
    }
    return (uint16_t)(crc ^ final);
}

static void vSgp40sht4xTimerCallback(TimerHandle_t xTimer)
{
    static telemtery_msg_t sensor_update = {
        .id = TELEMETRY_SENSOR,
    };
    xQueueSendToBack(xTelemetryQueue, &sensor_update, 10);
}

static void telemetry_task(void *pdata)
{
    static uint8_t telemetry_buffer[128];
    sgp40_sht4x_sensor_t sgp40_sht4x_data;

    while (1)
    {
        telemtery_msg_t msg;
        xQueueReceive(xTelemetryQueue, &msg, portMAX_DELAY);

        ESP_LOGI(TAG, "Telemetry Queue Task! %d", msg.id);

        if (msg.id == TELEMETRY_TASK_STOP)
        {
            break;
        }
        else if (msg.id == TELEMETRY_TASK_LOG)
        {
        }
        else if (msg.id == TELEMETRY_SENSOR)
        {
            ESP_LOGI(TAG, "Telemetry Sensor!");
            sgp40_sht4x_get_data(&sgp40_sht4x_data);
            telemetry_sgp40_sht4x_t *sgp40_sht4x_telemetry = (telemetry_sgp40_sht4x_t *)telemetry_buffer;
            sgp40_sht4x_telemetry->type = TELEMETRY_TYPE_SENSOR;
            sgp40_sht4x_telemetry->device_type = 5;
            sgp40_sht4x_telemetry->serial = telemetry_id;
            sgp40_sht4x_telemetry->temperature = (int16_t)sgp40_sht4x_data.temperature;
            sgp40_sht4x_telemetry->humidity = (int16_t)sgp40_sht4x_data.relative_humidity;
            sgp40_sht4x_telemetry->voc_index =(int16_t)sgp40_sht4x_data.voc_index;
            sgp40_sht4x_telemetry->timestamp = telemetry_timestamp_generate();

            uint16_t *crc = (uint16_t *)&telemetry_buffer[sizeof(telemetry_sgp40_sht4x_t)];
            *crc = _CRC16(telemetry_buffer, sizeof(telemetry_sgp40_sht4x_t), 0xffff, 0x00);
            cloud_api_send(telemetry_buffer, sizeof(telemetry_sgp40_sht4x_t) + 2);
        }
        else if (msg.id == TELEMETRY_AIRQLTY)
        {
            /* Implement all air quality data to be sent including options that are not optional */
            // ESP_LOGI(TAG, "Telemetry Air Quality!");
            // airqlty_get_data(&airqlty_data);
            // telemetry_airqlty_t *airqlty_telemetry = (telemetry_airqlty_t*)telemetry_buffer;
            // airqlty_telemetry->type = TELEMETRY_TYPE_SENSOR;
            // airqlty_telemetry->device_type = 5;
            // airqlty_telemetry->serial = telemetry_id;
            // airqlty_telemetry->temperature = (int16_t)airqlty_data.temperature;
            // airqlty_telemetry->temperature = (int16_t)airqlty_data.temperature;
            // airqlty_telemetry->temperature = (int16_t)airqlty_data.temperature;

        }
    }
    xSemaphoreGive(xTelemetrySemph);
    vTaskDelete(NULL);
}

void telemetry_init(void)
{
    xTelemetryGuard = xSemaphoreCreateMutex();
    configASSERT(xTelemetryGuard);

    xTelemetryQueue = xQueueCreate(TELEMETRY_QUEUE_LEN, sizeof(telemtery_msg_t));
    configASSERT(xTelemetryQueue);

    /* TODO:  */
    xSgp40sht4xTimer = xTimerCreate("sgp40 sht4x timer", pdMS_TO_TICKS(30 * 1000), pdTRUE, NULL, vSgp40sht4xTimerCallback);
    configASSERT(xSgp40sht4xTimer != NULL);
}

void telemetry_sgp40sht4x_timer_start(void)
{
    ESP_LOGI(TAG, "SGP40 SHT4x Timer START!");
    xTimerStart(xSgp40sht4xTimer, 0);
}

void telemetry_sgp40sht4x_timer_stop(void)
{
    ESP_LOGI(TAG, "SGP40 SHT4x Timer STOP!");
    xTimerStop(xSgp40sht4xTimer, 0);
}

void telemetry_deinit(void)
{
    xTimerStop(xSgp40sht4xTimer, portMAX_DELAY);
    xTimerDelete(xSgp40sht4xTimer, portMAX_DELAY);
}

void telemetry_start(uint64_t *id)
{
    configASSERT(id != NULL);
    telemetry_id = *id;
    xTaskCreate(telemetry_task, "telemetry-task", TELEMETRY_STACK, NULL, TELEMETRY_PRIORITY, &xTelemetryTask);
}

void telemetry_stop(void)
{
    xTelemetrySemph = xSemaphoreCreateBinary();
    xTimerStop(xSgp40sht4xTimer, portMAX_DELAY);

    const telemtery_msg_t stop_msg = {
        .id = TELEMETRY_TASK_STOP};

    if (xQueueSendToBack(xTelemetryQueue, &stop_msg, pdMS_TO_TICKS(100) == pdPASS))
    {
        xSemaphoreTake(xTelemetrySemph, portMAX_DELAY);
    }
    else
    {
        ESP_LOGE(TAG, "Failed to send stop message.");
    }

    vSemaphoreDelete(xTelemetrySemph);
    vQueueDelete(xTelemetryQueue);
}

telemetry_err_t telemetry_notify_log(uint8_t device_type)
{
    const telemtery_msg_t user_log = {
        .id = TELEMETRY_TASK_LOG,
        .data = device_type};

    if (xQueueSendToFront(xTelemetryQueue, &user_log, pdMS_TO_TICKS(10)) == pdPASS)
    {
        return TELEMETRY_OK;
    }
    return TELEMETRY_ERR;
}
