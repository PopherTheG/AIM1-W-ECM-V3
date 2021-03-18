#include <time.h>
#include <string.h>
#include <stdio.h>
#include "esp_log.h"

#include "telemetry_encoder.h"

uint32_t telemetry_timestamp_generate(void)
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    // localtime_r(&now, &timeinfo);
    gmtime_r(&now, &timeinfo);
    char strftime_buf[64];

    sprintf(strftime_buf, "%2d:%02d %s", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_hour > 12 ? "PM" : "AM");
    ESP_LOGI(__FUNCTION__, "Current GMT Time: %s", strftime_buf);

    return mktime(&timeinfo);
}