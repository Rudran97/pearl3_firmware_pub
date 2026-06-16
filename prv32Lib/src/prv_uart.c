/**
 * @file    prv_uart.c
 * @brief   APIs for UART modules.
 * @version 0.1
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "prv_uart.h"

/*************************************************************/
/* Function prototypes */

static uint8_t UART_GetParity(uint8_t number);

/*************************************************************/

static uint8_t UART_GetParity(uint8_t number)
{
    uint8_t n = number ^ (number >> 1);
    n ^= (n >> 2);
    n ^= (n >> 4);

    if (n & 1)
        return 1;
    return 0;
}

/**
 * @brief API to Initialize Uart Module.
 * 
 * @param module Constant pointer to UART modules to access hardwre registers. Pass URT0 or URT1 as module parameter.
 * @param config Uart Configurations. Use UART_CONFIG_t structure to set the required configurations.
 */
void UART_Initialize(URT_REG_t *const module, UART_CONFIG_t *config)
{
	UART_bufferFlush(config);
	module->URTBRG = config->baud_rate;
    module->URTCON = (config->enbit9 << _URTCON_ENBIT9_POSN)
                     | (_URTCON_RXPIN_MASK & (config->rxpin << _URTCON_RXPIN_POSN))
                     | (_URTCON_TXPIN_MASK & (config->txpin << _URTCON_TXPIN_POSN));
    
    GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_UART1, config->txpin);

    GPIO_CONFIG_t RxPin = {
        .gpio_mode = GPIO_MODE_INPUT_TRISTATE,
    };

    GPIO_Init(GPIO_PORTB, config->rxpin, &RxPin);
}

/**
 * @brief API to Read data from Uart rx buffer. returns status of the read.
 * 
 * @param dest                Pointer to the location to copy the data from the rx buffer.
 * @param config              Uart Configurations. Use UART_CONFIG_t structure to set the required configurations.
 * @return UART_BUFF_STATUS_t Status of the operation. Refer to enum UART_BUFF_STATUS_t.
 */
UART_BUFF_STATUS_t UART_readByte(uint8_t *dest, UART_CONFIG_t *config)
{
	return pop_buffer(&config->buff_cfg, dest);
}

/**
 * @brief API to check the if data is available in the rx buffer.
 * 
 * @param config Uart Configurations. Use UART_CONFIG_t structure to set the required configurations.
 * @return true  If data is present in rx buffer.
 * @return false If rx buffer is empty.
 */
bool UART_isAvailable(UART_CONFIG_t *config)
{
    return (config->buff_cfg.buffHead != config->buff_cfg.buffTail);
}

/**
 * @brief API to clear rx buffer - resets the buffer index to 0 and buffer status.
 * 
 * @param config Uart Configurations. Use UART_CONFIG_t structure to set the required configurations.
 */
void UART_bufferFlush(UART_CONFIG_t *config)
{
	config->buff_cfg.buffHead = 0;
	config->buff_cfg.buffTail = 0;
	config->error = UART_STATUS_NOERR;
}

/********************************************************************************************************************************/
/* Buffer Implementation */

/**
 * @brief API to push a Byte into the Uart circular buffer.
 *
 * @param buff_cfg            Pointer to buffer configuration structure. Use BUFF_CONFIG_t structure to set the required configurations.
 * @param data                Byte to be pushed into the buffer.
 * @return UART_BUFF_STATUS_t Status of the buffer after the operation. Refer to enum UART_BUFF_STATUS_t.
 */
UART_BUFF_STATUS_t push_buffer(BUFF_CONFIG_t *buff_cfg, uint8_t data)
{
    uint32_t buffNext = (buff_cfg->buffHead + 1) & buff_cfg->buffMask;

    if (buffNext == buff_cfg->buffTail)
    {
        return UART_BUFF_STATUS_BUFFER_FULL;
    }

	buff_cfg->dataBuffer[buff_cfg->buffHead] = data;
	buff_cfg->buffHead = buffNext;

	return UART_BUFF_STATUS_NOERR;
}

/**
 * @brief API to pop a Byte from the Uart circular buffer.
 *
 * @param buff_cfg            Pointer to buffer configuration structure. Use BUFF_CONFIG_t structure to set the required configurations.
 * @param data                Pointer to the location where the Byte would be stored after the pop operation.
 * @return UART_BUFF_STATUS_t Status of the buffer after the operation. Refer to enum UART_BUFF_STATUS_t.
 */
UART_BUFF_STATUS_t pop_buffer(BUFF_CONFIG_t *buff_cfg, uint8_t *data)
{
    if (buff_cfg->buffHead == buff_cfg->buffTail)
    {
        return UART_BUFF_STATUS_BUFFER_EMPTY;
    }

	*data = buff_cfg->dataBuffer[buff_cfg->buffTail];
    buff_cfg->buffTail = (buff_cfg->buffTail + 1) & buff_cfg->buffMask;

	return UART_BUFF_STATUS_NOERR;
}

/********************************************************************************************************************************/
/* Hardware Interface */

/**
 * @brief API to Transmit UART data - blocking, polls TXIF flag.
 * 
 * @param module Constant pointer to UART modules to access hardwre registers. Pass URT0 or URT1 as module parameter.
 * @param data   Character to send.
 * @param config Uart Configurations. Use UART_CONFIG_t structure to set the required configurations.
 */
void UART_TXBlocking(URT_REG_t *const module, uint8_t data, const UART_CONFIG_t *const config)
{
    uint8_t data_parity = UART_GetParity(data) ^ config->parity;
    module->TX = ( uint32_t ) (data_parity << _URTTX_TXBIT9_POSN) | (data & _URTTX_TXDATA_MASK);
    module->URTCON |= _URTCON_TXEN_MASK;
    while(!(module->URTCON & _URTCON_TXIF_MASK));
    module->URTCON &= ~_URTCON_TXEN_MASK;
}

/**
 * @brief API to Receive UART data - non blocking. This API must be called inside an Interrupt Handler.
 *        The data received is stored in the data buffer pointed by rx_dataBuffer.
 * 
 * @param module Constant pointer to UART modules to access hardwre registers. Pass URT0 or URT1 as module parameter.
 * @param config Uart Configurations. Use UART_CONFIG_t structure to set the required configurations.
 */
void UART_RXnonBlocking(URT_REG_t *const module, UART_CONFIG_t *config)
{
    UART_STATUS_t status = UART_STATUS_NOERR;
    uint32_t rx_reg = module->RX;

    uint8_t rx_data = rx_reg & _URTRX_RXDATA_MASK;
    uint8_t rec_parity = (rx_reg >> _URTRX_RXBIT9_POSN) & (_URTRX_RXBIT9_MASK >> _URTRX_RXBIT9_POSN);
    
    // Push the received data in buffer
    if (push_buffer(&config->buff_cfg, rx_data) == UART_BUFF_STATUS_BUFFER_FULL)
    {
        status = UART_STATUS_BUFFER_FULL;
    }

    // Check Parity if enabled
    if (config->enbit9)
    {
        uint8_t calulated_parity = UART_GetParity(rx_data) ^ config->parity;
        if ((calulated_parity) != rec_parity)
            status = UART_STATUS_PARITY_ERR;
    }

    config->error = status;
}
