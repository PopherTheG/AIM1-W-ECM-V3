#include "gui.h"

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

/* img sources for icons */
#include "gui_img.h"
// LV_IMG_DECLARE(voc_img_map);
/* end */

#define LV_TICK_PERIOD_MS 1

/**
 * Creates a semaphore to handle concurrent calls to lvgl stuff.
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;

void gui_start_task()
{
    /* If you want to use a task to create the graphic, you NEED to create a Pinned
    task. Otherwise there can be problem such as memory corruption and so on.
    NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0. */
    xTaskCreatePinnedToCore(guiTask, "gui", 4096 * 2, NULL, 0, NULL, 1);
}

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

    st7899_display_application();
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

static void voc_bar_value_refresher_task(lv_task_t *task_info);
static void co2_label_value_refresher_task(lv_task_t *task_info);
static void co2_led_value_refresher_task(lv_task_t *task_info);

static lv_style_t screen_style;

static lv_style_t overall_indicator_bar_style;

static lv_style_t voc_value_style;
static lv_style_t voc_bar_style;

static lv_style_t co2_value_style;
static lv_style_t co2_bar_style;

static lv_style_t pm2_5_value_style;
static lv_style_t pm2_5_bar_style;

static lv_style_t pm10_value_style;
static lv_style_t pm10_bar_style;

static lv_style_t temp_value_style;
static lv_style_t temp_box_style;

static lv_style_t hum_value_style;
static lv_style_t hum_box_style;
static lv_style_t hum_bar_style;

