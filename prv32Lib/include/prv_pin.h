/**
 * @file    prv_pin.h
 * @brief   Defines default pin assignments.
 * @version 0.1
 * @date    2026-10-12
 *
 */

#ifndef _PRV_PIN_H_
#define _PRV_PIN_H_

#include "prv_hwreg.h"

/*************************************************************/
/* PORTA default pin assignments */

typedef enum {
    /* General assignments */
    PORTA_PIN_A0            = _LATA_LA0_POSN,
    PORTA_PIN_A1            = _LATA_LA1_POSN,
    PORTA_PIN_A2            = _LATA_LA2_POSN,
    PORTA_PIN_A3            = _LATA_LA3_POSN,
    PORTA_PIN_A4            = _LATA_LA4_POSN,
    PORTA_PIN_A5            = _LATA_LA5_POSN,
    PORTA_PIN_A6            = _LATA_LA6_POSN,
    PORTA_PIN_A7            = _LATA_LA7_POSN,
    PORTA_PIN_A8            = _LATA_LA8_POSN,
    PORTA_PIN_A9            = _LATA_LA9_POSN,
    PORTA_PIN_A10           = _LATA_LA10_POSN,
    PORTA_PIN_A11           = _LATA_LA11_POSN,
    PORTA_PIN_A12           = _LATA_LA12_POSN,
    PORTA_PIN_A13           = _LATA_LA13_POSN,
    PORTA_PIN_A14           = _LATA_LA14_POSN,
    PORTA_PIN_A15           = _LATA_LA15_POSN,
    /* Special assignments */
    PORTA_PIN_A0_PWM0       = _LATA_LA0_POSN,
    PORTA_PIN_A1_PWM1       = _LATA_LA1_POSN,
    PORTA_PIN_A2_PWM2       = _LATA_LA2_POSN,
    PORTA_PIN_A6_I2C0_SCL   = _LATA_LA6_POSN,
    PORTA_PIN_A7_I2C0_SDA   = _LATA_LA7_POSN,
    PORTA_PIN_A8_UART0_TX   = _LATA_LA8_POSN,
    PORTA_PIN_A9_UART0_RX   = _LATA_LA9_POSN,
    PORTA_PIN_A10_EINT0     = _LATA_LA10_POSN,
    PORTA_PIN_A10_EXT0_TRIG = PORTA_PIN_A10_EINT0,
    PORTA_PIN_A11_EINT1     = _LATA_LA11_POSN,
    PORTA_PIN_A11_EXT1_TRIG = PORTA_PIN_A11_EINT1,
} PORTA_PIN_t;

typedef enum {
    /* General assignments */
    PORTB_PIN_B0               = _LATB_LB0_POSN,
    PORTB_PIN_B1               = _LATB_LB1_POSN,
    PORTB_PIN_B2               = _LATB_LB2_POSN,
    PORTB_PIN_B3               = _LATB_LB3_POSN,
    PORTB_PIN_B4               = _LATB_LB4_POSN,
    PORTB_PIN_B5               = _LATB_LB5_POSN,
    PORTB_PIN_B6               = _LATB_LB6_POSN,
    PORTB_PIN_B7               = _LATB_LB7_POSN,
    PORTB_PIN_B8               = _LATB_LB8_POSN,
    PORTB_PIN_B9               = _LATB_LB9_POSN,
    PORTB_PIN_B10              = _LATB_LB10_POSN,
    PORTB_PIN_B11              = _LATB_LB11_POSN,
    PORTB_PIN_B12              = _LATB_LB12_POSN,
    PORTB_PIN_B13              = _LATB_LB13_POSN,
    PORTB_PIN_B14              = _LATB_LB14_POSN,
    PORTB_PIN_B15              = _LATB_LB15_POSN,
    /* Special assignments */
    PORTB_PIN_B0_PWM3          = _LATB_LB0_POSN,
    PORTB_PIN_B0_ICT0_CAP0     = _LATB_LB0_POSN & 0x3,
    PORTB_PIN_B1_PWM4          = _LATB_LB1_POSN,
    PORTB_PIN_B1_ICT0_CAP1     = _LATB_LB1_POSN & 0x3,
    PORTB_PIN_B2_UART1_TX      = _LATB_LB2_POSN,
    PORTB_PIN_B2_SERIAL_MON_TX = _LATB_LB2_POSN,
    PORTB_PIN_B2_ICT0_CAP2     = _LATB_LB2_POSN & 0x3,
    PORTB_PIN_B3_UART1_RX      = _LATB_LB3_POSN,
    PORTB_PIN_B3_SERIAL_MON_RX = _LATB_LB3_POSN,
    PORTB_PIN_B3_ICT0_CAP3     = _LATB_LB3_POSN & 0x3,
    PORTB_PIN_B4_PWM5          = _LATB_LB4_POSN,
    PORTB_PIN_B4_ICT1_CAP0     = _LATB_LB4_POSN & 0x3,
    PORTB_PIN_B5_ICT1_CAP1     = _LATB_LB5_POSN & 0x3,
    PORTB_PIN_B6_ICT1_CAP2     = _LATB_LB6_POSN & 0x3,
    PORTB_PIN_B7_ICT1_CAP3     = _LATB_LB7_POSN & 0x3,
    PORTB_PIN_B8_SPI_MI        = _LATB_LB8_POSN,
    PORTB_PIN_B9_SPI_MO        = _LATB_LB9_POSN,
    PORTB_PIN_B10_SPI_CLK      = _LATB_LB10_POSN,
    PORTB_PIN_B11_SPI_nCS0     = _LATB_LB11_POSN,
    PORTB_PIN_B12_SPI_nCS1     = _LATB_LB12_POSN,
    PORTB_PIN_B12_EINT2        = _LATB_LB12_POSN,
    PORTB_PIN_B12_EXT2_TRIG    = PORTB_PIN_B12_EINT2,
    PORTB_PIN_B13_SPI_nCS2     = _LATB_LB13_POSN,
    PORTB_PIN_B13_EINT3        = _LATB_LB13_POSN,
    PORTB_PIN_B13_EXT3_TRIG    = PORTB_PIN_B13_EINT3,
    PORTB_PIN_B14_SPI_nCS3     = _LATB_LB14_POSN,
} PORTB_PIN_t;

#endif /* _PRV_PIN_H_ */
