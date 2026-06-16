/**
 * @file    prv_spi_host.c
 * @brief   SPI Host Interface
 * @version 0.1
 * @date    2023-07-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "prv_spi_host.h"

/*************************************************************/
/* Function prototypes */

static void SPI_SendData(SPI_CONFIG_t *config);
static void SPI_ReceiveData(SPI_CONFIG_t *config);
static void SPI_SetDataBuffer(void *buffer1, void *buffer2, size_t bufferSize, SPI_CONFIG_t *config);
static void SPI_FullDuplexMode(SPI_CONFIG_t *config);

/*************************************************************/

/**
 * @brief API to Initialize SPI SPI0.
 * 
 * @param config Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
void SPI_Initialize(const SPI_CONFIG_t *const config)
{
    SPI0CON0 = (_SPI0CON0_SPIMODE_MASK & (config->mode << _SPI0CON0_SPIMODE_POSN))
               | (_SPI0CON0_BRG_MASK & (config->baud_rate << _SPI0CON0_BRG_POSN));
    SPI0CON1 = (_SPI0CON1_SCLKPIN_MASK & (config->sclkPin << _SPI0CON1_SCLKPIN_POSN))
               | (_SPI0CON1_SDOPIN_MASK & (config->sdoPin << _SPI0CON1_SDOPIN_POSN))
               | (_SPI0CON1_SDIPIN_MASK & (config->sdiPin << _SPI0CON1_SDIPIN_POSN))
               | (_SPI0CON1_SSPIN_MASK & (config->ssPin << _SPI0CON1_SSPIN_POSN));
    
    GPIO_CONFIG_t SdiPin = {
        .gpio_mode = GPIO_MODE_INPUT_TRISTATE,
    };

    GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_SPI0, config->sclkPin);
    GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_SPI0, config->sdoPin);
    GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_SPI0, config->ssPin);

    GPIO_Init(GPIO_PORTB, config->sdiPin, &SdiPin);
}

/**
 * @brief API to send 1 byte.
 * 
 * @param config Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 * @param data   data to send.
 */
void SPI_write1Byte(uint8_t data, SPI_CONFIG_t *config)
{
    SPI_SetDataBuffer(&data, &data, 1, config);
    SPI_SendData(config);
}

/**
 * @brief API to send N bytes.
 * 
 * @param data     Void pointer to the data that must be sent
 * @param data_len Number of bytes to send
 * @param config   Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
void SPI_writeNBytes(void* data, size_t data_len, SPI_CONFIG_t *config)
{
    SPI_SetDataBuffer(data, data, data_len, config);
    SPI_SendData(config);
}

/**
 * @brief API to read 1 byte of data from the device.
 * 
 * @param config   Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 * @return uint8_t Read value from device.
 */
uint8_t SPI_read1Byte(SPI_CONFIG_t *config)
{
    uint8_t rx_data;

    SPI_SetDataBuffer(&rx_data, &rx_data, 1, config);
    SPI_ReceiveData(config);

    return rx_data;
}

/**
 * @brief API to read N bytes of data from the device.
 * 
 * @param data     Void pointer to the buffer to store the incoming data.
 * @param data_len Number of bytes to read from device.
 * @param config   Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
void SPI_readNBytes(void* data, size_t data_len, SPI_CONFIG_t *config)
{
    SPI_SetDataBuffer(data, data, data_len, config);
    SPI_ReceiveData(config);
}

/**
 * @brief API to simultaneously send and receive data.
 * 
 * @param tx_data  Void pointer to tx data buffer
 * @param rx_data  Void pointer to rx data buffer
 * @param data_len Number of bytes to transmit/receive
 * @param config   Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
void SPI_transmitReceiveNBytes(void* tx_data, void* rx_data, size_t data_len, SPI_CONFIG_t *config)
{
    SPI_SetDataBuffer(tx_data, rx_data, data_len, config);
    SPI_FullDuplexMode(config);
}

/*************************************************************/
/* Internal functions */

/**
 * @brief API to Transmit SPI data - blocking, polls SPIIF flag.
 * 
 * @param data   Character to send.
 */
static void SPI_SendData(SPI_CONFIG_t *config)
{
    do
    {
        SPI0->TX = ( uint32_t )*config->data_ptr1++;
        SPI0->SPICON0 |= _SPI0CON0_SPIEN_MASK;
        while(!(SPI0->SPICON0 & _SPI0CON0_SPIIF_MASK));
        SPI0->SPICON0 &= ~_SPI0CON0_SPIEN_MASK;

    } while (--config->data_length);
}

/**
 * @brief API to Receive SPI data - blocking, polls SPIIF flag.
 * 
 * @param config Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
static void SPI_ReceiveData(SPI_CONFIG_t *config)
{
    do
    {
        SPI0->TX = 0; // dummy transmission while receiving
        SPI0->SPICON0 |= _SPI0CON0_SPIEN_MASK;
        while(!(SPI0->SPICON0 & _SPI0CON0_SPIIF_MASK));
        *config->data_ptr1++ = ( uint8_t )SPI0->RX;
        SPI0->SPICON0 &= ~_SPI0CON0_SPIEN_MASK;

    } while (--config->data_length);
}

/**
 * @brief API to handle SPI Full-duplex mode.
 * 
 * @param config Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
static void SPI_FullDuplexMode(SPI_CONFIG_t *config)
{
    do
    {
        SPI0->TX = ( uint32_t )*config->data_ptr1++;
        SPI0->SPICON0 |= _SPI0CON0_SPIEN_MASK;
        while(!(SPI0->SPICON0 & _SPI0CON0_SPIIF_MASK));
        *config->data_ptr2++ = ( uint8_t )SPI0->RX;
        SPI0->SPICON0 &= ~_SPI0CON0_SPIEN_MASK;

    } while (--config->data_length);
}

/**
 * @brief API to set the SPI data buffer and its size.
 * 
 * @param buffer1    Void pointer to the data buffer in half duplex mode - used by both read and write
 * @param buffer2    Void pointer to the data buffer in full duplex mode - used by store the read value
 * @param bufferSize size of the data buffer
 * @param config     Spi Configurations. Use SPI_CONFIG_t structure to set the required configurations.
 */
static void SPI_SetDataBuffer(void *buffer1, void *buffer2, size_t bufferSize, SPI_CONFIG_t *config)
{
    config->data_ptr1 = buffer1;
    config->data_ptr2 = buffer2;
    config->data_length = bufferSize;
}