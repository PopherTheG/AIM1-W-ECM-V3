#include "sht4x.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sensirion_sleep.h"
#include "sgp40_voc_index.h"
#include "sgp40_voc_index_task.h"
#include "cloud_api.h"
#include "cloud_mqtt.h"

#include "freertos/semphr.h"
#include "esp_log.h"
#include "telemetry.h"

#define TAG "sgp40_voc_index_task.c"
#define MUTEX_TIMEOUT_MS 50
#define MUTEX_LOCK() xSemaphoreTake(mutex, pdMS_TO_TICKS(MUTEX_TIMEOUT_MS))
#define MUTEX_UNLOCK() xSemaphoreGive(mutex)

static sgp40_sht4x_sensor_t cur_data;
static SemaphoreHandle_t mutex;
static uint8_t run_flag = 0;
static uint8_t data_ready = 0;

static void sgp40_voc_index_task(void *arg);

void sgp40_voc_index_start_task()
{
    xTaskCreate(sgp40_voc_index_task, "sgp40 voc index task", 1024 * 2, NULL, 2, NULL);
}

static void sgp40_voc_index_task(void *arg)
{
    (void)arg;
    int32_t voc_index;
    int32_t temperature_celsius;
    int32_t relative_humidity_percent;
    int16_t err;

    while ((err = sensirion_init_sensors()))
    {
        printf("Initialization failed: %d\n", err);
        sensirion_sleep_usec(1000000); /* wait one second */
    }
    printf("Initialization successful\n");

    memset(&cur_data, 0, sizeof(cur_data));
    data_ready = 0;
    mutex = xSemaphoreCreateMutex();
    configASSERT(mutex != NULL);
    ESP_LOGI(TAG, "SGP40 SHT4x Ready!");

    telemetry_sgp40sht4x_timer_start();

    while (1)
    {
        err = sensirion_measure_voc_index_with_rh_t(&voc_index, &relative_humidity_percent, &temperature_celsius); /* int32 int32 int32 */
        if (err == STATUS_OK)
        {
            data_ready = 1;
            cur_data.relative_humidity = relative_humidity_percent;
            cur_data.temperature = temperature_celsius;
            cur_data.voc_index = voc_index;
            printf("VOC Index: %i\n", voc_index);
            printf("Temerature: %.04fdegC\n", temperature_celsius * 0.001f);
            printf("Relative Humidity: %.03f%%RH\n",
                   relative_humidity_percent * 0.001f);
            SGP40_VOC = voc_index; /* For GUI purposes */
            SHT4X_TEMP = temperature_celsius * 0.001f; /* For GUI purposes */
            SHT4X_HUM = relative_humidity_percent * 0.001f; /* For GUI purposes */
        }
        else
        {
            printf("error reading signal: %d\n", err);
        }
        sensirion_sleep_usec(1000000); /* wait one second */
        // data_ready = 0;
    }
    vTaskDelete(NULL);
    telemetry_sgp40sht4x_timer_stop();
}

void sgp40_sht4x_get_data(sgp40_sht4x_sensor_t *data)
{
    if (data_ready)
    {
        MUTEX_LOCK();
        data->relative_humidity = cur_data.relative_humidity;
        data->temperature = cur_data.temperature;
        data->voc_index = cur_data.voc_index;
        MUTEX_UNLOCK();
    }
}

#if 0
static void sgp40_voc_index_task()
{
    int32_t voc_index;
    int32_t temperature_celsius;
    int32_t relative_humidity_percent;
    int16_t err;

    /* Initialize I2C bus, SHT, SGPm and VOC Engine*/
        while ((err = sensirion_init_sensors()))
        {
            printf("Initialization failed: %d\n", err);
            sensirion_sleep_usec(1000000); /* wait one second */
        }
        printf("Initialization successful\n");

        /* Run one measurement per second */
        while (1)
        {
            err = sensirion_measure_voc_index_with_rh_t(
                &voc_index, &relative_humidity_percent, &temperature_celsius);
            if (err == STATUS_OK)
            {
                printf("VOC Index: %i\n", voc_index);
                printf("Temerature: %.04fdegC\n", temperature_celsius * 0.001f);
                printf("Relative Humidity: %.03f%%RH\n",
                       relative_humidity_percent * 0.001f);
                SGP40_VOC = voc_index;
                SHT4X_TEMP = temperature_celsius * 0.001f;
                SHT4X_HUM = relative_humidity_percent * 0.001f;
                // uint8_t sample_data = 25;
                // cloud_mqtt_publish("xeleqt/aim1-w-ecm/hardware/voc", (uint8_t *)sample_data, 1, 0);
            }
            else
            {
                printf("error reading signal: %d\n", err);
            }
            sensirion_sleep_usec(1000000); /* wait one second */
        }
    }
#endif
