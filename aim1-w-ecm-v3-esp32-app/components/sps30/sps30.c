/*
 * Copyright (c) 2018, Sensirion AG
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

#include "sps30.h"
#include "sensirion_shdlc.h"
#include "sensirion_uart_hal.h"
#include "sps_git_version.h"
#include "sensirion_common.h"

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

#define TAG "SPS30"

#define SPS30_ADDR 0x00
#define SPS30_CMD_START_MEASUREMENT 0x00
#define SPS30_CMD_STOP_MEASUREMENT 0x01
#define SPS30_SUBCMD_MEASUREMENT_START \
    {                                  \
        0x01, 0x03                     \
    }
#define SPS30_CMD_READ_MEASUREMENT 0x03
#define SPS30_CMD_SLEEP 0x10
#define SPS30_CMD_WAKE_UP 0x11
#define SPS30_CMD_FAN_CLEAN_INTV 0x80
#define SPS30_CMD_FAN_CLEAN_INTV_LEN 5
#define SPS30_SUBCMD_READ_FAN_CLEAN_INTV 0x00
#define SPS30_CMD_START_FAN_CLEANING 0x56
#define SPS30_CMD_DEV_INFO 0xd0
#define SPS30_CMD_DEV_INFO_SUBCMD_GET_SERIAL \
    {                                        \
        0x03                                 \
    }
#define SPS30_CMD_READ_VERSION 0xd1
#define SPS30_CMD_RESET 0xd3
#define SPS30_ERR_STATE(state) (SPS30_ERR_STATE_MASK | (state))

void sps30_start_task()
{
    xTaskCreate(sps30_task, "sps30 task", 1024 * 4, NULL, 2, NULL);
}

static void sps30_task()
{
    struct sps30_measurement m;
    char serial[SPS30_MAX_SERIAL_LEN];
    const uint8_t AUTO_CLEAN_DAYS = 4;
    int16_t ret;

    while (sensirion_uart_open() != 0)
    {
        ESP_LOGE(TAG, "UART init failed");
        sensirion_sleep_usec(1000000); /* sleep for 1s */
    }

    /* Busy loop for initialization, because the main loop does not work without
     * a sensor.
     */
    while (sps30_probe() != 0)
    {
        ESP_LOGE(TAG, "SPS30: Sensor probing failed");
        sensirion_sleep_usec(1000000); /* sleep for 1s */
    }
    ESP_LOGI(TAG, "SPS30: Sensor probing successful");

    struct sps30_version_information version_information;
    ret = sps30_read_version(&version_information);
    if (ret)
    {
        ESP_LOGE(TAG, "SPS30: Error %d reading version information", ret);
    }
    else
    {
        ESP_LOGI(TAG, "SPS30: FW - %u.%u, HW - %u, SHDLC - %u.%u",
                 version_information.firmware_major,
                 version_information.firmware_minor,
                 version_information.hardware_revision,
                 version_information.shdlc_major,
                 version_information.shdlc_minor);
    }

    ret = sps30_get_serial(serial);
    if (ret)
        ESP_LOGE(TAG, "SPS30: Error %d reading serial", ret);
    else
        ESP_LOGI(TAG, "SPS30: Serial - %s", serial);

    ret = sps30_set_fan_auto_cleaning_interval_days(AUTO_CLEAN_DAYS);
    if (ret)
        ESP_LOGE(TAG, "SPS30: Error %d setting the auto-clean interval", ret);

    while (1)
    {
        ret = sps30_start_measurement();
        if (ret < 0)
        {
            ESP_LOGE(TAG, "SPS30: Error starting measurement");
        }

        ESP_LOGI(TAG, "SPS30: Measurements started");

        for (int i = 0; i < 60; ++i)
        {

            ret = sps30_read_measurement(&m);
            if (ret < 0)
            {
                ESP_LOGE(TAG, "SPS30: Error reading measurements");
            }
            else
            {
                if (SPS30_IS_ERR_STATE(ret))
                {
                    ESP_LOGW(TAG, "SPS30: Chip State %u - measurements may not be accurate",
                             SPS30_GET_ERR_STATE(ret));
                }

                /* Output measured data from SPS30 */
                ESP_LOGI(TAG, "SPS30: Measured Values\n"
                              "\t%0.2f pm1.0\n"
                              "\t%0.2f pm2.5\n"
                              "\t%0.2f pm4.0\n"
                              "\t%0.2f pm10.0\n"
                              "\t%0.2f nc0.5\n"
                              "\t%0.2f nc1.0\n"
                              "\t%0.2f nc2.5\n"
                              "\t%0.2f nc4.5\n"
                              "\t%0.2f nc10.0\n"
                              "\t%0.2f typical particle size\n\n",
                         m.mc_1p0, m.mc_2p5, m.mc_4p0, m.mc_10p0, m.nc_0p5,
                         m.nc_1p0, m.nc_2p5, m.nc_4p0, m.nc_10p0,
                         m.typical_particle_size);

                /* storing results */
                SPS30_PM2_5 = m.mc_2p5;
                SPS30_PM10 = m.mc_10p0;
            }
            sensirion_sleep_usec(1000000); /* sleep for 1s */
        }

        /* Stop measurement for 1min to preserve power. Also enter sleep mode
         * if the firmware version is >=2.0.
         */
        ret = sps30_stop_measurement();
        if (ret)
        {
            ESP_LOGE(TAG, "SPS30: Stopping measurement failed");
        }

        if (version_information.firmware_major >= 2)
        {
            ret = sps30_sleep();
            if (ret)
            {
                ESP_LOGE(TAG, "SPS30: Entering sleep failed");
            }
        }

        ESP_LOGI(TAG, "SPS30: No measurements for 1 minute");
        sensirion_sleep_usec(1000000 * 60); /* adjustment for sleep time */

        if (version_information.firmware_major >= 2)
        {
            ret = sps30_wake_up();
            if (ret)
            {
                // printf("Error %i waking up sensor\n", ret);
                ESP_LOGE(TAG, "SPS30: Error %i waking up sensor", ret);
            }
        }
    }
    if (sensirion_uart_close() != 0)
        ESP_LOGE(TAG, "SPS30: Failed to close UART");
}

