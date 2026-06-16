/**
 * @file    prv_i2c_master.c
 * @brief   I2C Master Interface functions. Low level.
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "prv32.h"
#include "prv_gpio.h"
#include "prv_i2c_master.h"

// I2C FSM
typedef enum
{
    I2C0_STATE_IDLE = 0,
    I2C0_STATE_WRITE_ADDR,
    I2C0_STATE_READ_ADDR,
    I2C0_STATE_TX,
    I2C0_STATE_RX,
    I2C0_STATE_START_RXEN,
    I2C0_STATE_RESTART_READ,
    I2C0_STATE_RESTART_WRITE,
    I2C0_STATE_STOP,
    I2C0_STATE_ADDR_NACK
} i2c0_state_t;

typedef struct
{
    uint8_t address;
    uint8_t *data_prt;
    size_t data_length;
    uint8_t i2c_time_out;
    i2c0_state_t state;
    i2c0_status_t error;
    uint8_t addrNackCheck : 1;
    uint8_t busy : 1;
    uint8_t inuse : 1;
    uint8_t bufferFree : 1;
} i2c0_directory_t;

i2c0_directory_t I2C0_Directory = {0};

/* I2C Internal control functions */
static inline void I2C0_INTERNAL_ClearInterrupts(void);
static inline bool I2C0_INTERNAL_MasterIsNack(void);
static inline void I2C0_INTERNAL_MasterTxData(uint8_t data);
static inline void I2C0_INTERNAL_MasterRestartEnable(void);

/* I2C State Functions */
static i2c0_state_t i2c0_function_idle(void);
static i2c0_state_t i2c0_function_write_addr(void);
static i2c0_state_t i2c0_function_read_addr(void);
static i2c0_state_t i2c0_function_tx(void);
static i2c0_state_t i2c0_function_rx(void);
static i2c0_state_t i2c0_function_start_rx(void);
static i2c0_state_t i2c0_function_restart_read(void);
static i2c0_state_t i2c0_function_restart_write(void);
static i2c0_state_t i2c0_function_stop(void);
static i2c0_state_t i2c0_function_addr_nack(void);

typedef i2c0_state_t (*stateHandler)(void);
const stateHandler i2c_states[] = {
    i2c0_function_idle,
    i2c0_function_write_addr,
    i2c0_function_read_addr,
    i2c0_function_tx,
    i2c0_function_rx,
    i2c0_function_start_rx,
    i2c0_function_restart_read,
    i2c0_function_restart_write,
    i2c0_function_stop,
    i2c0_function_addr_nack};

/*************************************************************/

/* I2C User Interface functions */

/**
 * @brief Initializes I2C0 module.
 * 
 * @param bd      I2C transmission frequency. Use the I2C_FREQ(_freq) Macro to get the actual bd.
 * @param sda_pin SDA pin number.
 * @param scl_pin SCL pin number.
 */
void I2C0_Initialize(const uint32_t bd, const uint8_t sda_pin, const uint8_t scl_pin)
{
    /* I2C Timeout timer is set between 15 to 16 ms */
    I2C0CON1 = (I2C_TOT << _I2C0CON1_TOT_POSN) | (_I2C0CON1_BRG_MASK & bd); // configure tot and baud rate

    /* I2C Setup and Hold timer is set between 0.6 to 0.8 us */
    I2C0CON2 = (I2C_SHTM << _I2C0CON2_SHTM_POSN) | (_I2C0CON2_SCLPIN_MASK & (scl_pin << _I2C0CON2_SCLPIN_POSN)) | (_I2C0CON2_SDAPIN_MASK & (sda_pin << _I2C0CON2_SDAPIN_POSN));

    /* Configuring Pins to I2C */
    GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_I2C0, scl_pin);
    GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_I2C0, sda_pin);
    
    I2C0_Directory.inuse = false;
}

i2c0_status_t I2C0_Open(uint8_t address)
{
    i2c0_status_t retVal = I2C0_STATUS_BUSY;

    if (!I2C0_Directory.inuse)
    {
        I2C0_Directory.address = address;
        I2C0_Directory.busy = false;
        I2C0_Directory.inuse = true;
        I2C0_Directory.addrNackCheck = 0;
        I2C0_Directory.state = I2C0_STATE_IDLE;
        I2C0_Directory.i2c_time_out = 24;
        I2C0_Directory.bufferFree = true;

        I2C0_INTERNAL_ClearInterrupts();
        I2C0CON0bits.I2CEN = 1;

        retVal = I2C0_STATUS_NOERR;
    }
    return retVal;
}

i2c0_status_t I2C0_Close(void)
{
    i2c0_status_t retVal = I2C0_STATUS_BUSY;
    if (!I2C0_Directory.busy)
    {
        I2C0_Directory.inuse = false;
        I2C0_INTERNAL_ClearInterrupts();
        I2C0CON0 = 0;
        retVal = I2C0_Directory.error;
    }
    return retVal;
}

