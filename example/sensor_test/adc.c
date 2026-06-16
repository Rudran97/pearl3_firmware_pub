#include "adc.h"
#include "prv_gpio.h"

GPIO_CONFIG_t adc_do_cfg = {
    .gpio_mode = GPIO_MODE_INPUT_TRISTATE
};

GPIO_CONFIG_t adc_clk_cfg = {
    .gpio_mode = GPIO_MODE_OUTPUT,
    .init_output_level = GPIO_OUTPUT_LEVEL_LOW
};

GPIO_CONFIG_t adc_ncs_cfg = {
    .gpio_mode = GPIO_MODE_OUTPUT,
    .init_output_level = GPIO_OUTPUT_LEVEL_HIGH
};

static void pulse_clk();
static void adc_delay();

void InitADC()
{
    GPIO_Init(GPIO_PORTA, ADC_nCS, &adc_ncs_cfg);
    GPIO_Init(GPIO_PORTA, ADC_CLK, &adc_clk_cfg);
    GPIO_Init(GPIO_PORTA, ADC_DO, &adc_do_cfg);
}

uint8_t readADC()
{
    uint8_t val = 0;
    
    GPIO_SetOutputLow(GPIO_PORTA, ADC_nCS);
    adc_delay();
    
    pulse_clk();
    for (int8_t idx = 7; idx >= 0; idx--)
    {
        pulse_clk();
        val |= GPIO_GetInput(GPIO_PORTA, ADC_DO) << idx;
    }
    pulse_clk();

    GPIO_SetOutputHigh(GPIO_PORTA, ADC_nCS);

    return val;
}

static void pulse_clk()
{
    GPIO_SetOutputHigh(GPIO_PORTA, ADC_CLK);
    adc_delay();
    GPIO_SetOutputLow(GPIO_PORTA, ADC_CLK);
    adc_delay();   
}

static void adc_delay()
{
    for (uint8_t i = 0; i < 5; i++)
    {
        DELAY1us();
    }
}