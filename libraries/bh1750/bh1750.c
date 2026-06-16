/**
 * @file    bh1750.c
 * @brief   Library for bh1750 light sensor.
 * @version 0.1
 * @date    2023-07-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "bh1750.h"
#include "prv_i2c.h"

#ifdef PRV_ASSERT_CHECKS
    #include "prv_csr.h"
    #include "prv_assert.h"
#endif /* PRV_ASSERT_CHECKS */

typedef struct
{
    uint8_t address;
    BH1750_MODE_t mode;
} bh1750_config_t;

bh1750_config_t bh1750_config = {0};

/**
 * @brief Initializes Sensor.
 * 
 * @param address I2C address of the sensor. Pass BH1750_I2CADDR.
 * @param mode    Selects the sensor mode. Use BH1750_MODE_t enum.
 */
void BH1750_begin(uint8_t address, BH1750_MODE_t mode)
{
    bh1750_config.address = address;

    #ifdef PRV_ASSERT_CHECKS
        /* Ensure Interrupts are enabled before using the i2c communication */
        prvASSERT(INTCONbits.GIE && (csr_read_mstatus() & MSTATUS_MIE_BIT_MASK), PRV_ASSERT_NO_INTERRUPT);
    #endif /* PRV_ASSERT_CHECKS */

    BH1750_configure(mode);
    
}

/**
 * @brief Re-configure the sensor after it has already been initialized.
 * 
 * @param mode   Selects the sensor mode. Use BH1750_MODE_t enum.
 * @return true  If mode selection was successful.
 * @return false If incorrect mode was selected.
 */
bool BH1750_configure(BH1750_MODE_t mode)
{
    bool status = true;

    switch (mode)
    {

    case CONTINUOUS_HIGH_RES_MODE:
    case CONTINUOUS_HIGH_RES_MODE_2:
    case CONTINUOUS_LOW_RES_MODE:
    case ONE_TIME_HIGH_RES_MODE:
    case ONE_TIME_HIGH_RES_MODE_2:
    case ONE_TIME_LOW_RES_MODE:
        i2c_write1Byte(bh1750_config.address, mode);
        bh1750_config.mode = mode;
        break;

    default:
        // Invalid measurement mode
        bh1750_config.mode = UNCONFIGURED;
        status = false;
        break;
    }

    return status;
}

/**
 * @brief Read the light level.
 * 
 * @return float Light level.
 */
float BH1750_readLightLevel(void)
{
    float conv_factor = 1.2;
    uint8_t data[2];
    float level = 0.0;

    if (bh1750_config.mode != UNCONFIGURED)
    {
        i2c_readNBytes(bh1750_config.address, data, 2);
        level = data[0] << 8 | data[1];
        level = level / conv_factor; // convert to lux
    }

    return level;
}
