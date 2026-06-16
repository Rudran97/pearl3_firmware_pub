/**
 * @file    prv_assert.h
 * @brief   Provides basic on device assertions
 * @version 0.1
 * @date    2023-06-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _PRV_ASSERT_H_
#define _PRV_ASSERT_H_

#include "prv32.h"
#include "prv_interrupt.h"

/* Defines assert failures. */
typedef enum
{
    PRV_ASSERT_NOERR,
    PRV_ASSERT_NO_INTERRUPT,
    PRV_ASSERT_SERIAL_BUFFER_NON_ALIGNED,
} PRV_ASSERT_t;

/**
 * @brief Macro to check for assertion fails. Currently it Disables global interrupts and sits
 * in a loop after executing the failing line and sets the on-board LED to depending on the
 * failure type.
 * 
 * @param cond Assert condition.
 * @param type Value to shown on LED if assert fails. Use PRV_ASSERT_t enum to set the value.
 */
#define prvASSERT( cond, type )         \
    do {                                \
        if( ( cond ) == 0 )             \
        {                               \
            DISABLE_GLOBAL_INTERRUPT(); \
            LATD = type & 0xff;         \
            for(;;);                    \
        }                               \
    } while (0)

#endif /* _PRV_ASSERT_H_ */