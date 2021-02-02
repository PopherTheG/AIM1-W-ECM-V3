/*
 * Copyright (c) 2018, Sensirion AG
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

#include "string.h"

#include "sensirion_config.h"
#include "sensirion_uart_hal.h"
#include "sensirion_sleep.h"

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_err.h"


#define SPS30_UART      UART_NUM_1 
#define TXD_PIN_UART1   GPIO_NUM_4
#define RXD_PIN_UART1   GPIO_NUM_5
#define RX_BUF_SIZE     (1024 * 1)
// #define TX_BUF_SIZE     (1024 * 1)
#define TAG             "SPS30 UART"

/*
 * INSTRUCTIONS
 * ============
 *
 * Implement all functions where they are marked with TODO: implement
 * Follow the function specification in the comments.
 */

/**
 * sensirion_uart_select_port() - select the UART port index to use
 *                                THE IMPLEMENTATION IS OPTIONAL ON SINGLE-PORT
 *                                SETUPS (only one SPS30)
 *
 * Return:      0 on success, an error code otherwise
 */
int16_t sensirion_uart_select_port(uint8_t port) {
    return 0;
}

/**
 * sensirion_uart_open() - initialize UART
 *
 * Return:      0 on success, an error code otherwise   
 */
int16_t sensirion_uart_open() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
    };
    int16_t err; /* For error checking */
    err = uart_param_config(SPS30_UART, &uart_config);
    if (err != ESP_OK)
        return err;
    err = uart_set_pin(SPS30_UART, TXD_PIN_UART1, RXD_PIN_UART1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    if (err != ESP_OK) 
        return err;
    uart_driver_install(SPS30_UART, RX_BUF_SIZE, 0, 0, NULL, 0);
    if (err != ESP_OK) 
        return err;
    return 0;
}

/**
 * sensirion_uart_close() - release UART resources
 *
 * Return:      0 on success, an error code otherwise
 */
int16_t sensirion_uart_close() {
    int16_t err; /* For error checking */
    err = uart_driver_delete(SPS30_UART);
    if (err != ESP_OK)
        return err;
    return 0;
}

/**
 * sensirion_uart_tx() - transmit data over UART
 *
 * @data_len:   number of bytes to send
 * @data:       data to send
 * Return:      Number of bytes sent or a negative error code
 */
int16_t sensirion_uart_tx(uint16_t data_len, const uint8_t* data) {                    
    return uart_write_bytes(SPS30_UART, (const char*)data, data_len);
}                      

/**
 * sensirion_uart_rx() - receive data over UART              
 *
 * @data_len:   max number of bytes to receive
 * @data:       Memory where received data is stored
 * Return:      Number of bytes received or a negative error code
 */
int16_t sensirion_uart_rx(uint16_t data_len, uint8_t* data) {
    return uart_read_bytes(SPS30_UART, (uint8_t*)data, (uint32_t)data_len, pdMS_TO_TICKS(1000));
}

