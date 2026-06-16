/**
 * @file    prv_ict.h
 * @brief   APIs for Input Capture Timer modules.
 *          In Capture mode ICT0 module can be mapped to PORTB[0..3]
 *          and ICT1 module can be mapped to PORTB[4..7].
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_ICT_H_
#define _PRV_ICT_H_

#include "prv32.h"

#define ICT0 ((TIMER_ICT_t *)_TIMER4_)
#define ICT1 ((TIMER_ICT_t *)_TIMER5_)

/* Macro to Start Timer4 */
#define ICT_TIMER4_START() (T4CON |= _T4CON_T4ON_MASK)

/* Macro to Start Input Capture0 */
#define ICT_INPUT_CAPTURE0_START() (T4CON |= _T4CON_TIC0ON_MASK)

/* Macro to Start Timer5 */
#define ICT_TIMER5_START() (T5CON |= _T5CON_T5ON_MASK)

/* Macro to Start Input Capture1 */
#define ICT_INPUT_CAPTURE1_START() (T5CON |= _T5CON_TIC1ON_MASK)

/* Macro to Stop Timer4 */
#define ICT_TIMER4_STOP() (T4CON &= ~_T4CON_T4ON_MASK)

/* Macro to Stop Input Capture0 */
#define ICT_INPUT_CAPTURE0_STOP() (T4CON &= ~_T4CON_TIC0ON_MASK)

/* Macro to Stop Timer5 */
#define ICT_TIMER5_STOP() (T5CON &= ~_T5CON_T5ON_MASK)

/* Macro to Stop Input Capture1 */
#define ICT_INPUT_CAPTURE1_STOP() (T5CON &= ~_T5CON_TIC1ON_MASK)

/* Macro to Clear Timer4 Match Flag */
#define ICT_TIMER4_CLEAR_FLAG() (T4CON |= _T4CON_T4CLRF_MASK)

/* Macro to Clear Input Capture0 Flag */
#define ICT_INPUT_CAPTURE0_CLEAR_FLAG() (T4CON |= _T4CON_TIC0CLRF_MASK)

/* Macro to Clear Timer5 Match Flag */
#define ICT_TIMER5_CLEAR_FLAG() (T5CON |= _T5CON_T5CLRF_MASK)

/* Macro to Clear Input Capture1 Flag */
#define ICT_INPUT_CAPTURE1_CLEAR_FLAG() (T5CON |= _T5CON_TIC1CLRF_MASK)

/* Macro to Read value of Timer4 buffer */
#define ICT_TIMER4_READ_BUFFER_VALUE() (T4BUF)

/* Macro to Read value of Input Capture0 buffer */
#define ICT_INPUT_CAPTURE0_READ_BUFFER_VALUE() (TC0BUF)

/* Macro to Read value of Timer5 buffer */
#define ICT_TIMER5_READ_BUFFER_VALUE() (T5BUF)

/* Macro to Read value of Input Capture1 buffer */
#define ICT_INPUT_CAPTURE1_READ_BUFFER_VALUE() (TC1BUF)

/* Defines the mode of ICT Modules */
typedef enum
{
    ICT_MODE_TIMER = 0,
    ICT_MODE_INPUT_CAPTURE,
} ICT_MODE_t;

/* Structure defining Prescale and Timer counter Match Value for ICT Module in Timer Mode */
typedef struct
{
    uint32_t prescale;
    uint32_t match_value;
} ICT_TIMER_PARAMETERS_t;

/* Structure defining ICT Module in Input Capture Mode */
typedef struct
{
    uint32_t prescale;
    uint32_t ic_start_edge;
    uint32_t ic_start_trigger_pin;
    uint32_t ic_end_edge;
    uint32_t ic_end_trigger_pin;
} ICT_INPUT_CAPTURE_PARAMETERS_t;

/* Structure defining the configuration of ICT Modules */
typedef struct
{
    ICT_MODE_t mode;
    ICT_TIMER_PARAMETERS_t timer_param;
    ICT_INPUT_CAPTURE_PARAMETERS_t capture_param;
} ICT_CONFIG_t;

/*************************************************************/
/* *** Mapped to Hardware *** */

/* Structure defining Input Capture and Timer Registers - mapped to the hardware */
typedef struct
{
    _IO_ uint32_t TCON;
    _IO_ uint32_t TL;
    _IO_ uint32_t TH;
} TIMER_ICT_t;

/*************************************************************/

/**
 * @brief API to Setup ICT Module.
 * 
 * @param module Constant pointer to ICT modules to access hardware registers. Pass ICT0, ICT1 as module parameters.
 * @param config ICT module configurations. Use ICT_CONFIG_t structure to set the required configurations.
 */
void ICT_SetTimer(TIMER_ICT_t *const module, ICT_CONFIG_t *config);

#endif /* _PRV_ICT_H_ */