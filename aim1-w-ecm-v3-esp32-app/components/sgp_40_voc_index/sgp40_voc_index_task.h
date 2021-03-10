#ifndef _SGP40_VOC_INDEX_TASK_H
#define _SGP40_VOC_INDEX_TASK_H

#include <stdint.h>

extern int32_t SGP40_VOC;
extern float SHT4X_HUM;
extern float SHT4X_TEMP;

/**
 * @brief   start a task to read voc index from the sgp40 and sht40
 */ 
void sgp40_voc_index_start_task();
#endif