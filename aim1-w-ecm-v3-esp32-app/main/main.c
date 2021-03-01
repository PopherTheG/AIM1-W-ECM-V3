/* Standard C library related includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* end */

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

/* Sensirion related includes */
#include "sensirion_common.h"
#include "sensirion_config.h"
#include "sensirion_sleep.h"
/* end */

/* SPS30 related includes*/
#include "sensirion_shdlc.h"
#include "sensirion_uart_hal.h"
#include "sps30.h"
/* end */

/* SVM40 related includes*/
#include "svm40.h"
#include "sensirion_i2c_hal.h"
#include "sensirion_i2c.h"
/* end */

/* IR transmitter related includes */
#include "irtransmitter.h"
#include "samsung_test.h"
/* end */

/* gui related includes */
#include "gui.h"
/* end */

#define TAG "MAIN.C"

#define I2C_MASTER_PORT I2C_NUM_0
#define I2C_SDA GPIO_NUM_32
#define I2C_SCL GPIO_NUM_33  

/* defining sensors used */
#define SPS30_INSTALLED
#define SVM40_INSTALLED


/* static prototypes */
static void run_all_samsung_test();
static void i2c_initialize(i2c_mode_t mode, int sda_io_num, int scl_io_num, bool sda_pullup_en, bool scl_pullup_en, uint32_t clk_speed, i2c_port_t i2c_num);

/*** Global Data - Values from sensors (SPS30, SGP40) ***/
float SPS30_PM2_5;
float SPS30_PM10;
float SVM40_VOC;
float SVM40_HUM;
float SVM40_TEMP;
float SCD4x_CO2;

void app_main(void)
{
    rmt_tx_init();                                                                    /* initialize ir peripheral of esp32 */
    i2c_initialize(I2C_MODE_MASTER, I2C_SDA, I2C_SCL, true, true, 100000, I2C_NUM_0); /* Slaves connected: SVM40 */


    gui_start_task(); /* Start task on st7899 display using LVGL library */
    #ifdef SPS30_INSTALLED
    sps30_start_task(); /* Start task on sps30 to get pm2.5 and pm10 data */
    #endif
    #ifdef SVM40_INSTALLED
    svm40_start_task(); /* Start task on svm40 to get temp, hum, and voc data */
    #endif
    xTaskCreate(run_all_samsung_test, "samsung ac test", 1024 * 2, NULL, 2, NULL);
}

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

/**
 * @name        run_all_samsung_test
 * 
 * @brief       Task to run all test codes for Samsung air conditioner.
 * 
 * @return      none
 */
static void run_all_samsung_test()
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



// on off mosfet.