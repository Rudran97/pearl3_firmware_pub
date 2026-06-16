/**
 * @file    prv32.h
 * @brief   Defines useful macros.
 * @version 0.1
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV32_H_
#define _PRV32_H_

#include "prv_device.h"
#include "prv_hwreg.h"

#if PRV_FAMILY == PRV32
#define SYSCLK 120000000
#define IOCLKDIV 5
#define DELAY1us_const 4
#define I2C_TOT 24
#define I2C_SHTM 1
#define TIMERms_const 23999
#elif PRV_FAMILY == PRVX3
#define SYSCLK 64000000
#define IOCLKDIV 1
#define DELAY1us_const 11
#define I2C_TOT 63
#define I2C_SHTM 3
#define TIMERms_const 63999
#else
#error "prv32.h: Unsupported device"
#endif

#define _I_ volatile
#define _O_ volatile
#define _IO_ volatile

#define HIGH 1
#define LOW  0

#define DELAY1us()                              \
    for (volatile uint8_t _dlus = DELAY1us_const; _dlus > 0; --_dlus) \
    {                                           \
    }; // The delay1us macro provides a delay of 1us approx.

#endif /* _PRV32_H_ */