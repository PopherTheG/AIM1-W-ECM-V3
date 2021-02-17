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
static void co2_bar_value_refresher_task(lv_task_t *task_info);

static lv_style_t voc_label_style;
static lv_style_t voc_value_style;
static lv_style_t voc_bar_style;
static lv_style_t co2_label_style;
static lv_style_t co2_value_style;
static lv_style_t co2_bar_style;
static lv_style_t temp_value_style;
static lv_style_t hum_value_style;

void st7899_display_application()
{
    /* screen creation */
    lv_obj_t *screen = lv_obj_create(NULL, NULL);
    lv_scr_load(screen);

    // static lv_style_t pm2_5_label_style;
    // static lv_style_t pm10_label_style;
    // static lv_style_t temp_label_style;
    // static lv_style_t hum_label_style;
    // lv_style_init(&pm2_5_label_style);
    // lv_style_init(&pm10_label_style);
    lv_style_init(&voc_value_style);
    lv_style_init(&voc_label_style);
    lv_style_init(&voc_bar_style);
    lv_style_init(&co2_label_style);
    lv_style_init(&co2_value_style);
    lv_style_init(&co2_bar_style);
    lv_style_init(&temp_value_style);
    lv_style_init(&hum_value_style);

    /* changing font size of label_style */
    // lv_style_set_text_font(&pm2_5_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    // lv_style_set_text_font(&pm10_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    lv_style_set_text_font(&temp_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    lv_style_set_text_font(&hum_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    lv_style_set_text_font(&voc_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    lv_style_set_text_font(&voc_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    lv_style_set_text_font(&co2_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    lv_style_set_text_font(&co2_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    // lv_obj_t *pm2_5_label = lv_label_create(lv_scr_act(), NULL);
    // lv_obj_t *pm10_label = lv_label_create(lv_scr_act(), NULL);
    // lv_obj_t *temp_label = lv_label_create(lv_scr_act(), NULL);
    // lv_obj_t *hum_label = lv_label_create(lv_scr_act(), NULL);

    /* voc related objects */
    lv_obj_t *voc_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(voc_box, 240, 48);
    lv_obj_align(voc_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

    lv_obj_t *voc_label = lv_label_create(voc_box, NULL);
    lv_label_set_text(voc_label, "VOC");
    lv_obj_align(voc_label, voc_box, LV_ALIGN_IN_LEFT_MID, 0, 0);

    lv_obj_t *voc_bar = lv_bar_create(voc_box, NULL);
    lv_obj_set_size(voc_bar, 100, 12);
    lv_obj_align(voc_bar, voc_box, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    lv_obj_t *voc_value = lv_label_create(voc_box, NULL);
    lv_obj_align(voc_value, voc_box, LV_ALIGN_CENTER, 0, 0);

    /* co2 related objects */
    lv_obj_t *co2_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(co2_box, 240, 48);
    lv_obj_set_pos(co2_box, 0, 48);

    lv_obj_t *co2_label = lv_label_create(co2_box, NULL);
    lv_label_set_text(co2_label, "CO2");
    lv_obj_align(co2_label, co2_box, LV_ALIGN_IN_LEFT_MID, 0, 0);

    lv_obj_t *co2_bar = lv_bar_create(co2_box, NULL);
    lv_obj_set_size(co2_bar, 100, 12);
    lv_obj_align(co2_bar, co2_box, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    lv_obj_t *co2_value = lv_label_create(co2_box, NULL);
    lv_obj_align(co2_value, co2_box, LV_ALIGN_IN_BOTTOM_MID, -15, -3);

    /* temp related objects */
    lv_obj_t *temp_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(temp_box, 120, 80);
    lv_obj_set_pos(temp_box, 0, 160);

    lv_obj_t *temp_value = lv_label_create(temp_box, NULL);
    lv_obj_align(temp_value, temp_box, LV_ALIGN_IN_LEFT_MID, 0, 0);

    /* hum related objects */
    lv_obj_t *hum_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(hum_box, 120, 80);
    lv_obj_set_pos(hum_box, 120, 160);

    lv_obj_t *hum_value = lv_label_create(hum_box, NULL);
    lv_obj_align(hum_value, hum_box, LV_ALIGN_IN_LEFT_MID, 0, 0);

    /* linking a label to a style */
    // lv_obj_add_style(pm2_5_label, LV_OBJ_PART_MAIN, &pm2_5_label_style);
    // lv_obj_add_style(pm10_label, LV_OBJ_PART_MAIN, &pm10_label_style);
    lv_obj_add_style(temp_value, LV_OBJ_PART_MAIN, &temp_value_style);
    lv_obj_add_style(hum_value, LV_OBJ_PART_MAIN, &hum_value_style);
    lv_obj_add_style(voc_label, LV_OBJ_PART_MAIN, &voc_label_style);
    lv_obj_add_style(voc_value, LV_OBJ_PART_MAIN, &voc_value_style);
    lv_obj_add_style(co2_label, LV_OBJ_PART_MAIN, &co2_label_style);
    lv_obj_add_style(co2_value, LV_OBJ_PART_MAIN, &co2_value_style);

    // lv_obj_set_pos(voc_label, 0, 0);
    // lv_obj_set_pos(pm2_5_label, 0, 0 + 50);
    // lv_obj_set_pos(pm10_label, 0, 0 + 110);
    // lv_obj_set_pos(temp_label, 0, 0 + 200);
    // lv_obj_set_pos(hum_label, 115, 0 + 200);

    /* task creation for dynamic value handling */
    // lv_task_create(pm2_5_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)pm2_5_label);    /* task to update pm2.5 value on tft display */
    // lv_task_create(pm10_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)pm10_label);      /* task to update pm10 value on tft display */
    lv_task_create(voc_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)voc_value);           /* task to update voc value on tft display */
    lv_task_create(voc_bar_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)voc_bar);               /* task to update the bar graphics of voc  on tft display */
    lv_task_create(co2_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)co2_value);           /* task to update the co2 value on tft display */
    lv_task_create(co2_bar_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)co2_bar);               /* task to update the bar graphics of co2 on tft display */
    lv_task_create(temp_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)temp_value);         /* task to update pm10 value on tft display */
    lv_task_create(hum_label_value_refresher_task, 250, LV_TASK_PRIO_MID, (void *)hum_value);           /* task to update pm10 value on tft display */
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
 * @brief   callback function to update voc label data on the display.
 */
