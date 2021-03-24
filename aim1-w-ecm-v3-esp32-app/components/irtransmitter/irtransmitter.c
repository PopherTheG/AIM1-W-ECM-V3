#include <stdio.h>
#include <stdint.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/rmt.h"
#include "driver/gpio.h"

#include "samsung_ir_codes.h"

#define IR_LED_PIN          GPIO_NUM_15
#define IR_RMT_CHANNEL      RMT_CHANNEL_0
#define TAG "irtransmitter.c"

void rmt_tx_init(void)
{
    rmt_config_t config;
    config.rmt_mode                         = RMT_MODE_TX;
    config.channel                          = IR_RMT_CHANNEL;
    config.gpio_num                         = IR_LED_PIN;
    config.clk_div                          = 80;
    config.mem_block_num                    = 1;
    config.tx_config.carrier_freq_hz        = 38000;
    config.tx_config.carrier_level          = RMT_CARRIER_LEVEL_HIGH;
    config.tx_config.idle_level             = RMT_IDLE_LEVEL_LOW;
    config.tx_config.carrier_duty_percent   = 50;
    config.tx_config.carrier_en             = true;
    config.tx_config.loop_en                = false;
    config.tx_config.idle_output_en         = true;
    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));
}

/*** START SAMSUNG ***/

/* The functions samsung_cool_lowfan, samsung_cool_medfan, 
samsung_cool_highfan, samsung_cool_autofan, samsung_dry,
samsung_fan_lowfan, samsung_fan_medfan, samsung_fan_highfan,
samsung_fan_autofan, and samsung_auto sends the while data 
packets for the mode, temperature and the fan speed settings.

The functions samsung_toggle_air_direction, samsung_toggle_swing
and samsung_toggle_turbo are just modifiers to the current setting.

Further explanation on this is found in samsung_ir_codes.h */

void samsung_cool_lowfan(uint8_t temp)
{
    switch (temp)
    {
    case 17:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_17_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_17_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_17_COOL_LOWFAN[0]), true));
        break;
    case 18:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_18_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_18_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_18_COOL_LOWFAN[0]), true));
        break;
    case 19:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_19_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_19_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_19_COOL_LOWFAN[0]), true));
        break;
    case 20:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_20_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_20_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_20_COOL_LOWFAN[0]), true));
        break;
    case 21:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_21_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_21_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_21_COOL_LOWFAN[0]), true));
        break;
    case 22:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_22_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_22_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_22_COOL_LOWFAN[0]), true));
        break;
    case 23:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_23_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_23_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_23_COOL_LOWFAN[0]), true));
        break;
    case 24:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_24_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_24_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_24_COOL_LOWFAN[0]), true));
        break;
    case 25:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_25_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_25_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_25_COOL_LOWFAN[0]), true));
        break;
    case 26:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_26_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_26_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_26_COOL_LOWFAN[0]), true));
        break;
    case 27:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_27_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_27_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_27_COOL_LOWFAN[0]), true));
        break;
    case 28:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_28_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_28_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_28_COOL_LOWFAN[0]), true));
        break;
    case 29:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_29_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_29_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_29_COOL_LOWFAN[0]), true));
        break;
    case 30:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_30_COOL_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_30_COOL_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_30_COOL_LOWFAN[0]), true));
        break;
    default:
        ESP_LOGW("WARNING", "Temp you sent is not acknowledged only from 17-30");
        break;
    }
    // ESP_LOGI(TAG, "SAMSUNG COOL LOWFAN %u", temp);
}