i2c0_status_t I2C0_Operation(bool read)
{
    i2c0_status_t retVal = I2C0_STATUS_BUSY;
    if (!I2C0_Directory.busy)
    {
        I2C0_Directory.busy = true;
        retVal = I2C0_STATUS_NOERR;

        if (read)
        {
            I2C0_Directory.state = I2C0_STATE_READ_ADDR;
        }
        else
        {
            I2C0_Directory.state = I2C0_STATE_WRITE_ADDR;
        }
        I2C0CON0bits.SEN = 1;
    }
    return retVal;
}

i2c0_status_t I2C0_MasterRead(void)
{
    return I2C0_Operation(true);
}

i2c0_status_t I2C0_MasterWrite(void)
{
    return I2C0_Operation(false);
}

void I2C0_SetDataBuffer(void *buffer, size_t bufferSize)
{
    if (I2C0_Directory.bufferFree)
    {
        I2C0_Directory.data_prt = buffer;
        I2C0_Directory.data_length = bufferSize;
        I2C0_Directory.bufferFree = false;
    }
}

bool I2C0_MasterIsBusy(void)
{
    return I2C0_Directory.busy;
}

/*************************************************************/

/* I2C Master FSM */

void I2C0_MasterFSM(void)
{
    I2C0_INTERNAL_ClearInterrupts();

    if (I2C0_Directory.addrNackCheck && I2C0_INTERNAL_MasterIsNack())
    {
        I2C0_Directory.state = I2C0_STATE_ADDR_NACK;
    }
    I2C0_Directory.state = i2c_states[I2C0_Directory.state]();
}

/*************************************************************/

/* State functions */

static i2c0_state_t i2c0_function_idle(void)
{
    I2C0_Directory.busy = false;
    I2C0_Directory.error = I2C0_STATUS_NOERR;
    return I2C0_STATE_IDLE;
}

static i2c0_state_t i2c0_function_write_addr(void)
{
    I2C0_Directory.addrNackCheck = 1;
    I2C0_INTERNAL_MasterTxData(I2C0_Directory.address << 1);
    return I2C0_STATE_TX;
}

static i2c0_state_t i2c0_function_read_addr(void)
{
    I2C0_Directory.addrNackCheck = 1;
    I2C0_INTERNAL_MasterTxData(I2C0_Directory.address << 1 | 1);
    return I2C0_STATE_START_RXEN;
}

static i2c0_state_t i2c0_function_tx(void)
{
    if (I2C0_INTERNAL_MasterIsNack())
    {
        return i2c0_function_stop();
    }
    else
    {
        I2C0_Directory.addrNackCheck = 0;
        I2C0_INTERNAL_MasterTxData(*I2C0_Directory.data_prt++);
        return (--I2C0_Directory.data_length) ? I2C0_STATE_TX : I2C0_STATE_STOP;
    }
}

static i2c0_state_t i2c0_function_rx(void)
{
    *I2C0_Directory.data_prt++ = (uint8_t)I2C0RX;
    if (--I2C0_Directory.data_length)
    {
        I2C0CON0bits.ACKDAT = 0;
        I2C0CON0bits.ACKEN = 1;
        return I2C0_STATE_START_RXEN;
    }
    else
    {
        I2C0_Directory.bufferFree = true;
        I2C0CON0bits.ACKDAT = 1;
        I2C0CON0bits.ACKEN = 1;
        return I2C0_STATE_STOP;
    }
}

static i2c0_state_t i2c0_function_start_rx(void)
{
    I2C0_Directory.addrNackCheck = 0;
    I2C0CON0bits.RXEN = 1;
    return I2C0_STATE_RX;
}

static i2c0_state_t i2c0_function_restart_read(void)
{
    I2C0_INTERNAL_MasterRestartEnable();
    return I2C0_STATE_READ_ADDR;
}

static i2c0_state_t i2c0_function_restart_write(void)
{
    I2C0_INTERNAL_MasterRestartEnable();
    return I2C0_STATE_WRITE_ADDR;
}

static i2c0_state_t i2c0_function_addr_nack(void)
{
    I2C0_Directory.addrNackCheck = 0;
    I2C0_Directory.error = I2C0_STATUS_FAIL;
    return i2c0_function_stop();
}

static i2c0_state_t i2c0_function_stop(void)
{
    I2C0_Directory.bufferFree = true;
    I2C0CON0bits.PEN = 1;
    return I2C0_STATE_IDLE;
}

/*************************************************************/

/* Internal Control-Status signals and Registers */

static inline bool I2C0_INTERNAL_MasterIsNack(void)
{
    return I2C0CON0bits.ACKSTAT;
}

static inline void I2C0_INTERNAL_ClearInterrupts(void)
{
    I2C0CON0bits.CLRF = 1;
}

static inline void I2C0_INTERNAL_MasterTxData(uint8_t data)
{
    I2C0TX = ( uint32_t )data;
    I2C0CON0bits.TXEN = 1;
}

static inline void I2C0_INTERNAL_MasterRestartEnable(void)
{
    I2C0CON0bits.RSEN = 1;
}