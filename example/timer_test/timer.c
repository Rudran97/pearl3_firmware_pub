#include "prv32.h"
#include "prv_i2c.h"
#include "lcd_I2C_lib.h"
#include "prv_plic.h"
#include "prv_timer0.h"

void InitLCD();

int main()
{
    SysTick_Init(TIMERms_const); // 1 ms tick period
    ENABLE_GLOBAL_INTERRUPT();
    InitLCD();

    LCD_print("** Stop Watch **");
    LCD_setCursor(0, 1);

    uint32_t s = 0, m = 0, h = 0;

    while(true)
    {
        s += 1;
        if (s == 60)
        {
            s = 0;
            m += 1;
        }
        if (m == 60)
        {
            m = 0;
            h += 1;
        }

        LCD_setCursor(0, 1);
        LCD_print("%02d:%02d:%02d", h, m, s);
        delay(990);
    }

}

void InitLCD()
{
    PLIC_INTERRUPT_CONFIG_t i2c_int_config = {
        .attach_interrupt_module = ATTACH_I2C0DNF_TO_INTERRUPT,
        .set_priority = INTERRUPT_PRIORITY_1
    };

    Set_Interrupt0(&i2c_int_config);

    uint32_t i2c_freq = I2C_FREQ(400000);
    I2C0_Initialize(i2c_freq, 7, 6);

    LCD_Initialize(0x27);
    LCD_noBlink();
    LCD_noCursor();
}
