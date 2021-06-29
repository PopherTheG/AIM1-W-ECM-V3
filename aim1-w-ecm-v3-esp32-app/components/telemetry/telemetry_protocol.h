#ifndef COMPONENTS_TELEMETRY_TELEMETRY_PROTOCOL
#define COMPONENTS_TELEMETRY_TELEMETRY_PROTOCOL

#include <stdint.h>

enum
{
    TELEMETRY_TYPE_AUTH = 0x01,
    TELEMETRY_TYPE_LOG = 0x02,
    TELEMETRY_TYPE_SENSOR = 0x03,
};

enum
{
    TELEMETRY_DEVICE_BLE = 0x01,
    TELEMETRY_DEVICE_BSCAN = 0x02,
};

typedef struct 
{
    uint8_t type;
    uint8_t device_type;
    uint64_t serial;
    uint32_t timestamp; 
    int16_t voc_index;
    int16_t temperature;
    int16_t humidity;
    int16_t pm2_5;
    int16_t pm10;
    int16_t co2;
} __attribute__((packed)) telemetry_sgp40_sht4x_t;

/* TO BE IMPLEMENTED*/
typedef struct 
{   
    uint8_t type;
    uint8_t device_type;
    uint64_t serial;
    uint32_t timestamp;
    int16_t voc_index;
    int16_t temperature;
    int16_t humidity;
    int16_t pm2_5;
    int16_t pm10;
    int16_t co2;
}__attribute__((packed)) telemetry_airparameters_t;


#endif