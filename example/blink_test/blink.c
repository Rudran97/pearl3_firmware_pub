#include "prv32.h"
#include "prv_timer0.h"
#include "prv_serial.h"
#include "prv_interrupt.h"

int main()
{
    SysTick_Init(TIMERms_const);
    ENABLE_GLOBAL_INTERRUPT();

    Serial_Initialize(115200);

    while (true)
    {
        LED_ToggleOutput(3);
        // printf("0x0A");
        delay(500);

        // LED_SetOutputLow(3);
        // printf("0x50");
        // delay(1000);
    }
    
}