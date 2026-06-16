/**
 * @file      prv_device.h
 * @brief     Defines device names and other constants
 * @version   0.1
 * @date      2025-12-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef _PRV_DEVICE_H_
#define _PRV_DEVICE_H_

/* Family definitions */
#define PRV32 (32)
#define PRVX3 (03)

#if   defined(PRV32IMX1515)
#define PRV_FAMILY       PRV32
#define PRV_FLASH        (32768UL)
#define PRV_SRAM         (32768UL)
#define PRV_ADDR_BITS    (16)
#elif defined(PRVX3IMC48SH)
#define PRV_FAMILY       PRVX3
#define PRV_FLASH        (49152UL)
#define PRV_SRAM         (16384UL)
#define PRV_ADDR_BITS    (32)
#else
#error "prv_device.h: Unsupported device"
#endif

#endif /* _PRV_DEVICE_H_ */