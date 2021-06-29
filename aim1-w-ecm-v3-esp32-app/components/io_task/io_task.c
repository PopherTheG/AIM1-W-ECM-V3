#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "freertos/timers.h"
#include "esp_log.h"

#include "TCA6416A.h"
#include "TCA6416A_i2c.h"

#include "io_task.h"

#define IO_MUTEX_LOCK(_mutex) xSemaphoreTake(_mutex, pdMS_TO_TICKS(10))
#define IO_MUTEX_UNLOCK(_mutex) xSemaphoreGive(_mutex)

#define TAG "io-task"

#define HIGH 1
#define LOW 0

#define LED_RED TCA6416A_P00   /* EXPNDR */
#define LED_GREEN TCA6416A_P01 /* EXPNDR */
#define LED_BLUE TCA6416A_P02  /* EXPNDR */

#define CTRL1 TCA6416A_P14 /* EXPNDR */
#define CTRL2 TCA6416A_P15 /* EXPNDR */
#define CTRL3 TCA6416A_P17 /* EXPNDR */
#define CTRL4 TCA6416A_P16 /* EXPNDR */


#define RELAY_SET TCA6416A_P05 /* MAIN */
#define RELAY_RST TCA6416A_P06 /* MAIN */

static void tca6416a_task(void *data);
static void init_main_expander(void);
static void init_secondary_expander(void);
static void io_redled_set_level(uint8_t level);
static void io_blueled_set_level(uint8_t level);
static void io_greenled_set_level(uint8_t level);

static SemaphoreHandle_t io_mutex;
static SemaphoreHandle_t io_semaphore;
static QueueHandle_t tca6416a_out_queue;
static TCA6416ARegs main_regs;
static TCA6416ARegs regs;
static TCA6416ARegs input_regs;

static uint8_t relay_level = 0;
static uint8_t ctrl1_level = 0;
static uint8_t ctrl2_level = 0;
static uint8_t ctrl3_level = 0;
static uint8_t ctrl4_level = 0;

