#include "hcsr04_sensor.h"

GPIO_CONFIG_t trig = {
    .gpio_mode = GPIO_MODE_OUTPUT,
    .init_output_level = GPIO_OUTPUT_LEVEL_LOW};

GPIO_CONFIG_t echo = {
    .gpio_mode = GPIO_MODE_INPUT_TRISTATE,
};

void InitUltraSonicSensor()
{
    GPIO_Init(GPIO_PORTB, TRIG_PIN, &trig);
    GPIO_Init(GPIO_PORTB, ECHO_PIN, &echo);

    ICT_CONFIG_t cap_cfg = {
        .capture_param.ic_start_edge = HIGH,
        .capture_param.ic_start_trigger_pin = ECHO_PIN,
        .capture_param.ic_end_edge = LOW,
        .capture_param.ic_end_trigger_pin = ECHO_PIN,
        .capture_param.prescale = 63, // set capture counter to 1 us
        .mode = ICT_MODE_INPUT_CAPTURE,
    };

    ICT_SetTimer(ICT0, &cap_cfg);
}

float getDistance()
{
    float dist;

    ICT_INPUT_CAPTURE0_START();

    /* Send a 10us Trigger pulse. */
    GPIO_SetOutputHigh(GPIO_PORTB, TRIG_PIN);

    for(uint8_t del = 0; del < 2; del++)
    {
        DELAY1us();
    }

    GPIO_SetOutputLow(GPIO_PORTB, TRIG_PIN);

    while (!TFREGbits.T4ICF);
    ICT_INPUT_CAPTURE0_STOP();
    ICT_INPUT_CAPTURE0_CLEAR_FLAG();

    dist = (float)ICT_INPUT_CAPTURE0_READ_BUFFER_VALUE() * 0.034 / 2.0; // speed of sound = 0.034 cm / us
    return dist;
}