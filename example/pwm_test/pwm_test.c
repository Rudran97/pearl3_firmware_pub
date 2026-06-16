#include "prv_dct.h"
#include "prv_pwm.h"
#include "prv_serial.h"
#include "prv_interrupt.h"

int main()
{
    Serial_Initialize(115200);
    ENABLE_GLOBAL_INTERRUPT();

    PWM_CONFIG_t led1_pwm = {
        .dutyCyc = 100,
        .name = PWM_MODULE3,
        .period_match = 228,
        .prescale = 29,
        .pwmPin = 0};

    PWM_CONFIG_t led2_pwm = {
        .dutyCyc = 600,
        .name = PWM_MODULE4,
        .period_match = 1199,
        .prescale = 39,
        .pwmPin = 1};

    PWM_Initialize(PWM3, &led1_pwm);

    PWM_Initialize(PWM4, &led2_pwm);

    PWM3_START();
    PWM4_START();

    uint8_t dutycycle;

    while (1)
    {
        Serial_read(&dutycycle); // read duty cycle value from serial buffer
        if (dutycycle >= 0 && dutycycle <= 100)
        {
            PWM_SetDutyCycle(PWM3, dutycycle, &led1_pwm);
            PWM_SetDutyCycle(PWM4, dutycycle, &led2_pwm);
        }
    }
}