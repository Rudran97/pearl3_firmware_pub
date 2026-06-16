#include "prv_i2c.h"
#include "lcd_I2C_lib.h"
#include "prv_serial.h"
#include "prv_plic.h"
#include "prv_uart.h"

const char message[] = "Hello World!";

uint8_t char_man[] = {
    0b01100,
    0b01100,
    0b00000,
    0b01110,
    0b11100,
    0b01100,
    0b11010,
    0b10011,
};

int main()
{
    Serial_Initialize(115200);

    PLIC_INTERRUPT_CONFIG_t i2c_int_config = {
        .attach_interrupt_module = ATTACH_I2C0DNF_TO_INTERRUPT,
        .set_priority = INTERRUPT_PRIORITY_1
    };

    Set_Interrupt0(&i2c_int_config);

    ENABLE_GLOBAL_INTERRUPT();

    uint32_t i2c_freq = I2C_FREQ(400000);
    I2C0_Initialize(i2c_freq, 7, 6);
    
    LCD_Initialize(0x27);
    LCD_createChar(1, char_man);

    LCD_setCursor(8, 0);
    LCD_write(1);

    LCD_setCursor(0, 1);
    uint8_t num = LCD_print("%s", message);

	uint8_t buff[18] = {0};

    // printf("Number of characters printed %d", num);
    while (1)
	{
		while(Serial_isAvailable())
		{
			Serial_read(&buff[0]);
			printf("%s", buff);
		}
	}
}
