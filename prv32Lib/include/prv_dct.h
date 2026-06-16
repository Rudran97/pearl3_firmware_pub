/**
 * @file    prv_dct.h
 * @brief   APIs for Dual Compare Timer modules.
 * @version 0.1
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_DCT_H_
#define _PRV_DCT_H_

#include "prv32.h"

#define DCT0 ((TIMER_DCT_t *)_TIMER0_)
#define DCT1 ((TIMER_DCT_t *)_TIMER1_)
#define DCT2 ((TIMER_DCT_t *)_TIMER2_)
#define DCT3 ((TIMER_DCT_t *)_TIMER3_)

/* Macro to Start Timer0A */
#define DCT_TIMER0A_START() (T0CON |= _T0CON_T0AON_MASK)

/* Macro to Start Timer0B */
#define DCT_TIMER0B_START() (T0CON |= _T0CON_T0BON_MASK)

/* Macro to Start Timer1A */
#define DCT_TIMER1A_START() (T1CON |= _T1CON_T1AON_MASK)

/* Macro to Start Timer1B */
#define DCT_TIMER1B_START() (T1CON |= _T1CON_T1BON_MASK)

/* Macro to Start Timer2A */
#define DCT_TIMER2A_START() (T2CON |= _T2CON_T2AON_MASK)

/* Macro to Start Timer2B */
#define DCT_TIMER2B_START() (T2CON |= _T2CON_T2BON_MASK)

/* Macro to Start Timer3A */
#define DCT_TIMER3A_START() (T3CON |= _T3CON_T3AON_MASK)

/* Macro to Start Timer3B */
#define DCT_TIMER3B_START() (T3CON |= _T3CON_T3BON_MASK)

/* Macro to Stop Timer0A */
#define DCT_TIMER0A_STOP() (T0CON &= ~_T0CON_T0AON_MASK)

/* Macro to Stop Timer0B */
#define DCT_TIMER0B_STOP() (T0CON &= ~_T0CON_T0BON_MASK)

/* Macro to Stop Timer1A */
#define DCT_TIMER1A_STOP() (T1CON &= ~_T1CON_T1AON_MASK)

/* Macro to Stop Timer1B */
#define DCT_TIMER1B_STOP() (T1CON &= ~_T1CON_T1BON_MASK)

/* Macro to Stop Timer2A */
#define DCT_TIMER2A_STOP() (T2CON &= ~_T2CON_T2AON_MASK)

/* Macro to Stop Timer2B */
#define DCT_TIMER2B_STOP() (T2CON &= ~_T2CON_T2BON_MASK)

/* Macro to Stop Timer3A */
#define DCT_TIMER3A_STOP() (T3CON &= ~_T3CON_T3AON_MASK)

/* Macro to Stop Timer3B */
#define DCT_TIMER3B_STOP() (T3CON &= ~_T3CON_T3BON_MASK)

/* Macro to Clear Timer0A Match Flag */
#define DCT_TIMER0A_CLEAR_FLAG() (T0CON |= _T0CON_T0ACLRF_MASK)

/* Macro to Clear Timer0B Match Flag */
#define DCT_TIMER0B_CLEAR_FLAG() (T0CON |= _T0CON_T0BCLRF_MASK)

/* Macro to Clear Timer1A Match Flag */
#define DCT_TIMER1A_CLEAR_FLAG() (T1CON |= _T1CON_T1ACLRF_MASK)

/* Macro to Clear Timer1B Match Flag */
#define DCT_TIMER1B_CLEAR_FLAG() (T1CON |= _T1CON_T1BCLRF_MASK)

/* Macro to Clear Timer2A Match Flag */
#define DCT_TIMER2A_CLEAR_FLAG() (T2CON |= _T2CON_T2ACLRF_MASK)

/* Macro to Clear Timer2B Match Flag */
#define DCT_TIMER2B_CLEAR_FLAG() (T2CON |= _T2CON_T2BCLRF_MASK)

/* Macro to Clear Timer3A Match Flag */
#define DCT_TIMER3A_CLEAR_FLAG() (T3CON |= _T3CON_T3ACLRF_MASK)

/* Macro to Clear Timer3B Match Flag */
#define DCT_TIMER3B_CLEAR_FLAG() (T3CON |= _T3CON_T3BCLRF_MASK)

/* Macro to Read value of Timer0A buffer */
#define DCT_TIMER0A_READ_BUFFER_VALUE() (T0ABUF)

/* Macro to Read value of Timer0B buffer */
#define DCT_TIMER0B_READ_BUFFER_VALUE() (T0BBUF)

/* Macro to Read value of Timer1A buffer */
#define DCT_TIMER1A_READ_BUFFER_VALUE() (T1ABUF)

/* Macro to Read value of Timer1B buffer */
#define DCT_TIMER1B_READ_BUFFER_VALUE() (T1BBUF)

/* Macro to Read value of Timer2A buffer */
#define DCT_TIMER2A_READ_BUFFER_VALUE() (T2ABUF)

/* Macro to Read value of Timer2B buffer */
#define DCT_TIMER2B_READ_BUFFER_VALUE() (T2BBUF)

/* Macro to Read value of Timer3A buffer */
#define DCT_TIMER3A_READ_BUFFER_VALUE() (T3ABUF)

/* Macro to Read value of Timer3B buffer */
#define DCT_TIMER3B_READ_BUFFER_VALUE() (T3BBUF)

/* Defines the Segments of DCT Modules */
typedef enum
{
    DCT_MODULE_SEGA = 0,
    DCT_MODULE_SEGB,
} DCT_MODULE_SEG_t;

/* Structure defining Prescale and Timer counter Match Value for DCT Module */
typedef struct
{
    uint32_t prescale;
    uint32_t match_value;
} DCT_TIMER_PARAMETERS_t ;

/* Structure defining the Configuration of DCT Modules */
typedef struct
{
    DCT_MODULE_SEG_t seg_name;
    DCT_TIMER_PARAMETERS_t timer_param;
} DCT_CONFIG_t;

/*************************************************************/
/* *** Mapped to Hardware *** */

/* Structure defining Dual Compare Timer Registers - mapped to the hardware */
typedef struct
{
    _IO_ uint32_t TCON;
    _IO_ uint32_t TL;
    _IO_ uint32_t TH;
} TIMER_DCT_t;

/*************************************************************/

/**
 * @brief API to Setup DCT Module.
 * 
 * @param module Constant pointer to DCT modules to access hardware registers. Pass DCT0, DCT1, DCT2, DCT3 as module parameters.
 * @param config DCT module configurations. Use DCT_CONFIG_t structure to set the required configurations.
 */
void DCT_SetTimer(TIMER_DCT_t *const module, DCT_CONFIG_t *config);

#endif /* _PRV_DCT_H_ */