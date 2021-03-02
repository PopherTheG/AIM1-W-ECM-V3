#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_HUM_IMG_SRC
#define LV_ATTRIBUTE_IMG_HUM_IMG_SRC
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_HUM_IMG_SRC uint8_t hum_img_src_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Blue: 2 bit, Green: 3 bit, Red: 3 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0x97, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7b, 0x53, 0x97, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0x9f, 0x9b, 0x53, 0x53, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x53, 0x77, 0x00, 0x00, 0x00, 0x00, 0xdf, 0x4b, 0xdf, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x57, 0x53, 0xdf, 0x00, 0x00, 0x00, 0x4b, 0x4f, 0x4b, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xbf, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x57, 0x57, 0x53, 0x00, 0x00, 0x6f, 0x4f, 0x6f, 0x4f, 0x6f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x57, 0x57, 0x53, 0xbb, 0xdb, 0x4b, 0x6f, 0x6f, 0x6f, 0x4b, 0xdb, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xbf, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x6f, 0x4f, 0x6f, 0x6f, 0x6f, 0x4f, 0x4b, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x53, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x4b, 0xbb, 0x00, 
  0x00, 0x00, 0xbf, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x4f, 0x6f, 0x00, 
  0x00, 0x00, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x53, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x4b, 0x00, 
  0x00, 0xdf, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x7b, 0x53, 0xbb, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x4b, 0xff, 
  0x00, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0xbf, 0xff, 0x9f, 0x7b, 0xdf, 0x00, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x4f, 0x6f, 0x6f, 0x6f, 0x6f, 0x4b, 0x00, 
  0x00, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0xbf, 0xff, 0x7f, 0x9f, 0x00, 0xbb, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x53, 0x6f, 0x6f, 0x6f, 0x4f, 0x93, 0x00, 
  0x00, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x7b, 0x00, 0x00, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x53, 0x6f, 0x4f, 0x4b, 0x4f, 0x00, 0x00, 
  0x00, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0xbf, 0x00, 0x77, 0x53, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x53, 0x4b, 0x4f, 0xb7, 0x00, 0x00, 0x00, 
  0x00, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x00, 0xff, 0x33, 0x97, 0x9b, 0x53, 0x57, 0x57, 0x57, 0x53, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0xdf, 0x00, 0x9b, 0x53, 0xdb, 0xdf, 0x53, 0x57, 0x57, 0x57, 0x53, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xdf, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0xbf, 0xdf, 0x7b, 0x53, 0x53, 0x53, 0x57, 0x57, 0x57, 0x57, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x57, 0x57, 0x57, 0x57, 0x53, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x57, 0x57, 0x57, 0x53, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xdf, 0x7b, 0x9f, 0x9f, 0x9f, 0x9f, 0x9b, 0x53, 0x57, 0x57, 0x57, 0x53, 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0x9f, 0x9f, 0x9f, 0x7b, 0x53, 0x53, 0x53, 0x33, 0x9b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x9f, 0x7b, 0x53, 0x77, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Blue: 5 bit, Green: 6 bit, Red: 5 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x6e, 0x9f, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x6e, 0x3f, 0x76, 0x3f, 0x34, 0x7f, 0x7d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x76, 0xbe, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0x3f, 0x34, 0x9f, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x9e, 0xbe, 0x7e, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0x9f, 0x4c, 0x3f, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x76, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0x9f, 0x44, 0xff, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0xd6, 0x7b, 0x42, 0xbf, 0xd6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x76, 0xbe, 0x7e, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0x5f, 0x3c, 0x9f, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x3a, 0xdb, 0x52, 0x3b, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xaf, 0x9e, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0x9f, 0x4c, 0x5f, 0x34, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x5b, 0xdb, 0x52, 0xfc, 0x52, 0xdb, 0x52, 0x3c, 0x5b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x6e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x7f, 0x3c, 0x3f, 0x96, 0x1e, 0xc6, 0x7b, 0x42, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0x7b, 0x42, 0xde, 0xbd, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x9e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x9f, 0x4c, 0xbf, 0x44, 0x1c, 0x53, 0xdb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xdb, 0x52, 0x7b, 0x42, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x6e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x1e, 0x4c, 0xbb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0x9b, 0x4a, 0x9e, 0xb5, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xa7, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xdf, 0x4c, 0xfb, 0x52, 0xfb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xdb, 0x52, 0xfc, 0x52, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x9e, 0x6e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0x7f, 0x3c, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xde, 0x4b, 0xdb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0x5b, 0x3a, 0x00, 0x00, 
  0x00, 0x00, 0x7f, 0xc7, 0x9e, 0x76, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0x76, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0x5e, 0xae, 0x7f, 0x44, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbb, 0x52, 0xfb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0x7b, 0x42, 0x3f, 0xe7, 
  0x00, 0x00, 0xdf, 0x8e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0x1e, 0xaf, 0x5e, 0xd7, 0xbe, 0x7e, 0xff, 0x65, 0x9e, 0xce, 0x00, 0x00, 0x7f, 0x44, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xdf, 0x4c, 0x3c, 0x53, 0xdb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfb, 0x52, 0x3b, 0x3a, 0x00, 0x00, 
  0x00, 0x00, 0x9e, 0x6e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0x1e, 0xaf, 0x5e, 0xdf, 0x9e, 0x76, 0x9e, 0x8e, 0x00, 0x00, 0xff, 0x9d, 0x7f, 0x3c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xde, 0x53, 0xdb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0x9b, 0x4a, 0x3d, 0x7c, 0x00, 0x00, 
  0x00, 0x00, 0x9e, 0x76, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0x9e, 0x76, 0x9e, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x34, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x3e, 0x4c, 0xdb, 0x52, 0xdb, 0x52, 0x9b, 0x4a, 0xdb, 0x52, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x9e, 0x76, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0x1e, 0xaf, 0x00, 0x00, 0x5f, 0x75, 0x7f, 0x3c, 0x9f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xfe, 0x43, 0x1b, 0x3a, 0xbb, 0x4a, 0xfd, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x9e, 0x6e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0x9e, 0x76, 0x00, 0x00, 0x3e, 0xe7, 0x3f, 0x2c, 0x9f, 0x85, 0xbf, 0x8d, 0x9f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x7f, 0x3c, 0x5f, 0x9e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xbe, 0x7e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x76, 0x5e, 0xcf, 0x00, 0x00, 0x3f, 0x76, 0x3f, 0x34, 0x7e, 0xbe, 0xde, 0xce, 0x7f, 0x3c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x5f, 0x3c, 0x1f, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x5f, 0xbf, 0x9e, 0x76, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0x1e, 0xaf, 0x3e, 0xbf, 0x3f, 0x6e, 0x7f, 0x44, 0x7f, 0x3c, 0x7f, 0x3c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x9f, 0x4c, 0x5f, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x9e, 0x76, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0x7e, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x5f, 0x3c, 0x7f, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x6e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x7f, 0x44, 0xff, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xc7, 0x7e, 0x6e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0xbf, 0x4c, 0xbf, 0x4c, 0x9f, 0x4c, 0x7f, 0x3c, 0xbf, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x7e, 0x9e, 0x76, 0xbe, 0x7e, 0xbe, 0x86, 0x3f, 0x76, 0x7f, 0x44, 0x9f, 0x44, 0x7f, 0x3c, 0x3f, 0x2c, 0xdf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xa7, 0xde, 0x8e, 0x3f, 0x76, 0x9f, 0x4c, 0x5f, 0x6d, 0x5f, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Blue: 5 bit, Green: 6 bit, Red: 5 bit BUT the 2 bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x1f, 0x85, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x9e, 0x76, 0x3f, 0x34, 0x3f, 0x7d, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x9e, 0x86, 0xbe, 0x76, 0x3f, 0x44, 0x7f, 0x34, 0x3f, 0xb6, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xff, 0x7e, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0x9f, 0x34, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x9e, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x44, 0x9f, 0x54, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd6, 0x9f, 0x42, 0x7b, 0xd6, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x9e, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x3c, 0x5f, 0xb6, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x3b, 0x52, 0xdb, 0x3a, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaf, 0x3f, 0x7e, 0x9e, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x9f, 0x34, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x1c, 0x52, 0xdb, 0x52, 0xfc, 0x52, 0xdb, 0x5b, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x9e, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x3c, 0x7f, 0x96, 0x3f, 0xc6, 0x1e, 0x42, 0x7b, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x42, 0x7b, 0xbd, 0xde, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xff, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x9f, 0x44, 0xbf, 0x53, 0x1c, 0x52, 0xdb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xdb, 0x42, 0x7b, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x9e, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x1e, 0x52, 0xbb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x4a, 0x9b, 0xb5, 0x9e, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xa7, 0x1f, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xdf, 0x52, 0xfb, 0x52, 0xfb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xdb, 0x52, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x6e, 0x9e, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x3c, 0x7f, 0x4c, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4b, 0xde, 0x52, 0xdb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x3a, 0x5b, 0x00, 0x00, 
  0x00, 0x00, 0xc7, 0x7f, 0x76, 0x9e, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0x76, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0xae, 0x5e, 0x44, 0x7f, 0x4c, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x52, 0xbb, 0x52, 0xfb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfc, 0x42, 0x7b, 0xe7, 0x3f, 
  0x00, 0x00, 0x8e, 0xdf, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0xaf, 0x1e, 0xd7, 0x5e, 0x7e, 0xbe, 0x65, 0xff, 0xce, 0x9e, 0x00, 0x00, 0x44, 0x7f, 0x4c, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xdf, 0x53, 0x3c, 0x52, 0xdb, 0x52, 0xfc, 0x52, 0xfc, 0x52, 0xfb, 0x3a, 0x3b, 0x00, 0x00, 
  0x00, 0x00, 0x6e, 0x9e, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0xaf, 0x1e, 0xdf, 0x5e, 0x76, 0x9e, 0x8e, 0x9e, 0x00, 0x00, 0x9d, 0xff, 0x3c, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x53, 0xde, 0x52, 0xdb, 0x52, 0xfc, 0x52, 0xfc, 0x4a, 0x9b, 0x7c, 0x3d, 0x00, 0x00, 
  0x00, 0x00, 0x76, 0x9e, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0x76, 0x9e, 0x6e, 0x9e, 0x00, 0x00, 0x00, 0x00, 0x34, 0x5f, 0x4c, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x3e, 0x52, 0xdb, 0x52, 0xdb, 0x4a, 0x9b, 0x52, 0xdb, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x76, 0x9e, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0xaf, 0x1e, 0x00, 0x00, 0x75, 0x5f, 0x3c, 0x7f, 0x44, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x43, 0xfe, 0x3a, 0x1b, 0x4a, 0xbb, 0x9c, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x6e, 0x9e, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0x76, 0x9e, 0x00, 0x00, 0xe7, 0x3e, 0x2c, 0x3f, 0x85, 0x9f, 0x8d, 0xbf, 0x44, 0x9f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x3c, 0x7f, 0x9e, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x7e, 0xbe, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x76, 0xbe, 0xcf, 0x5e, 0x00, 0x00, 0x76, 0x3f, 0x34, 0x3f, 0xbe, 0x7e, 0xce, 0xde, 0x3c, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x3c, 0x5f, 0xcf, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xbf, 0x5f, 0x76, 0x9e, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0xaf, 0x1e, 0xbf, 0x3e, 0x6e, 0x3f, 0x44, 0x7f, 0x3c, 0x7f, 0x3c, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x9f, 0x3c, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x76, 0x9e, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x7e, 0xbe, 0x7e, 0xbe, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x3c, 0x5f, 0xae, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x7e, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0xbf, 0x44, 0x7f, 0x5c, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x7f, 0x6e, 0x7e, 0x7e, 0xbe, 0x86, 0xbe, 0x86, 0xbe, 0x86, 0xde, 0x76, 0x3f, 0x44, 0x7f, 0x4c, 0xbf, 0x4c, 0xbf, 0x4c, 0x9f, 0x3c, 0x7f, 0x54, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x9e, 0x76, 0x9e, 0x7e, 0xbe, 0x86, 0xbe, 0x76, 0x3f, 0x44, 0x7f, 0x44, 0x9f, 0x3c, 0x7f, 0x2c, 0x3f, 0x8d, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa7, 0x1f, 0x8e, 0xde, 0x76, 0x3f, 0x4c, 0x9f, 0x6d, 0x5f, 0xa6, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  /*Pixel format: Blue: 8 bit, Green: 8 bit, Red: 8 bit, Fix 0xFF: 8 bit, */
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf6, 0xc1, 0x69, 0xff, 0xff, 0xb0, 0x7d, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf2, 0xd1, 0x6b, 0xff, 0xf6, 0xc5, 0x6f, 0xff, 0xff, 0x84, 0x33, 0xff, 0xff, 0xae, 0x75, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf3, 0xd1, 0x73, 0xff, 0xf3, 0xd6, 0x7d, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x86, 0x32, 0xff, 0xff, 0xd1, 0xb0, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf6, 0xdd, 0x96, 0xff, 0xf3, 0xd3, 0x76, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x92, 0x46, 0xff, 0xff, 0x84, 0x2e, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf2, 0xd0, 0x6e, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x8f, 0x41, 0xff, 0xff, 0x9b, 0x54, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf5, 0xd2, 0xcf, 0xff, 0xd9, 0x4b, 0x40, 0xff, 0xf5, 0xd3, 0xd0, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf3, 0xd1, 0x72, 0xff, 0xf3, 0xd4, 0x7b, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x88, 0x35, 0xff, 0xff, 0xd2, 0xb2, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xd8, 0x45, 0x39, 0xff, 0xdc, 0x58, 0x4d, 0xff, 0xd8, 0x45, 0x39, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf8, 0xe4, 0xac, 0xff, 0xf3, 0xd2, 0x75, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x92, 0x45, 0xff, 0xff, 0x88, 0x34, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xde, 0x62, 0x58, 0xff, 0xdc, 0x57, 0x4d, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdc, 0x57, 0x4d, 0xff, 0xde, 0x63, 0x59, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf2, 0xcf, 0x6b, 0xff, 0xf3, 0xd4, 0x7c, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x8c, 0x3c, 0xff, 0xff, 0xc3, 0x93, 0xff, 0xef, 0xbf, 0xc1, 0xff, 0xd9, 0x4d, 0x42, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xd9, 0x4d, 0x42, 0xff, 0xf0, 0xb9, 0xb5, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf6, 0xde, 0x9b, 0xff, 0xf3, 0xd3, 0x77, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x92, 0x46, 0xff, 0xff, 0x94, 0x3f, 0xff, 0xde, 0x60, 0x54, 0xff, 0xdc, 0x59, 0x50, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdc, 0x5a, 0x50, 0xff, 0xda, 0x4e, 0x43, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf2, 0xcf, 0x6b, 0xff, 0xf3, 0xd4, 0x7c, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x95, 0x46, 0xff, 0xf3, 0x81, 0x49, 0xff, 0xd9, 0x56, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xda, 0x4f, 0x45, 0xff, 0xef, 0xb2, 0xae, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf7, 0xe0, 0xa1, 0xff, 0xf3, 0xd3, 0x77, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x46, 0xff, 0xff, 0x9a, 0x45, 0xff, 0xdc, 0x5b, 0x52, 0xff, 0xdc, 0x5b, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdc, 0x59, 0x4f, 0xff, 0xdd, 0x5d, 0x53, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf2, 0xcf, 0x6c, 0xff, 0xf3, 0xd4, 0x7c, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8b, 0x3f, 0xff, 0xff, 0x8d, 0x3c, 0xff, 0xff, 0x92, 0x46, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x96, 0x46, 0xff, 0xef, 0x7a, 0x4c, 0xff, 0xda, 0x58, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xd8, 0x47, 0x3c, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xf9, 0xeb, 0xc1, 0xff, 0xf3, 0xd2, 0x74, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd3, 0x78, 0xff, 0xf4, 0xd3, 0x74, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc4, 0x6e, 0xff, 0xff, 0x8e, 0x44, 0xff, 0xf3, 0xc7, 0xaa, 0xff, 0xff, 0x8e, 0x3d, 0xff, 0xff, 0x92, 0x46, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x46, 0xff, 0xff, 0x95, 0x47, 0xff, 0xd8, 0x55, 0x53, 0xff, 0xdc, 0x5b, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xd9, 0x4c, 0x41, 0xff, 0xf9, 0xe5, 0xe3, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xf5, 0xd9, 0x8a, 0xff, 0xf3, 0xd3, 0x79, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd3, 0x78, 0xff, 0xf4, 0xdf, 0xa9, 0xff, 0xf4, 0xe9, 0xd4, 0xff, 0xf3, 0xd5, 0x76, 0xff, 0xf8, 0xbb, 0x5d, 0xff, 0xf0, 0xd2, 0xc5, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x8d, 0x3d, 0xff, 0xff, 0x92, 0x46, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x98, 0x45, 0xff, 0xe2, 0x66, 0x50, 0xff, 0xdb, 0x5a, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdc, 0x5b, 0x51, 0xff, 0xd8, 0x45, 0x39, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xf2, 0xcf, 0x6c, 0xff, 0xf3, 0xd4, 0x7c, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd3, 0x77, 0xff, 0xf4, 0xe0, 0xac, 0xff, 0xf4, 0xea, 0xd9, 0xff, 0xf4, 0xd2, 0x70, 0xff, 0xf3, 0xd2, 0x89, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf5, 0xbc, 0x95, 0xff, 0xff, 0x8d, 0x3b, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x96, 0x46, 0xff, 0xee, 0x78, 0x4d, 0xff, 0xda, 0x58, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdd, 0x5c, 0x52, 0xff, 0xdb, 0x52, 0x47, 0xff, 0xe5, 0x84, 0x7c, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xf2, 0xd0, 0x70, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd3, 0x77, 0xff, 0xf4, 0xd2, 0x74, 0xff, 0xf4, 0xd0, 0x6b, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x87, 0x31, 0xff, 0xff, 0x92, 0x46, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x95, 0x46, 0xff, 0xf4, 0x83, 0x4a, 0xff, 0xda, 0x57, 0x52, 0xff, 0xdc, 0x5a, 0x4f, 0xff, 0xda, 0x50, 0x45, 0xff, 0xdc, 0x58, 0x4e, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xf2, 0xd0, 0x70, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd3, 0x75, 0xff, 0xf4, 0xe0, 0xaa, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf9, 0xa7, 0x6e, 0xff, 0xff, 0x8b, 0x39, 0xff, 0xff, 0x8f, 0x3f, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x95, 0x46, 0xff, 0xf4, 0x7d, 0x43, 0xff, 0xd5, 0x42, 0x3c, 0xff, 0xdb, 0x55, 0x4b, 0xff, 0xea, 0x9c, 0x96, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xf2, 0xcf, 0x6c, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd4, 0x7c, 0xff, 0xf4, 0xd2, 0x71, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf4, 0xe4, 0xdf, 0xff, 0xff, 0x83, 0x29, 0xff, 0xf8, 0xb0, 0x7e, 0xff, 0xf7, 0xb5, 0x88, 0xff, 0xff, 0x8f, 0x3f, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x8c, 0x3c, 0xff, 0xff, 0xc7, 0x9a, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xf3, 0xd4, 0x7a, 0xff, 0xf3, 0xd4, 0x7b, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd3, 0x74, 0xff, 0xf4, 0xe7, 0xcc, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf6, 0xc6, 0x74, 0xff, 0xff, 0x86, 0x34, 0xff, 0xf1, 0xce, 0xb9, 0xff, 0xef, 0xd8, 0xca, 0xff, 0xff, 0x8c, 0x3a, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x89, 0x36, 0xff, 0xff, 0xdf, 0xc8, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xf8, 0xe7, 0xb5, 0xff, 0xf3, 0xd2, 0x74, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd3, 0x78, 0xff, 0xf4, 0xdf, 0xa7, 0xff, 0xf3, 0xe4, 0xb6, 0xff, 0xf6, 0xc3, 0x68, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x8d, 0x3b, 0xff, 0xff, 0x8c, 0x3a, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x92, 0x45, 0xff, 0xff, 0x89, 0x36, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf2, 0xd0, 0x6e, 0xff, 0xf3, 0xd4, 0x7c, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd3, 0x78, 0xff, 0xf3, 0xd5, 0x78, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x89, 0x36, 0xff, 0xff, 0xcb, 0xa6, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf2, 0xce, 0x6a, 0xff, 0xf3, 0xd4, 0x7c, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x8d, 0x3e, 0xff, 0xff, 0x9c, 0x56, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf9, 0xeb, 0xc3, 0xff, 0xf2, 0xce, 0x69, 0xff, 0xf3, 0xd4, 0x7b, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf4, 0xd5, 0x7d, 0xff, 0xf3, 0xd7, 0x7e, 0xff, 0xf6, 0xc5, 0x71, 0xff, 0xff, 0x8d, 0x42, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x93, 0x47, 0xff, 0xff, 0x92, 0x46, 0xff, 0xff, 0x8b, 0x39, 0xff, 0xff, 0x96, 0x4d, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf3, 0xd2, 0x76, 0xff, 0xf3, 0xd1, 0x71, 0xff, 0xf3, 0xd3, 0x78, 0xff, 0xf3, 0xd6, 0x7d, 0xff, 0xf6, 0xc5, 0x70, 0xff, 0xff, 0x8c, 0x41, 0xff, 0xff, 0x90, 0x42, 0xff, 0xff, 0x8c, 0x3c, 0xff, 0xff, 0x83, 0x2c, 0xff, 0xff, 0xb8, 0x85, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xf7, 0xe1, 0xa4, 0xff, 0xf4, 0xda, 0x8a, 0xff, 0xf6, 0xc5, 0x70, 0xff, 0xff, 0x90, 0x46, 0xff, 0xfe, 0xa7, 0x69, 0xff, 0xff, 0xc7, 0x9f, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
#endif
};

const lv_img_dsc_t hum_img_src = {
  .header.always_zero = 0,
  .header.w = 25,
  .header.h = 25,
  .data_size = 625 * LV_COLOR_SIZE / 8,
  .header.cf = LV_IMG_CF_TRUE_COLOR,
  .data = hum_img_src_map,
};
