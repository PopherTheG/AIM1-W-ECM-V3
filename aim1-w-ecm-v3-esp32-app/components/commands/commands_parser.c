#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#include <string.h>
#include <stdio.h>

#include "esp_log.h"
#include "esp_system.h"

#include "ota.h"
#include "cloud_api.h"
#include "commands_nvs.h"
#include "commands_parser.h"
#include "io_task.h"
#include "irtransmitter.h"



#define SUCCESS_STR "OK"
#define ERROR_STR "ERROR"
#define MAX_SCAN_LIST 10

#define TAG "commands_parser.c"

typedef struct
{
    uint8_t used;
    char name[23];
    uint8_t bda[6];
} scan_db_t;

static TimerHandle_t xRestartTimer = NULL;
// static scan_db_t scan_db[MAX_SCAN_LIST];

static void restart_timer_cb(void *data)
{
    esp_restart();
}

size_t command_parser_relay(char *param, char *out, void *arg)
{
    if (!param)
    {
        return sprintf(out, "+RELAY: %d\r\nOK", io_relay_get_level());
    }
    int param_int = strtoul(param, NULL, 0);
    io_relay_set_level((param_int == 1) ? 1 : 0);
    if (io_relay_get_level() == 0)
    {
        io_ledcolor(LED_COLOR_RED);
    }
    else if (io_relay_get_level() == 1)
    {
        io_ledcolor(LED_COLOR_GREEN);
    }
    return sprintf(out, SUCCESS_STR);
}

size_t command_parser_restart(char *param, char *out, void *arg)
{
    (void)param;

    xRestartTimer = xTimerCreate("restart-tmr", pdMS_TO_TICKS(5000), pdFALSE, NULL, restart_timer_cb);
    if (xRestartTimer)
    {
        xTimerStart(xRestartTimer, 0);
    }

    return sprintf(out, SUCCESS_STR);
}

size_t command_parser_wifi_ap_config(char *param, char *out, void *arg)
{
    return sprintf(out, "ERROR");
}

size_t command_parser_ota_start(char *param, char *out, void *arg)
{
    if (!param)
    {
        ota_start();
        return sprintf(out, SUCCESS_STR);
    }

    return sprintf(out, "ERROR");
}

size_t command_parser_ota_url(char *param, char *out, void *arg)
{
    if (!param)
    {
        return sprintf(out, "+OTAURL:%s", ota_get_url());
    }
    ota_set_url(param);

    return sprintf(out, SUCCESS_STR);
}

size_t command_parser_cloud(char *param, char *out, void *arg)
{
    if (!param)
    {
        cloud_config_t config;
        cloud_api_get_config(&config);
        return sprintf(out, "+CLOUD:%d,%s,%d\r\nOK",
                       config.conntype, config.host, config.port);
    }

    char *token[3], *save_ptr;
    token[0] = strtok_r(param, ",", &save_ptr);
    token[1] = strtok_r(NULL, ",", &save_ptr);
    token[2] = strtok_r(NULL, ",", &save_ptr);

    if (token[0] && token[1] && token[2])
    {
        cloud_config_t config;
        config.conntype = strtoul(token[0], NULL, 10);
        strcpy(config.host, token[1]);
        config.port = strtoul(token[2], NULL, 10);
        cloud_api_set_config(&config);
        return sprintf(out, SUCCESS_STR);
    }
    return sprintf(out, ERROR_STR);
}

size_t command_parser_samsung(char *param, char *out, void *args)
{
    if (!param)
    {
        return sprintf(out, "+SAMSUNG\r\nOK");
    }

    char *token[2], *save_ptr;
    token[0] = strtok_r(param, ",", &save_ptr);
    token[1] = strtok_r(NULL, ",", &save_ptr);

    if (token[0] && token[1])
    {       

        switch (atoi(token[0]))
        {
        case 9:
            samsung_fan_autofan();
            break;

        case 8:
            samsung_fan_highfan();
            break;

        case 7:
            samsung_fan_medfan();
            break;

        case 6:
            samsung_fan_lowfan();
            break;

        case 5:
            samsung_auto(atoi(token[1]));
            break;

        case 4:
            samsung_dry(atoi(token[1]));
            break;

        case 3:
            samsung_cool_autofan(atoi(token[1]));
            break;

        case 2:
            samsung_cool_highfan(atoi(token[1]));
            break;

        case 1:
            samsung_cool_medfan(atoi(token[1]));
            break;

        case 0:
            samsung_cool_lowfan(atoi(token[1]));
            break;

        default:
            return sprintf(out, ERROR_STR);
            break;
        }
        return sprintf(out, SUCCESS_STR);
    }

    return sprintf(out, ERROR_STR);
}

size_t command_parser_stoggle(char *param, char *out, void *args)
{
    if (!param)
    {
        return sprintf(out, "+STOGGLE:\r\nOK");
    }

    switch (atoi(param))
    {
    case 2: //TURBO
        samsung_toggle_turbo();
        return sprintf(out, SUCCESS_STR);
        break;

    case 1: // Swing
        samsung_toggle_swing();
        return sprintf(out, SUCCESS_STR);
        break;

    case 0:
        samsung_toggle_air_direction();
        return sprintf(out, SUCCESS_STR);
    default:
        break;
    }

    return sprintf(out, ERROR_STR);
}

size_t command_parser_soff(char *param, char *out, void *args)
{
    if (!param)
    {
        return sprintf(out, "+SOFF:\r\nOK");
    }
    samsung_off();

    return sprintf(out, SUCCESS_STR);
}

size_t command_parser_ctrl(char* param, char* out, void* args)
{
    return sprintf(out, ERROR_STR);
}