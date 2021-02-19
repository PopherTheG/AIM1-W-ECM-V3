#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_VOC_IMG_SRC
#define LV_ATTRIBUTE_IMG_VOC_IMG_SRC
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_VOC_IMG_SRC uint8_t voc_img_src_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Blue: 2 bit, Green: 3 bit, Red: 3 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x33, 0x33, 0x33, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x32, 0x5b, 0x5b, 0x5b, 0x5b, 0x5b, 0x32, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x2a, 0x32, 0x00, 0x37, 0x5b, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x5b, 0x57, 0x00, 0x2e, 0x2e, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x32, 0x00, 0x5b, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x5b, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x57, 0x00, 0x5b, 0x57, 0x57, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x57, 0x57, 0x5b, 0x00, 0x57, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x32, 0x00, 0x37, 0x57, 0x57, 0x37, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x37, 0x57, 0x57, 0x57, 0x00, 0x33, 0x00, 0x00, 
  0x00, 0x00, 0x33, 0x00, 0x5b, 0x57, 0x57, 0x57, 0xdf, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x17, 0xdf, 0x57, 0x57, 0x57, 0x5b, 0x00, 0x33, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x32, 0x57, 0x57, 0x57, 0x37, 0xdf, 0x37, 0x37, 0x37, 0x9b, 0xff, 0xff, 0xff, 0xbb, 0x37, 0x37, 0x57, 0x57, 0x33, 0x00, 0x29, 0x00, 
  0x00, 0x32, 0x00, 0x5b, 0x57, 0x57, 0x37, 0x37, 0xdf, 0x7b, 0xff, 0xff, 0xff, 0xbf, 0x9b, 0xbf, 0xff, 0xff, 0x9b, 0x7b, 0x57, 0x5b, 0x00, 0x32, 0x00, 
  0x00, 0x33, 0x00, 0x5b, 0x57, 0x57, 0xff, 0xbf, 0xdf, 0x5b, 0x17, 0x17, 0x17, 0x57, 0x7b, 0x37, 0x17, 0x9b, 0xff, 0xdf, 0x57, 0x5b, 0x00, 0x33, 0x00, 
  0x00, 0x33, 0x00, 0x5b, 0x57, 0xff, 0xbf, 0x9b, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7b, 0x37, 0x57, 0x57, 0x5b, 0x00, 0x33, 0x00, 
  0x00, 0x33, 0x00, 0x5b, 0x57, 0x37, 0x7b, 0x57, 0xdf, 0x9b, 0xff, 0xff, 0xdf, 0x9b, 0x57, 0x9b, 0xff, 0xff, 0xff, 0x7b, 0x37, 0x5b, 0x00, 0x33, 0x00, 
  0x00, 0x32, 0x00, 0x5b, 0x37, 0xbf, 0xdf, 0xbf, 0xdf, 0x7b, 0x17, 0x17, 0x37, 0x37, 0x57, 0x37, 0xbf, 0x37, 0x37, 0x37, 0x57, 0x5b, 0x00, 0x32, 0x00, 
  0x00, 0x00, 0x00, 0x32, 0x57, 0x37, 0x37, 0x37, 0xdf, 0xff, 0xff, 0xff, 0x7b, 0x57, 0x57, 0x37, 0xdf, 0x57, 0x57, 0x57, 0x57, 0x33, 0x00, 0x2a, 0x00, 
  0x00, 0x00, 0x33, 0x00, 0x5b, 0x57, 0x57, 0x57, 0xdf, 0x13, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0xdf, 0x57, 0x57, 0x57, 0x5b, 0x00, 0x32, 0x00, 0x00, 
  0x00, 0x00, 0x32, 0x00, 0x57, 0x57, 0x57, 0x37, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x37, 0x57, 0x57, 0x57, 0x00, 0x33, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x57, 0x00, 0x5b, 0x57, 0x57, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x57, 0x57, 0x5b, 0x00, 0x57, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x5b, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x5b, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x2e, 0x2e, 0x00, 0x57, 0x5b, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x5b, 0x57, 0x00, 0x2e, 0x2e, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x33, 0x5b, 0x5b, 0x5b, 0x5b, 0x5b, 0x33, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x32, 0x33, 0x33, 0x33, 0x32, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Blue: 5 bit, Green: 6 bit, Red: 5 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x2b, 0x55, 0x34, 0x76, 0x34, 0x55, 0x34, 0xd3, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x2b, 0x76, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x34, 0x14, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x3d, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x2b, 0xbc, 0x3d, 0xdc, 0x45, 0xdc, 0x3d, 0xdc, 0x45, 0xbc, 0x3d, 0xf3, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x18, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x1a, 0xd2, 0x2b, 0x00, 0x00, 0x96, 0x34, 0xdc, 0x45, 0x7a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x7a, 0x3d, 0xdc, 0x3d, 0xd7, 0x34, 0x00, 0x00, 0x91, 0x23, 0xee, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd2, 0x2b, 0x00, 0x00, 0xdc, 0x3d, 0x7a, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x7a, 0x3d, 0xfd, 0x45, 0x00, 0x00, 0x71, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x3d, 0x00, 0x00, 0xdc, 0x45, 0x5a, 0x3d, 0x39, 0x3d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x39, 0x3d, 0x5a, 0x3d, 0xfd, 0x45, 0x00, 0x00, 0xf8, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xf3, 0x2b, 0x00, 0x00, 0x96, 0x34, 0x7a, 0x3d, 0x39, 0x3d, 0x19, 0x2d, 0xbf, 0xef, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7e, 0xdf, 0xdf, 0xf7, 0x19, 0x2d, 0x39, 0x3d, 0x7a, 0x3d, 0xd8, 0x34, 0x00, 0x00, 0x35, 0x2c, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x76, 0x34, 0x00, 0x00, 0xdc, 0x45, 0x5a, 0x3d, 0x39, 0x3d, 0x39, 0x35, 0x3e, 0xcf, 0xd9, 0x1c, 0x19, 0x2d, 0x19, 0x2d, 0xf9, 0x24, 0xd8, 0x1c, 0xb8, 0x14, 0x98, 0x04, 0x3e, 0xc7, 0x5a, 0x3d, 0x39, 0x3d, 0x5a, 0x3d, 0xdc, 0x3d, 0x00, 0x00, 0x34, 0x2c, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x2b, 0x7a, 0x3d, 0x5a, 0x3d, 0x39, 0x3d, 0x39, 0x35, 0x5e, 0xcf, 0x19, 0x2d, 0xf9, 0x24, 0x19, 0x2d, 0x3c, 0x86, 0x7e, 0xd7, 0xff, 0xff, 0xdf, 0xf7, 0x9c, 0x9e, 0xf9, 0x24, 0x19, 0x2d, 0x39, 0x35, 0x7a, 0x3d, 0x34, 0x2c, 0x00, 0x00, 0x6c, 0x1a, 0x00, 0x00, 
  0x00, 0x00, 0xd2, 0x2b, 0x00, 0x00, 0xbc, 0x3d, 0x5a, 0x3d, 0x39, 0x35, 0x19, 0x2d, 0x19, 0x2d, 0x3e, 0xc7, 0xdb, 0x65, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdd, 0xae, 0x3c, 0x86, 0x9d, 0x9e, 0xff, 0xff, 0xff, 0xff, 0x1c, 0x7e, 0xdb, 0x65, 0x7a, 0x45, 0xdc, 0x3d, 0x00, 0x00, 0x14, 0x2c, 0x00, 0x00, 
  0x00, 0x00, 0x55, 0x2c, 0x00, 0x00, 0xdc, 0x45, 0x39, 0x35, 0x7a, 0x4d, 0x7e, 0xdf, 0x9d, 0x9e, 0x1e, 0xbf, 0x9a, 0x55, 0xb8, 0x0c, 0xb8, 0x14, 0xb8, 0x0c, 0x5a, 0x45, 0xbb, 0x5d, 0x19, 0x35, 0xb8, 0x0c, 0x3c, 0x86, 0x9f, 0xe7, 0x1e, 0xbf, 0x39, 0x35, 0xdc, 0x3d, 0x00, 0x00, 0x75, 0x34, 0x00, 0x00, 
  0x00, 0x00, 0x76, 0x34, 0x00, 0x00, 0xdc, 0x3d, 0x5a, 0x45, 0x9f, 0xe7, 0xbd, 0xa6, 0x1b, 0x76, 0xdd, 0xae, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xe7, 0xdb, 0x6d, 0xf9, 0x24, 0x9a, 0x55, 0x39, 0x35, 0xdc, 0x3d, 0x00, 0x00, 0x35, 0x2c, 0x00, 0x00, 
  0x00, 0x00, 0x55, 0x2c, 0x00, 0x00, 0xdc, 0x45, 0x39, 0x35, 0x19, 0x35, 0xfb, 0x6d, 0x5a, 0x45, 0x1e, 0xbf, 0x3c, 0x7e, 0xbf, 0xef, 0xff, 0xff, 0x5e, 0xd7, 0x3c, 0x7e, 0x9a, 0x4d, 0x3c, 0x86, 0x7e, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x6d, 0x39, 0x35, 0xdc, 0x3d, 0x00, 0x00, 0x75, 0x34, 0x00, 0x00, 
  0x00, 0x00, 0xd3, 0x2b, 0x00, 0x00, 0xbc, 0x3d, 0x39, 0x2d, 0xbd, 0xa6, 0x3e, 0xcf, 0xfd, 0xb6, 0x1e, 0xbf, 0xbb, 0x5d, 0xb8, 0x0c, 0xb8, 0x14, 0x19, 0x2d, 0x19, 0x2d, 0x39, 0x35, 0xf9, 0x24, 0x9d, 0x9e, 0xf9, 0x24, 0xf9, 0x24, 0x39, 0x35, 0x5a, 0x3d, 0xdc, 0x45, 0x00, 0x00, 0x14, 0x2c, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x2b, 0x7a, 0x3d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0xfd, 0xb6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbb, 0x5d, 0x39, 0x35, 0x5a, 0x3d, 0x19, 0x2d, 0x5e, 0xd7, 0x5a, 0x3d, 0x39, 0x3d, 0x5a, 0x3d, 0x7a, 0x3d, 0x35, 0x2c, 0x00, 0x00, 0x8c, 0x1a, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x55, 0x34, 0x00, 0x00, 0xdc, 0x3d, 0x5a, 0x3d, 0x39, 0x3d, 0x39, 0x35, 0x3e, 0xcf, 0x98, 0x04, 0xf9, 0x24, 0xd8, 0x14, 0xf9, 0x24, 0x19, 0x2d, 0x19, 0x2d, 0xd9, 0x1c, 0x3e, 0xcf, 0x5a, 0x3d, 0x39, 0x3d, 0x5a, 0x3d, 0xdc, 0x3d, 0x00, 0x00, 0x14, 0x2c, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x14, 0x2c, 0x00, 0x00, 0xd7, 0x34, 0x7a, 0x3d, 0x39, 0x3d, 0x19, 0x2d, 0xdf, 0xf7, 0x7e, 0xdf, 0x7e, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7e, 0xdf, 0xdf, 0xff, 0x19, 0x2d, 0x39, 0x3d, 0x7a, 0x3d, 0xf8, 0x34, 0x00, 0x00, 0x55, 0x34, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x35, 0x00, 0x00, 0xdd, 0x45, 0x5a, 0x3d, 0x39, 0x3d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x39, 0x3d, 0x5a, 0x3d, 0xfd, 0x45, 0x00, 0x00, 0xd7, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0x23, 0x00, 0x00, 0xfd, 0x45, 0x7a, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x7a, 0x3d, 0xfd, 0x45, 0x00, 0x00, 0x2f, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x22, 0x71, 0x23, 0x00, 0x00, 0xd8, 0x34, 0xdc, 0x3d, 0x7a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x7a, 0x3d, 0xdc, 0x3d, 0xf8, 0x34, 0x00, 0x00, 0x2f, 0x23, 0x30, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x34, 0x00, 0x00, 0x00, 0x00, 0x34, 0x2c, 0xdc, 0x45, 0xdc, 0x3d, 0xdc, 0x3d, 0xdc, 0x3d, 0xdc, 0x45, 0x34, 0x2c, 0x00, 0x00, 0x00, 0x00, 0xd7, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x2c, 0x34, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x2c, 0x55, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x1a, 0x14, 0x2c, 0x75, 0x34, 0x55, 0x2c, 0x75, 0x34, 0x14, 0x2c, 0x8c, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Blue: 5 bit, Green: 6 bit, Red: 5 bit BUT the 2 bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0xd3, 0x34, 0x55, 0x34, 0x76, 0x34, 0x55, 0x2b, 0xd3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0xf3, 0x34, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x55, 0x2c, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x19, 0x00, 0x00, 0x00, 0x00, 0x2b, 0xd3, 0x3d, 0xbc, 0x45, 0xdc, 0x3d, 0xdc, 0x45, 0xdc, 0x3d, 0xbc, 0x2b, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x35, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x8c, 0x2b, 0xd2, 0x00, 0x00, 0x34, 0x96, 0x45, 0xdc, 0x3d, 0x7a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x7a, 0x3d, 0xdc, 0x34, 0xd7, 0x00, 0x00, 0x23, 0x91, 0x22, 0xee, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0xd2, 0x00, 0x00, 0x3d, 0xdc, 0x3d, 0x7a, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x7a, 0x45, 0xfd, 0x00, 0x00, 0x23, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x19, 0x00, 0x00, 0x45, 0xdc, 0x3d, 0x5a, 0x3d, 0x39, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x3d, 0x39, 0x3d, 0x5a, 0x45, 0xfd, 0x00, 0x00, 0x34, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x2b, 0xf3, 0x00, 0x00, 0x34, 0x96, 0x3d, 0x7a, 0x3d, 0x39, 0x2d, 0x19, 0xef, 0xbf, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7e, 0xf7, 0xdf, 0x2d, 0x19, 0x3d, 0x39, 0x3d, 0x7a, 0x34, 0xd8, 0x00, 0x00, 0x2c, 0x35, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x34, 0x76, 0x00, 0x00, 0x45, 0xdc, 0x3d, 0x5a, 0x3d, 0x39, 0x35, 0x39, 0xcf, 0x3e, 0x1c, 0xd9, 0x2d, 0x19, 0x2d, 0x19, 0x24, 0xf9, 0x1c, 0xd8, 0x14, 0xb8, 0x04, 0x98, 0xc7, 0x3e, 0x3d, 0x5a, 0x3d, 0x39, 0x3d, 0x5a, 0x3d, 0xdc, 0x00, 0x00, 0x2c, 0x34, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0xd3, 0x3d, 0x7a, 0x3d, 0x5a, 0x3d, 0x39, 0x35, 0x39, 0xcf, 0x5e, 0x2d, 0x19, 0x24, 0xf9, 0x2d, 0x19, 0x86, 0x3c, 0xd7, 0x7e, 0xff, 0xff, 0xf7, 0xdf, 0x9e, 0x9c, 0x24, 0xf9, 0x2d, 0x19, 0x35, 0x39, 0x3d, 0x7a, 0x2c, 0x34, 0x00, 0x00, 0x1a, 0x6c, 0x00, 0x00, 
  0x00, 0x00, 0x2b, 0xd2, 0x00, 0x00, 0x3d, 0xbc, 0x3d, 0x5a, 0x35, 0x39, 0x2d, 0x19, 0x2d, 0x19, 0xc7, 0x3e, 0x65, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xae, 0xdd, 0x86, 0x3c, 0x9e, 0x9d, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x1c, 0x65, 0xdb, 0x45, 0x7a, 0x3d, 0xdc, 0x00, 0x00, 0x2c, 0x14, 0x00, 0x00, 
  0x00, 0x00, 0x2c, 0x55, 0x00, 0x00, 0x45, 0xdc, 0x35, 0x39, 0x4d, 0x7a, 0xdf, 0x7e, 0x9e, 0x9d, 0xbf, 0x1e, 0x55, 0x9a, 0x0c, 0xb8, 0x14, 0xb8, 0x0c, 0xb8, 0x45, 0x5a, 0x5d, 0xbb, 0x35, 0x19, 0x0c, 0xb8, 0x86, 0x3c, 0xe7, 0x9f, 0xbf, 0x1e, 0x35, 0x39, 0x3d, 0xdc, 0x00, 0x00, 0x34, 0x75, 0x00, 0x00, 
  0x00, 0x00, 0x34, 0x76, 0x00, 0x00, 0x3d, 0xdc, 0x45, 0x5a, 0xe7, 0x9f, 0xa6, 0xbd, 0x76, 0x1b, 0xae, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x9f, 0x6d, 0xdb, 0x24, 0xf9, 0x55, 0x9a, 0x35, 0x39, 0x3d, 0xdc, 0x00, 0x00, 0x2c, 0x35, 0x00, 0x00, 
  0x00, 0x00, 0x2c, 0x55, 0x00, 0x00, 0x45, 0xdc, 0x35, 0x39, 0x35, 0x19, 0x6d, 0xfb, 0x45, 0x5a, 0xbf, 0x1e, 0x7e, 0x3c, 0xef, 0xbf, 0xff, 0xff, 0xd7, 0x5e, 0x7e, 0x3c, 0x4d, 0x9a, 0x86, 0x3c, 0xd7, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x6d, 0xfb, 0x35, 0x39, 0x3d, 0xdc, 0x00, 0x00, 0x34, 0x75, 0x00, 0x00, 
  0x00, 0x00, 0x2b, 0xd3, 0x00, 0x00, 0x3d, 0xbc, 0x2d, 0x39, 0xa6, 0xbd, 0xcf, 0x3e, 0xb6, 0xfd, 0xbf, 0x1e, 0x5d, 0xbb, 0x0c, 0xb8, 0x14, 0xb8, 0x2d, 0x19, 0x2d, 0x19, 0x35, 0x39, 0x24, 0xf9, 0x9e, 0x9d, 0x24, 0xf9, 0x24, 0xf9, 0x35, 0x39, 0x3d, 0x5a, 0x45, 0xdc, 0x00, 0x00, 0x2c, 0x14, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0xf3, 0x3d, 0x7a, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0xb6, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x5d, 0xbb, 0x35, 0x39, 0x3d, 0x5a, 0x2d, 0x19, 0xd7, 0x5e, 0x3d, 0x5a, 0x3d, 0x39, 0x3d, 0x5a, 0x3d, 0x7a, 0x2c, 0x35, 0x00, 0x00, 0x1a, 0x8c, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x34, 0x55, 0x00, 0x00, 0x3d, 0xdc, 0x3d, 0x5a, 0x3d, 0x39, 0x35, 0x39, 0xcf, 0x3e, 0x04, 0x98, 0x24, 0xf9, 0x14, 0xd8, 0x24, 0xf9, 0x2d, 0x19, 0x2d, 0x19, 0x1c, 0xd9, 0xcf, 0x3e, 0x3d, 0x5a, 0x3d, 0x39, 0x3d, 0x5a, 0x3d, 0xdc, 0x00, 0x00, 0x2c, 0x14, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x2c, 0x14, 0x00, 0x00, 0x34, 0xd7, 0x3d, 0x7a, 0x3d, 0x39, 0x2d, 0x19, 0xf7, 0xdf, 0xdf, 0x7e, 0xdf, 0x7e, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7f, 0xdf, 0x7e, 0xff, 0xdf, 0x2d, 0x19, 0x3d, 0x39, 0x3d, 0x7a, 0x34, 0xf8, 0x00, 0x00, 0x34, 0x55, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x18, 0x00, 0x00, 0x45, 0xdd, 0x3d, 0x5a, 0x3d, 0x39, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x2d, 0x19, 0x3d, 0x39, 0x3d, 0x5a, 0x45, 0xfd, 0x00, 0x00, 0x34, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x91, 0x00, 0x00, 0x45, 0xfd, 0x3d, 0x7a, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x39, 0x3d, 0x7a, 0x45, 0xfd, 0x00, 0x00, 0x23, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0xee, 0x23, 0x71, 0x00, 0x00, 0x34, 0xd8, 0x3d, 0xdc, 0x3d, 0x7a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x5a, 0x3d, 0x7a, 0x3d, 0xdc, 0x34, 0xf8, 0x00, 0x00, 0x23, 0x2f, 0x23, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x34, 0x45, 0xdc, 0x3d, 0xdc, 0x3d, 0xdc, 0x3d, 0xdc, 0x45, 0xdc, 0x2c, 0x34, 0x00, 0x00, 0x00, 0x00, 0x34, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x55, 0x2c, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x14, 0x34, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x6c, 0x2c, 0x14, 0x34, 0x75, 0x2c, 0x55, 0x34, 0x75, 0x2c, 0x14, 0x1a, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  /*Pixel format: Blue: 8 bit, Green: 8 bit, Red: 8 bit, Fix 0xFF: 8 bit, */
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x95, 0x79, 0x27, 0xff, 0xa8, 0x88, 0x2d, 0xff, 0xad, 0x8d, 0x2e, 0xff, 0xa8, 0x88, 0x2d, 0xff, 0x96, 0x7a, 0x28, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x9a, 0x7d, 0x29, 0xff, 0xad, 0x8d, 0x2e, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa9, 0x8a, 0x2d, 0xff, 0x9f, 0x81, 0x2a, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xc7, 0xa2, 0x35, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x96, 0x7a, 0x28, 0xff, 0xdd, 0xb4, 0x3b, 0xff, 0xe3, 0xb9, 0x3d, 0xff, 0xe2, 0xb8, 0x3c, 0xff, 0xe3, 0xb9, 0x3d, 0xff, 0xdf, 0xb6, 0x3c, 0xff, 0x99, 0x7c, 0x29, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xc3, 0x9f, 0x34, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x62, 0x50, 0x1a, 0xff, 0x94, 0x78, 0x27, 0xff, 0x00, 0x00, 0x00, 0xff, 0xb2, 0x91, 0x2f, 0xff, 0xe4, 0xb9, 0x3d, 0xff, 0xd4, 0xad, 0x39, 0xff, 0xce, 0xa7, 0x37, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xd4, 0xac, 0x38, 0xff, 0xe3, 0xb9, 0x3c, 0xff, 0xb9, 0x97, 0x31, 0xff, 0x00, 0x00, 0x00, 0xff, 0x89, 0x6f, 0x24, 0xff, 0x71, 0x5c, 0x1e, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x94, 0x78, 0x27, 0xff, 0x00, 0x00, 0x00, 0xff, 0xe3, 0xb9, 0x3c, 0xff, 0xd4, 0xac, 0x38, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xd3, 0xac, 0x38, 0xff, 0xe5, 0xbb, 0x3d, 0xff, 0x00, 0x00, 0x00, 0xff, 0x87, 0x6d, 0x24, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xc7, 0xa2, 0x35, 0xff, 0x00, 0x00, 0x00, 0xff, 0xe2, 0xb8, 0x3d, 0xff, 0xd0, 0xa9, 0x37, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xc8, 0x9f, 0x25, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xc8, 0x9f, 0x25, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcf, 0xa8, 0x37, 0xff, 0xe5, 0xbb, 0x3d, 0xff, 0x00, 0x00, 0x00, 0xff, 0xc2, 0x9d, 0x33, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x9a, 0x7d, 0x29, 0xff, 0x00, 0x00, 0x00, 0xff, 0xb2, 0x91, 0x2f, 0xff, 0xd4, 0xac, 0x38, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xfa, 0xf5, 0xec, 0xff, 0xf5, 0xed, 0xda, 0xff, 0xf5, 0xed, 0xdb, 0xff, 0xf5, 0xed, 0xdb, 0xff, 0xf5, 0xed, 0xdb, 0xff, 0xf5, 0xed, 0xdb, 0xff, 0xf5, 0xed, 0xdb, 0xff, 0xf4, 0xed, 0xd9, 0xff, 0xfb, 0xf7, 0xf0, 0xff, 0xc9, 0xa1, 0x2a, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xd2, 0xab, 0x38, 0xff, 0xbd, 0x9a, 0x32, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa5, 0x86, 0x2c, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xad, 0x8d, 0x2e, 0xff, 0x00, 0x00, 0x00, 0xff, 0xe4, 0xb9, 0x3d, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcb, 0xa4, 0x31, 0xff, 0xf1, 0xe6, 0xc7, 0xff, 0xc5, 0x99, 0x17, 0xff, 0xc8, 0x9f, 0x26, 0xff, 0xc8, 0x9f, 0x25, 0xff, 0xc6, 0x9b, 0x1d, 0xff, 0xc4, 0x98, 0x15, 0xff, 0xc3, 0x96, 0x11, 0xff, 0xc0, 0x91, 0x04, 0xff, 0xf0, 0xe4, 0xc3, 0xff, 0xcd, 0xa8, 0x3a, 0xff, 0xcc, 0xa6, 0x35, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xe2, 0xb8, 0x3c, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa4, 0x86, 0x2c, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x96, 0x7a, 0x28, 0xff, 0xd4, 0xad, 0x39, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcb, 0xa4, 0x30, 0xff, 0xf2, 0xe7, 0xca, 0xff, 0xc8, 0x9f, 0x25, 0xff, 0xc7, 0x9e, 0x22, 0xff, 0xc8, 0x9f, 0x26, 0xff, 0xdf, 0xc6, 0x80, 0xff, 0xf4, 0xeb, 0xd4, 0xff, 0xfe, 0xfd, 0xfe, 0xff, 0xfc, 0xf9, 0xf4, 0xff, 0xe4, 0xcf, 0x96, 0xff, 0xc7, 0x9d, 0x21, 0xff, 0xca, 0xa2, 0x2c, 0xff, 0xcb, 0xa4, 0x31, 0xff, 0xd3, 0xab, 0x37, 0xff, 0xa2, 0x83, 0x2b, 0xff, 0x00, 0x00, 0x00, 0xff, 0x5e, 0x4d, 0x19, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x94, 0x79, 0x28, 0xff, 0x00, 0x00, 0x00, 0xff, 0xdd, 0xb4, 0x3b, 0xff, 0xce, 0xa7, 0x37, 0xff, 0xcc, 0xa5, 0x33, 0xff, 0xc8, 0x9f, 0x26, 0xff, 0xc9, 0x9f, 0x26, 0xff, 0xf0, 0xe4, 0xc3, 0xff, 0xd7, 0xba, 0x64, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfc, 0xfb, 0xff, 0xe9, 0xd8, 0xa8, 0xff, 0xde, 0xc5, 0x7d, 0xff, 0xe6, 0xd2, 0x9b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdd, 0xc2, 0x77, 0xff, 0xd6, 0xb8, 0x5f, 0xff, 0xd0, 0xac, 0x43, 0xff, 0xe3, 0xb8, 0x3b, 0xff, 0x00, 0x00, 0x00, 0xff, 0x9e, 0x80, 0x2a, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xa8, 0x89, 0x2c, 0xff, 0x00, 0x00, 0x00, 0xff, 0xe3, 0xb9, 0x3d, 0xff, 0xcb, 0xa4, 0x31, 0xff, 0xd0, 0xad, 0x45, 0xff, 0xf4, 0xec, 0xd6, 0xff, 0xe5, 0xd2, 0x9b, 0xff, 0xee, 0xe0, 0xba, 0xff, 0xd3, 0xb1, 0x4f, 0xff, 0xc1, 0x93, 0x0a, 0xff, 0xc3, 0x95, 0x0f, 0xff, 0xc1, 0x93, 0x0a, 0xff, 0xce, 0xa9, 0x3e, 0xff, 0xd6, 0xb6, 0x5c, 0xff, 0xca, 0xa2, 0x2d, 0xff, 0xc1, 0x93, 0x09, 0xff, 0xde, 0xc6, 0x7f, 0xff, 0xf7, 0xf1, 0xe1, 0xff, 0xed, 0xe0, 0xba, 0xff, 0xcb, 0xa5, 0x32, 0xff, 0xe2, 0xb8, 0x3b, 0xff, 0x00, 0x00, 0x00, 0xff, 0xab, 0x8b, 0x2d, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xae, 0x8c, 0x2e, 0xff, 0x00, 0x00, 0x00, 0xff, 0xe1, 0xb7, 0x3a, 0xff, 0xce, 0xaa, 0x3d, 0xff, 0xf6, 0xf0, 0xdf, 0xff, 0xe7, 0xd5, 0xa0, 0xff, 0xdb, 0xc0, 0x73, 0xff, 0xea, 0xd9, 0xab, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0xed, 0xd8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xf2, 0xe3, 0xff, 0xd8, 0xba, 0x65, 0xff, 0xc8, 0x9e, 0x24, 0xff, 0xd2, 0xb0, 0x4e, 0xff, 0xcb, 0xa5, 0x32, 0xff, 0xe0, 0xb7, 0x3c, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa6, 0x86, 0x2c, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xa8, 0x89, 0x2c, 0xff, 0x00, 0x00, 0x00, 0xff, 0xe3, 0xb9, 0x3d, 0xff, 0xcc, 0xa5, 0x33, 0xff, 0xca, 0xa2, 0x2d, 0xff, 0xd9, 0xbd, 0x6a, 0xff, 0xce, 0xa9, 0x3d, 0xff, 0xee, 0xe1, 0xbc, 0xff, 0xdd, 0xc4, 0x7b, 0xff, 0xf8, 0xf4, 0xe6, 0xff, 0xfd, 0xfc, 0xfb, 0xff, 0xf2, 0xe8, 0xcd, 0xff, 0xdd, 0xc3, 0x79, 0xff, 0xd2, 0xb0, 0x4c, 0xff, 0xde, 0xc6, 0x80, 0xff, 0xf3, 0xeb, 0xd3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xbc, 0x69, 0xff, 0xcb, 0xa4, 0x30, 0xff, 0xe2, 0xb8, 0x3c, 0xff, 0x00, 0x00, 0x00, 0xff, 0xab, 0x8b, 0x2d, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x96, 0x7a, 0x28, 0xff, 0x00, 0x00, 0x00, 0xff, 0xdf, 0xb5, 0x3b, 0xff, 0xcb, 0xa3, 0x2c, 0xff, 0xe7, 0xd5, 0xa3, 0xff, 0xf1, 0xe6, 0xc7, 0xff, 0xea, 0xdb, 0xb0, 0xff, 0xed, 0xdf, 0xb7, 0xff, 0xd5, 0xb5, 0x58, 0xff, 0xc1, 0x93, 0x0a, 0xff, 0xc2, 0x95, 0x0d, 0xff, 0xc9, 0x9f, 0x27, 0xff, 0xca, 0xa2, 0x2c, 0xff, 0xcb, 0xa4, 0x31, 0xff, 0xc7, 0x9d, 0x21, 0xff, 0xe6, 0xd2, 0x9c, 0xff, 0xc7, 0x9d, 0x20, 0xff, 0xc7, 0x9d, 0x21, 0xff, 0xcb, 0xa4, 0x30, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xe4, 0xba, 0x3d, 0xff, 0x00, 0x00, 0x00, 0xff, 0x9f, 0x82, 0x2b, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x99, 0x7d, 0x29, 0xff, 0xd4, 0xac, 0x38, 0xff, 0xca, 0xa2, 0x2c, 0xff, 0xc9, 0xa0, 0x27, 0xff, 0xc8, 0x9f, 0x25, 0xff, 0xec, 0xdd, 0xb4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd6, 0xb6, 0x5c, 0xff, 0xcb, 0xa4, 0x32, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xf3, 0xe8, 0xcd, 0xff, 0xcd, 0xa8, 0x38, 0xff, 0xcc, 0xa6, 0x35, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xd3, 0xac, 0x38, 0xff, 0xa5, 0x86, 0x2c, 0xff, 0x00, 0x00, 0x00, 0xff, 0x62, 0x50, 0x1a, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa9, 0x8a, 0x2d, 0xff, 0x00, 0x00, 0x00, 0xff, 0xe3, 0xb9, 0x3c, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcb, 0xa4, 0x31, 0xff, 0xf1, 0xe6, 0xc7, 0xff, 0xbf, 0x90, 0x02, 0xff, 0xc7, 0x9c, 0x21, 0xff, 0xc3, 0x97, 0x12, 0xff, 0xc7, 0x9d, 0x21, 0xff, 0xc8, 0x9f, 0x26, 0xff, 0xc8, 0x9f, 0x26, 0xff, 0xc5, 0x99, 0x17, 0xff, 0xf1, 0xe5, 0xc6, 0xff, 0xcd, 0xa8, 0x39, 0xff, 0xcc, 0xa6, 0x35, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xe1, 0xb7, 0x3c, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa0, 0x82, 0x2a, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x9e, 0x81, 0x2a, 0xff, 0x00, 0x00, 0x00, 0xff, 0xb9, 0x97, 0x31, 0xff, 0xd3, 0xac, 0x38, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xc9, 0xa0, 0x28, 0xff, 0xfb, 0xf7, 0xf1, 0xff, 0xf4, 0xec, 0xd6, 0xff, 0xf4, 0xec, 0xd7, 0xff, 0xf5, 0xed, 0xd8, 0xff, 0xf5, 0xed, 0xd8, 0xff, 0xf5, 0xed, 0xd8, 0xff, 0xf5, 0xed, 0xd8, 0xff, 0xf4, 0xec, 0xd6, 0xff, 0xfc, 0xfa, 0xf6, 0xff, 0xc9, 0xa1, 0x2a, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xd2, 0xab, 0x38, 0xff, 0xc3, 0x9e, 0x34, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa9, 0x89, 0x2d, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xc4, 0x9f, 0x34, 0xff, 0x00, 0x00, 0x00, 0xff, 0xe5, 0xba, 0x3d, 0xff, 0xcf, 0xa9, 0x37, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xc8, 0x9f, 0x26, 0xff, 0xc9, 0xa1, 0x2a, 0xff, 0xc9, 0xa1, 0x2a, 0xff, 0xc9, 0xa1, 0x2a, 0xff, 0xc9, 0xa1, 0x2a, 0xff, 0xc9, 0xa1, 0x2a, 0xff, 0xc9, 0xa1, 0x2a, 0xff, 0xc9, 0xa1, 0x2a, 0xff, 0xc8, 0x9f, 0x26, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xce, 0xa8, 0x37, 0xff, 0xe7, 0xbc, 0x3e, 0xff, 0x00, 0x00, 0x00, 0xff, 0xbc, 0x99, 0x32, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x88, 0x6f, 0x24, 0xff, 0x00, 0x00, 0x00, 0xff, 0xe5, 0xbb, 0x3d, 0xff, 0xd2, 0xab, 0x38, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xcc, 0xa6, 0x36, 0xff, 0xd2, 0xab, 0x38, 0xff, 0xe8, 0xbd, 0x3e, 0xff, 0x00, 0x00, 0x00, 0xff, 0x7a, 0x63, 0x20, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x71, 0x5c, 0x1e, 0xff, 0x87, 0x6e, 0x24, 0xff, 0x00, 0x00, 0x00, 0xff, 0xbd, 0x9a, 0x32, 0xff, 0xe2, 0xb8, 0x3c, 0xff, 0xd3, 0xac, 0x38, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xcd, 0xa7, 0x37, 0xff, 0xd3, 0xac, 0x38, 0xff, 0xe1, 0xb7, 0x3c, 0xff, 0xc3, 0x9e, 0x34, 0xff, 0x00, 0x00, 0x00, 0xff, 0x7a, 0x63, 0x20, 0xff, 0x7d, 0x66, 0x21, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xc1, 0x9d, 0x34, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa1, 0x83, 0x2b, 0xff, 0xe3, 0xb9, 0x3d, 0xff, 0xe2, 0xb8, 0x3c, 0xff, 0xe0, 0xb7, 0x3c, 0xff, 0xe2, 0xb8, 0x3c, 0xff, 0xe4, 0xba, 0x3d, 0xff, 0xa4, 0x86, 0x2c, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xbc, 0x99, 0x32, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa5, 0x87, 0x2c, 0xff, 0xa4, 0x85, 0x2b, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xa0, 0x82, 0x2a, 0xff, 0xa8, 0x89, 0x2d, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x5e, 0x4d, 0x19, 0xff, 0x9d, 0x80, 0x2a, 0xff, 0xab, 0x8b, 0x2d, 0xff, 0xa6, 0x87, 0x2c, 0xff, 0xaa, 0x8b, 0x2d, 0xff, 0x9f, 0x82, 0x2a, 0xff, 0x61, 0x4f, 0x1a, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
#endif
};

const lv_img_dsc_t voc_img_src = {
  .header.always_zero = 0,
  .header.w = 25,
  .header.h = 25,
  .data_size = 625 * LV_COLOR_SIZE / 8,
  .header.cf = LV_IMG_CF_TRUE_COLOR,
  .data = voc_img_src_map,
};

