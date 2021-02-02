#include "sensirion_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/**
 * Sleep for a given number of microseconds. The function should delay the
 * execution for at least the given time, but may also sleep longer.
 *
 * Despite the unit, a <10 millisecond precision is sufficient.
 *
 * @param useconds the sleep time in microseconds
 */
void sensirion_sleep_usec(uint32_t useconds) {
    uint32_t usec_to_ms = (useconds / 1000);
    vTaskDelay(pdMS_TO_TICKS(usec_to_ms));
}
 