/**
 * @file    prv_interrupt.h
 * @brief   Defines macros and ISR handler prototypes.
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_INTERRUPT_H_
#define _PRV_INTERRUPT_H_

#include "prv32.h"

#if PRV_FAMILY == PRV32
    /* Macro to Enable Global Interrupt */
    #define ENABLE_GLOBAL_INTERRUPT() (INTCONbits.GIE = 1)

    /* Macro to Disable Global Interrupt */
    #define DISABLE_GLOBAL_INTERRUPT() (INTCONbits.GIE = 0)
#elif PRV_FAMILY == PRVX3
    #include "prv_csr.h"

    /* Macro to Enable Global Interrupt */
    #define ENABLE_GLOBAL_INTERRUPT()                       \
        do {                                                \
            CSR_SET_BITS_IMM_MSTATUS(MSTATUS_MIE_BIT_MASK); \
            INTCONbits.GIE = 1;                             \
        } while (0)

    /* Macro to Disable Global Interrupt */
    #define DISABLE_GLOBAL_INTERRUPT()                      \
        do {                                                \
            INTCONbits.GIE = 0;                             \
            CSR_CLR_BITS_IMM_MSTATUS(MSTATUS_MIE_BIT_MASK); \
        } while (0)

    /* Macro to set/change interrupt vector modes */
    #define SET_INTERRUPT_VECTOR_MODE(mode)                                             \
        do {                                                                            \
            CSR_CLR_BITS_IMM_MTVEC(MTVEC_MODE_BIT_MASK);                                \
            CSR_SET_BITS_IMM_MTVEC(( uint32_t )MTVEC_MODE_BIT_MASK & ( uint32_t )mode); \
        } while (0)

    #define INTERRUPT_MODE_DIRECT    0
    #define INTERRUPT_MODE_VECTORED  1
    #define INTERRUPT_MODE_FAST_IRQ  2

    /* Macro to get current Interrupt ID */
    #define GET_INTERRUPT_ID() (IRQID)
#endif

/* Macro to Disable Interrupt0 */
#define DISABLE_INTERRUPT0() (INT0PRIO = 0)

/* Macro to Disable Interrupt1 */
#define DISABLE_INTERRUPT1() (INT1PRIO = 0)

/* Macro to Disable Interrupt2 */
#define DISABLE_INTERRUPT2() (INT2PRIO = 0)

/* Macro to Disable Interrupt3 */
#define DISABLE_INTERRUPT3() (INT3PRIO = 0)

/* Macro to Disable Interrupt4 */
#define DISABLE_INTERRUPT4() (INT4PRIO = 0)

/* Macro to Disable Interrupt5 */
#define DISABLE_INTERRUPT5() (INT5PRIO = 0)

/* Macro to Disable Interrupt6 */
#define DISABLE_INTERRUPT6() (INT6PRIO = 0)

/* Macro to Disable Interrupt7 */
#define DISABLE_INTERRUPT7() (INT7PRIO = 0)

/* Interrupt Handler prototypes */
void INT0_handler(void);
void INT1_handler(void);
void INT2_handler(void);
void INT3_handler(void);
void INT4_handler(void);
void INT5_handler(void);
void INT6_handler(void);
void INT7_handler(void);

#endif /* _PRV_INTERRUPT_H_ */
