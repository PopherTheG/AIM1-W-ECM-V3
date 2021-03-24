/* Standard C library related includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
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
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "esp_sntp.h"
#include "esp_attr.h"
#include "esp_event.h"
#include "esp_heap_caps.h"
/* end */

/* WiFi related includes */
#include "wifi_manager.h"
#include "cloud_api.h"
#include "cloud_nvs.h"
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
// #include "svm40.h"
#include "sgp40_voc_index_task.h"
// #include "sensirion_i2c_hal.h"
// #include "sensirion_i2c.h"
/* end */

/* IR transmitter related includes */
#include "irtransmitter.h"
#include "samsung_test.h"
/* end */

/* gui related includes */
#include "gui.h"
/* end */

/* io expander related includes */
#include "io_task.h"
/* end */

/* telemetry related includes */
#include "telemetry.h"
#include "telemetry_protocol.h"
/* end */

/* commands related includes */
#include "commands.h"
/* end */

/* OTA related includes */
#include "ota.h"
/* end */


#define TAG "MAIN.C"

#define I2C1_SDA GPIO_NUM_32
#define I2C1_SCL GPIO_NUM_33
#define I2C2_SDA GPIO_NUM_27
#define I2C2_SCL GPIO_NUM_14

#define ONLINE
#ifdef ONLINE
#define HOST "52.221.96.155"
#define PORT 2883
#else
#define HOST "192.168.10.4"
#define PORT 1883
#endif

/* defining sensors used */
#define SPS30_INSTALLED
#define SGP40_INSTALLED
#define SHT40_INSTALLED

/*** Global Data - Values from sensors (SPS30, SGP40) ***/
float SPS30_PM2_5;
float SPS30_PM10;
int32_t SGP40_VOC;
float SHT4X_HUM;
float SHT4X_TEMP;
float SCD4x_CO2;

static uint8_t sent = 0;
static uint8_t uuid[16];
static uint8_t obtain_time = 1;
char serial[32] = {0};
uint8_t chipId[6] = {0};

static uint8_t device_type = 0;

/* static prototypes */
static void run_all_samsung_test();
static void system_init(void);
static void i2c_initialize(i2c_mode_t mode, int sda_io_num, int scl_io_num, bool sda_pullup_en, bool scl_pullup_en, uint32_t clk_speed, i2c_port_t i2c_num);
static void cloud_cb(cloud_event_t *evt);
static void connect_to_cloud(void);
static void display_time();
static void time_sync_notification_cb(struct timeval *tv);
static void initialize_sntp(void);
static void sntp_obtain_time(void);
static void cb_connection_ok(void *pvParamter);
static void system_info_task(void *pvParameters);
static void remote_command_cloud_response_wrapper(const char *out, size_t len);

void app_main(void)
{
    ESP_LOGI(TAG, "Start!");
    system_init();
    io_init();

#ifdef SPS30_INSTALLED
    /* Start task on sps30 to get pm2.5 and pm10 data */
    // sps30_start_task();
#endif

    /* Start task on st7899 display using LVGL library */
    commands_init();
    gui_start_task();

    esp_efuse_mac_get_default(chipId);
    sprintf(serial, "%d%d%d%d%d%d", chipId[0], chipId[1], chipId[2], chipId[3], chipId[4], chipId[5]);
    ESP_LOGI(TAG, "%s", serial);

    ESP_LOGI(TAG, "Long serial: %lld", strtoll(serial, NULL, 0));

    /* Used to connect set up the SSID and PASSWORD through a phone */
    wifi_manager_start();
    /* Once internet connection is established. Connect to the cloud
    with the callback cb_connection_ok */
    wifi_manager_set_callback(WM_EVENT_STA_GOT_IP, &cb_connection_ok);

    /* Initializes the Queue for telemetry related events */
    telemetry_init();

    uint64_t id = strtoull(serial, NULL, 0);
    /* starts the telemetry task of sending data to cloud with the specific ID of the esp32 */
    telemetry_start(&id);

    /* Start task on getting VOC index, temperature and humidity */
    /* this task must be called right after the initialization of the I2C
    Not doing so will affect the probing of SHT4x ( call this before wifi manager ) */
    sgp40_voc_index_start_task();

    /* Create and start task to run a test on actuating the samsung airconditioner */
    // xTaskCreate(run_all_samsung_test, "samsung ac test", 1024 * 2, NULL, 2, NULL);
}

