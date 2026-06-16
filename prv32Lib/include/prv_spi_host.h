/**
 * @file    prv_spi_host.h
 * @brief   Defines SPI Host Interface APIs
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_SPI_HOST_H_
#define _PRV_SPI_HOST_H_

#include "prv_gpio.h"

#define SPI0 ((SPI_REG_t *)_SPI0_)

/* Macro to Start SPI0 communicaiton */
#define SPI0_START_COMM() (SPI0CON0 |= _SPI0CON0_SPIEN_MASK)

/* Macro to Stop SPI0 communication */
#define SPI0_STOP_COMM() (SPI0CON &= ~_SPI0CON0_SPIEN_MASK)

/* Macro to Clear SPI0 transmission complete flag */
#define SPI0_CLEAR_FLAG() (SPI0CON |= _SPI0CON0_CLRF_MASK)

/* Macro to get the correct value for the baud rate */
#define SPI_FREQ(_bdrate) ((((SYSCLK / IOCLKDIV) / (_bdrate * 4))) - 1)

/* Defines different SPI mode options */
typedef enum
{
    SPI_MODE0 = 1,
    SPI_MODE1 = 0,
    SPI_MODE2 = 3,
    SPI_MODE3 = 2
} SPI_MODE_t;

/* Structure defining configuration of SPI Module */
typedef struct
{
    SPI_MODE_t mode;
    uint32_t baud_rate;
    uint8_t sclkPin;
    uint8_t sdoPin;
    uint8_t sdiPin;
    uint8_t ssPin;
    uint8_t *data_ptr1;
    uint8_t *data_ptr2;
    size_t  data_length;
} SPI_CONFIG_t;

/*************************************************************/
/* *** Mapped to Hardware *** */

/* Structure defining SPI Registers - mapped to the hardware */
typedef struct
{
    _IO_ uint32_t SPICON0;
    _IO_ uint32_t SPICON1;
    _IO_ uint32_t TX;
    _IO_ uint32_t RX;
} SPI_REG_t;

/*************************************************************/

/**
 * @brief API to Initialize SPI SPI0.
 * 
 * @param config Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
void SPI_Initialize(const SPI_CONFIG_t *const config);

/**
 * @brief API to send 1 byte.
 * 
 * @param config Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 * @param data   data to send.
 */
void SPI_write1Byte(uint8_t data, SPI_CONFIG_t *config);

/**
 * @brief API to send N bytes.
 * 
 * @param data     Void pointer to the data that must be sent
 * @param data_len Number of bytes to send
 * @param config   Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
void SPI_writeNBytes(void* data, size_t data_len, SPI_CONFIG_t *config);

/**
 * @brief API to read 1 byte of data from the device.
 * 
 * @param config   Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 * @return uint8_t Read value from device.
 */
uint8_t SPI_read1Byte(SPI_CONFIG_t *config);

/**
 * @brief API to read N bytes of data from the device.
 * 
 * @param data     Void pointer to the buffer to store the incoming data.
 * @param data_len Number of bytes to read from device.
 * @param config   Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
void SPI_readNBytes(void* data, size_t data_len, SPI_CONFIG_t *config);

/**
 * @brief API to simultaneously send and receive data.
 * 
 * @param tx_data  Void pointer to tx data buffer
 * @param rx_data  Void pointer to rx data buffer
 * @param data_len Number of bytes to transmit/receive
 * @param config   Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
void SPI_transmitReceiveNBytes(void* tx_data, void* rx_data, size_t data_len, SPI_CONFIG_t *config);

#endif /* _PRV_SPI_HOST_H_*/