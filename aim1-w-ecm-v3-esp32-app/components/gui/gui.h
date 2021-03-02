#ifndef GUI_H
#define GUI_H

/* lvgl related includes */
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"
// #ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
// #if defined CONFIG_LV_USE_DEMO_WIDGETS
// #include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"
// #elif defined CONFIG_LV_USE_DEMO_KEYPAD_AND_ENCODER
// #include "lv_examples/src/lv_demo_keypad_and_encoder/lv_demo_keypad_and_encoder.h"
// #elif defined CONFIG_LV_USE_DEMO_BENCHMARK
// #include "lv_examples/src/lv_demo_benchmark/lv_demo_benchmark.h"
// #elif defined CONFIG_LV_USE_DEMO_STRESS
// #include "lv_examples/src/lv_demo_stress/lv_demo_stress.h"
// #else
// #error "No demo application selected."
// #endif
// #endif
/* end */

/* global variable from main.c 
contains sensor values */
extern float SPS30_PM2_5;
extern float SPS30_PM10;
extern float SVM40_VOC;
extern float SVM40_HUM;
extern float SVM40_TEMP;
extern float SCD4x_CO2;

#define LV_COLOR_GOOD                               LV_COLOR_MAKE(0x28, 0x96, 0x3C)
#define LV_COLOR_MODERATE                           LV_COLOR_MAKE(0xF8, 0xFB, 0x89)
#define LV_COLOR_UNHEALTHY_FOR_SENSITIVE_GROUPS     LV_COLOR_MAKE(0xF6, 0xC1, 0x42)
#define LV_COLOR_UNHEALTHY                          LV_COLOR_MAKE(0xDC, 0x84, 0x42)
#define LV_COLOR_VERY_UNHEALTHY                     LV_COLOR_MAKE(0xED, 0x64, 0x74)
#define LV_COLOR_HAZARDOUS                          LV_COLOR_MAKE(0xEB, 0x32, 0x23)

void gui_start_task();
static void lv_tick_task(void *arg);
static void guiTask(void *pvParameters);
static void st7899_display_application();
static void pm2_5_label_value_refresher_task(lv_task_t *task_info);
static void pm10_label_value_refresher_task(lv_task_t *task_info);
static void voc_label_value_refresher_task(lv_task_t *task_info);
static void temp_label_value_refresher_task(lv_task_t *task_info);
static void hum_label_value_refresher_task(lv_task_t *task_info);

#endif