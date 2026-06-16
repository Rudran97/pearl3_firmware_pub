#include "prv_i2c.h"
#include "lcd_I2C_lib.h"
#include "prv_plic.h"
#include "prv_timer0.h"
#include "hcsr04_sensor.h"
#include "adc.h"
#include "bh1750.h"
// #include "prv_serial.h"

void InitLCD();
void deleteChar(uint8_t n);

int main()
{
    SysTick_Init(TIMERms_const);
    // Serial_Initialize(115200);

    ENABLE_GLOBAL_INTERRUPT();

    InitLCD();
    InitUltraSonicSensor();
    BH1750_begin(BH1750_I2CADDR, CONTINUOUS_HIGH_RES_MODE);
    // InitADC();

    uint8_t lx_char_printed = 0, adc_char_printed = 0, us_char_printed = 0;

    LCD_setCursor(0, 0);
    uint8_t intensity_char = LCD_print("Lx : ");

    LCD_setCursor(0, 1);
    uint8_t dist_char = LCD_print("Distance : ");

    // LCD_setCursor(1, 0);
    // uint8_t adc_char = LCD_print("ADC value : ");

    while(1)
    {
        delay(100);

        /* Print BH1750 values */
        LCD_setCursor(intensity_char + lx_char_printed, 0);
        deleteChar(lx_char_printed);
        float intensity = BH1750_readLightLevel();
        lx_char_printed = LCD_print("%.2f", intensity);
        
        /* Print Ultrasonic Sensor values */
        LCD_setCursor(dist_char + us_char_printed, 1);
        deleteChar(us_char_printed);
        float distance = getDistance();
        us_char_printed = LCD_print("%.2f", distance);

        // LCD_setCursor(1, adc_char + adc_char_printed);
        // deleteChar(adc_char_printed);
        // uint8_t pot_val = readADC();
        // adc_char_printed = LCD_print("%d", pot_val);
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
}

void deleteChar(uint8_t n)
{
    for(uint8_t i=1; i<=n; i++)
    {
        LCD_command(LCD_CMD_CURSORSHIFT | LCD_MOVELEFT);
    }
    for(uint8_t i=1; i<=n; i++)
    {
        LCD_print(" ");
    }
    for(uint8_t i=1; i<=n; i++)
    {
        LCD_command(LCD_CMD_CURSORSHIFT | LCD_MOVELEFT);
    }
}