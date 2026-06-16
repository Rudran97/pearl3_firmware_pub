/**
 * @file    prv_gpio.c
 * @brief   Provides APIs for GPIO
 * @version 0.1
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "prv_gpio.h"

/**
 * @brief API to Initialize a GPIO pin.
 * 
 * @param port   Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin    Port pin number.
 * @param config Constant pointer to pin configuration. Use GPIO_CONFIG_t structure to set up the pin configs.
 */
void GPIO_Init(GPIO_PORT_t *const port, const uint8_t pin, const GPIO_CONFIG_t *const config)
{
    port->OUT = (port->OUT & ~(1 << pin)) | (config->init_output_level << pin);
    port->DDR = (port->DDR & ~(1 << pin)) | (config->gpio_mode << pin);
}

/**
 * @brief API to Set the Mode of a pin after it has already been initialized.
 * 
 * @param port Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin  Port pin number.
 * @param mode Pin direction selection. Use GPIO_MODE_t enum to select the mode of the pin.
 */
void GPIO_SetMode(GPIO_PORT_t *const port, const uint8_t pin, const GPIO_MODE_t mode)
{
    port->DDR = (port->DDR & ~(1 << pin)) | (mode << pin);
}

/**
 * @brief API to Set the Ouput Level of a pin.
 * 
 * @param port  Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin   Port pin number.
 * @param level Sets the output level of the pin. Use GPIO_OUTPUT_LEVEL_t enum to select the level.
 */
void GPIO_SetOutputLevel(GPIO_PORT_t *const port, const uint8_t pin, const GPIO_OUTPUT_LEVEL_t level)
{
    port->OUT = (port->OUT & ~(1 << pin)) | (level << pin);
}

/**
 * @brief API to Set the Output of a pin High.
 * 
 * @param port Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin  Port pin number.
 */
void GPIO_SetOutputHigh(GPIO_PORT_t *const port, const uint8_t pin)
{
    port->OUT |= 1 << pin;
}

/**
 * @brief API to Set the Output of a pin Low.
 * 
 * @param port Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin  Port pin number.
 */
void GPIO_SetOutputLow(GPIO_PORT_t *const port, const uint8_t pin)
{
    port->OUT &=  ~ (1 << pin);
}

/**
 * @brief API to Toggle the Output of a pin.
 * 
 * @param port Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin  Port pin number.
 */
void GPIO_ToggleOutput(GPIO_PORT_t *const port, const uint8_t pin)
{
    port->OUT ^= 1 << pin;
}

/**
 * @brief API to read the actual pin state.
 * 
 * @param port                Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin                 Port pin number.
 * @return GPIO_INPUT_STATE_t Indicates state of the pin either High or Low. Refer to enum GPIO_INPUT_STATE_t.
 */
GPIO_INPUT_STATE_t GPIO_GetInput(GPIO_PORT_t *const port, const uint8_t pin)
{
    return (((port->IN) >> pin) & 0x1) ? GPIO_INPUT_STATE_HIGH : GPIO_INPUT_STATE_LOW;
}

/**
 * @brief API to Set the Output Level of an on-board LED.
 * 
 * @param pin   Port pin number.
 * @param level Sets the output level of the pin. Use GPIO_OUTPUT_LEVEL_t enum to select the level.
 */
void LED_SetOutputLevel(const uint8_t pin, const GPIO_OUTPUT_LEVEL_t level)
{
    LATD = (LATD & ~(1 << pin)) | (level << pin);
}

/**
 * @brief API to Set the Output of an on-board LED High.
 * 
 * @param pin Port pin number
 */
void LED_SetOutputHigh(const uint8_t pin)
{
    LATD |= 1 << pin;
}

/**
 * @brief API to Set the Output of an on-board LED Low.
 * 
 * @param pin Port pin number.
 */
void LED_SetOutputLow(const uint8_t pin)
{
    LATD &= ~ (1 << pin);
}

/**
 * @brief API to Toggle the Output of an on-board LED.
 * 
 * @param pin Port pin number.
 */
void LED_ToggleOutput(const uint8_t pin)
{
    LATD ^= 1 << pin;
}

/**
 * @brief API to set GPIO as alternate output.
 * 
 * @param alternate_function Alternate function name. Use GPIO_ALTOUT_t enum to select the Alternate function.
 * @param pin                Port pin number to enable alternate output.
 */
void GPIO_SetAlternateOutputPin(const GPIO_ALTOUT_t alternate_function, uint8_t pin)
{
    GPIO_CONFIG_t pin_config = {
        .gpio_mode = GPIO_MODE_OUTPUT,
        .init_output_level = GPIO_OUTPUT_LEVEL_HIGH
    };

    ALTOUTEN |= (1 << alternate_function);
    
    /* PWM, UART, SPI configures:
    *  - GPIO_Init
    *  - ALTOUTxCON
    * 
    *  I2C configures:
    *  - ALTOUTACON
    */

    switch (alternate_function)
    {
    case ALTERNATE_OUTPUT_PWM0:
    case ALTERNATE_OUTPUT_PWM1:
    case ALTERNATE_OUTPUT_PWM2:
    case ALTERNATE_OUTPUT_UART0:
        GPIO_Init(GPIO_PORTA, pin, &pin_config);
    case ALTERNATE_OUTPUT_I2C0:
        ALTOUTACON |= (1 << (0xf & pin));
        break;
    case ALTERNATE_OUTPUT_PWM3:
    case ALTERNATE_OUTPUT_PWM4:
    case ALTERNATE_OUTPUT_PWM5:
    case ALTERNATE_OUTPUT_UART1:
    case ALTERNATE_OUTPUT_SPI0:
        GPIO_Init(GPIO_PORTB, pin, &pin_config);
        ALTOUTBCON |= (1 << (0xf & pin));
        break;
    default:
        break;
    }
}

/**
 * @brief API to disable alternate output at GPIO pin.
 * 
 * @param alternate_function Alternate function name. Use GPIO_ALTOUT_t enum to select the Alternate function.
 * @param pin                Port pin number to disable alternate output.
 */
void GPIO_DisableAlternateOutputPin(const GPIO_ALTOUT_t alternate_function, uint8_t pin)
{
    ALTOUTEN &= ~(1 << alternate_function);
    
    switch (alternate_function)
    {
    case ALTERNATE_OUTPUT_PWM0:
    case ALTERNATE_OUTPUT_PWM1:
    case ALTERNATE_OUTPUT_PWM2:
    case ALTERNATE_OUTPUT_UART0:
    case ALTERNATE_OUTPUT_I2C0:
        ALTOUTACON &= ~(1 << (0xf & pin));
        break;
    case ALTERNATE_OUTPUT_PWM3:
    case ALTERNATE_OUTPUT_PWM4:
    case ALTERNATE_OUTPUT_PWM5:
    case ALTERNATE_OUTPUT_UART1:
    case ALTERNATE_OUTPUT_SPI0:
        ALTOUTBCON &= ~(1 << (0xf & pin));
        break;
    default:
        break;
    }
}