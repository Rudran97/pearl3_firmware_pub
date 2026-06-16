/**
 * @file    prv_serial.h
 * @brief   Provides APIs for serial communication.
 * @version 0.1
 * @date    2023-06-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _PRV_SERIAL_H_
#define _PRV_SERIAL_H_

#include <stdint.h>
#include <stdbool.h>
#include "prv_uart.h"
#include "../common/printf.h"

#define TX_PIN 2
#define RX_PIN 3

#define UART_BUFFER_SIZE 128

/**
 * @brief API to Initialize Serial Communication. Configures URT1 module to use PB2 as TX and PB3 as RX.
 * (Default Serial Configuration) - No parity bit. The serial buffer size is 128 characters (must be of power 2).
 *
 * @param bd baud rate for the Serial Communication.
 */
void Serial_Initialize(const uint32_t bd);

/**
 * @brief Reading a char from the serial buffer.
 *
 * @param dest                Location to store the char. 
 * @return UART_BUFF_STATUS_t Status of the operation. Refer to enum UART_BUFF_STATUS_t.
 */
UART_BUFF_STATUS_t Serial_read(uint8_t *dest);

/**
 * @brief API to check if data is present in the serial buffer. 
 * 
 * @return true  If data is present in the serial buffer.
 * @return false If serial buffer is empty.
 */
bool Serial_isAvailable();

#endif /* _PRV_SERIAL_H_ */
