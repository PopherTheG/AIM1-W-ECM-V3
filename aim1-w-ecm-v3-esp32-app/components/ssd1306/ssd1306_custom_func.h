#ifndef SSD1306_CUSTOM_FUNC_H
#define SSD1306_CUSTOM_FUNC_H

#include <stdint.h>

/**
 * @name        ssd1306_binarizedimg_to_pixel
 * 
 * @note        only works for monochrome bitmap images.
 * @param x     starting x position of image.
 * @param y     starting y position of image.
 * @param w     width of image.
 * @param h     height of image.
 * @param buf   buffer that holds bit data of image.
 */
void ssd1306_binarizedimg_to_pixel(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *buf);

#endif