static void voc_label_value_refresher_task(lv_task_t *task_info)
{
    /* update value */
    // lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "%.01f", SVM40_VOC);
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "");
}
static void voc_bar_value_refresher_task(lv_task_t *task_info)
{
    /* update value */
    int16_t scaled_voc_value = SVM40_VOC / 5;
    lv_bar_set_anim_time((lv_obj_t *)(task_info->user_data), 200);
    lv_bar_set_value((lv_obj_t *)(task_info->user_data), scaled_voc_value, LV_ANIM_ON);
}
static void co2_label_value_refresher_task(lv_task_t *task_info)
{
    /* update value */
    // lv_label_set_text_fmt((lv_obj_t*)(task_info->user_data), "%.01f ppm", (float)500);
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "");
}
static void co2_bar_value_refresher_task(lv_task_t *task_info)
{
    /* update value */
    float pseudo_co2_value = 500;
    int16_t scaled_co2_value = (int16_t)(pseudo_co2_value / 20);
    lv_bar_set_anim_time((lv_obj_t *)(task_info->user_data), 200);
    lv_bar_set_value((lv_obj_t *)(task_info->user_data), scaled_co2_value, LV_ANIM_ON);
}
/**
 * @brief   callback function to update temp label data on the display.
 */
static void temp_label_value_refresher_task(lv_task_t *task_info)
{
    /* update label value */
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "%.01f°C", SVM40_TEMP);
}
/**
 * @brief   callback function to update hum label data on the display.
 */
static void hum_label_value_refresher_task(lv_task_t *task_info)
{
    /* update label value */
    lv_label_set_text_fmt((lv_obj_t *)(task_info->user_data), "%.01f%%RH", SVM40_HUM);
}

static void lv_tick_task(void *arg)
{
    (void)arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}