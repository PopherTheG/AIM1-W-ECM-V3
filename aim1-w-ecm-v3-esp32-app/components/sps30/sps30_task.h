#ifndef SPS30_TASK_H
#define SPS30_TASK_H

#include <stdint.h>
#include "telemetry_protocol.h"

extern float SPS30_PM2_5;
extern float SPS30_PM10;

typedef enum
{
    SPS30_EVT_DATA_READY,
} sps30_event_id_t;

typedef struct 
{
    
} sps30_sensor_t;

typedef struct 
{
    sps30_event_id_t id;
    union
    {
        sps30_sensor_t data;
    }
} sps30_event_t;



/**
 * sps30_start_task() - start sps30 task
 */
void sps30_start_task();

void sps30_get_data(sps30_sensor_t *data);

#endif