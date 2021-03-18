#include <string.h>
#include <time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_log.h"

#include "telemetry_protocol.h"
#include "telemetry_encoder.h"
#include "telemetry_encoder.h"
#include "cloud_api.h"
#include "sgp40_voc_index_task.h"

#define TELEMETRY_STACK 3072
#define TELEMETRY_PRIORITY 2
#define TELEMETRY_QUEUE_LEN 10

#define TAG "telemetry"
#define TELEMETRY_LOCK(_mutex) xSemaphoreTake(_mutex, portMAX_DELAY)
#define TELEMETRY_UNLOCK(_mutex) xSemaphoreGive(_mutex)
#define SCALE_10X(__float_num) (__float_num * 10)

static uint16_t reqNo = 1;
static SemaphoreHandle_t