/**
 * @file    lcd_I2C_lib.c
 * @brief   Library to control 1602 I2C LCD module
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "prv32.h"
#include "prv_i2c.h"
#include "../../prv32Lib/common/printf.h"
#include "lcd_I2C_lib.h"

#ifdef PRV_ASSERT_CHECKS
    #include "prv_csr.h"
    #include "prv_assert.h"
#endif /* PRV_ASSERT_CHECKS */

#define EN 0b00000100
#define RW 0b00000010
#define RS 0b00000001

typedef struct
{
	uint8_t address;
	uint8_t displayFunction;
	uint8_t displayControl;
	uint8_t displayMode;
	uint8_t backLightVal;
} lcd_I2C_config_t;

lcd_I2C_config_t lcd_config = {0};

void LCD_send(uint8_t data, uint8_t mode);
void LCD_write4bits(uint8_t data);
void LCD_transmit(uint8_t data);
void LCD_delayMicros(uint32_t delay_us);

/*************************************************************/

/* User Commands to Control LCD */

/**
 * @brief Initilazes the LCD Module.
 * 
 * @param address Device Address (default is 0x27).
 */
void LCD_Initialize(uint8_t address)
{	
	lcd_config.address = address;
	lcd_config.displayFunction = LCD_FNC_4BITMODE | LCD_FNC_2LINE | LCD_FNC_5x8DOTS;
	lcd_config.displayControl = LCD_CTRL_DISPLAYON | LCD_CTRL_CURSORON | LCD_CTRL_BLINKON;
	lcd_config.displayMode = LCD_MODE_ENTRYLEFT | LCD_MODE_ENTRYSHIFTDECREMENT;
	lcd_config.backLightVal = LCD_BACKLIGHT;

    #ifdef PRV_ASSERT_CHECKS
        /* Ensure Interrupts are enabled before using the i2c communication */
        prvASSERT(INTCONbits.GIE && (csr_read_mstatus() & MSTATUS_MIE_BIT_MASK), PRV_ASSERT_NO_INTERRUPT);
    #endif /* PRV_ASSERT_CHECKS */

	// Trying to set the LCD to 4 bit mode
	for(uint8_t i=0; i<3; i++)
	{
		LCD_write4bits(0x30);
		LCD_delayMicros(3500);
	}

	// Setting LCD to 4 bit mode
	LCD_write4bits(0x20);

	// LCD function set
	LCD_command(LCD_CMD_FUNCTIONSET | lcd_config.displayFunction);

	// LCD Display control
	LCD_command(LCD_CMD_DISPLAYCONTROL | lcd_config.displayControl);

	LCD_clear();

	LCD_command(LCD_CMD_ENTRYMODESET | lcd_config.displayMode);
}

/**
 * @brief Prints characters on the LCD screen.
 * 
 * @param format   Text format specifier similar to printf.
 * @param ... 
 * @return uint8_t Returns number of characters printed on the screen.
 */
uint8_t LCD_print(const char *format, ...)
{
	va_list va;
	va_start(va, format);
	char buffer[40];
	vsnprintf(buffer, 20, format, va);
	va_end(va);
	uint8_t idx = 0;
	while(buffer[idx])
	{
		LCD_write(buffer[idx]);
		idx += 1;
	}
	return idx;
}

/**
 * @brief Clear Display
 * 
 */
void LCD_clear()
{
	LCD_command(LCD_CMD_CLEARDISPLAY);
	LCD_delayMicros(2000);
}

/**
 * @brief Returns Home - Cursor is set to 0, 0.
 * 
 */
void LCD_home()
{
	LCD_command(LCD_CMD_RETURNHOME);
	LCD_delayMicros(2000);
}

/**
 * @brief Sets Cursor position on the screen.
 * 
 * @param row Row value 0 or 1.
 * @param col Column value.
 */
void LCD_setCursor(uint8_t col, uint8_t row)
{
	uint8_t row_offsets[] = { 0x00, 0x40 };
	if (row > 1) {
		row = 0;
	}
	LCD_command(LCD_CMD_SETDDRAMADDR | (col + row_offsets[row]));
}

/**
 * @brief Turn Cursor Off.
 * 
 */
void LCD_noCursor() {
	lcd_config.displayControl &= ~LCD_CTRL_CURSORON;
	LCD_command(LCD_CMD_DISPLAYCONTROL | lcd_config.displayControl);
}

/**
 * @brief Turn Cursor On.
 * 
 */