void samsung_cool_medfan(uint8_t temp)
{
    switch (temp)
    {
    case 17:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_17_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_17_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_17_COOL_MEDFAN[0]), true));
        break;
    case 18:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_18_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_18_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_18_COOL_MEDFAN[0]), true));
        break;
    case 19:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_19_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_19_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_19_COOL_MEDFAN[0]), true));
        break;
    case 20:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_20_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_20_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_20_COOL_MEDFAN[0]), true));
        break;
    case 21:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_21_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_21_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_21_COOL_MEDFAN[0]), true));
        break;
    case 22:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_22_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_22_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_22_COOL_MEDFAN[0]), true));
        break;
    case 23:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_23_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_23_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_23_COOL_MEDFAN[0]), true));
        break;
    case 24:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_24_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_24_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_24_COOL_MEDFAN[0]), true));
        break;
    case 25:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_25_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_25_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_25_COOL_MEDFAN[0]), true));
        break;
    case 26:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_26_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_26_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_26_COOL_MEDFAN[0]), true));
        break;
    case 27:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_27_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_27_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_27_COOL_MEDFAN[0]), true));
        break;
    case 28:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_28_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_28_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_28_COOL_MEDFAN[0]), true));
        break;
    case 29:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_29_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_29_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_29_COOL_MEDFAN[0]), true));
        break;
    case 30:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_30_COOL_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_30_COOL_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_30_COOL_MEDFAN[0]), true));
        break;
    default:
        ESP_LOGW("WARNING", "Temp you sent is not acknowledged onle from 17-30");
        break;
    }
    // ESP_LOGI(TAG, "SAMSUNG COOL MEDFAN %u", temp);
}

void samsung_cool_highfan(uint8_t temp)
{
    switch (temp)
    {
    case 17:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_17_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_17_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_17_COOL_HIGHFAN[0]), true));
        break;
    case 18:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_18_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_18_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_18_COOL_HIGHFAN[0]), true));
        break;
    case 19:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_19_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_19_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_19_COOL_HIGHFAN[0]), true));
        break;
    case 20:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_20_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_20_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_20_COOL_HIGHFAN[0]), true));
        break;
    case 21:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_21_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_21_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_21_COOL_HIGHFAN[0]), true));
        break;
    case 22:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_22_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_22_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_22_COOL_HIGHFAN[0]), true));
        break;
    case 23:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_23_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_23_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_23_COOL_HIGHFAN[0]), true));
        break;
    case 24:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_24_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_24_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_24_COOL_HIGHFAN[0]), true));
        break;
    case 25:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_25_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_25_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_25_COOL_HIGHFAN[0]), true));
        break;
    case 26:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_26_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_26_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_26_COOL_HIGHFAN[0]), true));
        break;
    case 27:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_27_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_27_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_27_COOL_HIGHFAN[0]), true));
        break;
    case 28:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_28_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_28_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_28_COOL_HIGHFAN[0]), true));
        break;
    case 29:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_29_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_29_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_29_COOL_HIGHFAN[0]), true));
        break;
    case 30:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_30_COOL_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_30_COOL_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_30_COOL_HIGHFAN[0]), true));
        break;
    default:
        ESP_LOGW("WARNING", "Temp you sent is not acknowledged only from 17-30");
        break;
    }
    // ESP_LOGI(TAG, "SAMSUNG COOL HIGHFAN %u", temp);
}

void samsung_cool_autofan(uint8_t temp)
{
    switch (temp)
    {
    case 17:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_17_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_17_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_17_COOL_AUTOFAN[0]), true));
        break;
    case 18:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_18_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_18_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_18_COOL_AUTOFAN[0]), true));
        break;
    case 19:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_19_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_19_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_19_COOL_AUTOFAN[0]), true));
        break;
    case 20:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_20_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_20_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_20_COOL_AUTOFAN[0]), true));
        break;
    case 21:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_21_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_21_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_21_COOL_AUTOFAN[0]), true));
        break;
    case 22:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_22_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_22_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_22_COOL_AUTOFAN[0]), true));
        break;
    case 23:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_23_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_23_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_23_COOL_AUTOFAN[0]), true));
        break;
    case 24:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_24_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_24_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_24_COOL_AUTOFAN[0]), true));
        break;
    case 25:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_25_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_25_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_25_COOL_AUTOFAN[0]), true));
        break;
    case 26:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_26_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_26_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_26_COOL_AUTOFAN[0]), true));
        break;
    case 27:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_27_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_27_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_27_COOL_AUTOFAN[0]), true));
        break;
    case 28:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_28_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_28_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_28_COOL_AUTOFAN[0]), true));
        break;
    case 29:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_29_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_29_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_29_COOL_AUTOFAN[0]), true));
        break;
    case 30:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_30_COOL_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_30_COOL_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_30_COOL_AUTOFAN[0]), true));
        break;
    default:
        ESP_LOGW("WARNING", "Temp you sent is not acknowledged only from 17-30");
        break;
    }
    // ESP_LOGI(TAG, "SAMSUNG COOL AUTOFAN %u", temp);
}