const char *sps_get_driver_version(void)
{
    return SPS_DRV_VERSION_STR;
}

int16_t sps30_probe(void)
{
    char serial[SPS30_MAX_SERIAL_LEN];
    // Try to wake up, but ignore failure if it is not in sleep mode
    (void)sps30_wake_up();
    int16_t ret = sps30_get_serial(serial);

    return ret;
}

int16_t sps30_get_serial(char *serial)
{
    struct sensirion_shdlc_rx_header header;
    uint8_t param_buf[] = SPS30_CMD_DEV_INFO_SUBCMD_GET_SERIAL;
    int16_t ret;

    ret = sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_DEV_INFO, sizeof(param_buf),
                              param_buf, SPS30_MAX_SERIAL_LEN, &header,
                              (uint8_t *)serial);
    if (ret < 0)
        return ret;

    if (header.state)
        return SPS30_ERR_STATE(header.state);

    return 0;
}

int16_t sps30_start_measurement(void)
{
    struct sensirion_shdlc_rx_header header;
    uint8_t param_buf[] = SPS30_SUBCMD_MEASUREMENT_START;

    return sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_START_MEASUREMENT,
                               sizeof(param_buf), param_buf, 0, &header,
                               (uint8_t *)NULL);
}

int16_t sps30_stop_measurement(void)
{
    struct sensirion_shdlc_rx_header header;

    return sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_STOP_MEASUREMENT, 0,
                               (uint8_t *)NULL, 0, &header, (uint8_t *)NULL);
}

int16_t sps30_read_measurement(struct sps30_measurement *measurement)
{
    struct sensirion_shdlc_rx_header header;
    int16_t error;
    uint8_t data[10][4];

    error = sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_READ_MEASUREMENT, 0,
                                (uint8_t *)NULL, sizeof(data), &header,
                                (uint8_t *)data);
    if (error)
    {
        return error;
    }

    if (header.data_len != sizeof(data))
    {
        return SPS30_ERR_NOT_ENOUGH_DATA;
    }

    measurement->mc_1p0 = sensirion_bytes_to_float(data[0]);
    measurement->mc_2p5 = sensirion_bytes_to_float(data[1]);
    measurement->mc_4p0 = sensirion_bytes_to_float(data[2]);
    measurement->mc_10p0 = sensirion_bytes_to_float(data[3]);
    measurement->nc_0p5 = sensirion_bytes_to_float(data[4]);
    measurement->nc_1p0 = sensirion_bytes_to_float(data[5]);
    measurement->nc_2p5 = sensirion_bytes_to_float(data[6]);
    measurement->nc_4p0 = sensirion_bytes_to_float(data[7]);
    measurement->nc_10p0 = sensirion_bytes_to_float(data[8]);
    measurement->typical_particle_size = sensirion_bytes_to_float(data[9]);

    if (header.state)
    {
        return SPS30_ERR_STATE(header.state);
    }

    return 0;
}

