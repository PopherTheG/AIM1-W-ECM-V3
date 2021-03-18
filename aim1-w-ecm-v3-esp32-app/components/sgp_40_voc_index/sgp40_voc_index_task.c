#include "sht4x.h"
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sensirion_sleep.h"
#include "sgp40_voc_index.h"
#include "sgp40_voc_index_task.h"
#include "cloud_api.h"
#include "cloud_mqtt.h"


static void sgp40_voc_index_task();

void sgp40_voc_index_start_task()
{
    xTaskCreate(sgp40_voc_index_task, "sgp40 voc index task", 1024 * 2, NULL, 2, NULL);
}

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
