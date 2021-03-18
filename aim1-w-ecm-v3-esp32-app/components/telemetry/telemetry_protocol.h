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

// typedef struct {
//     uint8_t type;
//     uint16_t version;
//     uint8_t device_type;
//     uint16_t reqNo;
//     uint64_t serial;
//     float temperature;
//     uint8_t namespaceID[10];
//     uint8_t instanceID[6];
// } __attribute__((packed)) telemetry_t;

// typedef struct {
//     uint8_t type;
//     uint8_t device_type;
//     uint16_t reqNo;
//     uint64_t serial;
//     uint32_t timestamp;
//     uint16_t temperature;
//     char uuid[37];
// } __attribute__((packed)) telemetry_simple_t;

// typedef struct {
//     uint8_t type;
//     uint8_t device_type;    
//     uint64_t serial;
//     uint32_t timestamp;
//     int16_t voc_index;
//     int16_t humidity;
//     int16_t temperature;
// } __attribute__((packed)) telemetry_svm40_t;

typedef struct 
{
    uint8_t type;
    uint8_t device_type;
    uint64_t serial;
    uint32_t timestamp;
    int32_t voc_index;
    float temperature;
    float humidity;
} __attribute((packed)) telemetry_sgp40_sht4x_t;

#endif