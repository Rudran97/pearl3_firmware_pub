/**
 * @file    prv_timer0.c
 * @brief   Provides timer0 functions.
 * @version 0.1
 * @date    2023-07-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "prv_timer0.h"
#include "prv_dct.h"
#include "prv_plic.h"

#ifdef PRV_ASSERT_CHECKS
    #include "prv_csr.h"
    #include "prv_assert.h"
#endif /* PRV_ASSERT_CHECKS */

volatile uint32_t _sys_ticks;

/**
 * @brief Initialize System Tick Counter. Uses Timer0B and Interrupt6 to set up the Counter.
 *
 * @param ticks Match value for the counter.
 */
void SysTick_Init(const uint16_t ticks)
{
    _sys_ticks = 0;

    DCT_CONFIG_t sys_timer_config = {
        .seg_name = DCT_MODULE_SEGB,
        .timer_param.match_value = ticks,
        .timer_param.prescale = 0
    };

    DCT_SetTimer(DCT0, &sys_timer_config);

    PLIC_INTERRUPT_CONFIG_t sys_timer_int_config = {
        .attach_interrupt_module = ATTACH_TIMER0B_TO_INTERRUPT,
        .set_priority = INTERRUPT_PRIORITY_MAXIMUM
    };

    Set_Interrupt6(&sys_timer_int_config);

    DCT_TIMER0B_START();
}

/**
 * @brief Produces delay specified by delayamt with reference to the _sys_ticks.
 *        Blocking function.
 *
 * @param delayamt Number of tick delays.
 */
void delay(uint32_t delayamt)
{
    uint32_t ref_ticks = _sys_ticks;

    #ifdef PRV_ASSERT_CHECKS
        /* Ensure Interrupts are enabled or else __sys_ticks will never be incremented */
        prvASSERT(INTCONbits.GIE && (csr_read_mstatus() & MSTATUS_MIE_BIT_MASK), PRV_ASSERT_NO_INTERRUPT);
    #endif /* PRV_ASSERT_CHECKS */

    while ((_sys_ticks - ref_ticks) < delayamt);
}

/**
 * @brief Configures Timer0A to produce delay in milliseconds.
 *
 * @param delayamt Delay amount in millisecond.
 */
void delayms(uint32_t delayamt)
{
    DCT_CONFIG_t timer_config = {
        .seg_name = DCT_MODULE_SEGA,
        .timer_param.match_value = TIMERms_const,
        .timer_param.prescale = 0
    };

    DCT_SetTimer(DCT0, &timer_config);

    while (delayamt)
    {
        DCT_TIMER0A_START();
        while (!TFREGbits.T0AF);
        DCT_TIMER0A_STOP();
        DCT_TIMER0A_CLEAR_FLAG();
        delayamt--;
    }
}

void INT6_handler(void)
{
    _sys_ticks++;
}