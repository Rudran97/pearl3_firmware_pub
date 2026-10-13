// --------------------------------------------------------------------------
// ST7735-library (hw-specific defines and interfaces)
//
// If you want to port the library to a different platform, change this
// include (pins and ports, includes, function-map at the end of the file).
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-st7735
// --------------------------------------------------------------------------

#ifndef _HW_H
#define _HW_H

// ----------------------------------------------------------------
// necessary includes

#include <stdlib.h>
#include "prv_spi_host.h"
#include "prv_timer0.h"
#include "prv_pin.h"

// ----------------------------------------------------------------
// pin and ports (usually defined in the makefile)

// chip-select output pin
#ifndef PIN_TFT_CS
#define PIN_TFT_CS PORTB_PIN_B11_SPI_nCS0
#endif

// TFT_DC output pin
#ifndef PIN_TFT_DC
#define PIN_TFT_DC PORTB_PIN_B12
#endif

// TFT_RST output pin
#ifndef PIN_TFT_RST
#define PIN_TFT_RST PORTB_PIN_B13
#endif

// SPI_SCLK pin
#ifndef PIN_SPI_SCLK
#define PIN_SPI_SCLK PORTB_PIN_B10_SPI_CLK
#endif

// SPI_SDO pin
#ifndef PIN_SPI_SDO
#define PIN_SPI_SDO PORTB_PIN_B9_SPI_MO
#endif

// SPI_SDI pin
#ifndef PIN_SPI_SDI
#define PIN_SPI_SDI PORTB_PIN_B8_SPI_MI
#endif

// ----------------------------------------------------------------

// ----------------------------------------------------------------
// function-map

#define __delay_ms(x)              delayms(x)

extern SPI_CONFIG_t tft_spi_config;
#define spiwrite(data) SPI_write1Byte(data, &tft_spi_config)

#define tft_cs_low() LATB &= ~(1 << PIN_TFT_CS)
#define tft_cs_high() LATB |= (1 << PIN_TFT_CS)

#define tft_dc_low() LATB &= ~(1 << PIN_TFT_DC)
#define tft_dc_high() LATB |= (1 << PIN_TFT_DC)

#define tft_rst_low() LATB &= ~(1 << PIN_TFT_RST)
#define tft_rst_high() LATB |= (1 << PIN_TFT_RST)
// ----------------------------------------------------------------

#endif