void samsung_dry(uint8_t temp)
{
    switch (temp)
    {
    case 17:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_17_DRY, sizeof(SAMSUNG_TURN_ON_AC_17_DRY) / sizeof(SAMSUNG_TURN_ON_AC_17_DRY[0]), true));
        break;
    case 18:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_18_DRY, sizeof(SAMSUNG_TURN_ON_AC_18_DRY) / sizeof(SAMSUNG_TURN_ON_AC_18_DRY[0]), true));
        break;
    case 19:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_19_DRY, sizeof(SAMSUNG_TURN_ON_AC_19_DRY) / sizeof(SAMSUNG_TURN_ON_AC_19_DRY[0]), true));
        break;
    case 20:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_20_DRY, sizeof(SAMSUNG_TURN_ON_AC_20_DRY) / sizeof(SAMSUNG_TURN_ON_AC_20_DRY[0]), true));
        break;
    case 21:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_21_DRY, sizeof(SAMSUNG_TURN_ON_AC_21_DRY) / sizeof(SAMSUNG_TURN_ON_AC_21_DRY[0]), true));
        break;
    case 22:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_22_DRY, sizeof(SAMSUNG_TURN_ON_AC_22_DRY) / sizeof(SAMSUNG_TURN_ON_AC_22_DRY[0]), true));
        break;
    case 23:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_23_DRY, sizeof(SAMSUNG_TURN_ON_AC_23_DRY) / sizeof(SAMSUNG_TURN_ON_AC_23_DRY[0]), true));
        break;
    case 24:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_24_DRY, sizeof(SAMSUNG_TURN_ON_AC_24_DRY) / sizeof(SAMSUNG_TURN_ON_AC_24_DRY[0]), true));
        break;
    case 25:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_25_DRY, sizeof(SAMSUNG_TURN_ON_AC_25_DRY) / sizeof(SAMSUNG_TURN_ON_AC_25_DRY[0]), true));
        break;
    case 26:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_26_DRY, sizeof(SAMSUNG_TURN_ON_AC_26_DRY) / sizeof(SAMSUNG_TURN_ON_AC_26_DRY[0]), true));
        break;
    case 27:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_27_DRY, sizeof(SAMSUNG_TURN_ON_AC_27_DRY) / sizeof(SAMSUNG_TURN_ON_AC_27_DRY[0]), true));
        break;
    case 28:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_28_DRY, sizeof(SAMSUNG_TURN_ON_AC_28_DRY) / sizeof(SAMSUNG_TURN_ON_AC_28_DRY[0]), true));
        break;
    case 29:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_29_DRY, sizeof(SAMSUNG_TURN_ON_AC_29_DRY) / sizeof(SAMSUNG_TURN_ON_AC_29_DRY[0]), true));
        break;
    case 30:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_30_DRY, sizeof(SAMSUNG_TURN_ON_AC_30_DRY) / sizeof(SAMSUNG_TURN_ON_AC_30_DRY[0]), true));
        break;
    default:
        ESP_LOGW("WARNING", "Temp you sent is not acknowledged only from 17-30");
        break;
    }
    // ESP_LOGI(TAG, "SAMSUNG DRY %u", temp);
}


void samsung_fan_lowfan()
{
    ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_FAN_LOWFAN, sizeof(SAMSUNG_TURN_ON_AC_FAN_LOWFAN) / sizeof(SAMSUNG_TURN_ON_AC_FAN_LOWFAN[0]), true));
    // ESP_LOGI(TAG, "SAMSUNG FAN LOWFAN");
}

void samsung_fan_medfan()
{
    ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_FAN_MEDFAN, sizeof(SAMSUNG_TURN_ON_AC_FAN_MEDFAN) / sizeof(SAMSUNG_TURN_ON_AC_FAN_MEDFAN[0]), true));
    // ESP_LOGI(TAG, "SAMSUNG FAN MEDFAN");
}


void samsung_fan_highfan()
{
    ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_FAN_HIGHFAN, sizeof(SAMSUNG_TURN_ON_AC_FAN_HIGHFAN) / sizeof(SAMSUNG_TURN_ON_AC_FAN_HIGHFAN[0]), true));
    // ESP_LOGI(TAG, "SAMSUNG FAN HIGHFAN");
}


