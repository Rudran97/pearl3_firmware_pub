#include "prv_serial.h"
#include "prv_interrupt.h"
#include "prv_timer0.h"

int main()
{
    SysTick_Init(TIMERms_const);
    Serial_Initialize(115200);
    ENABLE_GLOBAL_INTERRUPT();

    uint8_t ch;

    printf("Hello World!\n");

    while(true)
    {
        if (Serial_read(&ch) == UART_BUFF_STATUS_NOERR)
            printf("%c", ch);

        LATD ^= 10;
        delay(100);
    }

    return 0;
}