void LCD_cursor() {
	lcd_config.displayControl |= LCD_CTRL_CURSORON;
	LCD_command(LCD_CMD_DISPLAYCONTROL | lcd_config.displayControl);
}

/**
 * @brief Turn Blink Off.
 * 
 */
void LCD_noBlink() {
	lcd_config.displayControl &= ~LCD_CTRL_BLINKON;
	LCD_command(LCD_CMD_DISPLAYCONTROL | lcd_config.displayControl);
}

/**
 * @brief Turn Blink On.
 * 
 */
void LCD_blink() {
	lcd_config.displayControl |= LCD_CTRL_BLINKON;
	LCD_command(LCD_CMD_DISPLAYCONTROL | lcd_config.displayControl);
}

/**
 * @brief Scroll the Display Left without changing the RAM.
 * 
 */
void LCD_scrollDisplayLeft(void) {
	LCD_command(LCD_CMD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

/**
 * @brief Scroll the Display Right without changing the RAM.
 * 
 */
void LCD_scrollDisplayRight(void) {
	LCD_command(LCD_CMD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

/**
 * @brief This is for text that flows Left to Right.
 * 
 */
void LCD_leftToRight(void) {
	lcd_config.displayMode |= LCD_MODE_ENTRYLEFT;
	LCD_command(LCD_CMD_ENTRYMODESET | lcd_config.displayMode);
}

/**
 * @brief This is for text that flows Right to Left.
 * 
 */
void LCD_rightToLeft(void) {
	lcd_config.displayMode &= ~LCD_MODE_ENTRYLEFT;
	LCD_command(LCD_CMD_ENTRYMODESET | lcd_config.displayMode);
}

/**
 * @brief This will 'right justify' text from the cursor.
 * 
 */
void LCD_autoscroll(void) {
	lcd_config.displayMode |= LCD_MODE_ENTRYSHIFTINCREMENT;
	LCD_command(LCD_CMD_ENTRYMODESET | lcd_config.displayMode);
}

/**
 * @brief This will 'left justify' text from the cursor.
 * 
 */
void LCD_noAutoscroll(void) {
	lcd_config.displayMode &= ~LCD_MODE_ENTRYSHIFTINCREMENT;
	LCD_command(LCD_CMD_ENTRYMODESET | lcd_config.displayMode);
}

/**
 * @brief Turn Off LCD Backlight.
 * 
 */
void LCD_noBacklight(void) {
	lcd_config.backLightVal = LCD_NOBACKLIGHT;
	LCD_transmit(0);
}

/**
 * @brief Turn On LCD Backlight.
 * 
 */
void LCD_backlight(void) {
	lcd_config.backLightVal = LCD_BACKLIGHT;
	LCD_transmit(0);
}

/**
 * @brief Add custom characters into first 8 CGRAM locations.
 * 
 * @param location Location in CGRAM to put the Custom character - 0 to 7.
 * @param charmap  Array with bit map pattern.
 */
void LCD_createChar(uint8_t location, uint8_t charmap[]) {
	location &= 0x7; // we only have 8 locations 0-7
	LCD_command(LCD_CMD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
		LCD_write(charmap[i]);
	}
}

/*************************************************************/

/* Send Command or Data */

/**
 * @brief Send Command to the LCD Module.
 * 
 * @param value Command to send.
 */
void LCD_command(uint8_t value)
{
	LCD_send(value, 0);
}

/**
 * @brief Write Data on the LCD Module.
 * 
 * @param data Data to write.
 */
void LCD_write(uint8_t data)
{
	LCD_send(data, RS);
}

/*************************************************************/

/* LCD Interface Functions */

void LCD_send(uint8_t data, uint8_t mode)
{
	LCD_write4bits((data & 0xf0) | mode);		 // Send higher nibble
	LCD_write4bits(((data << 4) & 0xf0) | mode); // Send lower nibble
}

void LCD_write4bits(uint8_t data)
{
	LCD_transmit(data);

	// pulse EN pin
	LCD_transmit(data | EN);
	LCD_delayMicros(1);
	LCD_transmit(data & ~EN);
	LCD_delayMicros(50);
}

void LCD_transmit(uint8_t data)
{
	i2c_write1Byte(lcd_config.address, data | lcd_config.backLightVal);
}

void LCD_delayMicros(uint32_t delay_us)
{
	for (uint32_t i = 0; i < delay_us; i++)
	{
		DELAY1us();
	};
}
