/*
 * Copyright (c) 2020, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "svm40.h"
#include "sensirion_sleep.h"
#include "svm40_git_version.h"

/* ESP32 related includes */
#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/i2c.h"
#include "driver/rmt.h"
/* end */

#define TAG "SVM40"

void svm40_start_task()
{
    xTaskCreate(svm40_task, "svm40 task", 1024 * 2, NULL, 2, NULL);
}

static void svm40_task()
{
    int16_t error;
    char serial_id[SVM40_MAX_SERIAL_LEN];

    const char *driver_version = svm40_get_driver_version();
    if (driver_version)
    {
        printf("SVM40 driver version %s\n", driver_version);
    }
    else
    {
        printf("fatal: Getting driver version failed\n");
    }

    /* Initialize I2C bus */
    sensirion_i2c_init();

    while (svm40_probe() != 0)
    {
        printf("SVM40 sensor probing failed\n");
        sensirion_sleep_usec(1000000); /* wait 1s */
    }
    printf("SVM40 sensor probing successful\n");

    error = svm40_get_serial(serial_id);
    if (error != NO_ERROR)
    {
        printf("Error reading SVM40 serial: %i\n", error);
    }
    else
    {
        printf("Serial Number: %s\n", serial_id);
    }

    struct svm40_version_information version_information;
    error = svm40_get_version(&version_information);
    if (error)
    {
        printf("Error reading SVM40 version: %i\n", error);
    }
    else
    {
        if (version_information.firmware_debug)
        {
            printf("Development firmware version: ");
        }
        printf("FW: %u.%u, HW: %u.%u, protocol: %u.%u\n",
               version_information.firmware_major,
               version_information.firmware_minor,
               version_information.hardware_major,
               version_information.hardware_minor,
               version_information.protocol_major,
               version_information.protocol_minor);

        // check if firmware is older than 2.2
        if (version_information.firmware_major < 2 ||
            (version_information.firmware_major == 2 &&
             version_information.firmware_minor < 2))
        {
            printf("Warning: Old firmware version which may return constant "
                   "values after a few hours of operation\n");
        }
    }

    error = svm40_start_continuous_measurement();
    if (error)
    {
        printf("Error starting measurement: %i\n", error);
    }

    while (1)
    {
        int16_t voc_index;
        int16_t relative_humidity;
        int16_t temperature;
        sensirion_sleep_usec(SVM40_MEASUREMENT_INTERVAL_USEC); /* wait 1s */
        error = svm40_read_measured_values_as_integers(
            &voc_index, &relative_humidity, &temperature);
        if (error)
        {
            ESP_LOGE(TAG, "SVM40: Error reading measurement values: %i", error);
        }
        else
        {
            ESP_LOGI(TAG, "SVM30: Measured values\n"
                          "\t%.1f\n"
                          "\t%.2f%%\n"
                          "\t%.2f°C\n",
                     voc_index / 10.0f, relative_humidity / 100.0f, temperature / 200.0f);
            /* storing results in global variable */
            SVM40_VOC = voc_index / 10.0f;
            SVM40_HUM = relative_humidity / 100.0f;
            SVM40_TEMP = temperature / 200.0f;
        }
    }
}

const char* svm40_get_driver_version(void) {
    return SVM40_DRV_VERSION_STR;
}

int16_t svm40_get_serial(char* serial) {
    int16_t error;

    error =
        sensirion_i2c_write_cmd(SVM40_I2C_ADDRESS, SVM40_CMD_GET_SERIAL_NUMBER);
    if (error != NO_ERROR) {
        return error;
    }
    sensirion_sleep_usec(SVM40_CMD_DELAY);
    error = sensirion_i2c_read_words_as_bytes(
        SVM40_I2C_ADDRESS, (uint8_t*)serial,
        SVM40_MAX_SERIAL_LEN / SENSIRION_WORD_SIZE);
    if (error != NO_ERROR) {
        return error;
    }
    serial[SVM40_MAX_SERIAL_LEN - 1] = '\0';
    return NO_ERROR;
}