static void system_init(void)
{
    ESP_LOGI(TAG, "System Init");
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(nvs_flash_init_partition("cfg_part"));

    setenv("TZ", "PST-8", 1);
    tzset();

    rmt_tx_init(); /* initialize ir peripheral of esp32 */
    i2c_initialize(I2C_MODE_MASTER, I2C1_SDA, I2C1_SCL, true, true, 100000, I2C_NUM_0);
    i2c_initialize(I2C_MODE_MASTER, I2C2_SDA, I2C2_SCL, true, true, 100000, I2C_NUM_1); /* Slaves connected: SGP40, SHT4X, IO Expander on DEX*/
}

static void system_info_task(void *pvParameters)
{
    (void)pvParameters;
    TickType_t last_wake_time = xTaskGetTickCount();

    while (1)
    {
        vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(30000));
        uint32_t iram_free = heap_caps_get_free_size(MALLOC_CAP_32BIT);
        uint32_t uptime = esp_timer_get_time() / 1000000;

        display_time();

        ESP_LOGI(TAG, "RAM32: %u Uptime: %u seconds", iram_free, uptime);
    }
    vTaskDelete(NULL);
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
        // samsung_test_auto();
        // samsung_test_toggle_air_direction(10);
        // samsung_test_toggle_swing(10);
    }
}

static void cloud_cb(cloud_event_t *evt)
{
    static int retries = 0;
    switch (evt->id)
    {
    case CLOUD_EVT_CONNECT:
        ESP_LOGI(TAG, "CLOUD_EVT_CONNECT");

        // const char *ver = ota_get_version();
        // ESP_LOGI(TAG, "Current Version: %s", ver);
        // ota_start();
        // uint64_t id = strtoull(serial, NULL, 0);
        // telemetry_start(&id);

        break;

    case CLOUD_EVT_DISCONNECT:
        ESP_LOGI(TAG, "CLOUD_EVT_DISCONNECT");
        // telemetry_stop();
        break;

    case CLOUD_EVT_RECONNECT:
        ESP_LOGI(TAG, "CLOUD_EVT_RECONNECT");
        break;

    case CLOUD_EVT_DATA_MQTT:
        ESP_LOGI(TAG, "CLOUD_EVT_DATA_MQTT");
        sent = 0;

        ESP_LOGI(TAG, "MQTT Data received");
        ESP_LOGI(TAG, "Topic=%.*s", evt->evt.data.mqtt.topic_len, evt->evt.data.mqtt.topic);
        ESP_LOGI(TAG, "Data=%.*s", evt->evt.data.mqtt.len, evt->evt.data.mqtt.data);
        commands_process((char *)evt->evt.data.mqtt.len, evt->evt.data.mqtt.data, remote_command_cloud_response_wrapper);
        break;

    default:
        ESP_LOGI(TAG, "UNKNOW_CLOUD_EVENT %d", evt->id);
        break;
    }
}

static void connect_to_cloud(void)
{
    // cloud_ret_t cloud_ret = cloud_api_connect_host(HOST, PORT);
    cloud_api_init(cloud_cb);
    cloud_api_set_mqtt_id(serial);
    cloud_ret_t cloud_ret = cloud_api_connect();

    if (cloud_ret == CLOUD_RET_OK)
    {
        ESP_LOGI(TAG, "Cloud Connected\r\n");
    }
    else if (cloud_ret == CLOUD_RET_UNKNOWN_PROTOCOL)
    {
        ESP_LOGI(TAG, "Cloud Unknown Protocol\r\n");
    }
}

static void display_time()
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    char strftime_buf[64];

    sprintf(strftime_buf, "%2d:%02d %s", timeinfo.tm_hour > 12 ? timeinfo.tm_hour - 12 : timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_hour > 12 ? "PM" : "AM");
    ESP_LOGI(TAG, "Current Time: %s", strftime_buf);
}

static void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Notification of a time synchronizaion event");
    display_time();
}

static void initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
    sntp_init();
}

static void sntp_obtain_time(void)
{
    if (obtain_time == 1)
    {
        obtain_time = 0;
        initialize_sntp();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        int retry = 0;
        const int retry_count = 10;
        while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count)
        {
            ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

static void remote_command_cloud_response_wrapper(const char *out, size_t len) 
{
    cloud_api_send_rc_response((uint8_t *)out, len);
}

static void cb_connection_ok(void *pvParamter)
{
    ip_event_got_ip_t *param = (ip_event_got_ip_t *)pvParamter;

    char str_ip[16];
    esp_ip4addr_ntoa(&param->ip_info.ip, str_ip, IP4ADDR_STRLEN_MAX);

    ESP_LOGI(TAG, "I have a connection and my ip is: %s!", str_ip);

    connect_to_cloud();
    sntp_obtain_time();

    // const cloud_config_t cloud_config = {
    // .conntype = CLOUD_TYPE_MQTT,
    // .host = "52.221.96.155",
    // .port = 2883
    // };

    // cloud_api_set_config(&cloud_config);
}
