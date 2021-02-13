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

/* LittleVGL specific includes */
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"

#include "lv_examples/src/lv_ex_get_started/lv_ex_get_started.h"

#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
#if defined CONFIG_LV_USE_DEMO_WIDGETS
#include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"
#elif defined CONFIG_LV_USE_DEMO_KEYPAD_AND_ENCODER
#include "lv_examples/src/lv_demo_keypad_and_encoder/lv_demo_keypad_and_encoder.h"
#elif defined CONFIG_LV_USE_DEMO_BENCHMARK
#include "lv_examples/src/lv_demo_benchmark/lv_demo_benchmark.h"
#elif defined CONFIG_LV_USE_DEMO_STRESS
#include "lv_examples/src/lv_demo_stress/lv_demo_stress.h"
#else
#error "No demo application selected."
#endif
#endif
/* end */

#define TAG "MAIN.C"

#define I2C_MASTER_PORT I2C_NUM_0
#define I2C_SDA GPIO_NUM_32
#define I2C_SCL GPIO_NUM_33

/* lvgl related defines */
#define LV_TICK_PERIOD_MS 1

/* static prototypes */
static void i2c_initialize(i2c_mode_t mode, int sda_io_num, int scl_io_num, bool sda_pullup_en, bool scl_pullup_en, uint32_t clk_speed, i2c_port_t i2c_num);
static void lv_tick_task(void *arg);
static void guiTask(void *pvParameters);
// static void create_demo_application(void);
static void sps30_task();
static void svm40_task();
static void run_all_samsung_test();
static void st7899_display_application(float *PM2_5_data, float *PM10_data, float *VOC_data, float *HUM_data, float *TEMP_data, float *CO2_data);

/*** Global Data - Values from sensors (SPS30, SGP40) ***/
float SPS30_PM2_5 = 4.5;
float SPS30_PM10 = 5.6;
float SVM40_VOC = 25.6;

float SVM40_HUM = 57.6;
float SVM40_TEMP = 27.1;
float SCD4x_CO2 = 768;


void app_main(void)
{
    rmt_tx_init();                                                                          /* initialize ir peripheral of esp32 */
    i2c_initialize(I2C_MODE_MASTER, I2C_SDA, I2C_SCL, true, true, 100000, I2C_MASTER_PORT); /* Initalize I2C communication for OLED */

    /*** Task Creation ***/
    /* If you want to use a task to create the graphic, you NEED to create a Pinned
    task. Otherwise there can be problem such as memory corruption and so on.
    NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0. */
    xTaskCreatePinnedToCore(guiTask, "gui", 4096 * 2, NULL, 0, NULL, 1);
    xTaskCreate(sps30_task, "sps30 task", 1024 * 4, NULL, 2, NULL);
    xTaskCreate(svm40_task, "svm40 task", 1024 * 2, NULL, 2, NULL);
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
 * @name        sps30_task
 * 
 * @brief       Task for SPS30 to read the measurements from the sensor.
 * 
 * @return      none
 */
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

/**
 * Creates a semaphore to handle concurrent calls to lvgl stuff.
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;

static void guiTask(void *pvParameter)
{

    (void)pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();

    /* Initialize SPI or I2C bus used by the drivers */
    lvgl_driver_init();

    static lv_color_t buf1[DISP_BUF_SIZE];

    /* Use double buffered when not working with monochrome displays */
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    static lv_color_t buf2[DISP_BUF_SIZE];
#else
    static lv_color_t *buf2 = NULL;
#endif

    static lv_disp_buf_t disp_buf;

    uint32_t size_in_px = DISP_BUF_SIZE;

#if defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820 || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D

    /* Actual size in pixels, not bytes. */
    size_in_px *= 8;
#endif

    /* Initialize the working buffer depending on the selected display.
     * NOTE: buf2 == NULL when using monochrome displays. */
    lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;

    /* When using a monochrome display we need to register the callbacks:
     * - rounder_cb
     * - set_px_cb */
#ifdef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    disp_drv.rounder_cb = disp_driver_rounder;
    disp_drv.set_px_cb = disp_driver_set_px;
#endif

    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    /* Register an input device when enabled on the menuconfig */
#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = touch_driver_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
#endif

    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    /* Create the demo application */
    st7899_display_application(&SPS30_PM2_5, &SPS30_PM10, &SVM40_VOC, &SVM40_HUM, &SVM40_TEMP, &SCD4x_CO2);
    while (1)
    {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
        {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }
    }

    /* A task should NEVER return */
    vTaskDelete(NULL);
}


static void st7899_display_application(float *PM2_5_data, float *PM10_data, float *VOC_data, float *HUM_data, float *TEMP_data, float *CO2_data)
{
    /* Create an Arc */
    lv_obj_t * arc = lv_arc_create(lv_scr_act(), NULL);
    lv_arc_set_end_angle(arc, 200);
    lv_obj_set_size(arc, 150, 150);
    lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 0);
}

// static void create_demo_application(void)
// {
//     /* When using a monochrome display we only show "Hello World" centered on the 
//      * screen */
// #if defined CONFIG_LV_TFT_DISPLAY_MONOCHROME || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7735S
//     /* use a pretty small demo for monochrome displays */
//     /* Get the current screen  */
//     lv_obj_t *scr = lv_disp_get_scr_act(NULL);

//     /*Create a Label on the currently active screen*/
//     lv_obj_t *label1 = lv_label_create(scr, NULL);

//     /*Modify the Label's text*/
//     lv_label_set_text(label1, "Hello\nworld");

//     /* Align the Label to the center
//      * NULL means align on parent (which is the screen now)
//      * 0, 0 at the end means an x, y offset after alignment*/
//     lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
// #else
//     /* Otherwise we show the selected demo */

// #if defined CONFIG_LV_USE_DEMO_WIDGETS
//     lv_demo_widgets();
//     // lv_ex_get_started_1();
//     // lv_ex_get_started_2();
//     // lv_ex_get_started_3();
// #elif defined CONFIG_LV_USE_DEMO_KEYPAD_AND_ENCODER
//     lv_demo_keypad_encoder();
// #elif defined CONFIG_LV_USE_DEMO_BENCHMARK
//     lv_demo_benchmark();
// #elif defined CONFIG_LV_USE_DEMO_STRESS
//     lv_demo_stress();
// #else
// #error "No demo application selected."
// #endif
// #endif
// } 

static void lv_tick_task(void *arg)
{
    (void)arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}