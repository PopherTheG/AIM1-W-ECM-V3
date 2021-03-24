#ifndef _SGP40_VOC_INDEX_TASK_H
#define _SGP40_VOC_INDEX_TASK_H


#include <stdint.h>
#include "telemetry_protocol.h"

extern int32_t SGP40_VOC;
extern float SHT4X_HUM;
extern float SHT4X_TEMP;

typedef enum
{
    SGP40SHT4X_EVT_DATA_READY,
} sgp40_sht4x_event_id_t;

typedef struct 
{
    int32_t voc_index;
    int32_t relative_humidity;
    int32_t temperature;
} sgp40_sht4x_sensor_t;

typedef struct 
{
    sgp40_sht4x_event_id_t id;
    union 
    {
        sgp40_sht4x_sensor_t data;
    } evt;
} sgp40_sht4x_event_t;


/**
 * @brief   start a task to read voc index from the sgp40 and sht40
 */
void sgp40_voc_index_start_task();

void sgp40_sht4x_get_data(sgp40_sht4x_sensor_t *data);
#endif