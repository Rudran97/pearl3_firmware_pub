#include "prv_i2c.h"
#include "prv_serial.h"
#include "prv_plic.h"
#include "bh1750.h"
#include "prv_timer0.h"

const char message[] = "Hello World!";

int main()
{
    Serial_Initialize(115200);

    SysTick_Init(TIMERms_const);

    uint32_t i2c_freq = I2C_FREQ(400000);
    I2C0_Initialize(i2c_freq, 7, 6);

    PLIC_INTERRUPT_CONFIG_t i2c_int_config = {
        .attach_interrupt_module = ATTACH_I2C0DNF_TO_INTERRUPT,
        .set_priority = INTERRUPT_PRIORITY_1};

    Set_Interrupt0(&i2c_int_config);

    ENABLE_GLOBAL_INTERRUPT();

    BH1750_begin(BH1750_I2CADDR, CONTINUOUS_LOW_RES_MODE);

    printf("%.2f\n", (float) 5 / 2);

    while (1)
    {
        delay(500);
        float level = BH1750_readLightLevel();

        if (level > 500){
            LATD = 0xF0;
        }
        else{
            LATD = 0x0A;
        }

        printf("%.3f\n", level);
    }
}