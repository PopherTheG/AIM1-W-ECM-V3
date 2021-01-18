#include <stdio.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/i2c.h"
#include "driver/rmt.h"
#include "string.h"

#include "sensirion_uart.h"
#include "sps30.h"
#include "irtransmitter.h"
#include "samsung_test.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"

#define TAG "MAIN.C"

#define I2C_MASTER_PORT I2C_NUM_0
#define I2C_SDA GPIO_NUM_21
#define I2C_SCL GPIO_NUM_22
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

/**
 * @brief       Task for SPS30 to read the measurements from the sensor.
 */
void sps30_task()
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

                // char str_sps30_pm1_0_buf[64];
                // char str_sps30_pm2_5_buf[64];
                // char str_sps30_pm4_0_buf[64];
                // char str_sps30_pm10_0_buf[64];
                // char str_sps30_nc0_5_buf[64];
                // char str_sps30_nc1_0_buf[64];
                // char str_sps30_nc2_5_buf[64];
                // char str_sps30_nc4_0_buf[64];
                // char str_sps30_nc10_0_buf[64];
                // char str_sps30_typsize_buf[64];

                // ssd1306_set_cursor(0, 0);
                // sprintf(str_sps30_nc0_5_buf, "%0.2fnc0.5", m.nc_0p5);
                // ssd1306_write_string((char *)str_sps30_nc0_5_buf, Font_6x8, White);
                // ssd1306_set_cursor(0, 10);
                // sprintf(str_sps30_nc1_0_buf, "%0.2fnc1.0", m.nc_1p0);
                // ssd1306_write_string((char *)str_sps30_nc1_0_buf, Font_6x8, White);
                // ssd1306_set_cursor(0, 20);
                // sprintf(str_sps30_nc2_5_buf, "%0.2fnc2.5", m.nc_2p5);
                // ssd1306_write_string((char *)str_sps30_nc2_5_buf, Font_6x8, White);
                // ssd1306_set_cursor(0, 30);
                // sprintf(str_sps30_nc4_0_buf, "%0.2fnc4.0", m.nc_4p0);
                // ssd1306_write_string((char *)str_sps30_nc4_0_buf, Font_6x8, White);
                // ssd1306_set_cursor(0, 40);
                // sprintf(str_sps30_nc10_0_buf, "%0.2fnc10.0", m.nc_10p0);
                // ssd1306_write_string((char *)str_sps30_nc10_0_buf, Font_6x8, White);
                // ssd1306_set_cursor(0, 50);
                // sprintf(str_sps30_typsize_buf, "%0.2f typ. part. size", m.typical_particle_size);
                // ssd1306_write_string((char *)str_sps30_typsize_buf, Font_6x8, White);
                // ssd1306_set_cursor(65, 0);
                // sprintf(str_sps30_pm1_0_buf, "%.02fpm1.0", m.mc_1p0);
                // ssd1306_write_string((char *)str_sps30_pm1_0_buf, Font_6x8, White);
                // ssd1306_set_cursor(65, 10);
                // sprintf(str_sps30_pm2_5_buf, "%.02fpm2.5", m.mc_2p5);
                // ssd1306_write_string((char *)str_sps30_pm2_5_buf, Font_6x8, White);
                // ssd1306_set_cursor(65, 20);
                // sprintf(str_sps30_pm4_0_buf, "%.02fpm4.0", m.mc_4p0);
                // ssd1306_write_string((char *)str_sps30_pm4_0_buf, Font_6x8, White);
                // ssd1306_set_cursor(65, 30);
                // sprintf(str_sps30_pm10_0_buf, "%.02fpm10.0", m.mc_10p0);
                // ssd1306_write_string((char *)str_sps30_pm10_0_buf, Font_6x8, White);

                ssd1306_set_cursor(0, 0);
                #include "font8x8_basic.h"
                

                ssd1306_update_screen();
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

/**
 * @brief       Task to run all test codes for Samsung air conditioner.
 */
void run_all_samsung_test()
{
    while (1)
    {
        /* Run all functionalities of Samsung airconditioner */
        samsung_test_cool_lowfan();
        samsung_test_cool_medfan();
        samsung_test_cool_highfan();
        samsung_test_dry();
        samsung_test_auto();
        samsung_test_toggle_air_direction(10);
        samsung_test_toggle_swing(10);
    }
}

void app_main(void)
{
    i2c_config_t i2c_master_config = {
        .mode = I2C_MODE_MASTER,
        .scl_io_num = I2C_SCL,
        .sda_io_num = I2C_SDA,
        .scl_pullup_en = true,
        .sda_pullup_en = true,
        .master.clk_speed = 100000,
    };
    i2c_param_config(SSD1306_I2C_PORT, &i2c_master_config);
    i2c_driver_install(SSD1306_I2C_PORT, i2c_master_config.mode, 0, 0, 0);

    rmt_tx_init(); /* initialize ir peripheral of esp32 */
    ssd1306_init();

    /*** Task Creation ***/
    xTaskCreate(&sps30_task, "sps30 task", 1024 * 4, NULL, 2, NULL);
    // xTaskCreate(&run_all_samsung_test, "samsung test", 1024 * 2, NULL, 1, NULL);
}