int16_t svm40_probe(void) {
    struct svm40_version_information version_information;
    return svm40_get_version(&version_information);
}

int16_t svm40_start_continuous_measurement(void) {
    int16_t error;
    error = sensirion_i2c_write_cmd(SVM40_I2C_ADDRESS,
                                    SVM40_CMD_START_CONTINUOUS_MEASUREMENT);
    sensirion_sleep_usec(SVM40_CMD_DELAY);
    return error;
}

int16_t svm40_stop_measurement(void) {
    int16_t error;
    error =
        sensirion_i2c_write_cmd(SVM40_I2C_ADDRESS, SVM40_CMD_STOP_MEASUREMENT);
    sensirion_sleep_usec(SVM40_STOP_MEASUREMENT_DELAY);
    return error;
}

int16_t svm40_read_measured_values_as_integers(int16_t* voc_index,
                                               int16_t* relative_humidity,
                                               int16_t* temperature) {
    int16_t error;
    int16_t buffer[3];
    error = sensirion_i2c_write_cmd(SVM40_I2C_ADDRESS,
                                    SVM40_CMD_READ_MEASURED_VALUES_AS_INTEGERS);
    if (error) {
        return error;
    }
    sensirion_sleep_usec(SVM40_CMD_DELAY);

    error = sensirion_i2c_read_words(SVM40_I2C_ADDRESS, (uint16_t*)buffer,
                                     SENSIRION_NUM_WORDS(buffer));
    if (error) {
        return error;
    }

    *voc_index = buffer[0];
    *relative_humidity = buffer[1];
    *temperature = buffer[2];

    return NO_ERROR;
}

int16_t svm40_read_measured_values_as_integers_with_raw_params(
    int16_t* voc_index, int16_t* relative_humidity, int16_t* temperature,
    uint16_t* voc_ticks_raw, int16_t* uncompensated_relative_humidity,
    int16_t* uncompensated_temperature) {
    int16_t error;
    uint16_t buffer[6];

    error = sensirion_i2c_write_cmd(
        SVM40_I2C_ADDRESS,
        SVM40_CMD_READ_MEASURED_VALUES_AS_INTEGERS_WITH_RAW_PARAMETERS);
    if (error) {
        return error;
    }
    sensirion_sleep_usec(SVM40_CMD_DELAY);

    error = sensirion_i2c_read_words(SVM40_I2C_ADDRESS, buffer,
                                     SENSIRION_NUM_WORDS(buffer));
    if (error) {
        return error;
    }

    *voc_index = (int16_t)buffer[0];
    *relative_humidity = (int16_t)buffer[1];
    *temperature = (int16_t)buffer[2];
    *voc_ticks_raw = buffer[3];
    *uncompensated_relative_humidity = (int16_t)buffer[4];
    *uncompensated_temperature = (int16_t)buffer[5];

    return NO_ERROR;
}

int16_t
svm40_get_version(struct svm40_version_information* version_information) {
    int16_t error;
    uint8_t buffer[8];
    error = sensirion_i2c_write_cmd(SVM40_I2C_ADDRESS, SVM40_CMD_GET_VERSION);
    if (error) {
        return error;
    }

    sensirion_sleep_usec(SVM40_CMD_DELAY);

    error = sensirion_i2c_read_words_as_bytes(SVM40_I2C_ADDRESS, buffer,
                                              SENSIRION_NUM_WORDS(buffer));

    if (error) {
        return error;
    }

    version_information->firmware_major = buffer[0];
    version_information->firmware_minor = buffer[1];
    version_information->firmware_debug = buffer[2];
    version_information->hardware_major = buffer[3];
    version_information->hardware_minor = buffer[4];
    version_information->protocol_major = buffer[5];
    version_information->protocol_minor = buffer[6];
    // the last byte is a padding byte

    return NO_ERROR;
}

int16_t svm40_device_reset(void) {
    int16_t error;
    error = sensirion_i2c_write_cmd(SVM40_I2C_ADDRESS, SVM40_CMD_DEVICE_RESET);
    sensirion_sleep_usec(SVM40_DEVICE_RESET_DELAY);
    return error;
}
