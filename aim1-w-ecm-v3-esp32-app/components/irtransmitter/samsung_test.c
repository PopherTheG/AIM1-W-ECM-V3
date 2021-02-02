#include <stdio.h>
#include <stdint.h>
#include "esp_log.h"
#include "irtransmitter.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "SAMSUNG_TEST.C"

void samsung_test_cool_lowfan()
{
    for (uint32_t i = 17; i <= 30; i++)
    {
        ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: COOL MODE - LOW FAN - TEMP %u", i);
        samsung_cool_lowfan(i);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}


void samsung_test_cool_medfan()
{
    for (uint32_t i = 17; i <= 30; i++)
    {
        ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: COOL MODE - MED FAN - TEMP %u", i);
        samsung_cool_medfan(i);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}


void samsung_test_cool_highfan()
{
    for (uint32_t i = 17; i <= 30; i++)
    {
        ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: COOL MODE - HIGH FAN - TEMP %u", i);
        samsung_cool_highfan(i);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void samsung_test_cool_autofan()
{
    for (uint32_t i = 17; i <= 30; i++)
    {
        ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: COOL MODE - AUTO FAN - TEMP %u", i);
        samsung_cool_lowfan(i);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}


void samsung_test_dry()
{
    for (uint32_t i = 17; i <= 30; i++)
    {
        ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: DRY MODE - TEMP %u", i);
        samsung_dry(i);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}


void samsung_test_fan()
{
    ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: FAN MODE - LOW FAN");
    samsung_fan_lowfan();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: FAN MODE - MED FAN");
    samsung_fan_medfan();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: FAN MODE - HIGH FAN");
    samsung_fan_highfan();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: FAN MODE - AUTO FAN");
    samsung_fan_autofan(); 
    vTaskDelay(5000 / portTICK_PERIOD_MS);
}


void samsung_test_auto()
{
    for(uint32_t i = 17; i <= 30; i++)
    {
        ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: AUTO MODE - TEMP %u", i);
        samsung_auto(i);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}  

void samsung_test_toggle_air_direction(uint32_t times)
{
    for(uint32_t i = 0; i <= times; i++)
    {
        ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: TOGGLE AIR DIRECTION %u TIMES", i);
        samsung_toggle_air_direction();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

// Runs a test on the Samsung air conditioner IR protocol, that sends
// IR signals to toggle swing. The number of times that it will be toggled
// depends on the argument you pass in `uint32_t times` parameter.
void samsung_test_toggle_swing(uint32_t times)
{
    for(uint32_t i = 0; i <= times; i++)
    {
        ESP_LOGI(TAG, "Transmitting SAMSUNG IR Signal: TOGGLE SWING %u TIMES", i);
        samsung_toggle_swing();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

