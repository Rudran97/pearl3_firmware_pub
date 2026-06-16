/**
 * @file    prv_serial.c
 * @brief   Provides APIs for serial communication.
 * @version 0.1
 * @date    2023-06-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "prv_serial.h"
#include "prv_uart.h"
#include "prv_plic.h"

#ifdef PRV_ASSERT_CHECKS
    #include "prv_assert.h"
#endif /* PRV_ASSERT_CHECKS */

UART_CONFIG_t serConfig;
uint8_t serBuffer[UART_BUFFER_SIZE];

/**
 * @brief API to Initialize Serial Communication. Configures URT1 module to use PB2 as TX and PB3 as RX.
 * (Default Serial Configuration) - No parity bit. The serial buffer size is 128 characters (must be of power 2).
 * Initializes Interrupt7 to receive serial data.
 *
 * @param bd baud rate for the Serial Communication.
 */
void Serial_Initialize(const uint32_t bd)
{
    #ifdef PRV_ASSERT_CHECKS
        /* Ensure that UART_BUFFER_SIZE is a power of 2 */
        prvASSERT((UART_BUFFER_SIZE != 0) && (UART_BUFFER_SIZE & (UART_BUFFER_SIZE - 1)) == 0,
            PRV_ASSERT_SERIAL_BUFFER_NON_ALIGNED);
    #endif /* PRV_ASSERT_CHECKS */

    /* Setting up UART registers */
    serConfig.baud_rate = UART_BAUD_RATE(bd);
    serConfig.enbit9 = false;
    serConfig.parity = UART_PARITY_EVEN;
    serConfig.txpin = TX_PIN;
    serConfig.rxpin = RX_PIN;
    serConfig.buff_cfg.dataBuffer = serBuffer;
    serConfig.buff_cfg.buffMask = UART_BUFFER_SIZE - 1; /* Assuming power of 2, create a mask i.e. all 0xffff... */

    UART_Initialize(URT1, &serConfig);

    PLIC_INTERRUPT_CONFIG_t serInt = {
        .attach_interrupt_module = ATTACH_UART1RX_TO_INTERRUPT,
        .set_priority = INTERRUPT_PRIORITY_MAXIMUM,
    };

    Set_Interrupt7(&serInt);

    URT1_START_RECEIVE();
}

/**
 * @brief *INTERNAL* API to send characters using Serial Interface. This function is called from the printf function to
 * print formatted strings.
 *
 * @param character character to be printed.
 */
void _putchar(char character)
{
    UART_TXBlocking(URT1, character, &serConfig);
}

/**
 * @brief Reading a char from the serial buffer.
 *
 * @param dest                Location to store the char. 
 * @return UART_BUFF_STATUS_t Status of the operation. Refer to enum UART_BUFF_STATUS_t.
 */
UART_BUFF_STATUS_t Serial_read(uint8_t *dest)
{
    return UART_readByte(dest, &serConfig);
}

/**
 * @brief API to check if data is present in the serial buffer. 
 * 
 * @return true  If data is present in the serial buffer.
 * @return false If serial buffer is empty.
 */
bool Serial_isAvailable()
{
	return UART_isAvailable(&serConfig);
}

/**
 * @brief Interrupt Handler to receive data.
 * 
 */
void INT7_handler(void)
{
    UART_RXnonBlocking(URT1, &serConfig);
    URT1_STOP_RECEIVE();
    URT1_START_RECEIVE();
}
