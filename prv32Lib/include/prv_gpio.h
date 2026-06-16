/**
 * @file    prv_gpio.h
 * @brief   Provides APIs for GPIO
 * @version 0.1
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_GPIO_H_
#define _PRV_GPIO_H_

#include "prv32.h"

#define GPIO_PORTA ((GPIO_PORT_t *)_GPIO_PORTA_)
#define GPIO_PORTB ((GPIO_PORT_t *)_GPIO_PORTB_)

/* GPIO Mode definition - defines the direction of Pins */
typedef enum
{
    GPIO_MODE_OUTPUT = 0,
    GPIO_MODE_INPUT_TRISTATE = 1,
} GPIO_MODE_t;

/* GPIO Output level definition */
typedef enum
{
    GPIO_OUTPUT_LEVEL_LOW = 0,
    GPIO_OUTPUT_LEVEL_HIGH = 1,
} GPIO_OUTPUT_LEVEL_t;

typedef enum
{
    GPIO_INPUT_STATE_LOW = 0,
    GPIO_INPUT_STATE_HIGH = 1,
} GPIO_INPUT_STATE_t;

/* Defines different Alternate Output options */
typedef enum
{
    ALTERNATE_OUTPUT_UART0 = 0,
    ALTERNATE_OUTPUT_UART1,
    ALTERNATE_OUTPUT_I2C0,
    ALTERNATE_OUTPUT_SPI0 = 4,
    ALTERNATE_OUTPUT_PWM0 = 6,
    ALTERNATE_OUTPUT_PWM1,
    ALTERNATE_OUTPUT_PWM2,
    ALTERNATE_OUTPUT_PWM3,
    ALTERNATE_OUTPUT_PWM4,
    ALTERNATE_OUTPUT_PWM5
} GPIO_ALTOUT_t;

/*************************************************************/

/* Structure defining the Configuration of Pin */
typedef struct
{
    GPIO_MODE_t gpio_mode;
    GPIO_OUTPUT_LEVEL_t init_output_level;
} GPIO_CONFIG_t;

/*************************************************************/
/* *** Mapped to Hardware *** */

/* Structure defining the GPIO Registers - mapped to the hardware */
typedef struct
{
    _IO_ uint32_t DDR;
    _IO_ uint32_t IN;
    _IO_ uint32_t OUT;
} GPIO_PORT_t;

/*************************************************************/

/**
 * @brief API to Initialize a GPIO pin.
 * 
 * @param port   Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin    Port pin number.
 * @param config Constant pointer to pin configuration. Use GPIO_CONFIG_t structure to set up the pin configs.
 */
void GPIO_Init(GPIO_PORT_t *const port, const uint8_t pin, const GPIO_CONFIG_t *const config);

/**
 * @brief API to Set the Mode of a pin after it has already been initialized.
 * 
 * @param port Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin  Port pin number.
 * @param mode Pin direction selection. Use GPIO_MODE_t enum to select the mode of the pin.
 */
void GPIO_SetMode(GPIO_PORT_t *const port, const uint8_t pin, const GPIO_MODE_t mode);

/**
 * @brief API to Set the Ouput Level of a pin.
 * 
 * @param port  Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin   Port pin number
 * @param level Sets the output level of the pin. Use GPIO_OUTPUT_LEVEL_t enum to select the level.
 */
void GPIO_SetOutputLevel(GPIO_PORT_t *const port, const uint8_t pin, const GPIO_OUTPUT_LEVEL_t level);

/**
 * @brief API to Set the Output of a pin High.
 * 
 * @param port Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin  Port pin number.
 */
void GPIO_SetOutputHigh(GPIO_PORT_t *const port, const uint8_t pin);

/**
 * @brief API to Set the Output of a pin Low.
 * 
 * @param port Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin  Port pin number.
 */
void GPIO_SetOutputLow(GPIO_PORT_t *const port, const uint8_t pin);

/**
 * @brief API to Toggle the Output of a pin.
 * 
 * @param port Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin  Port pin number.
 */
void GPIO_ToggleOutput(GPIO_PORT_t *const port, const uint8_t pin);

/**
 * @brief API to read the actual pin state.
 * 
 * @param port                Constant pointer to GPIO PORT modules to access hardware registers. Pass GPIO_PORTA or GPIO_PORTB as port parameter.
 * @param pin                 Port pin number.
 * @return GPIO_INPUT_STATE_t Indicates state of the pin either High or Low. Refer to enum GPIO_INPUT_STATE_t.
 */
GPIO_INPUT_STATE_t GPIO_GetInput(GPIO_PORT_t *const port, const uint8_t pin);

/**
 * @brief API to Set the Output Level of an on-board LED.
 * 
 * @param pin   Port pin number.
 * @param level Sets the output level of the pin. Use GPIO_OUTPUT_LEVEL_t enum to select the level.
 */
void LED_SetOutputLevel(const uint8_t pin, const GPIO_OUTPUT_LEVEL_t level);

/**
 * @brief API to Set the Output of an on-board LED High.
 * 
 * @param pin Port pin number
 */
void LED_SetOutputHigh(const uint8_t pin);

/**
 * @brief API to Set the Output of an on-board LED Low.
 * 
 * @param pin Port pin number.
 */
void LED_SetOutputLow(const uint8_t pin);

/**
 * @brief API to Toggle the Output of an on-board LED.
 * 
 * @param pin Port pin number.
 */
void LED_ToggleOutput(const uint8_t pin);

/**
 * @brief API to set GPIO as alternate output.
 * 
 * @param alternate_function Alternate function name. Use GPIO_ALTOUT_t enum to select the Alternate function.
 * @param pin                Port pin number to enable alternate output.
 */
void GPIO_SetAlternateOutputPin(const GPIO_ALTOUT_t alternate_function, uint8_t pin);

/**
 * @brief API to disable alternate output at GPIO pin.
 * 
 * @param alternate_function Alternate function name. Use GPIO_ALTOUT_t enum to select the Alternate function.
 * @param pin                Port pin number to disable alternate output.
 */
void GPIO_DisableAlternateOutputPin(const GPIO_ALTOUT_t alternate_function, uint8_t pin);

#endif /* _PRV_GPIO_H_ */