/*
 * Copyright (c) 2020, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "svm40.h"

#include <stdio.h>

/* TO USE CONSOLE OUTPUT (printf) YOU MAY NEED TO ADAPT THE
 * INCLUDES ABOVE OR DEFINE THEM ACCORDING TO YOUR PLATFORM.
 * #define printf(...)
 */

int main(void) {
    int16_t error;
    char serial_id[SVM40_MAX_SERIAL_LEN];

    const char* driver_version = svm40_get_driver_version();
    if (driver_version) {
        printf("SVM40 driver version %s\n", driver_version);
    } else {
        printf("fatal: Getting driver version failed\n");
        return -1;
    }

    /* Initialize I2C bus */
    sensirion_i2c_init();

    while (svm40_probe() != 0) {
        printf("SVM40 sensor probing failed\n");
        sensirion_sleep_usec(1000000); /* wait 1s */
    }
    printf("SVM40 sensor probing successful\n");

    error = svm40_get_serial(serial_id);
    if (error != NO_ERROR) {
        printf("Error reading SVM40 serial: %i\n", error);
    } else {
        printf("Serial Number: %s\n", serial_id);
    }

    struct svm40_version_information version_information;
    error = svm40_get_version(&version_information);
    if (error) {
        printf("Error reading SVM40 version: %i\n", error);
    } else {
        if (version_information.firmware_debug) {
            printf("Development firmware version: ");
        }
        printf("FW: %u.%u, HW: %u.%u, protocol: %u.%u\n",
               version_information.firmware_major,
               version_information.firmware_minor,
               version_information.hardware_major,
               version_information.hardware_minor,
               version_information.protocol_major,
               version_information.protocol_minor);

        // check if firmware is older than 2.2
        if (version_information.firmware_major < 2 ||
            (version_information.firmware_major == 2 &&
             version_information.firmware_minor < 2)) {
            printf("Warning: Old firmware version which may return constant "
                   "values after a few hours of operation\n");
        }
    }

    error = svm40_start_continuous_measurement();
    if (error) {
        printf("Error starting measurement: %i\n", error);
    }

    for (;;) {
        int16_t voc_index;
        int16_t relative_humidity;
        int16_t temperature;
        sensirion_sleep_usec(SVM40_MEASUREMENT_INTERVAL_USEC); /* wait 1s */
        error = svm40_read_measured_values_as_integers(
            &voc_index, &relative_humidity, &temperature);
        if (error) {
            printf("Error reading measurement values: %i\n", error);
        } else {
            printf("Measurement result\n");
            printf(" VOC index: %.1f\n", voc_index / 10.0f);
            printf(" Relative Humidity: %.2f%%RH\n",
                   relative_humidity / 100.0f);
            printf(" Temperature: %.2f°C\n", temperature / 200.0f);
        }
    }

    return 0;
}
