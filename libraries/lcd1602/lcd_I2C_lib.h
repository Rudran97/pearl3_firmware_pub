/**
 * @file    lcd_I2C_lib.h
 * @brief 
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LCD_I2C_LIB_H
#define LCD_I2C_LIB_H

#include <stdarg.h>
#include <stddef.h>

// LCD Commands
#define LCD_CMD_CLEARDISPLAY 0x01
#define LCD_CMD_RETURNHOME 0x02
#define LCD_CMD_ENTRYMODESET 0x04
#define LCD_CMD_DISPLAYCONTROL 0x08
#define LCD_CMD_CURSORSHIFT 0x10
#define LCD_CMD_FUNCTIONSET 0x20
#define LCD_CMD_SETCGRAMADDR 0x40
#define LCD_CMD_SETDDRAMADDR 0x80

// Display entry mode
#define LCD_MODE_ENTRYRIGHT 0x00
#define LCD_MODE_ENTRYLEFT 0x02
#define LCD_MODE_ENTRYSHIFTINCREMENT 0x01
#define LCD_MODE_ENTRYSHIFTDECREMENT 0x00

// Display on/off control
#define LCD_CTRL_DISPLAYON 0x04
#define LCD_CTRL_DISPLAYOFF 0x00
#define LCD_CTRL_CURSORON 0x02
#define LCD_CTRL_CURSOROFF 0x00
#define LCD_CTRL_BLINKON 0x01
#define LCD_CTRL_BLINKOFF 0x00

// Display/Cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// Function set
#define LCD_FNC_8BITMODE 0x10
#define LCD_FNC_4BITMODE 0x00
#define LCD_FNC_2LINE 0x08
#define LCD_FNC_1LINE 0x00
#define LCD_FNC_5x10DOTS 0x04
#define LCD_FNC_5x8DOTS 0x00

// Backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

/**
 * @brief Initilazes the LCD Module.
 * 
 * @param address Device Address (default is 0x27).
 */
void LCD_Initialize(uint8_t address);

/**
 * @brief Prints characters on the LCD screen.
 * 
 * @param format   Text format specifier similar to printf.
 * @param ... 
 * @return uint8_t Returns number of characters printed on the screen.
 */
uint8_t LCD_print(const char *format, ...);

/**
 * @brief Clear Display
 * 
 */
void LCD_clear();

/**
 * @brief Returns Home - Cursor is set to 0, 0.
 * 
 */
void LCD_home();

/**
 * @brief Sets Cursor position on the screen.
 * 
 * @param row Row value 0 or 1.
 * @param col Column value.
 */
void LCD_setCursor(uint8_t col, uint8_t row);

/**
 * @brief Turn Cursor Off.
 * 
 */
void LCD_noCursor();

/**
 * @brief Turn Cursor On.
 * 
 */
void LCD_cursor();

/**
 * @brief Turn Blink Off.
 * 
 */
void LCD_noBlink();

/**
 * @brief Turn Blink On.
 * 
 */
void LCD_blink();

/**
 * @brief Scroll the Display Left without changing the RAM.
 * 
 */
void LCD_scrollDisplayLeft();

/**
 * @brief Scroll the Display Right without changing the RAM.
 * 
 */
void LCD_scrollDisplayRight();

/**
 * @brief This is for text that flows Left to Right.
 * 
 */
void LCD_leftToRight();

/**
 * @brief This is for text that flows Right to Left.
 * 
 */
void LCD_rightToLeft();

/**
 * @brief This will 'right justify' text from the cursor.
 * 
 */
void LCD_autoscroll();

/**
 * @brief This will 'left justify' text from the cursor.
 * 
 */
void LCD_noAutoscroll();

/**
 * @brief Turn Off LCD Backlight.
 * 
 */
void LCD_noBacklight();

/**
 * @brief Turn On LCD Backlight.
 * 
 */
void LCD_backlight();

/**
 * @brief Add custom characters into first 8 CGRAM locations.
 * 
 * @param location Location in CGRAM to put the Custom character - 0 to 7.
 * @param charmap  Array with bit map pattern.
 */
void LCD_createChar(uint8_t location, uint8_t charmap[]);

/**
 * @brief Send Command to the LCD Module.
 * 
 * @param value Command to send.
 */
void LCD_command(uint8_t value);

/**
 * @brief Write Data on the LCD Module.
 * 
 * @param data Data to write.
 */
void LCD_write(uint8_t data);

#endif /* LCD_I2C_LIB_H */
