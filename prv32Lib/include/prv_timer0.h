/**
 * @file    prv_timer0.h
 * @brief   Provides timer0 functions.
 * @version 0.1
 * @date    2023-07-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_TIMER0_H_
#define _PRV_TIMER0_H_

#include "prv32.h"

extern volatile uint32_t _sys_ticks;

/**
 * @brief Initialize System Tick Counter. Uses Timer0B and Interrupt6 to set up the Counter.
 * 
 * @param ticks Match value for the counter.
 */
void SysTick_Init(const uint16_t ticks);

/**
 * @brief Produces delay specified by delayamt with reference to the _sys_ticks.
 *        Blocking function.
 * 
 * @param delayamt Number of tick delays.
 */
void delay(uint32_t delayamt);

/**
 * @brief Configures Timer0A to produce delay in milliseconds.
 *
 * @param delayamt Delay amount in millisecond.
 */
void delayms(uint32_t delayamt);

#endif /* _PRV_TIMER0_H_ */