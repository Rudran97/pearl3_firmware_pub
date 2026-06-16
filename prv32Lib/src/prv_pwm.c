/**
 * @file    prv_pwm.c
 * @brief   APIs for PWM modules.
 * @version 0.1
 * @date    2023-07-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "prv_dct.h"
#include "prv_pwm.h"

/**
 * @brief API to Initialize PWM Module.
 * 
 * @param module Constant pointer to PWM modules to access hardwre registers. Pass PWM0, PWM1, PWM2, PWM3, PWM4, or PWM5 as module parameter.
 * @param config PWM module configuration. Use PWM_CONFIG_t structure to set the required configurations.
 */
void PWM_Initialize(PWM_REG_t *const module, PWM_CONFIG_t *config)
{
    module->PWMCON = (config->period_match & _PWMCON_PWMPR_MASK) | (_PWMCON_PWMPIN_MASK & (config->pwmPin << _PWMCON_PWMPIN_POSN));
    module->PWMDC = _PWMDC_PWMDTYCYC_MASK & config->dutyCyc;

    DCT_TIMER_PARAMETERS_t timer_paramn = {
        .match_value = config->period_match,
        .prescale = config->prescale
    };

    DCT_CONFIG_t timer_config = {
        .timer_param = timer_paramn
    };

    switch (config->name)
    {
    case PWM_MODULE0:
        timer_config.seg_name = DCT_MODULE_SEGA;
        DCT_SetTimer(DCT1, &timer_config);
        GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_PWM0, config->pwmPin);
        break;
    case PWM_MODULE1:
        timer_config.seg_name = DCT_MODULE_SEGB;
        DCT_SetTimer(DCT1, &timer_config);
        GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_PWM1, config->pwmPin);
        break;
    case PWM_MODULE2:
        timer_config.seg_name = DCT_MODULE_SEGA;
        DCT_SetTimer(DCT2, &timer_config);
        GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_PWM2, config->pwmPin);
        break;
    case PWM_MODULE3:
        timer_config.seg_name = DCT_MODULE_SEGB;
        DCT_SetTimer(DCT2, &timer_config);
        GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_PWM3, config->pwmPin);
        break;
    case PWM_MODULE4:
        timer_config.seg_name = DCT_MODULE_SEGA;
        DCT_SetTimer(DCT3, &timer_config);
        GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_PWM4, config->pwmPin);
        break;
    case PWM_MODULE5:
        timer_config.seg_name = DCT_MODULE_SEGB;
        DCT_SetTimer(DCT3, &timer_config);
        GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_PWM5, config->pwmPin);
        break;
    default:
        break;
    }
}

/**
 * @brief API to Change the PWM Duty cycle.
 * 
 * @param module    Constant pointer to PWM modules to access hardwre registers. Pass PWM0, PWM1, PWM2, PWM3, PWM4, or PWM5 as module parameter.
 * @param dutyCycle Duty Cycle value in 0 - 100 percent.
 * @param config    PWM module configuration. Use PWM_CONFIG_t structure to set the required configurations.
 */
void PWM_SetDutyCycle(PWM_REG_t *const module, uint8_t dutyCycle, PWM_CONFIG_t *config)
{
    config->dutyCyc = (config->period_match * dutyCycle) / 100;
    module->PWMDC = config->dutyCyc;
}
