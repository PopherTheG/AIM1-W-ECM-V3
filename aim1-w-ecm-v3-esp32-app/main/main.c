#include <stdio.h>
#include "main.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/i2c.h"
#include "driver/rmt.h"
#include "string.h"

/* Sensirion related includes */
#include "sensirion_common.h"
#include "sensirion_config.h"
#include "sensirion_sleep.h"

/* SPS30 related includes*/
#include "sensirion_shdlc.h"
#include "sensirion_uart_hal.h"
#include "sps30.h"

/* SVM40 related includes*/
#include "svm40.h"
#include "sensirion_i2c_hal.h"
#include "sensirion_i2c.h"

/* SSD1306 related includes */
#include "ssd1306.h"
#include "ssd1306_tests.h"
#include "ssd1306_custom_func.h"
#include "ssd1306_aim1_icons.h"

/* IR transmitter related includes */
#include "irtransmitter.h"
#include "samsung_test.h"

#define TAG "MAIN.C"

#define I2C_MASTER_PORT SSD1306_I2C_PORT
#define I2C_SDA GPIO_NUM_21
#define I2C_SCL GPIO_NUM_22

/*** Global Data - Values from sensors (SPS30, SGP40) ***/
float SPS30_PM2_5;
float SPS30_PM10;
float SVM40_VOC;
float SVM40_HUM;
float SVM40_TEMP;
float SCD4x_CO2;

/**
 * @name                    i2c_initialize
 * 
 * @brief                   Initialize an I2C port
 * 
 * @param   mode            Set I2C as MASTER or SLAVE
 * @param   sda_io_num      GPIO number for SDA
 * @param   scl_io_num      GPIO number for SCL
 * @param   sda_pullup_en   Enable or disable pullup
 * @param   scl_pullup_en   Enable or disable pullup
 * @param   clk_speed       Desired clock speed for I2C bus
 * @param   i2c_num         I2C port to use
 */
static void i2c_initialize(i2c_mode_t mode, int sda_io_num, int scl_io_num, bool sda_pullup_en, bool scl_pullup_en, uint32_t clk_speed, i2c_port_t i2c_num)
{
    i2c_config_t conf = {
        .mode = mode,
        .sda_io_num = sda_io_num,
        .scl_io_num = scl_io_num,
        .sda_pullup_en = sda_pullup_en,
        .scl_pullup_en = scl_pullup_en,
        .master.clk_speed = clk_speed};
    ESP_ERROR_CHECK(i2c_param_config(i2c_num, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(i2c_num, conf.mode, 0, 0, 0));
}

/*** Display components for OLED START ***/
void display_uv_OLED128x64()
{
    uint8_t uvActivated = 1; /* 1: UV light is activated. 0: UV light is deactivated. */
    if (uvActivated)
    {
        ssd1306_binarizedimg_to_pixel(0, 1, 15, 16, uv_icon_15x16);
        ssd1306_set_cursor(17, 4);
        ssd1306_write_string("ON", Font_6x8, White);
    }
}

void display_aqi_OLED128x64()
{
    char str_sgp40_voc_buf[64];
    ssd1306_set_cursor(23, 23);
    sprintf(str_sgp40_voc_buf, "%.01fVOC   ", SVM40_VOC);
    ssd1306_write_string((char *)str_sgp40_voc_buf, Font_11x18, White);
}

void display_clearrow_OLED128x64(uint8_t x, uint8_t y, SSD1306_COLOR color)
{
    for (uint32_t i = x; i < SSD1306_WIDTH; i++)
    {
        ssd1306_draw_pixel(i, y, color);
    }
}

void display_temp_OLED128x64()
{
    char str_sgp40_temp_buf[64];
    ssd1306_binarizedimg_to_pixel(34, 0, 16, 16, temp_icon_16x16);
    ssd1306_set_cursor(51, 4);
    sprintf(str_sgp40_temp_buf, "%.01fC    ", SVM40_TEMP);
    ssd1306_write_string((char *)str_sgp40_temp_buf, Font_6x8, White);
}

void display_hum_OLED128x64()
{
    char str_sgp40_hum_buf[64];
    ssd1306_binarizedimg_to_pixel(86, 0, 16, 16, humidity_icon_16x16);
    ssd1306_set_cursor(103, 4);
    sprintf(str_sgp40_hum_buf, "%.00f%%    ", SVM40_HUM);
    ssd1306_write_string((char *)str_sgp40_hum_buf, Font_6x8, White);
}

void display_PM2_5_PM10_OLED128x64()
{
    char str_sps30_pm2_5_pm10_0_buf[64];
    ssd1306_set_cursor(0, 45);
    sprintf(str_sps30_pm2_5_pm10_0_buf, "PM2.5:%.02f PM10:%.02f    ", SPS30_PM2_5, SPS30_PM10);
    ssd1306_write_string((char *)str_sps30_pm2_5_pm10_0_buf, Font_6x8, White);
}

void display_CO2_TVOC_OLED128x64()
{
    char str_scd4x_co2_buf[64];
    ssd1306_set_cursor(0, 56);
    sprintf(str_scd4x_co2_buf, "CO2:%.00fppm", (float)2501);
    ssd1306_write_string((char *)str_scd4x_co2_buf, Font_6x8, White);
}
/*** Display components for OLED END ***/

/**
 * @name                display_data_OLED128x64_task
 * 
 * @brief               Display important air quality parameters measure by SPS30 on OLED
 *                      display ( to add more sensors to display data e.g. temp and hum )
 * 
 * @param   pm2_5       Pointer to the measured sensor value of PM2.5
 * @param   pm10_0      Pointer to the measured sensor value of PM10.0
 *   
 * @note                PM2.5 and PM10.0 are two measures of air quality that is mostly used to      
 *                      evaluate air quality
 */
void display_data_OLED128x64_task()
{
    while (1)
    {
        display_uv_OLED128x64();
        display_aqi_OLED128x64();
        display_temp_OLED128x64();
        display_hum_OLED128x64();
        display_PM2_5_PM10_OLED128x64();
        display_CO2_TVOC_OLED128x64();
        ssd1306_update_screen();
    }
}

/**
 * @name        sps30_task
 * 
 * @brief       Task for SPS30 to read the measurements from the sensor.
 * 
 * @return      none
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

                /* storing results in global variables */
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

/**
 * @name        svm40_task
 * 
 * @brief       Task for SVM40 to read measurements from the sensor.
 * 
 * @return      none
 */
void svm40_task()
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

/**
 * @name        run_all_samsung_test
 * 
 * @brief       Task to run all test codes for Samsung air conditioner.
 * 
 * @return      none
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
    rmt_tx_init();                                                                          /* initialize ir peripheral of esp32 */
    i2c_initialize(I2C_MODE_MASTER, I2C_SDA, I2C_SCL, true, true, 100000, I2C_MASTER_PORT); /* Initalize I2C communication for OLED */
    ssd1306_init();                                                                         /* initialize driver for OLED display */
    ssd1306_fill(Black);
    ssd1306_update_screen();

    /*** Task Creation ***/
    xTaskCreate(&sps30_task, "sps30 task", 1024 * 4, NULL, 2, NULL);
    xTaskCreate(&svm40_task, "svm40 task", 1024 * 2, NULL, 2, NULL);
    xTaskCreate(&display_data_OLED128x64_task, "OLED task", 1024 * 4, NULL, 3, NULL);
    // xTaskCreate(&guvc_t10gm_la_task, "uv sensor task", 1*1024, NULL, 2, NULL);
}