static void tca6416a_task(void *data)
{
    (void)data;
    while (1)
    {
        output_event_t output_evt;
        if (xQueueReceive(tca6416a_out_queue, &output_evt, portMAX_DELAY) == pdPASS)
        {
            switch (output_evt.id)
            {
            case TCA6416A_CTRL1:
                ESP_LOGI(TAG, "CTRL1 status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                TCA6416AWriteOutputPin(CTRL1, output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                ctrl1_level = output_evt.level;
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case TCA6416A_CTRL2:
                ESP_LOGI(TAG, "CTRL2 status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                TCA6416AWriteOutputPin(CTRL2, output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                ctrl2_level = output_evt.level;
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case TCA6416A_CTRL3:
                ESP_LOGI(TAG, "CTRL3 status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                TCA6416AWriteOutputPin(CTRL3, output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                ctrl3_level = output_evt.level;
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case TCA6416A_CTRL4:
                ESP_LOGI(TAG, "CTRL4 status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                TCA6416AWriteOutputPin(CTRL4, output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                ctrl4_level = output_evt.level;
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case TCA6416A_LED_RED:
                // ESP_LOGI(TAG, "RED LED status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                TCA6416AWriteOutputPin(LED_RED, output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case TCA6416A_LED_BLUE:
                // ESP_LOGI(TAG, "BLUE LED status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                TCA6416AWriteOutputPin(LED_BLUE, output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case TCA6416A_LED_GREEN:
                // ESP_LOGI(TAG, "GREEN LED status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                TCA6416AWriteOutputPin(LED_GREEN, output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case TCA6416A_RELAY:
                ESP_LOGI(TAG, "RELAY status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                if (output_evt.level == 1)
                {
                    TCA6416AWriteOutputPin(RELAY_SET, 1, TCA6416A_ADDRESS, 0);
                    TCA6416AWriteOutputPin(RELAY_RST, 0, TCA6416A_ADDRESS, 0);
                }
                else if (output_evt.level == 0)
                {
                    TCA6416AWriteOutputPin(RELAY_SET, 0, TCA6416A_ADDRESS, 0);
                    TCA6416AWriteOutputPin(RELAY_RST, 1, TCA6416A_ADDRESS, 0);
                }
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case BUZZER_PASS:
                for (uint16_t i = 0; i < 50; i++)
                {
                    TCA6416AWriteOutputPin(TCA6416A_P06, HIGH, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                    TCA6416AWriteOutputPin(TCA6416A_P06, LOW, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                }
                vTaskDelay(pdMS_TO_TICKS(100));
                for (uint16_t i = 0; i < 50; i++)
                {
                    TCA6416AWriteOutputPin(TCA6416A_P06, HIGH, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                    TCA6416AWriteOutputPin(TCA6416A_P06, LOW, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                }
                break;
            case BUZZER_FAIL:
                for (uint16_t i = 0; i < 100; i++)
                {
                    TCA6416AWriteOutputPin(TCA6416A_P06, HIGH, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                    TCA6416AWriteOutputPin(TCA6416A_P06, LOW, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                }
                vTaskDelay(pdMS_TO_TICKS(100));
                for (uint16_t i = 0; i < 100; i++)
                {
                    TCA6416AWriteOutputPin(TCA6416A_P06, HIGH, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                    TCA6416AWriteOutputPin(TCA6416A_P06, LOW, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                }
                vTaskDelay(pdMS_TO_TICKS(100));
                for (uint16_t i = 0; i < 100; i++)
                {
                    TCA6416AWriteOutputPin(TCA6416A_P06, HIGH, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                    TCA6416AWriteOutputPin(TCA6416A_P06, LOW, TCA6416A_ADDRESS_EXPND, 1);
                    vTaskDelay(pdMS_TO_TICKS(0.25));
                }
                break;
            case ST7789_RST_EVT:
                // ESP_LOGI(TAG, "ST7789_RST status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                // TCA6416AWriteOutputPin(TCA6416A_P05, output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case ST7789_DC_EVT:
                // ESP_LOGI(TAG, "ST7789_DC status: %d", output_evt.level);
                IO_MUTEX_LOCK(io_mutex);
                // TCA6416AWriteOutputPin(TCA6416A_P03, output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            case ST7789_BCKLGHT_EVT:
                IO_MUTEX_LOCK(io_mutex);
                ESP_LOGI(TAG, "ST7789_BCKLGHT: %d", output_evt.level);
                TCA6416AWriteOutputPin(TCA6416A_P04,  output_evt.level, TCA6416A_ADDRESS_EXPND, 1);
                IO_MUTEX_UNLOCK(io_mutex);
                break;
            default:
                break;
            }
        }
    }
}

static void init_main_expander(void)
{
    TCA6416AInitDefault(&main_regs);

    main_regs.Config.Port.P0.bit.B0 = TCA6416A_CONFIG_INPUT;

    main_regs.Config.Port.P0.bit.B5 = TCA6416A_CONFIG_OUTPUT; /* 2A Relay SET */
    main_regs.Config.Port.P0.bit.B6 = TCA6416A_CONFIG_OUTPUT; /* 2A Relay RST */

    main_regs.Config.Port.P1.bit.B2 = TCA6416A_CONFIG_OUTPUT;
    main_regs.Config.Port.P1.bit.B3 = TCA6416A_CONFIG_OUTPUT; /* BUZZER */

    main_regs.Output.Port.P1.bit.B2 = 0;
    main_regs.Output.Port.P1.bit.B3 = 0;

    if (TCA6416AInitI2CReg(&main_regs, TCA6416A_ADDRESS, 0) == I2C_OPERATION_FAIL)
    {
        ESP_LOGE(TAG, "Failed to init TCA6416A");
    }
}

static void init_secondary_expander(void)
{
    TCA6416AInitDefault(&regs);

    regs.Config.Port.P0.bit.B0 = TCA6416A_CONFIG_OUTPUT; /* RED LED */
    regs.Config.Port.P0.bit.B1 = TCA6416A_CONFIG_OUTPUT; /* GREEN LED */
    regs.Config.Port.P0.bit.B2 = TCA6416A_CONFIG_OUTPUT; /* BLUE LED */
    regs.Config.Port.P0.bit.B5 = TCA6416A_CONFIG_OUTPUT; /* RST PIN ST7789 */
    regs.Config.Port.P0.bit.B3 = TCA6416A_CONFIG_OUTPUT; /* DC PIN ST7789 */
    regs.Config.Port.P0.bit.B4 = TCA6416A_CONFIG_OUTPUT; /* BCKLGHT PIN ST7789 */

    regs.Config.Port.P1.bit.B4 = TCA6416A_CONFIG_OUTPUT; /* CTRL1 LED */
    regs.Config.Port.P1.bit.B5 = TCA6416A_CONFIG_OUTPUT; /* CTRL2 LED */
    regs.Config.Port.P1.bit.B7 = TCA6416A_CONFIG_OUTPUT; /* CTRL3 LED */
    regs.Config.Port.P1.bit.B6 = TCA6416A_CONFIG_OUTPUT; /* CTRL4 LED */

    /* Initial output*/
    // regs.Output.Port.P0.bit.B4 = HIGH; /* Activate ST7789 backlight*/
    regs.Output.Port.P0.bit.B0 = HIGH; /* RED LED note: active low device */
    regs.Output.Port.P0.bit.B1 = HIGH; /* GREEN LED note: active low device */
    regs.Output.Port.P0.bit.B2 = HIGH; /* BLUE LED note: active low device */
    
    regs.Output.Port.P1.bit.B4 = LOW;  /* CTRL1 LED initially unconnected */
    regs.Output.Port.P1.bit.B5 = LOW;  /* CTRL2 LED initially unconnected */
    regs.Output.Port.P1.bit.B7 = LOW;  /* CTRL3 LED initially unconnected */
    regs.Output.Port.P1.bit.B6 = LOW;  /* CTRL4 LED initially unconnected */

    if (TCA6416AInitI2CReg(&regs, TCA6416A_ADDRESS_EXPND, 1) == I2C_OPERATION_FAIL)
    {
        ESP_LOGE(TAG, "Failed to init TCA6416A on DEX");
    }
}

void io_init(void)
{
    init_main_expander();
    init_secondary_expander();

    tca6416a_out_queue = xQueueCreate(10, sizeof(output_event_t));

    io_mutex = xSemaphoreCreateMutex();
    configASSERT(io_mutex);
    xTaskCreate(tca6416a_task, "tca6416a-out", 1024 * 3, NULL, 6, NULL);
}

void io_st7789rst_set_level(uint8_t level)
{
    // output_event_t event = {0};
    // event.id = ST7789_RST_EVT; 

    // if (level == 0)
    // {
    //     event.level = LOW;
    // }
    // else if (level == 1)
    // {
    //     event.level = HIGH;
    // }
    // else
    // {
    //     ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    // }

    // xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));

    TCA6416AWriteOutputPin(TCA6416A_P05, level, TCA6416A_ADDRESS_EXPND, 1);
}

void io_st7789dc_set_level(uint8_t level)
{
    // output_event_t event = {0};
    // event.id = ST7789_DC_EVT;

    // if (level == 0)
    // {
    //     event.level = LOW;
    // }
    // else if (level == 1)
    // {
    //     event.level = HIGH;
    // }
    // else
    // {
    //     ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    // }

    // xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
    TCA6416AWriteOutputPin(TCA6416A_P03, level, TCA6416A_ADDRESS_EXPND, 1);
}

void io_st7789bcklght_set_level(uint8_t level)
{
    output_event_t event = {0};
    event.id = ST7789_BCKLGHT_EVT;
    if (level == 0 || level == 1)
    {
        event.level = level;
    }
    else
    {
        ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    }
    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}

void io_ctrl1_set_level(uint8_t level)
{
    output_event_t event = {0};

    event.id = TCA6416A_CTRL1;
    if (level == 0)
    {
        event.level = LOW;
    }
    else if (level == 1)
    {
        event.level = HIGH;
    }
    else
    {
        ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    }

    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}
void io_ctrl2_set_level(uint8_t level)
{
    output_event_t event = {0};

    event.id = TCA6416A_CTRL2;
    if (level == 0)
    {
        event.level = LOW;
    }
    else if (level == 1)
    {
        event.level = HIGH;
    }
    else
    {
        ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    }

    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}
void io_ctrl3_set_level(uint8_t level)
{
    output_event_t event = {0};

    event.id = TCA6416A_CTRL3;
    if (level == 0)
    {
        event.level = LOW;
    }
    else if (level == 1)
    {
        event.level = HIGH;
    }
    else
    {
        ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    }

    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}
void io_ctrl4_set_level(uint8_t level)
{
    output_event_t event = {0};

    event.id = TCA6416A_CTRL4;
    if (level == 0)
    {
        event.level = LOW;
    }
    else if (level == 1)
    {
        event.level = HIGH;
    }
    else
    {
        ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    }

    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}

uint8_t io_ctrl1_get_level()
{
    return ctrl1_level;
}

uint8_t io_ctrl2_get_level()
{
    return ctrl2_level;
}

uint8_t io_ctrl3_get_level()
{
    return ctrl3_level;
}

uint8_t io_ctrl4_get_level()
{
    return ctrl4_level;
}

static void io_redled_set_level(uint8_t level)
{
    output_event_t event = {0};

    event.id = TCA6416A_LED_RED;
    if (level == 0)
    {
        event.level = HIGH; /* LED is active low */
    }
    else if (level == 1)
    {
        event.level = LOW;
    }
    else
    {
        ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    }

    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}
static void io_blueled_set_level(uint8_t level)
{
    output_event_t event = {0};

    event.id = TCA6416A_LED_BLUE;
    if (level == 0)
    {
        event.level = HIGH; /* LED is active low */
    }
    else if (level == 1)
    {
        event.level = LOW;
    }
    else
    {
        ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    }

    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}
static void io_greenled_set_level(uint8_t level)
{
    output_event_t event = {0};

    event.id = TCA6416A_LED_GREEN;
    if (level == 0)
    {
        event.level = HIGH; /* LED is active low */
    }
    else if (level == 1)
    {
        event.level = LOW;
    }
    else
    {
        ESP_LOGE(TAG, "Unkown event level (only 0 or 1)");
    }

    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}

void io_ledcolor(io_ledcolor_t ledcolor)
{
    switch (ledcolor)
    {
    case LED_COLOR_NONE:
        io_blueled_set_level(0);
        io_redled_set_level(0);
        io_greenled_set_level(0);
        ESP_LOGI(TAG, "LED_COLOR_NONE");
        break;
    case LED_COLOR_BLUE:
        io_blueled_set_level(1);
        io_redled_set_level(0);
        io_greenled_set_level(0);
        ESP_LOGI(TAG, "LED_COLOR_BLUE");
        break;
    case LED_COLOR_RED:
        io_blueled_set_level(0);
        io_redled_set_level(1);
        io_greenled_set_level(0);
        ESP_LOGI(TAG, "LED_COLOR_RED");
        break;
    case LED_COLOR_GREEN:
        io_blueled_set_level(0);
        io_redled_set_level(0);
        io_greenled_set_level(1);
        ESP_LOGI(TAG, "LED_COLOR_GREEN");
        break;
    case LED_COLOR_MAGENTA:
        io_blueled_set_level(1);
        io_redled_set_level(1);
        io_greenled_set_level(0);
        ESP_LOGI(TAG, "LED_COLOR_MAGENTA");
        break;
    case LED_COLOR_CYAN:
        io_blueled_set_level(1);
        io_redled_set_level(0);
        io_greenled_set_level(1);
        ESP_LOGI(TAG, "LED_COLOR_CYAN");
        break;
    case LED_COLOR_YELLOW:
        io_blueled_set_level(0);
        io_redled_set_level(1);
        io_greenled_set_level(1);
        ESP_LOGI(TAG, "LED_COLOR_YELLOW");
        break;
    case LED_COLOR_WHITE:
        io_blueled_set_level(1);
        io_redled_set_level(1);
        io_greenled_set_level(1);
        ESP_LOGI(TAG, "LED_COLOR_WHITE");
        break;
    default:
        break;
    }
}

void io_relay_set_level(uint8_t level)
{
    output_event_t event = {0};
    event.id = TCA6416A_RELAY;

    if (level == 0)
    {
        event.level = LOW;
        relay_level = 0;
    }
    else if (level == 1)
    {
        event.level = HIGH;
        relay_level = 1;
    }
    else
    {
        ESP_LOGE(TAG, "Unknown event level (only 0 or 1)");
    }
    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}

uint8_t io_relay_get_level(void)
{
    return relay_level;
}

void io_buzzer(uint8_t state)
{
    output_event_t event = {0};

    event.id = state;

    // if (state == BUZZER_STATE_PASS)
    // {
    // }
    // else if (state == BUZZER_STATE_FAIL)
    // {
    // }

    xQueueSendToBack(tca6416a_out_queue, &event, pdMS_TO_TICKS(100));
}