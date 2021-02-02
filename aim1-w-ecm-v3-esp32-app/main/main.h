#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include "driver/i2c.h"

void app_main(void);
void sps30_task();
static void display_data_OLED128x64_task();
static void i2c_initialize(i2c_mode_t mode, int sda_io_num, int scl_io_num, bool sda_pullup_en, bool scl_pullup_en, uint32_t clk_speed, i2c_port_t i2c_num);
void run_all_samsung_test();

#endif