void samsung_fan_autofan()
{
    ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_FAN_AUTOFAN, sizeof(SAMSUNG_TURN_ON_AC_FAN_AUTOFAN) / sizeof(SAMSUNG_TURN_ON_AC_FAN_AUTOFAN[0]), true));
    // ESP_LOGI(TAG, "SAMSUNG FAN AUTOFAN");
}

void samsung_auto(uint8_t temp)
{
    switch (temp)
    {
    case 17:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_17_AUTO, sizeof(SAMSUNG_TURN_ON_AC_17_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_17_AUTO[0]), true));
        break;
    case 18:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_18_AUTO, sizeof(SAMSUNG_TURN_ON_AC_18_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_18_AUTO[0]), true));
        break;
    case 19:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_19_AUTO, sizeof(SAMSUNG_TURN_ON_AC_19_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_19_AUTO[0]), true));
        break;
    case 20:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_20_AUTO, sizeof(SAMSUNG_TURN_ON_AC_20_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_20_AUTO[0]), true));
        break;
    case 21:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_21_AUTO, sizeof(SAMSUNG_TURN_ON_AC_21_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_21_AUTO[0]), true));
        break;
    case 22:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_22_AUTO, sizeof(SAMSUNG_TURN_ON_AC_22_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_22_AUTO[0]), true));
        break;
    case 23:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_23_AUTO, sizeof(SAMSUNG_TURN_ON_AC_23_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_23_AUTO[0]), true));
        break;
    case 24:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_24_AUTO, sizeof(SAMSUNG_TURN_ON_AC_24_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_24_AUTO[0]), true));
        break;
    case 25:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_25_AUTO, sizeof(SAMSUNG_TURN_ON_AC_25_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_25_AUTO[0]), true));
        break;
    case 26:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_26_AUTO, sizeof(SAMSUNG_TURN_ON_AC_26_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_26_AUTO[0]), true));
        break;
    case 27:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_27_AUTO, sizeof(SAMSUNG_TURN_ON_AC_27_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_27_AUTO[0]), true));
        break;
    case 28:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_28_AUTO, sizeof(SAMSUNG_TURN_ON_AC_28_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_28_AUTO[0]), true));
        break;
    case 29:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_29_AUTO, sizeof(SAMSUNG_TURN_ON_AC_29_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_29_AUTO[0]), true));
        break;
    case 30:
        ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_ON_AC_30_AUTO, sizeof(SAMSUNG_TURN_ON_AC_30_AUTO) / sizeof(SAMSUNG_TURN_ON_AC_30_AUTO[0]), true));
        break;
    default:
        ESP_LOGW("WARNING", "Temp you sent is not acknowledged only from 17-30");
        break;
    }
    // ESP_LOGI(TAG, "SAMSUNG AUTO %u", temp);
}


void samsung_toggle_air_direction()
{
    ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_AC_TOGGLE_AIR_DIRECION, sizeof(SAMSUNG_AC_TOGGLE_AIR_DIRECION) / sizeof(SAMSUNG_AC_TOGGLE_AIR_DIRECION[0]), true));
    // ESP_LOGI(TAG, "SAMSUNG TOGGLE AIR DIRECTION");
}

void samsung_toggle_swing()
{
    ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_AC_TOGGLE_SWING, sizeof(SAMSUNG_AC_TOGGLE_SWING) / sizeof(SAMSUNG_AC_TOGGLE_SWING[0]), true));
    // ESP_LOGI(TAG, "SAMSUNG TOGGLE SWING");
}


void samsung_toggle_turbo()
{
    ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_AC_TOGGLE_TURBO, sizeof(SAMSUNG_AC_TOGGLE_TURBO) / sizeof(SAMSUNG_AC_TOGGLE_TURBO[0]), true));
    // ESP_LOGI(TAG, "SAMSUNG TOGGLE TURBO");
}

void samsung_off()
{
    ESP_ERROR_CHECK(rmt_write_items(IR_RMT_CHANNEL, SAMSUNG_TURN_OFF_AC, sizeof(SAMSUNG_TURN_OFF_AC) / sizeof(SAMSUNG_TURN_OFF_AC[0]), true));
    // ESP_LOGI(TAG, "SAMSUNG OFF");
}

/*** END SAMSUNG ***/