/**
 * @file    bh1750.h
 * @brief   Library for bh1750 light sensor.
 * @version 0.1
 * @date    2023-07-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _BH1750_H_
#define _BH1750_H_

#include <stdint.h>
#include <stdbool.h>

#define BH1750_I2CADDR 0x23

// No active state
#define BH1750_POWER_DOWN 0x00

// Waiting for measurement command
#define BH1750_POWER_ON 0x01

// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_RESET 0x07

/**
 * @brief Enum to select the sensor mode.
 * 
 */
typedef enum
{
    // same as Power Down
    UNCONFIGURED = 0,
    // Measurement at 1 lux resolution. Measurement time is approx 120ms.
    CONTINUOUS_HIGH_RES_MODE = 0x10,
    // Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
    CONTINUOUS_HIGH_RES_MODE_2 = 0x11,
    // Measurement at 4 lux resolution. Measurement time is approx 16ms.
    CONTINUOUS_LOW_RES_MODE = 0x13,
    // Measurement at 1 lux resolution. Measurement time is approx 120ms.
    ONE_TIME_HIGH_RES_MODE = 0x20,
    // Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
    ONE_TIME_HIGH_RES_MODE_2 = 0x21,
    // Measurement at 4 lux resolution. Measurement time is approx 16ms.
    ONE_TIME_LOW_RES_MODE = 0x23
} BH1750_MODE_t;

/*************************************************************/

/**
 * @brief Initializes Sensor.
 * 
 * @param address I2C address of the sensor. Pass BH1750_I2CADDR.
 * @param mode    Selects the sensor mode. Use BH1750_MODE_t enum.
 */
void BH1750_begin(uint8_t address, BH1750_MODE_t mode);

/**
 * @brief Re-configure the sensor after it has already been initialized.
 * 
 * @param mode   Selects the sensor mode. Use BH1750_MODE_t enum.
 * @return true  If mode selection was successful.
 * @return false If incorrect mode was selected.
 */
bool BH1750_configure(BH1750_MODE_t mode);

/**
 * @brief Read the light level.
 * 
 * @return float Light level.
 */
float BH1750_readLightLevel(void);

#endif /* _BH1750_H_ */