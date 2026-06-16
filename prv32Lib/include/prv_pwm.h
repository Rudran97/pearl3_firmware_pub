/**
 * @file    prv_pwm.h
 * @brief   APIs for PWM modulues.
 * @version 0.1
 * @date    2023-07-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _PRV_PWM_H_
#define _PRV_PWM_H_

#include "prv_gpio.h"

#define PWM0 ((PWM_REG_t *)_PWM0_)
#define PWM1 ((PWM_REG_t *)_PWM1_)
#define PWM2 ((PWM_REG_t *)_PWM2_)
#define PWM3 ((PWM_REG_t *)_PWM3_)
#define PWM4 ((PWM_REG_t *)_PWM4_)
#define PWM5 ((PWM_REG_t *)_PWM5_)

/* Macro to Start PWM0 */
#define PWM0_START() (DCT_TIMER1A_START())

/* Macro to Start PWM1 */
#define PWM1_START() (DCT_TIMER1B_START())

/* Macro to Start PWM2 */
#define PWM2_START() (DCT_TIMER2A_START())

/* Macro to Start PWM3 */
#define PWM3_START() (DCT_TIMER2B_START())

/* Macro to Start PWM4 */
#define PWM4_START() (DCT_TIMER3A_START())

/* Macro to Start PWM5 */
#define PWM5_START() (DCT_TIMER3B_START())

/* Macro to Stop PWM0 */
#define PWM0_STOP() (DCT_TIMER1A_STOP())

/* Macro to Stop PWM1 */
#define PWM1_STOP() (DCT_TIMER1B_STOP())

/* Macro to Stop PWM2 */
#define PWM2_STOP() (DCT_TIMER2A_STOP())

/* Macro to Stop PWM3 */
#define PWM3_STOP() (DCT_TIMER2B_STOP())

/* Macro to Stop PWM4 */
#define PWM4_STOP() (DCT_TIMER3A_STOP())

/* Macro to Stop PWM5 */
#define PWM5_STOP() (DCT_TIMER3B_STOP())

/* Defines PWM module names */
typedef enum
{
    PWM_MODULE0 = 0,
    PWM_MODULE1,
    PWM_MODULE2,
    PWM_MODULE3,
    PWM_MODULE4,
    PWM_MODULE5
} PWM_MODULE_t;

/* Structure defining configuration of PWM Module */
typedef struct
{
    PWM_MODULE_t name;
    uint32_t dutyCyc;
    uint32_t period_match;
    uint32_t prescale;
    uint32_t pwmPin;
} PWM_CONFIG_t;

/*************************************************************/
/* *** Mapped to Hardware *** */

/* Structure defining PWM registers - mapped to the hardware */
typedef struct
{
    _IO_ uint32_t PWMCON;
    _IO_ uint32_t PWMDC;
} PWM_REG_t;

/*************************************************************/

/**
 * @brief API to Initialize PWM Module.
 * 
 * @param module Constant pointer to PWM modules to access hardwre registers. Pass PWM0, PWM1, PWM2, PWM3, PWM4, or PWM5 as module parameter.
 * @param config PWM module configuration. Use PWM_CONFIG_t structure to set the required configurations.
 */
void PWM_Initialize(PWM_REG_t *const module, PWM_CONFIG_t *config);

/**
 * @brief API to Change the PWM Duty cycle.
 * 
 * @param module    Constant pointer to PWM modules to access hardwre registers. Pass PWM0, PWM1, PWM2, PWM3, PWM4, or PWM5 as module parameter.
 * @param dutyCycle Duty Cycle value in 0 - 100 percent.
 * @param config    PWM module configuration. Use PWM_CONFIG_t structure to set the required configurations.
 */
void PWM_SetDutyCycle(PWM_REG_t *const module, uint8_t dutyCycle, PWM_CONFIG_t *config);

#endif /* _PRV_PWM_H_ */