int16_t sps30_sleep(void)
{
    struct sensirion_shdlc_rx_header header;

    return sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_SLEEP, 0, (uint8_t *)NULL,
                               0, &header, (uint8_t *)NULL);
}

int16_t sps30_wake_up(void)
{
    struct sensirion_shdlc_rx_header header;
    int16_t ret;
    const uint8_t data = 0xFF;

    ret = sensirion_uart_tx(1, &data);
    if (ret < 0)
    {
        return ret;
    }
    return sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_WAKE_UP, 0, (uint8_t *)NULL,
                               0, &header, (uint8_t *)NULL);
}

int16_t sps30_get_fan_auto_cleaning_interval(uint32_t *interval_seconds)
{
    struct sensirion_shdlc_rx_header header;
    uint8_t tx_data[] = {SPS30_SUBCMD_READ_FAN_CLEAN_INTV};
    int16_t ret;
    uint8_t data[4];

    ret = sensirion_shdlc_xcv(
        SPS30_ADDR, SPS30_CMD_FAN_CLEAN_INTV, sizeof(tx_data), tx_data,
        sizeof(*interval_seconds), &header, (uint8_t *)data);
    if (ret < 0)
        return ret;

    *interval_seconds = sensirion_bytes_to_uint32_t(data);

    if (header.state)
        return SPS30_ERR_STATE(header.state);

    return 0;
}

int16_t sps30_set_fan_auto_cleaning_interval(uint32_t interval_seconds)
{
    struct sensirion_shdlc_rx_header header;
    uint8_t cleaning_command[SPS30_CMD_FAN_CLEAN_INTV_LEN];

    cleaning_command[0] = SPS30_SUBCMD_READ_FAN_CLEAN_INTV;
    sensirion_uint32_t_to_bytes(interval_seconds, &cleaning_command[1]);

    return sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_FAN_CLEAN_INTV,
                               sizeof(cleaning_command), cleaning_command, 0,
                               &header, (uint8_t *)NULL);
}

int16_t sps30_get_fan_auto_cleaning_interval_days(uint8_t *interval_days)
{
    int16_t ret;
    uint32_t interval_seconds;

    ret = sps30_get_fan_auto_cleaning_interval(&interval_seconds);
    if (ret < 0)
        return ret;

    *interval_days = interval_seconds / (24 * 60 * 60);
    return ret;
}

int16_t sps30_set_fan_auto_cleaning_interval_days(uint8_t interval_days)
{
    return sps30_set_fan_auto_cleaning_interval((uint32_t)interval_days * 24 *
                                                60 * 60);
}

int16_t sps30_start_manual_fan_cleaning(void)
{
    struct sensirion_shdlc_rx_header header;

    return sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_START_FAN_CLEANING, 0,
                               (uint8_t *)NULL, 0, &header, (uint8_t *)NULL);
}

int16_t
sps30_read_version(struct sps30_version_information *version_information)
{
    struct sensirion_shdlc_rx_header header;
    int16_t error;
    uint8_t data[7];

    error = sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_READ_VERSION, 0,
                                (uint8_t *)NULL, sizeof(data), &header, data);
    if (error)
    {
        return error;
    }

    if (header.data_len != sizeof(data))
    {
        return SPS30_ERR_NOT_ENOUGH_DATA;
    }

    if (header.state)
    {
        return SPS30_ERR_STATE(header.state);
    }

    version_information->firmware_major = data[0];
    version_information->firmware_minor = data[1];
    version_information->hardware_revision = data[3];
    version_information->shdlc_major = data[5];
    version_information->shdlc_minor = data[6];

    return error;
}

int16_t sps30_reset(void)
{
    return sensirion_shdlc_tx(SPS30_ADDR, SPS30_CMD_RESET, 0, (uint8_t *)NULL);
}
