#ifndef COMPONENTS_IO_IO
#define COMPONENTS_IO_IO

#include <stdint.h>

typedef enum
{
    TCA6416A_BEEP_FAIL,
    TCA6416A_BEEP_PASS,
    
    TCA6416A_VL53L3,
    TCA6416A_LED_OFF,
    /* Used by ECM */

    TCA6416A_CTRL1,
    TCA6416A_CTRL2,
    TCA6416A_CTRL3,
    TCA6416A_CTRL4,
    TCA6416A_LED_BLUE,
    TCA6416A_LED_RED,
    TCA6416A_LED_GREEN,
    TCA6416A_RELAY
} output_event_id_t;

typedef struct
{
    output_event_id_t id;
    uint8_t level;
} output_event_t;

typedef enum
{
    LED_COLOR_BLUE,
    LED_COLOR_RED,
    LED_COLOR_GREEN,
    LED_COLOR_MAGENTA, /* BLUE + RED */
    LED_COLOR_CYAN,    /* BLUE + GREEN */
    LED_COLOR_YELLOW,  /* RED + GREEN */
    LED_COLOR_WHITE,   /* BLUE + RED + GREEN */
} io_ledcolor_t;

void io_init(void);

void io_ctrl1_set_level(uint8_t level);
void io_ctrl2_set_level(uint8_t level);
void io_ctrl3_set_level(uint8_t level);
void io_ctrl4_set_level(uint8_t level);
void io_ledcolor(io_ledcolor_t ledcolor);
void io_relay_set_level(uint8_t level);
uint8_t io_relay_get_level(void);


#if 0
void io_set_red_led(uint8_t state);

void io_set_blue_led(uint8_t state);

void io_set_green_led(uint8_t state);

void io_set_buzzer(uint8_t state);

void io_set_relay(uint8_t level);

uint8_t io_get_relay(void);

void io_beep(uint8_t type);

void io_enable_vl53l3(uint8_t en);
#endif

#endif