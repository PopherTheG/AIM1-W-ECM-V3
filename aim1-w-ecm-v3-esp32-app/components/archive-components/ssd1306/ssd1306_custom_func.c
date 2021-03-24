#include "ssd1306_custom_func.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
#include <stdio.h>

void ssd1306_binarizedimg_to_pixel(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *buf)
{
  for (uint32_t j = y; j < y + h; j++)
  {
    for (uint32_t i = x; i < x + w; i++)
    {
      uint32_t color_in_pixel;
      color_in_pixel = (i - x) + ((j - y) * w);
      // printf("color index: %u\n", color_in_pixel);
      ssd1306_draw_pixel(i, j, buf[color_in_pixel]);
    }
  }
}