/**
 * @file    prv_i2c_master.h
 * @brief   I2C Master Interface. Low level.
 *          Note - The Low level I2C interface uses interrupts to control the I2C_MasterFSN(void) function.
 *          An example of the ISR handler is provided below. Attach it to the appropriate interrupt.
 * 
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_I2C_MASTER_H_
#define _PRV_I2C_MASTER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define I2C_FREQ(_freq) ((((SYSCLK / IOCLKDIV) / (_freq * 3))) - 1);

/**
 * @brief ISR Handler example.
 * 
 */
/* 
void INT0_handler(void)
{
    if (I2C0CON0bits.I2CIF)
    {
        I2C0_MasterFSM();
    }
    else
    {
        I2C0CON0 = 0;
    }
} */

// I2C Errors
typedef enum
{
    I2C0_STATUS_NOERR = 0,
    I2C0_STATUS_BUSY,
    I2C0_STATUS_FAIL
} i2c0_status_t;

/**
 * @brief I2C0 Control FSM.
 * 
 */
void I2C0_MasterFSM(void);

/* I2C Interface Functions */

/**
 * @brief Initializes I2C0 module.
 * 
 * @param bd      I2C transmission frequency. Use the I2C_FREQ(_freq) Macro to get the actual bd.
 * @param sda_pin SDA pin number.
 * @param scl_pin SCL pin number.
 */
void I2C0_Initialize(const uint32_t bd, const uint8_t sda_pin, const uint8_t scl_pin);

i2c0_status_t I2C0_Open(uint8_t address);
i2c0_status_t I2C0_Close(void);
i2c0_status_t I2C0_Operation(bool read);
i2c0_status_t I2C0_MasterRead(void);
i2c0_status_t I2C0_MasterWrite(void);
void I2C0_SetDataBuffer(void *buffer, size_t bufferSize);
bool I2C0_MasterIsBusy(void);

#endif /* _PRV_I2C_MASTER_H_ */