void st7899_display_application()
{
    /* screen creation */
    lv_obj_t *screen = lv_obj_create(NULL, NULL);
    lv_scr_load(screen);
    lv_style_init(&screen_style);
    lv_style_set_bg_color(&screen_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(screen, LV_OBJ_PART_MAIN, &screen_style);

    lv_color_t hum_border_color = LV_COLOR_GREEN;
    lv_color_t temp_border_color = LV_COLOR_WHITE;
    lv_color_t voc_border_color = LV_COLOR_GREEN;
    lv_color_t co2_border_color = LV_COLOR_GREEN;
    lv_color_t pm2_5_border_color = LV_COLOR_GREEN;
    lv_color_t pm10_border_color = LV_COLOR_GREEN;

    int8_t bar_x_offset = -10;
    int8_t bar_y_offset = 8;
    int8_t row2_y_offset = 110 + 5;
    int8_t row1_y_offset = 40 + 5;

    /* logo */
    // lv_obj_t *logo_box = lv_obj_create(lv_scr_act(), NULL);
    // lv_obj_set_size(logo_box, 230, 230/4);
    // lv_obj_align(logo_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 5, 5);
    // static lv_style_t logo_box_style;
    // lv_style_init(&logo_box_style);
    // lv_style_set_bg_color(&logo_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&logo_box_style, LV_STATE_DEFAULT, box_border_color);
    // lv_obj_add_style(logo_box, LV_OBJ_PART_MAIN, &logo_box_style);

    // lv_obj_t *logo_icon = lv_img_create(logo_box, NULL);
    // lv_img_set_src(logo_icon, &logo_img_src);
    // lv_obj_align(logo_icon, logo_box, LV_ALIGN_CENTER, 0, -3);

    /* indicator */
    // lv_obj_t *overall_indicator_bar = lv_bar_create(lv_scr_act(), NULL);
    // lv_obj_set_size(overall_indicator_bar, 230, 30);
    // lv_obj_align(overall_indicator_bar, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 0);
    // lv_bar_set_value(overall_indicator_bar, 100, LV_ANIM_OFF);
    // lv_style_init(&overall_indicator_bar_style);
    // lv_style_set_bg_color(&overall_indicator_bar_style, LV_STATE_DEFAULT, LV_COLOR_GREEN);
    // lv_obj_add_style(overall_indicator_bar, LV_BAR_PART_INDIC, &overall_indicator_bar_style);

    // lv_obj_t *overall_indicator_value = lv_label_create(overall_indicator_bar, NULL);
    // lv_obj_align(overall_indicator_value, overall_indicator_bar, LV_ALIGN_IN_TOP_LEFT, 70, 0);
    // lv_label_set_text(overall_indicator_value, "GOOD");
    // static lv_style_t overall_indicator_value_style;
    // lv_style_init(&overall_indicator_value_style);
    // lv_style_set_text_color(&overall_indicator_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_style_set_text_font(&overall_indicator_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    // lv_obj_add_style(overall_indicator_value, LV_OBJ_PART_MAIN, &overall_indicator_value_style);

    lv_obj_t *overall_indicator_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(overall_indicator_box, 240, 230 / 6);
    lv_obj_align(overall_indicator_box, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 0);
    static lv_style_t overall_indicator_box_style;
    lv_style_init(&overall_indicator_box_style);
    lv_style_set_bg_color(&overall_indicator_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_color(&overall_indicator_box_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(overall_indicator_box, LV_OBJ_PART_MAIN, &overall_indicator_box_style);

    lv_obj_t *overall_indicator_title = lv_label_create(overall_indicator_box, NULL);
    lv_obj_align(overall_indicator_title, overall_indicator_box, LV_ALIGN_IN_LEFT_MID, 2, 0);
    lv_label_set_text(overall_indicator_title, "AQI");
    static lv_style_t overall_indicator_title_style;
    lv_style_init(&overall_indicator_title_style);
    lv_style_set_text_color(&overall_indicator_title_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&overall_indicator_title_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
    lv_obj_add_style(overall_indicator_title, LV_OBJ_PART_MAIN, &overall_indicator_title_style);

    lv_obj_t *overall_indicator_pointer = lv_label_create(overall_indicator_box, NULL);
    lv_label_set_text(overall_indicator_pointer, LV_SYMBOL_EJECT);
    lv_obj_align(overall_indicator_pointer, overall_indicator_box, LV_ALIGN_IN_BOTTOM_LEFT, 55, 8);
    static lv_style_t overall_indicator_pointer_style;
    lv_style_set_text_color(&overall_indicator_pointer_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&overall_indicator_pointer_style, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_obj_add_style(overall_indicator_pointer, LV_OBJ_PART_MAIN, &overall_indicator_pointer_style);

    int8_t overall_indicator_color_box_y_offset = 5;
    int8_t overall_indicator_color_box_x_offset = 5;

    lv_obj_t *overall_indicator_green_box = lv_obj_create(overall_indicator_box, NULL);
    lv_obj_set_size(overall_indicator_green_box, 230 / 8, (230 / 12) - 2);
    lv_obj_align(overall_indicator_green_box, overall_indicator_box, LV_ALIGN_IN_TOP_LEFT, (235 / 8) * 2, overall_indicator_color_box_y_offset);
    // lv_obj_set_width_margin(overall_indicator_green_box, 0);
    static lv_style_t overall_indicator_green_box_style;
    lv_style_init(&overall_indicator_green_box_style);
    lv_style_set_radius(&overall_indicator_green_box_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&overall_indicator_green_box_style, LV_STATE_DEFAULT, LV_COLOR_GOOD);
    lv_style_set_border_color(&overall_indicator_green_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(overall_indicator_green_box, LV_OBJ_PART_MAIN, &overall_indicator_green_box_style);

    lv_obj_t *overall_indicator_yellow_box = lv_obj_create(overall_indicator_box, NULL);
    lv_obj_set_size(overall_indicator_yellow_box, 230 / 8, (230 / 12) - 2);
    lv_obj_align(overall_indicator_yellow_box, overall_indicator_box, LV_ALIGN_IN_TOP_LEFT, (235 / 8) * 3, overall_indicator_color_box_y_offset);
    // lv_obj_set_width_margin(overall_indicator_green_box, 0);
    static lv_style_t overall_indicator_yellow_box_style;
    lv_style_init(&overall_indicator_yellow_box_style);
    lv_style_set_radius(&overall_indicator_yellow_box_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&overall_indicator_yellow_box_style, LV_STATE_DEFAULT, LV_COLOR_GOOD);
    lv_style_set_border_color(&overall_indicator_yellow_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(overall_indicator_yellow_box, LV_OBJ_PART_MAIN, &overall_indicator_yellow_box_style);

    lv_obj_t *overall_indicator_orange_box = lv_obj_create(overall_indicator_box, NULL);
    lv_obj_set_size(overall_indicator_orange_box, 230 / 8, (230 / 12) - 2);
    lv_obj_align(overall_indicator_orange_box, overall_indicator_box, LV_ALIGN_IN_TOP_LEFT, (235 / 8) * 4, overall_indicator_color_box_y_offset);
    static lv_style_t overall_indicator_orange_box_style;
    lv_style_init(&overall_indicator_orange_box_style);
    lv_style_set_radius(&overall_indicator_orange_box_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&overall_indicator_orange_box_style, LV_STATE_DEFAULT, LV_COLOR_MODERATE);
    lv_style_set_border_color(&overall_indicator_orange_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(overall_indicator_orange_box, LV_OBJ_PART_MAIN, &overall_indicator_orange_box_style);

    lv_obj_t *overall_indicator_maroon_box = lv_obj_create(overall_indicator_box, NULL);
    lv_obj_set_size(overall_indicator_maroon_box, 230 / 8, (230 / 12) - 2);
    lv_obj_align(overall_indicator_maroon_box, overall_indicator_box, LV_ALIGN_IN_TOP_LEFT, (235 / 8) * 5, overall_indicator_color_box_y_offset);
    static lv_style_t overall_indicator_maroon_box_style;
    lv_style_init(&overall_indicator_maroon_box_style);
    lv_style_set_radius(&overall_indicator_maroon_box_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&overall_indicator_maroon_box_style, LV_STATE_DEFAULT, LV_COLOR_MODERATE);
    lv_style_set_border_color(&overall_indicator_maroon_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(overall_indicator_maroon_box, LV_OBJ_PART_MAIN, &overall_indicator_maroon_box_style);

    lv_obj_t *overall_indicator_pink_box = lv_obj_create(overall_indicator_box, NULL);
    lv_obj_set_size(overall_indicator_pink_box, 230 / 8, (230 / 12) - 2);
    lv_obj_align(overall_indicator_pink_box, overall_indicator_box, LV_ALIGN_IN_TOP_LEFT, (235 / 8) * 6, overall_indicator_color_box_y_offset);
    static lv_style_t overall_indicator_pink_box_style;
    lv_style_init(&overall_indicator_pink_box_style);
    lv_style_set_radius(&overall_indicator_pink_box_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&overall_indicator_pink_box_style, LV_STATE_DEFAULT, LV_COLOR_UNHEALTHY);
    lv_style_set_border_color(&overall_indicator_pink_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(overall_indicator_pink_box, LV_OBJ_PART_MAIN, &overall_indicator_pink_box_style);

    lv_obj_t *overall_indicator_red_box = lv_obj_create(overall_indicator_box, NULL);
    lv_obj_set_size(overall_indicator_red_box, 230 / 8, (230 / 12) - 2);
    lv_obj_align(overall_indicator_red_box, overall_indicator_box, LV_ALIGN_IN_TOP_LEFT, (235 / 8) * 7, overall_indicator_color_box_y_offset);
    static lv_style_t overall_indicator_red_box_style;
    lv_style_init(&overall_indicator_red_box_style);
    lv_style_set_radius(&overall_indicator_red_box_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&overall_indicator_red_box_style, LV_STATE_DEFAULT, LV_COLOR_UNHEALTHY);
    lv_style_set_border_color(&overall_indicator_red_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(overall_indicator_red_box, LV_OBJ_PART_MAIN, &overall_indicator_red_box_style);

    /*
    lv_obj_t *overall_indicator_green_box = lv_obj_create(overall_indicator_box, NULL);
    lv_obj_set_size(overall_indicator_green_box, 230 / 8, (230 / 9) - 2);
    lv_obj_align(overall_indicator_green_box, overall_indicator_box, LV_ALIGN_IN_LEFT_MID, 0, 0);
    static lv_style_t overall_indicator_green_box_style;
    lv_style_init(&overall_indicator_green_box_style);
    lv_style_set_bg_color(&overall_indicator_green_box_style, LV_STATE_DEFAULT, LV_COLOR_GREEN);
    lv_style_set_border_color(&overall_indicator_green_box_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(overall_indicator_green_box, LV_OBJ_PART_MAIN, &overall_indicator_green_box_style);
*/
    /* voc */
    lv_obj_t *voc_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(voc_box, 230 / 2, 230 / 4);
    lv_obj_align(voc_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, row1_y_offset);
    static lv_style_t voc_box_style;
    lv_style_init(&voc_box_style);
    lv_style_set_bg_color(&voc_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_color(&voc_box_style, LV_STATE_DEFAULT, voc_border_color);
    lv_obj_add_style(voc_box, LV_OBJ_PART_MAIN, &voc_box_style);

    // lv_obj_t *voc_icon = lv_img_create(voc_box, NULL);
    // lv_img_set_src(voc_icon, &voc_img_src);
    // lv_obj_align(voc_icon, voc_box, LV_ALIGN_IN_TOP_LEFT, 3, 3);

    lv_obj_t *voc_value = lv_label_create(voc_box, NULL);
    lv_label_set_text(voc_value, "42");
    // lv_obj_align(voc_value, voc_box, LV_ALIGN_IN_TOP_LEFT, 33, 0);
    lv_obj_align(voc_value, voc_box, LV_ALIGN_IN_TOP_LEFT, 3, 0);
    // static lv_style_t voc_value_style;
    lv_style_init(&voc_value_style);
    lv_style_set_text_font(&voc_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_28);
    lv_style_set_text_color(&voc_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(voc_value, LV_OBJ_PART_MAIN, &voc_value_style);

    lv_obj_t *voc_bar = lv_bar_create(voc_box, NULL);
    lv_obj_set_size(voc_bar, (6), (230 / 4) - 10);
    lv_obj_align(voc_bar, voc_box, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_bar_set_value(voc_bar, 100, LV_ANIM_OFF);
    lv_style_init(&voc_bar_style);
    lv_style_set_bg_color(&voc_bar_style, LV_STATE_DEFAULT, LV_COLOR_GREEN);
    lv_obj_add_style(voc_bar, LV_BAR_PART_INDIC, &voc_bar_style);

    lv_obj_t *voc_label = lv_label_create(voc_box, NULL);
    lv_label_set_text(voc_label, "VOC");
    lv_obj_align(voc_label, voc_box, LV_ALIGN_IN_BOTTOM_LEFT, 3, 0);
    static lv_style_t voc_label_style;
    lv_style_init(&voc_label_style);
    lv_style_set_text_font(&voc_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_18);
    lv_style_set_text_color(&voc_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(voc_label, LV_OBJ_PART_MAIN, &voc_label_style);

    /* co2 */
    lv_obj_t *co2_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(co2_box, 230 / 2, 230 / 4);
    lv_obj_align(co2_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, (230 / 2) + 10, row1_y_offset);
    static lv_style_t co2_box_style;
    lv_style_init(&co2_box_style);
    lv_style_set_bg_color(&co2_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_color(&co2_box_style, LV_STATE_DEFAULT, co2_border_color);
    lv_obj_add_style(co2_box, LV_OBJ_PART_MAIN, &co2_box_style);

    // lv_obj_t *co2_icon = lv_img_create(co2_box, NULL);
    // lv_img_set_src(co2_icon, &voc_img_src);
    // lv_obj_align(co2_icon, co2_box, LV_ALIGN_IN_TOP_LEFT, 3, 6);

    lv_obj_t *co2_value = lv_label_create(co2_box, NULL);
    lv_label_set_text(co2_value, "317");
    // lv_obj_align(co2_value, co2_box, LV_ALIGN_IN_TOP_LEFT, 30, 0);
    lv_obj_align(co2_value, co2_box, LV_ALIGN_IN_TOP_LEFT, 3, 0);
    lv_style_init(&co2_value_style);
    lv_style_set_text_font(&co2_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_28);
    lv_style_set_text_color(&co2_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(co2_value, LV_OBJ_PART_MAIN, &co2_value_style);

    lv_obj_t *co2_bar = lv_bar_create(co2_box, NULL);
    lv_obj_set_size(co2_bar, (6), (230 / 4) - 10);
    lv_obj_align(co2_bar, co2_box, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_bar_set_value(co2_bar, 100, LV_ANIM_OFF);
    lv_style_init(&co2_bar_style);
    lv_style_set_bg_color(&co2_bar_style, LV_STATE_DEFAULT, LV_COLOR_GREEN);
    lv_obj_add_style(co2_bar, LV_BAR_PART_INDIC, &co2_bar_style);

    lv_obj_t *co2_label = lv_label_create(co2_box, NULL);
    lv_label_set_text(co2_label, "CO2 (ppm)");
    lv_obj_align(co2_label, co2_box, LV_ALIGN_IN_BOTTOM_LEFT, 3, 0);
    static lv_style_t co2_label_style;
    lv_style_init(&co2_label_style);
    lv_style_set_text_font(&co2_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_16);
    lv_style_set_text_color(&co2_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(co2_label, LV_OBJ_PART_MAIN, &co2_label_style);

    /* temp */
    lv_obj_t *temp_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(temp_box, 230 / 2, 230 / 4);
    lv_obj_align(temp_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, row2_y_offset);
    static lv_style_t temp_box_style;
    lv_style_init(&temp_box_style);
    lv_style_set_bg_color(&temp_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_color(&temp_box_style, LV_STATE_DEFAULT, temp_border_color);
    lv_obj_add_style(temp_box, LV_OBJ_PART_MAIN, &temp_box_style);

    // lv_obj_t *temp_icon = lv_img_create(temp_box, NULL);
    // lv_img_set_src(temp_icon, &temp_img_src);
    // lv_obj_align(temp_icon, temp_box, LV_ALIGN_IN_TOP_LEFT, 3, 3);

    lv_obj_t *temp_value = lv_label_create(temp_box, NULL);
    lv_label_set_text(temp_value, "25.4C");
    // lv_obj_align(temp_value, temp_box, LV_ALIGN_IN_TOP_LEFT, 30, 0);
    lv_obj_align(temp_value, temp_box, LV_ALIGN_IN_TOP_LEFT, 3, 0);
    static lv_style_t temp_value_style;
    lv_style_init(&temp_value_style);
    lv_style_set_text_font(&temp_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_26);
    lv_style_set_text_color(&temp_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(temp_value, LV_OBJ_PART_MAIN, &temp_value_style);

    lv_obj_t *temp_label = lv_label_create(temp_box, NULL);
    lv_label_set_text(temp_label, "Temperature");
    lv_obj_align(temp_label, temp_box, LV_ALIGN_IN_BOTTOM_LEFT, 3, 0);
    static lv_style_t temp_label_style;
    lv_style_init(&temp_label_style);
    lv_style_set_text_font(&temp_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_16);
    lv_style_set_text_color(&temp_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(temp_label, LV_OBJ_PART_MAIN, &temp_label_style);

    /* hum */
    lv_obj_t *hum_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(hum_box, 230 / 2, 230 / 4);
    lv_obj_align(hum_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, (230 / 2) + 10, row2_y_offset);
    static lv_style_t hum_box_style;
    lv_style_init(&hum_box_style);
    lv_style_set_bg_color(&hum_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_color(&hum_box_style, LV_STATE_DEFAULT, hum_border_color);
    lv_obj_add_style(hum_box, LV_OBJ_PART_MAIN, &hum_box_style);

    // lv_obj_t *hum_icon = lv_img_create(hum_box, NULL);
    // lv_img_set_src(hum_icon, &hum_img_src);
    // lv_obj_align(hum_icon, hum_box, LV_ALIGN_IN_TOP_LEFT, 3, 3);

    lv_obj_t *hum_value = lv_label_create(hum_box, NULL);
    lv_label_set_text(hum_value, "47%");
    // lv_obj_align(hum_value, hum_box, LV_ALIGN_IN_TOP_LEFT, 35, 0);
    lv_obj_align(hum_value, hum_box, LV_ALIGN_IN_TOP_LEFT, 3, 0);
    static lv_style_t hum_value_style;
    lv_style_init(&hum_value_style);
    lv_style_set_text_font(&hum_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_26);
    lv_style_set_text_color(&hum_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(hum_value, LV_OBJ_PART_MAIN, &hum_value_style);

    lv_obj_t *hum_label = lv_label_create(hum_box, NULL);
    lv_label_set_text(hum_label, "Humidity");
    lv_obj_align(hum_label, hum_box, LV_ALIGN_IN_BOTTOM_LEFT, 3, 0);
    static lv_style_t hum_label_style;
    lv_style_init(&hum_label_style);
    lv_style_set_text_font(&hum_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_16);
    lv_style_set_text_color(&hum_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(hum_label, LV_OBJ_PART_MAIN, &hum_label_style);

    lv_obj_t *hum_bar = lv_bar_create(hum_box, NULL);
    lv_obj_set_size(hum_bar, (6), (230 / 4) - 10);
    lv_obj_align(hum_bar, hum_box, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_bar_set_value(hum_bar, 100, LV_ANIM_OFF);
    lv_style_init(&hum_bar_style);
    lv_style_set_bg_color(&hum_bar_style, LV_STATE_DEFAULT, LV_COLOR_GREEN);
    lv_obj_add_style(hum_bar, LV_BAR_PART_INDIC, &hum_bar_style);

#define PM_SENSORS_INSTALLED
#ifdef PM_SENSORS_INSTALLED
    /* pm2.5 */
    lv_obj_t *pm2_5_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(pm2_5_box, 230 / 2, 230 / 4);
    lv_obj_align(pm2_5_box, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    static lv_style_t pm2_5_box_style;
    lv_style_init(&pm2_5_box_style);
    lv_style_set_bg_color(&pm2_5_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_color(&pm2_5_box_style, LV_STATE_DEFAULT, pm2_5_border_color);
    lv_obj_add_style(pm2_5_box, LV_OBJ_PART_MAIN, &pm2_5_box_style);

    // lv_obj_t *pm2_5_icon = lv_img_create(pm2_5_box, NULL);
    // lv_img_set_src(pm2_5_icon, &dust_img_src);
    // lv_obj_align(pm2_5_icon, pm2_5_box, LV_ALIGN_IN_TOP_LEFT, 3, 6);

    lv_obj_t *pm2_5_value = lv_label_create(pm2_5_box, NULL);
    lv_label_set_text(pm2_5_value, "10.7");
    lv_obj_align(pm2_5_value, pm2_5_box, LV_ALIGN_IN_TOP_LEFT, 3, 0);
    // lv_obj_align(pm2_5_value, pm2_5_box, LV_ALIGN_IN_TOP_LEFT, 30, 0);
    static lv_style_t pm2_5_value_style;
    lv_style_init(&pm2_5_value_style);
    lv_style_set_text_font(&pm2_5_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_28);
    lv_style_set_text_color(&pm2_5_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(pm2_5_value, LV_OBJ_PART_MAIN, &pm2_5_value_style);

    lv_obj_t *pm2_5_bar = lv_bar_create(pm2_5_box, NULL);
    lv_obj_set_size(pm2_5_bar, (6), (230 / 4) - 10);
    lv_obj_align(pm2_5_bar, pm2_5_box, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_bar_set_value(pm2_5_bar, 100, LV_ANIM_OFF);
    lv_style_init(&pm2_5_bar_style);
    lv_style_set_bg_color(&pm2_5_bar_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm2_5_bar, LV_BAR_PART_INDIC, &pm2_5_bar_style);

    lv_obj_t *pm2_5_label = lv_label_create(pm2_5_box, NULL);
    lv_label_set_text(pm2_5_label, "PM2.5 (ug/m3)");
    lv_obj_align(pm2_5_label, pm2_5_box, LV_ALIGN_IN_BOTTOM_LEFT, 3, 0);
    static lv_style_t pm2_5_label_style;
    lv_style_init(&pm2_5_label_style);
    lv_style_set_text_font(&pm2_5_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_style_set_text_color(&pm2_5_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(pm2_5_label, LV_OBJ_PART_MAIN, &pm2_5_label_style);

    lv_obj_t *pm2_5_unit = lv_label_create(pm2_5_box, NULL);
    lv_label_set_text(pm2_5_unit, "");
    lv_obj_align(pm2_5_unit, pm2_5_box, LV_ALIGN_IN_BOTTOM_LEFT, 53, 0);
    static lv_style_t pm2_5_unit_style;
    lv_style_init(&pm2_5_unit_style);
    lv_style_set_text_font(&pm2_5_unit_style, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_style_set_text_color(&pm2_5_unit_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm2_5_unit, LV_OBJ_PART_MAIN, &pm2_5_unit_style);

    /* pm10 */
    lv_obj_t *pm10_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(pm10_box, 230 / 2, 230 / 4);
    lv_obj_align(pm10_box, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, (230 / 2) + 10, 0);
    static lv_style_t pm10_box_style;
    lv_style_init(&pm10_box_style);
    lv_style_set_bg_color(&pm10_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_color(&pm10_box_style, LV_STATE_DEFAULT, pm10_border_color);
    lv_obj_add_style(pm10_box, LV_OBJ_PART_MAIN, &pm10_box_style);

    // lv_obj_t *pm10_icon = lv_img_create(pm10_box, NULL);
    // lv_img_set_src(pm10_icon, &dust_img_src);
    // lv_obj_align(pm10_icon, pm10_box, LV_ALIGN_IN_TOP_LEFT, 3, 6);

    lv_obj_t *pm10_value = lv_label_create(pm10_box, NULL);
    lv_label_set_text(pm10_value, "9.7");
    // lv_obj_align(pm10_value, pm10_box, LV_ALIGN_IN_TOP_LEFT, 30, 0);
    lv_obj_align(pm10_value, pm10_box, LV_ALIGN_IN_TOP_LEFT, 3, 0);
    static lv_style_t pm10_value_style;
    lv_style_init(&pm10_value_style);
    lv_style_set_text_font(&pm10_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_28);
    lv_style_set_text_color(&pm10_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(pm10_value, LV_OBJ_PART_MAIN, &pm10_value_style);

    lv_obj_t *pm10_bar = lv_bar_create(pm10_box, NULL);
    lv_obj_set_size(pm10_bar, (6), (230 / 4) - 10);
    lv_obj_align(pm10_bar, pm10_box, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_bar_set_value(pm10_bar, 100, LV_ANIM_OFF);
    lv_style_init(&pm10_bar_style);
    lv_style_set_bg_color(&pm10_bar_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm10_bar, LV_BAR_PART_INDIC, &pm10_bar_style);

    lv_obj_t *pm10_label = lv_label_create(pm10_box, NULL);
    lv_label_set_text(pm10_label, "PM10 (ug/m3)");
    lv_obj_align(pm10_label, pm10_box, LV_ALIGN_IN_BOTTOM_LEFT, 3, 0);
    static lv_style_t pm10_label_style;
    lv_style_init(&pm10_label_style);
    lv_style_set_text_font(&pm10_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_style_set_text_color(&pm10_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(pm10_label, LV_OBJ_PART_MAIN, &pm10_label_style);

    lv_obj_t *pm10_unit = lv_label_create(pm10_box, NULL);
    lv_label_set_text(pm10_unit, "");
    lv_obj_align(pm10_unit, pm10_box, LV_ALIGN_IN_BOTTOM_LEFT, 50, 0);
    static lv_style_t pm10_unit_style;
    lv_style_init(&pm10_unit_style);
    lv_style_set_text_font(&pm10_unit_style, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_style_set_text_color(&pm10_unit_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm10_unit, LV_OBJ_PART_MAIN, &pm10_unit_style);
#else
    /* pm2.5 */
    lv_obj_t *pm2_5_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(pm2_5_box, 230 / 2, 230 / 4);
    lv_obj_align(pm2_5_box, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    static lv_style_t pm2_5_box_style;
    lv_style_init(&pm2_5_box_style);
    lv_style_set_bg_color(&pm2_5_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_color(&pm2_5_box_style, LV_STATE_DEFAULT, pm2_5_border_color);
    lv_obj_add_style(pm2_5_box, LV_OBJ_PART_MAIN, &pm2_5_box_style);

    lv_obj_t *pm2_5_value = lv_label_create(pm2_5_box, NULL);
    lv_label_set_text(pm2_5_value, "na");
    lv_obj_align(pm2_5_value, pm2_5_box, LV_ALIGN_IN_TOP_LEFT, 3, 0);
    // lv_obj_align(pm2_5_value, pm2_5_box, LV_ALIGN_IN_TOP_LEFT, 30, 0);
    static lv_style_t pm2_5_value_style;
    lv_style_init(&pm2_5_value_style);
    lv_style_set_text_font(&pm2_5_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_28);
    lv_style_set_text_color(&pm2_5_value_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm2_5_value, LV_OBJ_PART_MAIN, &pm2_5_value_style);

    lv_obj_t *pm2_5_bar = lv_bar_create(pm2_5_box, NULL);
    lv_obj_set_size(pm2_5_bar, (6), (230 / 4) - 10);
    lv_obj_align(pm2_5_bar, pm2_5_box, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_bar_set_value(pm2_5_bar, 100, LV_ANIM_OFF);
    lv_style_init(&pm2_5_bar_style);
    lv_style_set_bg_color(&pm2_5_bar_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm2_5_bar, LV_BAR_PART_INDIC, &pm2_5_bar_style);

    lv_obj_t *pm2_5_label = lv_label_create(pm2_5_box, NULL);
    lv_label_set_text(pm2_5_label, "PM2.5 (ug/m³)");
    lv_obj_align(pm2_5_label, pm2_5_box, LV_ALIGN_IN_BOTTOM_LEFT, 3, 0);
    static lv_style_t pm2_5_label_style;
    lv_style_init(&pm2_5_label_style);
    lv_style_set_text_font(&pm2_5_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_style_set_text_color(&pm2_5_label_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm2_5_label, LV_OBJ_PART_MAIN, &pm2_5_label_style);

    lv_obj_t *pm2_5_unit = lv_label_create(pm2_5_box, NULL);
    lv_label_set_text(pm2_5_unit, "");
    lv_obj_align(pm2_5_unit, pm2_5_box, LV_ALIGN_IN_BOTTOM_LEFT, 53, 0);
    static lv_style_t pm2_5_unit_style;
    lv_style_init(&pm2_5_unit_style);
    lv_style_set_text_font(&pm2_5_unit_style, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_style_set_text_color(&pm2_5_unit_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm2_5_unit, LV_OBJ_PART_MAIN, &pm2_5_unit_style);

    /* pm10 */
    lv_obj_t *pm10_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(pm10_box, 230 / 2, 230 / 4);
    lv_obj_align(pm10_box, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, (230 / 2) + 10, 0);
    static lv_style_t pm10_box_style;
    lv_style_init(&pm10_box_style);
    lv_style_set_bg_color(&pm10_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_color(&pm10_box_style, LV_STATE_DEFAULT, pm10_border_color);
    lv_obj_add_style(pm10_box, LV_OBJ_PART_MAIN, &pm10_box_style);

    // lv_obj_t *pm10_icon = lv_img_create(pm10_box, NULL);
    // lv_img_set_src(pm10_icon, &dust_img_src);
    // lv_obj_align(pm10_icon, pm10_box, LV_ALIGN_IN_TOP_LEFT, 3, 6);

    lv_obj_t *pm10_value = lv_label_create(pm10_box, NULL);
    lv_label_set_text(pm10_value, "na");
    // lv_obj_align(pm10_value, pm10_box, LV_ALIGN_IN_TOP_LEFT, 30, 0);
    lv_obj_align(pm10_value, pm10_box, LV_ALIGN_IN_TOP_LEFT, 3, 0);
    static lv_style_t pm10_value_style;
    lv_style_init(&pm10_value_style);
    lv_style_set_text_font(&pm10_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_28);
    lv_style_set_text_color(&pm10_value_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm10_value, LV_OBJ_PART_MAIN, &pm10_value_style);

    lv_obj_t *pm10_bar = lv_bar_create(pm10_box, NULL);
    lv_obj_set_size(pm10_bar, (6), (230 / 4) - 10);
    lv_obj_align(pm10_bar, pm10_box, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_bar_set_value(pm10_bar, 100, LV_ANIM_OFF);
    lv_style_init(&pm10_bar_style);
    lv_style_set_bg_color(&pm10_bar_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm10_bar, LV_BAR_PART_INDIC, &pm10_bar_style);

    lv_obj_t *pm10_label = lv_label_create(pm10_box, NULL);
    lv_label_set_text(pm10_label, "PM10 (ug/m3)");
    lv_obj_align(pm10_label, pm10_box, LV_ALIGN_IN_BOTTOM_LEFT, 3, 0);
    static lv_style_t pm10_label_style;
    lv_style_init(&pm10_label_style);
    lv_style_set_text_font(&pm10_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_style_set_text_color(&pm10_label_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm10_label, LV_OBJ_PART_MAIN, &pm10_label_style);

    lv_obj_t *pm10_unit = lv_label_create(pm10_box, NULL);
    lv_label_set_text(pm10_unit, "");
    lv_obj_align(pm10_unit, pm10_box, LV_ALIGN_IN_BOTTOM_LEFT, 50, 0);
    static lv_style_t pm10_unit_style;
    lv_style_init(&pm10_unit_style);
    lv_style_set_text_font(&pm10_unit_style, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_style_set_text_color(&pm10_unit_style, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_add_style(pm10_unit, LV_OBJ_PART_MAIN, &pm10_unit_style);
#endif
    /* new new new end */

    // /* task creation for dynamic value handling */
    // // lv_task_create(pm2_5_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)pm2_5_label);    /* task to update pm2.5 value on tft display */
    // // lv_task_create(pm10_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)pm10_label);      /* task to update pm10 value on tft display */
    // lv_task_create(overall_indicator_bar_refresher_task, 250, LV_TASK_PRIO_MID, (void *)overall_indicator_bar);
    // lv_task_create(overall_indicator_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)overall_indicator_value);
    // lv_task_create(voc_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)voc_value); /* task to update voc value on tft display */
    // lv_task_create(voc_bar_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)voc_bar);     /* task to update the bar graphics of voc  on tft display */
    // lv_task_create(co2_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)co2_value);   /* task to update the co2 value on tft display */
    // lv_task_create(co2_led_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)co2_bar);       /* task to update the bar graphics of co2 on tft display */
    // lv_task_create(temp_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)temp_value); /* task to update pm10 value on tft display */
    // lv_task_create(hum_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)hum_value);   /* task to update pm10 value on tft display */
}

/**
 * @brief   callback function to update pm2.5 label data on the display.
 */
static void pm2_5_label_value_refresher_task(lv_task_t *task_info)
{
    /* update label value */
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "PM2.5: \n%.02fug/m3", SPS30_PM2_5);
}
/**
 * @brief   callback function to update pm10 label data on the display.
 */
static void pm10_label_value_refresher_task(lv_task_t *task_info)
{
    /* update label value */
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "PM10: \n%.02fug/m3", SPS30_PM10);
}
/**
 * @brief   callback function to update the color of the bar
 */
static void overall_indicator_bar_refresher_task(lv_task_t *task_info)
{
}
/**
 * @brief   callback function to update the status of the overall air condition
 */
static void overall_indicator_value_refresher_task(lv_task_t *task_info)
{
}
/**
 * @brief   callback function to update voc label data on the display.
 */
static void voc_label_value_refresher_task(lv_task_t *task_info)
{
    /* update value */
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "%u", (uint16_t)SVM40_VOC);
    // lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "");
}
static void voc_bar_value_refresher_task(lv_task_t *task_info)
{
    /* update value */
    // int16_t scaled_voc_value = SVM40_VOC / 5;
    // lv_bar_set_anim_time((lv_obj_t *)(task_info->user_data), 200);
    lv_bar_set_value((lv_obj_t *)(task_info->user_data), 100, LV_ANIM_OFF);

    /* change color of the bar depending on the value. based on https://aqicn.org/faq/2013-09-09/revised-pm25-aqi-breakpoints/ */
    /**
     * GREEN -> GOOD
     * YELLOW -> MODERATE
     * ORANGE -> UNHEALTHY FOR SENSITIVE GROUPS
     * RED -> UNHEALTHY
     * PURPLE -> VERY UNHEALTHY
     * MAROON -> HAZARDOUS 
     */
    uint16_t voc_val = (uint16_t)SVM40_VOC;
    if (voc_val >= 0 && voc_val <= 50)
    {
        lv_style_set_bg_color(&voc_bar_style, LV_STATE_DEFAULT, LV_COLOR_GREEN);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &voc_bar_style);
    }
    else if (voc_val >= 51 && voc_val <= 100)
    {
        lv_style_set_bg_color(&voc_bar_style, LV_STATE_DEFAULT, LV_COLOR_YELLOW);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &voc_bar_style);
    }
    else if (voc_val >= 101 && voc_val <= 150)
    {
        lv_style_set_bg_color(&voc_bar_style, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &voc_bar_style);
    }
    else if (voc_val >= 151 && voc_val <= 200)
    {
        lv_style_set_bg_color(&voc_bar_style, LV_STATE_DEFAULT, LV_COLOR_RED);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &voc_bar_style);
    }
    else if (voc_val >= 201 && voc_val <= 300)
    {
        lv_style_set_bg_color(&voc_bar_style, LV_STATE_DEFAULT, LV_COLOR_PURPLE);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &voc_bar_style);
    }
    else if (voc_val >= 301)
    {
        lv_style_set_bg_color(&voc_bar_style, LV_STATE_DEFAULT, LV_COLOR_MAROON);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &voc_bar_style);
    }
}
static void co2_label_value_refresher_task(lv_task_t *task_info)
{
    /* update value */
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "%u", (uint16_t)2500);
    // lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "");
}
static void co2_led_value_refresher_task(lv_task_t *task_info)
{
    /* update led color based on co2 level based on wisconsin air department */
    SCD4x_CO2 = 2500;
    lv_bar_set_value((lv_obj_t *)(task_info->user_data), 100, LV_ANIM_OFF);
    if (SCD4x_CO2 >= 0 && SCD4x_CO2 <= 400)
    {
        lv_style_set_bg_color(&co2_bar_style, LV_STATE_DEFAULT, LV_COLOR_GREEN);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &co2_bar_style);
    }
    else if (SCD4x_CO2 >= 401 && SCD4x_CO2 <= 1000)
    {
        lv_style_set_bg_color(&co2_bar_style, LV_STATE_DEFAULT, LV_COLOR_YELLOW);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &co2_bar_style);
    }
    else if (SCD4x_CO2 >= 1001 && SCD4x_CO2 <= 2000)
    {
        lv_style_set_bg_color(&co2_bar_style, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &co2_bar_style);
    }
    else if (SCD4x_CO2 >= 2000 && SCD4x_CO2 <= 5000)
    {
        lv_style_set_bg_color(&co2_bar_style, LV_STATE_DEFAULT, LV_COLOR_RED);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &co2_bar_style);
    }
    else if (SCD4x_CO2 >= 5001 && SCD4x_CO2 <= 40000)
    {
        lv_style_set_bg_color(&co2_bar_style, LV_STATE_DEFAULT, LV_COLOR_PURPLE);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &co2_bar_style);
    }
    else if (SCD4x_CO2 >= 40001)
    {
        lv_style_set_bg_color(&co2_bar_style, LV_STATE_DEFAULT, LV_COLOR_MAROON);
        lv_obj_add_style((lv_obj_t *)(task_info->user_data), LV_BAR_PART_INDIC, &co2_bar_style);
    }
}
/**
 * @brief   callback function to update temp label data on the display.
 */
static void temp_label_value_refresher_task(lv_task_t *task_info)
{
    /* update label value */
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "%.01fC", SVM40_TEMP);
}
/**
 * @brief   callback function to update hum label data on the display.
 */
static void hum_label_value_refresher_task(lv_task_t *task_info)
{
    /* update label value */
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "%u%%", (uint8_t)SVM40_HUM);
}

static void lv_tick_task(void *arg)
{
    (void)arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}