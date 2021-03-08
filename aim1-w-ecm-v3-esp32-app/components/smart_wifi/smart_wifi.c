#include <string.h>
#include "esp_wifi.h"
#include "freertos/event_groups.h"
#include "esp_smartconfig.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wpa2.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "smart_wifi.h"

#define TAG "wifi-app"

#define NVS_PARTITION               "cfg_part"
#define NVS_PARTITION_NAMESPACE     "wifi-cfg"
#define NVS_KEY_SSID                "ssid"
#define NVS_KEY_PASSWORD            "password"

static EventGroupHandle_t s_wifi_event_group;
static smart_wifi_app_cb app_layer_cb;
