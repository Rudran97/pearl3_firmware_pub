/**
 * @file    prv_hwreg.h
 * @brief   Defines hardware registers and bitfields for all peripherals.
 * @version 0.1
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_HWREG_H_
#define _PRV_HWREG_H_

#include "prv_io_map.h"

/*************************************************************/
/* Interrupt Registers */

/* Interrupt0 ISR Vector Address Register */
#define INT0ADDR (*((volatile uint32_t *)&_INT0_ISR_VECTOR_ADDR_))

/* INT0ADDR bitfield definition */
typedef union
{
    uint32_t INT0ADDRreg;
    struct
    {
        uint32_t ADDR : 16;
        uint32_t : 16;
    };
} INT0ADDRbits_t;
#define INT0ADDRbits (*((volatile INT0ADDRbits_t*)&_INT0_ISR_VECTOR_ADDR_))

#define _INT0ADDR_ADDR_POSN 0x0
#define _INT0ADDR_ADDR_MASK 0xffff

/* Interrupt1 ISR Vector Address Register */
#define INT1ADDR (*((volatile uint32_t *)&_INT1_ISR_VECTOR_ADDR_))

/* INT1ADDR bitfield definition */
typedef union
{
    uint32_t INT1ADDRreg;
    struct
    {
        uint32_t ADDR : 16;
        uint32_t : 16;
    };
} INT1ADDRbits_t;
#define INT1ADDRbits (*((volatile INT1ADDRbits_t*)&_INT1_ISR_VECTOR_ADDR_))

#define _INT1ADDR_ADDR_POSN 0x0
#define _INT1ADDR_ADDR_MASK 0xffff

/* Interrupt2 ISR Vector Address Register */
#define INT2ADDR (*((volatile uint32_t *)&_INT2_ISR_VECTOR_ADDR_))

/* INT2ADDR bitfield definition */
typedef union
{
    uint32_t INT2ADDRreg;
    struct
    {
        uint32_t ADDR : 16;
        uint32_t : 16;
    };
} INT2ADDRbits_t;
#define INT2ADDRbits (*((volatile INT2ADDRbits_t*)&_INT2_ISR_VECTOR_ADDR_))

#define _INT2ADDR_ADDR_POSN 0x0
#define _INT2ADDR_ADDR_MASK 0xffff

/* Interrupt3 ISR Vector Address Register */
#define INT3ADDR (*((volatile uint32_t *)&_INT3_ISR_VECTOR_ADDR_))

/* INT3ADDR bitfield definition */
typedef union
{
    uint32_t INT3ADDRreg;
    struct
    {
        uint32_t ADDR : 16;
        uint32_t : 16;
    };
} INT3ADDRbits_t;
#define INT3ADDRbits (*((volatile INT3ADDRbits_t*)&_INT3_ISR_VECTOR_ADDR_))

#define _INT3ADDR_ADDR_POSN 0x0
#define _INT3ADDR_ADDR_MASK 0xffff

/* Interrupt4 ISR Vector Address Register */
#define INT4ADDR (*((volatile uint32_t *)&_INT4_ISR_VECTOR_ADDR_))

/* INT4ADDR bitfield definition */
typedef union
{
    uint32_t INT4ADDRreg;
    struct
    {
        uint32_t ADDR : 16;
        uint32_t : 16;
    };
} INT4ADDRbits_t;
#define INT4ADDRbits (*((volatile INT4ADDRbits_t*)&_INT4_ISR_VECTOR_ADDR_))

#define _INT4ADDR_ADDR_POSN 0x0
#define _INT4ADDR_ADDR_MASK 0xffff

/* Interrupt5 ISR Vector Address Register */
#define INT5ADDR (*((volatile uint32_t *)&_INT5_ISR_VECTOR_ADDR_))

/* INT5ADDR bitfield definition */
typedef union
{
    uint32_t INT5ADDRreg;
    struct
    {
        uint32_t ADDR : 16;
        uint32_t : 16;
    };
} INT5ADDRbits_t;
#define INT5ADDRbits (*((volatile INT5ADDRbits_t*)&_INT5_ISR_VECTOR_ADDR_))

#define _INT5ADDR_ADDR_POSN 0x0
#define _INT5ADDR_ADDR_MASK 0xffff

/* Interrupt6 ISR Vector Address Register */
#define INT6ADDR (*((volatile uint32_t *)&_INT6_ISR_VECTOR_ADDR_))

/* INT6ADDR bitfield definition */
typedef union
{
    uint32_t INT6ADDRreg;
    struct
    {
        uint32_t ADDR : 16;
        uint32_t : 16;
    };
} INT6ADDRbits_t;
#define INT6ADDRbits (*((volatile INT6ADDRbits_t*)&_INT6_ISR_VECTOR_ADDR_))

#define _INT6ADDR_ADDR_POSN 0x0
#define _INT6ADDR_ADDR_MASK 0xffff

/* Interrupt7 ISR Vector Address Register */
#define INT7ADDR (*((volatile uint32_t *)&_INT7_ISR_VECTOR_ADDR_))

/* INT7ADDR bitfield definition */
typedef union
{
    uint32_t INT7ADDRreg;
    struct
    {
        uint32_t ADDR : 16;
        uint32_t : 16;
    };
} INT7ADDRbits_t;
#define INT7ADDRbits (*((volatile INT7ADDRbits_t*)&_INT7_ISR_VECTOR_ADDR_))

#define _INT7ADDR_ADDR_POSN 0x0
#define _INT7ADDR_ADDR_MASK 0xffff

/* Interrupt0 Priority Register */
#define INT0PRIO (*((volatile uint32_t *)&_INT0_PRIORITY_))

/* INT0PRIO bitfield definition */
typedef union
{
    uint32_t INT0PRIOreg;
    struct
    {
        uint32_t PRIO : 3;
        uint32_t : 29;
    };
} INT0PRIObits_t;
#define INT0PRIObits (*((volatile INT0PRIObits_t*)&_INT0_PRIORITY_))

#define _INT0PRIO_PRIO_POSN 0x0
#define _INT0PRIO_PRIO_MASK 0x7

/* Interrupt1 Priority Register */
#define INT1PRIO (*((volatile uint32_t *)&_INT1_PRIORITY_))

/* INT1PRIO bitfield definition */
typedef union
{
    uint32_t INT1PRIOreg;
    struct
    {
        uint32_t PRIO : 3;
        uint32_t : 29;
    };
} INT1PRIObits_t;
#define INT1PRIObits (*((volatile INT1PRIObits_t*)&_INT1_PRIORITY_))

#define _INT1PRIO_PRIO_POSN 0x0
#define _INT1PRIO_PRIO_MASK 0x7

/* Interrupt2 Priority Register */
#define INT2PRIO (*((volatile uint32_t *)&_INT2_PRIORITY_))

/* INT2PRIO bitfield definition */
typedef union
{
    uint32_t INT2PRIOreg;
    struct
    {
        uint32_t PRIO : 3;
        uint32_t : 29;
    };
} INT2PRIObits_t;
#define INT2PRIObits (*((volatile INT2PRIObits_t*)&_INT2_PRIORITY_))

#define _INT2PRIO_PRIO_POSN 0x0
#define _INT2PRIO_PRIO_MASK 0x7

/* Interrupt3 Priority Register */
#define INT3PRIO (*((volatile uint32_t *)&_INT3_PRIORITY_))

/* INT3PRIO bitfield definition */
typedef union
{
    uint32_t INT3PRIOreg;
    struct
    {
        uint32_t PRIO : 3;
        uint32_t : 29;
    };
} INT3PRIObits_t;
#define INT3PRIObits (*((volatile INT3PRIObits_t*)&_INT3_PRIORITY_))

#define _INT3PRIO_PRIO_POSN 0x0
#define _INT3PRIO_PRIO_MASK 0x7

/* Interrupt4 Priority Register */
#define INT4PRIO (*((volatile uint32_t *)&_INT4_PRIORITY_))

/* INT4PRIO bitfield definition */
typedef union
{
    uint32_t INT4PRIOreg;
    struct
    {
        uint32_t PRIO : 3;
        uint32_t : 29;
    };
} INT4PRIObits_t;
#define INT4PRIObits (*((volatile INT4PRIObits_t*)&_INT4_PRIORITY_))

#define _INT4PRIO_PRIO_POSN 0x0
#define _INT4PRIO_PRIO_MASK 0x7

/* Interrupt5 Priority Register */
#define INT5PRIO (*((volatile uint32_t *)&_INT5_PRIORITY_))

/* INT5PRIO bitfield definition */
typedef union
{
    uint32_t INT5PRIOreg;
    struct
    {
        uint32_t PRIO : 3;
        uint32_t : 29;
    };
} INT5PRIObits_t;
#define INT5PRIObits (*((volatile INT5PRIObits_t*)&_INT5_PRIORITY_))

#define _INT5PRIO_PRIO_POSN 0x0
#define _INT5PRIO_PRIO_MASK 0x7

/* Interrupt6 Priority Register */
#define INT6PRIO (*((volatile uint32_t *)&_INT6_PRIORITY_))

/* INT6PRIO bitfield definition */
typedef union
{
    uint32_t INT6PRIOreg;
    struct
    {
        uint32_t PRIO : 3;
        uint32_t : 29;
    };
} INT6PRIObits_t;
#define INT6PRIObits (*((volatile INT6PRIObits_t*)&_INT6_PRIORITY_))

#define _INT6PRIO_PRIO_POSN 0x0
#define _INT6PRIO_PRIO_MASK 0x7

/* Interrupt7 Priority Register */
#define INT7PRIO (*((volatile uint32_t *)&_INT7_PRIORITY_))

/* INT7PRIO bitfield definition */
typedef union
{
    uint32_t INT7PRIOreg;
    struct
    {
        uint32_t PRIO : 3;
        uint32_t : 29;
    };
} INT7PRIObits_t;
#define INT7PRIObits (*((volatile INT7PRIObits_t*)&_INT7_PRIORITY_))

#define _INT7PRIO_PRIO_POSN 0x0
#define _INT7PRIO_PRIO_MASK 0x7

#if PRV_FAMILY == PRVX3
    /* Interrupt Config Register */
    #define INTCON (*((volatile uint32_t *)&_INT_CONFIG_))

    /* INTCON bitfield definition */
    typedef union
    {
        uint32_t INTCONreg;
        struct
        {
            uint8_t GIE : 1;
            uint8_t : 1;
            uint8_t EXTI: 1;
            uint32_t : 29;
        };
    } INTCONbits_t;
    #define INTCONbits (*((volatile INTCONbits_t*)&_INT_CONFIG_))

    #define _INTCON_GIE_POSN 0x0
    #define _INTCON_GIE_MASK 0x1
    #define _INTCON_EXTI_POSN 0x2
    #define _INTCON_EXTI_MASK 0x4

    /* Interrupt ID Register */
    #define IRQID (*((volatile uint32_t *)&_INT_IRQ_ID_))

    /* IRQID bitfield definition */
    typedef union
    {
        uint32_t IRQIDreg;
        struct
        {
            uint32_t ID : 16;
            uint32_t : 16;
        };
    } IRQIDbits_t;
    #define IRQIDbits (*((volatile IRQIDbits_t*)&_INT_IRQ_ID_))

    #define _IRQID_ADDR_POSN 0x0
    #define _IRQID_ADDR_MASK 0xffff

    /* Note: Registers INTSRC, INTCLR and INTSTAT are read-only registers.
     * Writing to these registers have no effects.
     */

    /* Interrupt Source Register */
    #define INTSRC (*((volatile uint32_t *)&_INT_SRC_))

    /* INTSRC bitfield definition */
    typedef union
    {
        uint32_t INTSRCreg;
        struct
        {
            uint32_t INT0 : 1;
            uint32_t INT1 : 1;
            uint32_t INT2 : 1;
            uint32_t INT3 : 1;
            uint32_t INT4 : 1;
            uint32_t INT5 : 1;
            uint32_t INT6 : 1;
            uint32_t INT7 : 1;
            uint32_t : 24;
        };
    } INTSRCbits_t;
    #define INTSRCbits (*((volatile INTSRCbits_t*)&_INT_SRC_))

    #define _INTSRC_INT0_POSN 0x0
    #define _INTSRC_INT0_MASK 0x1
    #define _INTSRC_INT1_POSN 0x1
    #define _INTSRC_INT1_MASK 0x2
    #define _INTSRC_INT2_POSN 0x2
    #define _INTSRC_INT2_MASK 0x4
    #define _INTSRC_INT3_POSN 0x3
    #define _INTSRC_INT3_MASK 0x8
    #define _INTSRC_INT4_POSN 0x4
    #define _INTSRC_INT4_MASK 0x10
    #define _INTSRC_INT5_POSN 0x5
    #define _INTSRC_INT5_MASK 0x20
    #define _INTSRC_INT6_POSN 0x6
    #define _INTSRC_INT6_MASK 0x40
    #define _INTSRC_INT7_POSN 0x7
    #define _INTSRC_INT7_MASK 0x80

    /* Interrupt Clear Register */
    #define INTCLR (*((volatile uint32_t *)&_INT_CLR_))

    /* INTCLR bitfield definition */
    typedef union
    {
        uint32_t INTCLRreg;
        struct
        {
            uint32_t INT0 : 1;
            uint32_t INT1 : 1;
            uint32_t INT2 : 1;
            uint32_t INT3 : 1;
            uint32_t INT4 : 1;
            uint32_t INT5 : 1;
            uint32_t INT6 : 1;
            uint32_t INT7 : 1;
            uint32_t : 24;
        };
    } INTCLRbits_t;
    #define INTCLRbits (*((volatile INTCLRbits_t*)&_INT_CLR_))

    #define _INTCLR_INT0_POSN 0x0
    #define _INTCLR_INT0_MASK 0x1
    #define _INTCLR_INT1_POSN 0x1
    #define _INTCLR_INT1_MASK 0x2
    #define _INTCLR_INT2_POSN 0x2
    #define _INTCLR_INT2_MASK 0x4
    #define _INTCLR_INT3_POSN 0x3
    #define _INTCLR_INT3_MASK 0x8
    #define _INTCLR_INT4_POSN 0x4
    #define _INTCLR_INT4_MASK 0x10
    #define _INTCLR_INT5_POSN 0x5
    #define _INTCLR_INT5_MASK 0x20
    #define _INTCLR_INT6_POSN 0x6
    #define _INTCLR_INT6_MASK 0x40
    #define _INTCLR_INT7_POSN 0x7
    #define _INTCLR_INT7_MASK 0x80

    /* Interrupt Status Register */
    #define INTSTAT (*((volatile uint32_t *)&_INT_STAT_))

    /* INTSTAT biffield definition */
    typedef union
    {
        uint32_t INTSTATreg;
        struct
        {
            uint32_t IRQ : 1;
            uint32_t : 31;
        };
    } INTSTATbits_t;
    #define INTSTATbits (*((volatile INTSTATbits_t*)&_INT_STAT_))

    #define _INTSTAT_IRQ_POSN 0x0
    #define _INTSTAT_IRQ_MASK 0x1
#else
    /* Interrupt Config Register */
    #define INTCON (*((volatile uint32_t *)&_INT_CONFIG_))

    /* INTCON bitfield definition */
    typedef union
    {
        uint32_t INTCONreg;
        struct
        {
            uint8_t GIE : 1;
            uint8_t GIC : 1;
            uint32_t : 30;
        };
    } INTCONbits_t;
    #define INTCONbits (*((volatile INTCONbits_t*)&_INT_CONFIG_))

    #define _INTCON_GIE_POSN 0x0
    #define _INTCON_GIE_MASK 0x1
    #define _INTCON_GIC_POSN 0x1
    #define _INTCON_GIC_MASK 0x2

    /* Interrupt Return Register */
    #define INTRET (*((volatile uint32_t *)&_INT_RETURN_ADDR_))

    /* INTRET bitfield definition */
    typedef union
    {
        uint32_t INTRETreg;
        struct
        {
            uint32_t ADDR : 16;
            uint32_t : 16;
        };
    } INTRETbits_t;
    #define INTRETbits (*((volatile INTRETbits_t*)&_INT_RETURN_ADDR_))

    #define _INTRET_ADDR_POSN 0x0
    #define _INTRET_ADDR_MASK 0xffff
#endif

/*************************************************************/
/* GPIO Registers */

/* Data Direction Register for PORTA */
#define DDRA (*((volatile uint32_t *)&_DDRA_))

/* DDRA bitfield definition */
typedef union
{
    uint32_t DDRAreg;
    struct
    {
        uint8_t DDRA0 : 1;
        uint8_t DDRA1 : 1;
        uint8_t DDRA2 : 1;
        uint8_t DDRA3 : 1;
        uint8_t DDRA4 : 1;
        uint8_t DDRA5 : 1;
        uint8_t DDRA6 : 1;
        uint8_t DDRA7 : 1;
        uint8_t DDRA8 : 1;
        uint8_t DDRA9 : 1;
        uint8_t DDRA10 : 1;
        uint8_t DDRA11 : 1;
        uint8_t DDRA12 : 1;
        uint8_t DDRA13 : 1;
        uint8_t DDRA14 : 1;
        uint8_t DDRA15 : 1;
        uint32_t : 16;
    };
} DDRAbits_t;
#define DDRAbits (*((volatile DDRAbits_t *)&_DDRA_))

#define _DDRA_DDRA0_POSN 0x0
#define _DDRA_DDRA0_MASK 0x1
#define _DDRA_DDRA1_POSN 0x1
#define _DDRA_DDRA1_MASK 0x2
#define _DDRA_DDRA2_POSN 0x2
#define _DDRA_DDRA2_MASK 0x4
#define _DDRA_DDRA3_POSN 0x3
#define _DDRA_DDRA3_MASK 0x8
#define _DDRA_DDRA4_POSN 0x4
#define _DDRA_DDRA4_MASK 0x10
#define _DDRA_DDRA5_POSN 0x5
#define _DDRA_DDRA5_MASK 0x20
#define _DDRA_DDRA6_POSN 0x6
#define _DDRA_DDRA6_MASK 0x40
#define _DDRA_DDRA7_POSN 0x7
#define _DDRA_DDRA7_MASK 0x80
#define _DDRA_DDRA8_POSN 0x8
#define _DDRA_DDRA8_MASK 0x100
#define _DDRA_DDRA9_POSN 0x9
#define _DDRA_DDRA9_MASK 0x200
#define _DDRA_DDRA10_POSN 0xa
#define _DDRA_DDRA10_MASK 0x400
#define _DDRA_DDRA11_POSN 0xb
#define _DDRA_DDRA11_MASK 0x800
#define _DDRA_DDRA12_POSN 0xc
#define _DDRA_DDRA12_MASK 0x1000
#define _DDRA_DDRA13_POSN 0xd
#define _DDRA_DDRA13_MASK 0x2000
#define _DDRA_DDRA14_POSN 0xe
#define _DDRA_DDRA14_MASK 0x4000
#define _DDRA_DDRA15_POSN 0xf
#define _DDRA_DDRA15_MASK 0x8000

/* Data Input Register for PORTA */
#define PORTA (*((volatile uint32_t *)&_PORTA_))

/* PORTA bitfield definition */
typedef union
{
    uint32_t PORTAreg;
    struct
    {
        uint8_t PORTA0 : 1;
        uint8_t PORTA1 : 1;
        uint8_t PORTA2 : 1;
        uint8_t PORTA3 : 1;
        uint8_t PORTA4 : 1;
        uint8_t PORTA5 : 1;
        uint8_t PORTA6 : 1;
        uint8_t PORTA7 : 1;
        uint8_t PORTA8 : 1;
        uint8_t PORTA9 : 1;
        uint8_t PORTA10 : 1;
        uint8_t PORTA11 : 1;
        uint8_t PORTA12 : 1;
        uint8_t PORTA13 : 1;
        uint8_t PORTA14 : 1;
        uint8_t PORTA15 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint8_t RA0 : 1;
        uint8_t RA1 : 1;
        uint8_t RA2 : 1;
        uint8_t RA3 : 1;
        uint8_t RA4 : 1;
        uint8_t RA5 : 1;
        uint8_t RA6 : 1;
        uint8_t RA7 : 1;
        uint8_t RA8 : 1;
        uint8_t RA9 : 1;
        uint8_t RA10 : 1;
        uint8_t RA11 : 1;
        uint8_t RA12 : 1;
        uint8_t RA13 : 1;
        uint8_t RA14 : 1;
        uint8_t RA15 : 1;
        uint32_t : 16;
    };
} PORTAbits_t;
#define PORTAbits (*((volatile PORTAbits_t *)&_PORTA_))

#define _PORTA_PORTA0_POSN 0x0
#define _PORTA_PORTA0_MASK 0x1
#define _PORTA_PORTA1_POSN 0x1
#define _PORTA_PORTA1_MASK 0x2
#define _PORTA_PORTA2_POSN 0x2
#define _PORTA_PORTA2_MASK 0x4
#define _PORTA_PORTA3_POSN 0x3
#define _PORTA_PORTA3_MASK 0x8
#define _PORTA_PORTA4_POSN 0x4
#define _PORTA_PORTA4_MASK 0x10
#define _PORTA_PORTA5_POSN 0x5
#define _PORTA_PORTA5_MASK 0x20
#define _PORTA_PORTA6_POSN 0x6
#define _PORTA_PORTA6_MASK 0x40
#define _PORTA_PORTA7_POSN 0x7
#define _PORTA_PORTA7_MASK 0x80
#define _PORTA_PORTA8_POSN 0x8
#define _PORTA_PORTA8_MASK 0x100
#define _PORTA_PORTA9_POSN 0x9
#define _PORTA_PORTA9_MASK 0x200
#define _PORTA_PORTA10_POSN 0xa
#define _PORTA_PORTA10_MASK 0x400
#define _PORTA_PORTA11_POSN 0xb
#define _PORTA_PORTA11_MASK 0x800
#define _PORTA_PORTA12_POSN 0xc
#define _PORTA_PORTA12_MASK 0x1000
#define _PORTA_PORTA13_POSN 0xd
#define _PORTA_PORTA13_MASK 0x2000
#define _PORTA_PORTA14_POSN 0xe
#define _PORTA_PORTA14_MASK 0x4000
#define _PORTA_PORTA15_POSN 0xf
#define _PORTA_PORTA15_MASK 0x8000
#define _PORTA_RA0_POSN 0x0
#define _PORTA_RA0_MASK 0x1
#define _PORTA_RA1_POSN 0x1
#define _PORTA_RA1_MASK 0x2
#define _PORTA_RA2_POSN 0x2
#define _PORTA_RA2_MASK 0x4
#define _PORTA_RA3_POSN 0x3
#define _PORTA_RA3_MASK 0x8
#define _PORTA_RA4_POSN 0x4
#define _PORTA_RA4_MASK 0x10
#define _PORTA_RA5_POSN 0x5
#define _PORTA_RA5_MASK 0x20
#define _PORTA_RA6_POSN 0x6
#define _PORTA_RA6_MASK 0x40
#define _PORTA_RA7_POSN 0x7
#define _PORTA_RA7_MASK 0x80
#define _PORTA_RA8_POSN 0x8
#define _PORTA_RA8_MASK 0x100
#define _PORTA_RA9_POSN 0x9
#define _PORTA_RA9_MASK 0x200
#define _PORTA_RA10_POSN 0xa
#define _PORTA_RA10_MASK 0x400
#define _PORTA_RA11_POSN 0xb
#define _PORTA_RA11_MASK 0x800
#define _PORTA_RA12_POSN 0xc
#define _PORTA_RA12_MASK 0x1000
#define _PORTA_RA13_POSN 0xd
#define _PORTA_RA13_MASK 0x2000
#define _PORTA_RA14_POSN 0xe
#define _PORTA_RA14_MASK 0x4000
#define _PORTA_RA15_POSN 0xf
#define _PORTA_RA15_MASK 0x8000

/* Data Output Register for PORTA */
#define LATA (*((volatile uint32_t *)&_LATA_))

/* LATA bitfield definition */
typedef union
{
    uint32_t LATAreg;
    struct
    {
        uint8_t LATA0 : 1;
        uint8_t LATA1 : 1;
        uint8_t LATA2 : 1;
        uint8_t LATA3 : 1;
        uint8_t LATA4 : 1;
        uint8_t LATA5 : 1;
        uint8_t LATA6 : 1;
        uint8_t LATA7 : 1;
        uint8_t LATA8 : 1;
        uint8_t LATA9 : 1;
        uint8_t LATA10 : 1;
        uint8_t LATA11 : 1;
        uint8_t LATA12 : 1;
        uint8_t LATA13 : 1;
        uint8_t LATA14 : 1;
        uint8_t LATA15 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint8_t LA0 : 1;
        uint8_t LA1 : 1;
        uint8_t LA2 : 1;
        uint8_t LA3 : 1;
        uint8_t LA4 : 1;
        uint8_t LA5 : 1;
        uint8_t LA6 : 1;
        uint8_t LA7 : 1;
        uint8_t LA8 : 1;
        uint8_t LA9 : 1;
        uint8_t LA10 : 1;
        uint8_t LA11 : 1;
        uint8_t LA12 : 1;
        uint8_t LA13 : 1;
        uint8_t LA14 : 1;
        uint8_t LA15 : 1;
        uint32_t : 16;
    };
} LATAbits_t;
#define LATAbits (*((volatile LATAbits_t *)&_LATA_))

#define _LATA_LATA0_POSN 0x0
#define _LATA_LATA0_MASK 0x1
#define _LATA_LATA1_POSN 0x1
#define _LATA_LATA1_MASK 0x2
#define _LATA_LATA2_POSN 0x2
#define _LATA_LATA2_MASK 0x4
#define _LATA_LATA3_POSN 0x3
#define _LATA_LATA3_MASK 0x8
#define _LATA_LATA4_POSN 0x4
#define _LATA_LATA4_MASK 0x10
#define _LATA_LATA5_POSN 0x5
#define _LATA_LATA5_MASK 0x20
#define _LATA_LATA6_POSN 0x6
#define _LATA_LATA6_MASK 0x40
#define _LATA_LATA7_POSN 0x7
#define _LATA_LATA7_MASK 0x80
#define _LATA_LATA8_POSN 0x8
#define _LATA_LATA8_MASK 0x100
#define _LATA_LATA9_POSN 0x9
#define _LATA_LATA9_MASK 0x200
#define _LATA_LATA10_POSN 0xa
#define _LATA_LATA10_MASK 0x400
#define _LATA_LATA11_POSN 0xb
#define _LATA_LATA11_MASK 0x800
#define _LATA_LATA12_POSN 0xc
#define _LATA_LATA12_MASK 0x1000
#define _LATA_LATA13_POSN 0xd
#define _LATA_LATA13_MASK 0x2000
#define _LATA_LATA14_POSN 0xe
#define _LATA_LATA14_MASK 0x4000
#define _LATA_LATA15_POSN 0xf
#define _LATA_LATA15_MASK 0x8000
#define _LATA_LA0_POSN 0x0
#define _LATA_LA0_MASK 0x1
#define _LATA_LA1_POSN 0x1
#define _LATA_LA1_MASK 0x2
#define _LATA_LA2_POSN 0x2
#define _LATA_LA2_MASK 0x4
#define _LATA_LA3_POSN 0x3
#define _LATA_LA3_MASK 0x8
#define _LATA_LA4_POSN 0x4
#define _LATA_LA4_MASK 0x10
#define _LATA_LA5_POSN 0x5
#define _LATA_LA5_MASK 0x20
#define _LATA_LA6_POSN 0x6
#define _LATA_LA6_MASK 0x40
#define _LATA_LA7_POSN 0x7
#define _LATA_LA7_MASK 0x80
#define _LATA_LA8_POSN 0x8
#define _LATA_LA8_MASK 0x100
#define _LATA_LA9_POSN 0x9
#define _LATA_LA9_MASK 0x200
#define _LATA_LA10_POSN 0xa
#define _LATA_LA10_MASK 0x400
#define _LATA_LA11_POSN 0xb
#define _LATA_LA11_MASK 0x800
#define _LATA_LA12_POSN 0xc
#define _LATA_LA12_MASK 0x1000
#define _LATA_LA13_POSN 0xd
#define _LATA_LA13_MASK 0x2000
#define _LATA_LA14_POSN 0xe
#define _LATA_LA14_MASK 0x4000
#define _LATA_LA15_POSN 0xf
#define _LATA_LA15_MASK 0x8000

/* Data Direction Register for PORTB */
#define DDRB (*((volatile uint32_t *)&_DDRB_))

/* DDRB bitfield definition */
typedef union
{
    uint32_t DDRBreg;
    struct
    {
        uint8_t DDRB0 : 1;
        uint8_t DDRB1 : 1;
        uint8_t DDRB2 : 1;
        uint8_t DDRB3 : 1;
        uint8_t DDRB4 : 1;
        uint8_t DDRB5 : 1;
        uint8_t DDRB6 : 1;
        uint8_t DDRB7 : 1;
        uint8_t DDRB8 : 1;
        uint8_t DDRB9 : 1;
        uint8_t DDRB10 : 1;
        uint8_t DDRB11 : 1;
        uint8_t DDRB12 : 1;
        uint8_t DDRB13 : 1;
        uint8_t DDRB14 : 1;
        uint8_t DDRB15 : 1;
        uint32_t : 16;
    };
} DDRBbits_t;
#define DDRBbits (*((volatile DDRBbits_t *)&_DDRB_))

#define _DDRB_DDRB0_POSN 0x0
#define _DDRB_DDRB0_MASK 0x1
#define _DDRB_DDRB1_POSN 0x1
#define _DDRB_DDRB1_MASK 0x2
#define _DDRB_DDRB2_POSN 0x2
#define _DDRB_DDRB2_MASK 0x4
#define _DDRB_DDRB3_POSN 0x3
#define _DDRB_DDRB3_MASK 0x8
#define _DDRB_DDRB4_POSN 0x4
#define _DDRB_DDRB4_MASK 0x10
#define _DDRB_DDRB5_POSN 0x5
#define _DDRB_DDRB5_MASK 0x20
#define _DDRB_DDRB6_POSN 0x6
#define _DDRB_DDRB6_MASK 0x40
#define _DDRB_DDRB7_POSN 0x7
#define _DDRB_DDRB7_MASK 0x80
#define _DDRB_DDRB8_POSN 0x8
#define _DDRB_DDRB8_MASK 0x100
#define _DDRB_DDRB9_POSN 0x9
#define _DDRB_DDRB9_MASK 0x200
#define _DDRB_DDRB10_POSN 0xa
#define _DDRB_DDRB10_MASK 0x400
#define _DDRB_DDRB11_POSN 0xb
#define _DDRB_DDRB11_MASK 0x800
#define _DDRB_DDRB12_POSN 0xc
#define _DDRB_DDRB12_MASK 0x1000
#define _DDRB_DDRB13_POSN 0xd
#define _DDRB_DDRB13_MASK 0x2000
#define _DDRB_DDRB14_POSN 0xe
#define _DDRB_DDRB14_MASK 0x4000
#define _DDRB_DDRB15_POSN 0xf
#define _DDRB_DDRB15_MASK 0x8000

/* Data Input Register for PORTB */
#define PORTB (*((volatile uint32_t *)&_PORTB_))

/* PORTB bitfield definition */
typedef union
{
    uint32_t PORTBreg;
    struct
    {
        uint8_t PORTB0 : 1;
        uint8_t PORTB1 : 1;
        uint8_t PORTB2 : 1;
        uint8_t PORTB3 : 1;
        uint8_t PORTB4 : 1;
        uint8_t PORTB5 : 1;
        uint8_t PORTB6 : 1;
        uint8_t PORTB7 : 1;
        uint8_t PORTB8 : 1;
        uint8_t PORTB9 : 1;
        uint8_t PORTB10 : 1;
        uint8_t PORTB11 : 1;
        uint8_t PORTB12 : 1;
        uint8_t PORTB13 : 1;
        uint8_t PORTB14 : 1;
        uint8_t PORTB15 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint8_t RB0 : 1;
        uint8_t RB1 : 1;
        uint8_t RB2 : 1;
        uint8_t RB3 : 1;
        uint8_t RB4 : 1;
        uint8_t RB5 : 1;
        uint8_t RB6 : 1;
        uint8_t RB7 : 1;
        uint8_t RB8 : 1;
        uint8_t RB9 : 1;
        uint8_t RB10 : 1;
        uint8_t RB11 : 1;
        uint8_t RB12 : 1;
        uint8_t RB13 : 1;
        uint8_t RB14 : 1;
        uint8_t RB15 : 1;
        uint32_t : 16;
    };
} PORTBbits_t;
#define PORTBbits (*((volatile PORTBbits_t *)&_PORTB_))

#define _PORTB_PORTB0_POSN 0x0
#define _PORTB_PORTB0_MASK 0x1
#define _PORTB_PORTB1_POSN 0x1
#define _PORTB_PORTB1_MASK 0x2
#define _PORTB_PORTB2_POSN 0x2
#define _PORTB_PORTB2_MASK 0x4
#define _PORTB_PORTB3_POSN 0x3
#define _PORTB_PORTB3_MASK 0x8
#define _PORTB_PORTB4_POSN 0x4
#define _PORTB_PORTB4_MASK 0x10
#define _PORTB_PORTB5_POSN 0x5
#define _PORTB_PORTB5_MASK 0x20
#define _PORTB_PORTB6_POSN 0x6
#define _PORTB_PORTB6_MASK 0x40
#define _PORTB_PORTB7_POSN 0x7
#define _PORTB_PORTB7_MASK 0x80
#define _PORTB_PORTB8_POSN 0x8
#define _PORTB_PORTB8_MASK 0x100
#define _PORTB_PORTB9_POSN 0x9
#define _PORTB_PORTB9_MASK 0x200
#define _PORTB_PORTB10_POSN 0xa
#define _PORTB_PORTB10_MASK 0x400
#define _PORTB_PORTB11_POSN 0xb
#define _PORTB_PORTB11_MASK 0x800
#define _PORTB_PORTB12_POSN 0xc
#define _PORTB_PORTB12_MASK 0x1000
#define _PORTB_PORTB13_POSN 0xd
#define _PORTB_PORTB13_MASK 0x2000
#define _PORTB_PORTB14_POSN 0xe
#define _PORTB_PORTB14_MASK 0x4000
#define _PORTB_PORTB15_POSN 0xf
#define _PORTB_PORTB15_MASK 0x8000
#define _PORTB_RB0_POSN 0x0
#define _PORTB_RB0_MASK 0x1
#define _PORTB_RB1_POSN 0x1
#define _PORTB_RB1_MASK 0x2
#define _PORTB_RB2_POSN 0x2
#define _PORTB_RB2_MASK 0x4
#define _PORTB_RB3_POSN 0x3
#define _PORTB_RB3_MASK 0x8
#define _PORTB_RB4_POSN 0x4
#define _PORTB_RB4_MASK 0x10
#define _PORTB_RB5_POSN 0x5
#define _PORTB_RB5_MASK 0x20
#define _PORTB_RB6_POSN 0x6
#define _PORTB_RB6_MASK 0x40
#define _PORTB_RB7_POSN 0x7
#define _PORTB_RB7_MASK 0x80
#define _PORTB_RB8_POSN 0x8
#define _PORTB_RB8_MASK 0x100
#define _PORTB_RB9_POSN 0x9
#define _PORTB_RB9_MASK 0x200
#define _PORTB_RB10_POSN 0xa
#define _PORTB_RB10_MASK 0x400
#define _PORTB_RB11_POSN 0xb
#define _PORTB_RB11_MASK 0x800
#define _PORTB_RB12_POSN 0xc
#define _PORTB_RB12_MASK 0x1000
#define _PORTB_RB13_POSN 0xd
#define _PORTB_RB13_MASK 0x2000
#define _PORTB_RB14_POSN 0xe
#define _PORTB_RB14_MASK 0x4000
#define _PORTB_RB15_POSN 0xf
#define _PORTB_RB15_MASK 0x8000

/* Data Output Register for PORTB */
#define LATB (*((volatile uint32_t *)&_LATB_))

/* LATB bitfield definition */
typedef union
{
    uint32_t LATBreg;
    struct
    {
        uint8_t LATB0 : 1;
        uint8_t LATB1 : 1;
        uint8_t LATB2 : 1;
        uint8_t LATB3 : 1;
        uint8_t LATB4 : 1;
        uint8_t LATB5 : 1;
        uint8_t LATB6 : 1;
        uint8_t LATB7 : 1;
        uint8_t LATB8 : 1;
        uint8_t LATB9 : 1;
        uint8_t LATB10 : 1;
        uint8_t LATB11 : 1;
        uint8_t LATB12 : 1;
        uint8_t LATB13 : 1;
        uint8_t LATB14 : 1;
        uint8_t LATB15 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint8_t LB0 : 1;
        uint8_t LB1 : 1;
        uint8_t LB2 : 1;
        uint8_t LB3 : 1;
        uint8_t LB4 : 1;
        uint8_t LB5 : 1;
        uint8_t LB6 : 1;
        uint8_t LB7 : 1;
        uint8_t LB8 : 1;
        uint8_t LB9 : 1;
        uint8_t LB10 : 1;
        uint8_t LB11 : 1;
        uint8_t LB12 : 1;
        uint8_t LB13 : 1;
        uint8_t LB14 : 1;
        uint8_t LB15 : 1;
        uint32_t : 16;
    };
} LATBbits_t;
#define LATBbits (*((volatile LATBbits_t *)&_LATB_))

#define _LATB_LATB0_POSN 0x0
#define _LATB_LATB0_MASK 0x1
#define _LATB_LATB1_POSN 0x1
#define _LATB_LATB1_MASK 0x2
#define _LATB_LATB2_POSN 0x2
#define _LATB_LATB2_MASK 0x4
#define _LATB_LATB3_POSN 0x3
#define _LATB_LATB3_MASK 0x8
#define _LATB_LATB4_POSN 0x4
#define _LATB_LATB4_MASK 0x10
#define _LATB_LATB5_POSN 0x5
#define _LATB_LATB5_MASK 0x20
#define _LATB_LATB6_POSN 0x6
#define _LATB_LATB6_MASK 0x40
#define _LATB_LATB7_POSN 0x7
#define _LATB_LATB7_MASK 0x80
#define _LATB_LATB8_POSN 0x8
#define _LATB_LATB8_MASK 0x100
#define _LATB_LATB9_POSN 0x9
#define _LATB_LATB9_MASK 0x200
#define _LATB_LATB10_POSN 0xa
#define _LATB_LATB10_MASK 0x400
#define _LATB_LATB11_POSN 0xb
#define _LATB_LATB11_MASK 0x800
#define _LATB_LATB12_POSN 0xc
#define _LATB_LATB12_MASK 0x1000
#define _LATB_LATB13_POSN 0xd
#define _LATB_LATB13_MASK 0x2000
#define _LATB_LATB14_POSN 0xe
#define _LATB_LATB14_MASK 0x4000
#define _LATB_LATB15_POSN 0xf
#define _LATB_LATB15_MASK 0x8000
#define _LATB_LB0_POSN 0x0
#define _LATB_LB0_MASK 0x1
#define _LATB_LB1_POSN 0x1
#define _LATB_LB1_MASK 0x2
#define _LATB_LB2_POSN 0x2
#define _LATB_LB2_MASK 0x4
#define _LATB_LB3_POSN 0x3
#define _LATB_LB3_MASK 0x8
#define _LATB_LB4_POSN 0x4
#define _LATB_LB4_MASK 0x10
#define _LATB_LB5_POSN 0x5
#define _LATB_LB5_MASK 0x20
#define _LATB_LB6_POSN 0x6
#define _LATB_LB6_MASK 0x40
#define _LATB_LB7_POSN 0x7
#define _LATB_LB7_MASK 0x80
#define _LATB_LB8_POSN 0x8
#define _LATB_LB8_MASK 0x100
#define _LATB_LB9_POSN 0x9
#define _LATB_LB9_MASK 0x200
#define _LATB_LB10_POSN 0xa
#define _LATB_LB10_MASK 0x400
#define _LATB_LB11_POSN 0xb
#define _LATB_LB11_MASK 0x800
#define _LATB_LB12_POSN 0xc
#define _LATB_LB12_MASK 0x1000
#define _LATB_LB13_POSN 0xd
#define _LATB_LB13_MASK 0x2000
#define _LATB_LB14_POSN 0xe
#define _LATB_LB14_MASK 0x4000
#define _LATB_LB15_POSN 0xf
#define _LATB_LB15_MASK 0x8000

/* Data Output Regsiter for On board LEDs */
#define LATD (*((volatile uint32_t *)&_LATD_))
/* LATD bitfield definition */
typedef union
{
    uint32_t LATDreg;
    struct
    {
        uint8_t LATD0 : 1;
        uint8_t LATD1 : 1;
        uint8_t LATD2 : 1;
        uint8_t LATD3 : 1;
        uint8_t LATD4 : 1;
        uint8_t LATD5 : 1;
        uint8_t LATD6 : 1;
        uint8_t LATD7 : 1;
        uint8_t LATD8 : 1;
        uint8_t LATD9 : 1;
        uint8_t LATD10 : 1;
        uint8_t LATD11 : 1;
        uint8_t LATD12 : 1;
        uint8_t LATD13 : 1;
        uint8_t LATD14 : 1;
        uint8_t LATD15 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint8_t LD0 : 1;
        uint8_t LD1 : 1;
        uint8_t LD2 : 1;
        uint8_t LD3 : 1;
        uint8_t LD4 : 1;
        uint8_t LD5 : 1;
        uint8_t LD6 : 1;
        uint8_t LD7 : 1;
        uint8_t LD8 : 1;
        uint8_t LD9 : 1;
        uint8_t LD10 : 1;
        uint8_t LD11 : 1;
        uint8_t LD12 : 1;
        uint8_t LD13 : 1;
        uint8_t LD14 : 1;
        uint8_t LD15 : 1;
        uint32_t : 16;
    };
} LATDbits_t;
#define LATDbits (*((volatile LATDbits_t *)&_LATD_))

#define _LATD_LATD0_POSN 0x0
#define _LATD_LATD0_MASK 0x1
#define _LATD_LATD1_POSN 0x1
#define _LATD_LATD1_MASK 0x2
#define _LATD_LATD2_POSN 0x2
#define _LATD_LATD2_MASK 0x4
#define _LATD_LATD3_POSN 0x3
#define _LATD_LATD3_MASK 0x8
#define _LATD_LATD4_POSN 0x4
#define _LATD_LATD4_MASK 0x10
#define _LATD_LATD5_POSN 0x5
#define _LATD_LATD5_MASK 0x20
#define _LATD_LATD6_POSN 0x6
#define _LATD_LATD6_MASK 0x40
#define _LATD_LATD7_POSN 0x7
#define _LATD_LATD7_MASK 0x80
#define _LATD_LATD8_POSN 0x8
#define _LATD_LATD8_MASK 0x100
#define _LATD_LATD9_POSN 0x9
#define _LATD_LATD9_MASK 0x200
#define _LATD_LATD10_POSN 0xa
#define _LATD_LATD10_MASK 0x400
#define _LATD_LATD11_POSN 0xb
#define _LATD_LATD11_MASK 0x800
#define _LATD_LATD12_POSN 0xc
#define _LATD_LATD12_MASK 0x1000
#define _LATD_LATD13_POSN 0xd
#define _LATD_LATD13_MASK 0x2000
#define _LATD_LATD14_POSN 0xe
#define _LATD_LATD14_MASK 0x4000
#define _LATD_LATD15_POSN 0xf
#define _LATD_LATD15_MASK 0x8000
#define _LATD_LD0_POSN 0x0
#define _LATD_LD0_MASK 0x1
#define _LATD_LD1_POSN 0x1
#define _LATD_LD1_MASK 0x2
#define _LATD_LD2_POSN 0x2
#define _LATD_LD2_MASK 0x4
#define _LATD_LD3_POSN 0x3
#define _LATD_LD3_MASK 0x8
#define _LATD_LD4_POSN 0x4
#define _LATD_LD4_MASK 0x10
#define _LATD_LD5_POSN 0x5
#define _LATD_LD5_MASK 0x20
#define _LATD_LD6_POSN 0x6
#define _LATD_LD6_MASK 0x40
#define _LATD_LD7_POSN 0x7
#define _LATD_LD7_MASK 0x80
#define _LATD_LD8_POSN 0x8
#define _LATD_LD8_MASK 0x100
#define _LATD_LD9_POSN 0x9
#define _LATD_LD9_MASK 0x200
#define _LATD_LD10_POSN 0xa
#define _LATD_LD10_MASK 0x400
#define _LATD_LD11_POSN 0xb
#define _LATD_LD11_MASK 0x800
#define _LATD_LD12_POSN 0xc
#define _LATD_LD12_MASK 0x1000
#define _LATD_LD13_POSN 0xd
#define _LATD_LD13_MASK 0x2000
#define _LATD_LD14_POSN 0xe
#define _LATD_LD14_MASK 0x4000
#define _LATD_LD15_POSN 0xf
#define _LATD_LD15_MASK 0x8000

/* Alternate Output Config Register for PORTA - Enables the PIN to output alternate peripheral outputs */
#define ALTOUTACON (*((volatile uint32_t *)&_ALTOUTACON_))

/* ALTOUTACON bitfields definition*/
typedef union
{
    uint32_t ALTOUTACONreg;
    struct
    {
        uint8_t ALTA0 : 1;
        uint8_t ALTA1 : 1;
        uint8_t ALTA2 : 1;
        uint8_t ALTA3 : 1;
        uint8_t ALTA4 : 1;
        uint8_t ALTA5 : 1;
        uint8_t ALTA6 : 1;
        uint8_t ALTA7 : 1;
        uint8_t ALTA8 : 1;
        uint8_t ALTA9 : 1;
        uint8_t ALTA10 : 1;
        uint8_t ALTA11 : 1;
        uint8_t ALTA12 : 1;
        uint8_t ALTA13 : 1;
        uint8_t ALTA14 : 1;
        uint8_t ALTA15 : 1;
        uint32_t : 16;
    };
} ALTOUTACONbits_t;
#define ALTOUTACONbits (*((volatile ALTOUTACONbits_t *)&_ALTOUTACON_))

#define _ALTOUTACON_ALTA0_POSN 0x0
#define _ALTOUTACON_ALTA0_MASK 0x1
#define _ALTOUTACON_ALTA1_POSN 0x1
#define _ALTOUTACON_ALTA1_MASK 0x2
#define _ALTOUTACON_ALTA2_POSN 0x2
#define _ALTOUTACON_ALTA2_MASK 0x4
#define _ALTOUTACON_ALTA3_POSN 0x3
#define _ALTOUTACON_ALTA3_MASK 0x8
#define _ALTOUTACON_ALTA4_POSN 0x4
#define _ALTOUTACON_ALTA4_MASK 0x10
#define _ALTOUTACON_ALTA5_POSN 0x5
#define _ALTOUTACON_ALTA5_MASK 0x20
#define _ALTOUTACON_ALTA6_POSN 0x6
#define _ALTOUTACON_ALTA6_MASK 0x40
#define _ALTOUTACON_ALTA7_POSN 0x7
#define _ALTOUTACON_ALTA7_MASK 0x80
#define _ALTOUTACON_ALTA8_POSN 0x8
#define _ALTOUTACON_ALTA8_MASK 0x100
#define _ALTOUTACON_ALTA9_POSN 0x9
#define _ALTOUTACON_ALTA9_MASK 0x200
#define _ALTOUTACON_ALTA10_POSN 0xa
#define _ALTOUTACON_ALTA10_MASK 0x400
#define _ALTOUTACON_ALTA11_POSN 0xb
#define _ALTOUTACON_ALTA11_MASK 0x800
#define _ALTOUTACON_ALTA12_POSN 0xc
#define _ALTOUTACON_ALTA12_MASK 0x1000
#define _ALTOUTACON_ALTA13_POSN 0xd
#define _ALTOUTACON_ALTA13_MASK 0x2000
#define _ALTOUTACON_ALTA14_POSN 0xe
#define _ALTOUTACON_ALTA14_MASK 0x4000
#define _ALTOUTACON_ALTA15_POSN 0xf
#define _ALTOUTACON_ALTA15_MASK 0x8000

/* Alternate Output Config Register for PORTB - Enables the PIN to output alternate peripheral outputs */
#define ALTOUTBCON (*((volatile uint32_t *)&_ALTOUTBCON_))

/* ALTOUTBCON bitfields definition*/
typedef union
{
    uint32_t ALTOUTBCONreg;
    struct
    {
        uint8_t ALTB0 : 1;
        uint8_t ALTB1 : 1;
        uint8_t ALTB2 : 1;
        uint8_t ALTB3 : 1;
        uint8_t ALTB4 : 1;
        uint8_t ALTB5 : 1;
        uint8_t ALTB6 : 1;
        uint8_t ALTB7 : 1;
        uint8_t ALTB8 : 1;
        uint8_t ALTB9 : 1;
        uint8_t ALTB10 : 1;
        uint8_t ALTB11 : 1;
        uint8_t ALTB12 : 1;
        uint8_t ALTB13 : 1;
        uint8_t ALTB14 : 1;
        uint8_t ALTB15 : 1;
        uint32_t : 16;
    };
} ALTOUTBCONbits_t;
#define ALTOUTBCONbits (*((volatile ALTOUTBCONbits_t *)&_ALTOUTBCON_))

#define _ALTOUTBCON_ALTB0_POSN 0x0
#define _ALTOUTBCON_ALTB0_MASK 0x1
#define _ALTOUTBCON_ALTB1_POSN 0x1
#define _ALTOUTBCON_ALTB1_MASK 0x2
#define _ALTOUTBCON_ALTB2_POSN 0x2
#define _ALTOUTBCON_ALTB2_MASK 0x4
#define _ALTOUTBCON_ALTB3_POSN 0x3
#define _ALTOUTBCON_ALTB3_MASK 0x8
#define _ALTOUTBCON_ALTB4_POSN 0x4
#define _ALTOUTBCON_ALTB4_MASK 0x10
#define _ALTOUTBCON_ALTB5_POSN 0x5
#define _ALTOUTBCON_ALTB5_MASK 0x20
#define _ALTOUTBCON_ALTB6_POSN 0x6
#define _ALTOUTBCON_ALTB6_MASK 0x40
#define _ALTOUTBCON_ALTB7_POSN 0x7
#define _ALTOUTBCON_ALTB7_MASK 0x80
#define _ALTOUTBCON_ALTB8_POSN 0x8
#define _ALTOUTBCON_ALTB8_MASK 0x100
#define _ALTOUTBCON_ALTB9_POSN 0x9
#define _ALTOUTBCON_ALTB9_MASK 0x200
#define _ALTOUTBCON_ALTB10_POSN 0xa
#define _ALTOUTBCON_ALTB10_MASK 0x400
#define _ALTOUTBCON_ALTB11_POSN 0xb
#define _ALTOUTBCON_ALTB11_MASK 0x800
#define _ALTOUTBCON_ALTB12_POSN 0xc
#define _ALTOUTBCON_ALTB12_MASK 0x1000
#define _ALTOUTBCON_ALTB13_POSN 0xd
#define _ALTOUTBCON_ALTB13_MASK 0x2000
#define _ALTOUTBCON_ALTB14_POSN 0xe
#define _ALTOUTBCON_ALTB14_MASK 0x4000
#define _ALTOUTBCON_ALTB15_POSN 0xf
#define _ALTOUTBCON_ALTB15_MASK 0x8000

/* Alternate Peripheral Output Enable Register - Enables the Peripheral to Use GPIO Pins */
#define ALTOUTEN (*((volatile uint32_t *)&_ALTOUTEN_))

/* ALTOUTEN bitfield definition */
typedef union
{
    uint32_t ALTOUTENreg;
    struct
    {
        uint8_t ENURT0 : 1;
        uint8_t ENURT1 : 1;
        uint8_t ENI2C0 : 1;
        uint8_t : 1;
        uint8_t ENSPI0 : 1;
        uint8_t : 1;
        uint8_t ENPWM0 : 1;
        uint8_t ENPWM1 : 1;
        uint8_t ENPWM2 : 1;
        uint8_t ENPWM3 : 1;
        uint8_t ENPWM4 : 1;
        uint8_t ENPWM5 : 1;
        uint32_t : 20;
    } ALTOUTENbits;
} ALTOUTENbits_t;
#define ALTOUTENbits (*((volatile ALTOUTENbits_t *)&_ALTOUTEN_))

#define _ALTOUTEN_ENURT0_POSN 0x0
#define _ALTOUTEN_ENURT0_MASK 0x1
#define _ALTOUTEN_ENURT1_POSN 0x1
#define _ALTOUTEN_ENURT1_MASK 0x2
#define _ALTOUTEN_ENI2C0_POSN 0x2
#define _ALTOUTEN_ENI2C0_MASK 0x4
#define _ALTOUTEN_ENSPI0_POSN 0x4
#define _ALTOUTEN_ENSPI0_MASK 0x10
#define _ALTOUTEN_ENPWM0_POSN 0x6
#define _ALTOUTEN_ENPWM0_MASK 0x40
#define _ALTOUTEN_ENPWM1_POSN 0x7
#define _ALTOUTEN_ENPWM1_MASK 0x80
#define _ALTOUTEN_ENPWM2_POSN 0x8
#define _ALTOUTEN_ENPWM2_MASK 0x100
#define _ALTOUTEN_ENPWM3_POSN 0x9
#define _ALTOUTEN_ENPWM3_MASK 0x200
#define _ALTOUTEN_ENPWM4_POSN 0xa
#define _ALTOUTEN_ENPWM4_MASK 0x400
#define _ALTOUTEN_ENPWM5_POSN 0xb
#define _ALTOUTEN_ENPWM5_MASK 0x800

/*************************************************************/
/* Timer Registers */

/* Timer0 Config Register */
#define T0CON (*((volatile uint32_t *)&_T0CON_))

/* T0CON bitfield definition */
typedef union
{
    uint32_t T0CONreg;
    struct
    {
        uint8_t T0AON : 1;
        uint8_t T0BON : 1;
        uint8_t T0ASET : 1;
        uint8_t T0BSET : 1;
        uint8_t T0ACLRF : 1;
        uint8_t T0BCLRF : 1;
        uint32_t : 26;
    };
} T0CONbits_t;
#define T0CONbits (*((volatile T0CONbits_t *)&_T0CON_))

#define _T0CON_T0AON_POSN 0x0
#define _T0CON_T0AON_MASK 0x1
#define _T0CON_T0BON_POSN 0x1
#define _T0CON_T0BON_MASK 0x2
#define _T0CON_T0ASET_POSN 0x2
#define _T0CON_T0ASET_MASK 0x4
#define _T0CON_T0BSET_POSN 0x3
#define _T0CON_T0BSET_MASK 0x8
#define _T0CON_T0ACLRF_POSN 0x4
#define _T0CON_T0ACLRF_MASK 0x10
#define _T0CON_T0BCLRF_POSN 0x5
#define _T0CON_T0BCLRF_MASK 0x20

/* Timer0 Input Buffer Low */
#define T0L (*((volatile uint32_t *)&_T0L_))

/* T0L bitfield definition */
typedef union
{
    uint32_t T0Lreg;
} T0Lbits_t;
#define T0Lbits (*((volatile T0Lbits_t *)&_T0L_))

#define _T0L_T0L_POSN 0x0
#define _T0L_T0L_MASK 0xffff

/* Timer0 Input Buffer High */
#define T0H (*((volatile uint32_t *)&_T0H_))

/* T0H bitfield definition */
typedef union
{
    uint32_t T0Hreg;
} T0Hbits_t;
#define T0Hbits (*((volatile T0Hbits_t *)&_T0H_))

#define _T0H_T0H_POSN 0x0
#define _T0H_T0H_MASK 0xffff

/* Timer0A Read Buffer */
#define T0ABUF (*((volatile uint32_t *)&_T0ABUF_))

/* T0ABUF bitfield definition */
typedef union
{
    uint32_t T0ABUFreg;
} T0ABUFbits_t;
#define T0ABUFbits (*((volatile T0ABUFbits_t *)&_T0ABUF_))

#define _T0ABUF_T0ABUF_POSN 0x0
#define _T0ABUF_T0ABUF_MASK 0xffff

/* Timer0B Read Buffer */
#define T0BBUF (*((volatile uint32_t *)&_T0BBUF_))

/* T0BBUF bitfield definition */
typedef union
{
    uint32_t T0BBUFreg;
} T0BBUFbits_t;
#define T0BBUFbits (*((volatile T0BBUFbits_t *)&_T0BBUF_))

#define _T0BBUF_T0BBUF_POSN 0x0
#define _T0BBUF_T0BBUF_MASK 0xffff

/* Timer1 Config Register */
#define T1CON (*((volatile uint32_t *)&_T1CON_))

/* T1CON bitfield definition */
typedef union
{
    uint32_t T1CONreg;
    struct
    {
        uint8_t T1AON : 1;
        uint8_t T1BON : 1;
        uint8_t T1ASET : 1;
        uint8_t T1BSET : 1;
        uint8_t T1ACLRF : 1;
        uint8_t T1BCLRF : 1;
        uint32_t : 26;
    };
} T1CONbits_t;
#define T1CONbits (*((volatile T1CONbits_t *)&_T1CON_))

#define _T1CON_T1AON_POSN 0x0
#define _T1CON_T1AON_MASK 0x1
#define _T1CON_T1BON_POSN 0x1
#define _T1CON_T1BON_MASK 0x2
#define _T1CON_T1ASET_POSN 0x2
#define _T1CON_T1ASET_MASK 0x4
#define _T1CON_T1BSET_POSN 0x3
#define _T1CON_T1BSET_MASK 0x8
#define _T1CON_T1ACLRF_POSN 0x4
#define _T1CON_T1ACLRF_MASK 0x10
#define _T1CON_T1BCLRF_POSN 0x5
#define _T1CON_T1BCLRF_MASK 0x20

/* Timer1 Input Buffer Low */
#define T1L (*((volatile uint32_t *)&_T1L_))

/* T1L bitfield definition */
typedef union
{
    uint32_t T1Lreg;
} T1Lbits_t;
#define T1Lbits (*((volatile T1Lbits_t *)&_T1L_))

#define _T1L_T1L_POSN 0x0
#define _T1L_T1L_MASK 0xffff

/* Timer1 Input Buffer High */
#define T1H (*((volatile uint32_t *)&_T1H_))

/* T1H bitfield definition */
typedef union
{
    uint32_t T1Hreg;
} T1Hbits_t;
#define T1Hbits (*((volatile T1Hbits_t *)&_T1H_))

#define _T1H_T1H_POSN 0x0
#define _T1H_T1H_MASK 0xffff

/* Timer1A Read Buffer */
#define T1ABUF (*((volatile uint32_t *)&_T1ABUF_))

/* T1ABUF bitfield definition */
typedef union
{
    uint32_t T1ABUFreg;
} T1ABUFbits_t;
#define T1ABUFbits (*((volatile T1ABUFbits_t *)&_T1ABUF_))

#define _T1ABUF_T1ABUF_POSN 0x0
#define _T1ABUF_T1ABUF_MASK 0xffff

/* Timer1B Read Buffer */
#define T1BBUF (*((volatile uint32_t *)&_T1BBUF_))

/* T1BBUF bitfield definition */
typedef union
{
    uint32_t T1BBUFreg;
} T1BBUFbits_t;
#define T1BBUFbits (*((volatile T1BBUFbits_t *)&_T1BBUF_))

#define _T1BBUF_T1BBUF_POSN 0x0
#define _T1BBUF_T1BBUF_MASK 0xffff

/* Timer2 Config Register */
#define T2CON (*((volatile uint32_t *)&_T2CON_))

/* T2CON bitfield definition */
typedef union
{
    uint32_t T2CONreg;
    struct
    {
        uint8_t T2AON : 1;
        uint8_t T2BON : 1;
        uint8_t T2ASET : 1;
        uint8_t T2BSET : 1;
        uint8_t T2ACLRF : 1;
        uint8_t T2BCLRF : 1;
        uint32_t : 26;
    };
} T2CONbits_t;
#define T2CONbits (*((volatile T2CONbits_t *)&_T2CON_))

#define _T2CON_T2AON_POSN 0x0
#define _T2CON_T2AON_MASK 0x1
#define _T2CON_T2BON_POSN 0x1
#define _T2CON_T2BON_MASK 0x2
#define _T2CON_T2ASET_POSN 0x2
#define _T2CON_T2ASET_MASK 0x4
#define _T2CON_T2BSET_POSN 0x3
#define _T2CON_T2BSET_MASK 0x8
#define _T2CON_T2ACLRF_POSN 0x4
#define _T2CON_T2ACLRF_MASK 0x10
#define _T2CON_T2BCLRF_POSN 0x5
#define _T2CON_T2BCLRF_MASK 0x20

/* Timer2 Input Buffer Low */
#define T2L (*((volatile uint32_t *)&_T2L_))

/* T2L bitfield definition */
typedef union
{
    uint32_t T2Lreg;
} T2Lbits_t;
#define T2Lbits (*((volatile T2Lbits_t *)&_T2L_))

#define _T2L_T2L_POSN 0x0
#define _T2L_T2L_MASK 0xffff

/* Timer2 Input Buffer High */
#define T2H (*((volatile uint32_t *)&_T2H_))

/* T2H bitfield definition */
typedef union
{
    uint32_t T2Hreg;
} T2Hbits_t;
#define T2Hbits (*((volatile T2Hbits_t *)&_T2H_))

#define _T2H_T2H_POSN 0x0
#define _T2H_T2H_MASK 0xffff

/* Timer2A Read Buffer */
#define T2ABUF (*((volatile uint32_t *)&_T2ABUF_))

/* T2ABUF bitfield definition */
typedef union
{
    uint32_t T2ABUFreg;
} T2ABUFbits_t;
#define T2ABUFbits (*((volatile T2ABUFbits_t *)&_T2ABUF_))

#define _T2ABUF_T2ABUF_POSN 0x0
#define _T2ABUF_T2ABUF_MASK 0xffff

/* Timer2B Read Buffer */
#define T2BBUF (*((volatile uint32_t *)&_T2BBUF_))

/* T2BBUF bitfield definition */
typedef union
{
    uint32_t T2BBUFreg;
} T2BBUFbits_t;
#define T2BBUFbits (*((volatile T2BBUFbits_t *)&_T2BBUF_))

#define _T2BBUF_T2BBUF_POSN 0x0
#define _T2BBUF_T2BBUF_MASK 0xffff

/* Timer3 Config Register */
#define T3CON (*((volatile uint32_t *)&_T3CON_))

/* T3CON bitfield definition */
typedef union
{
    uint32_t T3CONreg;
    struct
    {
        uint8_t T3AON : 1;
        uint8_t T3BON : 1;
        uint8_t T3ASET : 1;
        uint8_t T3BSET : 1;
        uint8_t T3ACLRF : 1;
        uint8_t T3BCLRF : 1;
        uint32_t : 26;
    };
} T3CONbits_t;
#define T3CONbits (*((volatile T3CONbits_t *)&_T3CON_))

#define _T3CON_T3AON_POSN 0x0
#define _T3CON_T3AON_MASK 0x1
#define _T3CON_T3BON_POSN 0x1
#define _T3CON_T3BON_MASK 0x2
#define _T3CON_T3ASET_POSN 0x2
#define _T3CON_T3ASET_MASK 0x4
#define _T3CON_T3BSET_POSN 0x3
#define _T3CON_T3BSET_MASK 0x8
#define _T3CON_T3ACLRF_POSN 0x4
#define _T3CON_T3ACLRF_MASK 0x10
#define _T3CON_T3BCLRF_POSN 0x5
#define _T3CON_T3BCLRF_MASK 0x20

/* Timer3 Input Buffer Low */
#define T3L (*((volatile uint32_t *)&_T3L_))

/* T3L bitfield definition */
typedef union
{
    uint32_t T3Lreg;
} T3Lbits_t;
#define T3Lbits (*((volatile T3Lbits_t *)&_T3L_))

#define _T3L_T3L_POSN 0x0
#define _T3L_T3L_MASK 0xffff

/* Timer3 Input Buffer High */
#define T3H (*((volatile uint32_t *)&_T3H_))

/* T3H bitfield definition */
typedef union
{
    uint32_t T3Hreg;
} T3Hbits_t;
#define T3Hbits (*((volatile T3Hbits_t *)&_T3H_))

#define _T3H_T3H_POSN 0x0
#define _T3H_T3H_MASK 0xffff

/* Timer3A Read Buffer */
#define T3ABUF (*((volatile uint32_t *)&_T3ABUF_))

/* T3ABUF bitfield definition */
typedef union
{
    uint32_t T3ABUFreg;
} T3ABUFbits_t;
#define T3ABUFbits (*((volatile T3ABUFbits_t *)&_T3ABUF_))

#define _T3ABUF_T3ABUF_POSN 0x0
#define _T3ABUF_T3ABUF_MASK 0xffff

/* Timer3B Read Buffer */
#define T3BBUF (*((volatile uint32_t *)&_T3BBUF_))

/* T3BBUF bitfield definition */
typedef union
{
    uint32_t T3BBUFreg;
} T3BBUFbits_t;
#define T3BBUFbits (*((volatile T3BBUFbits_t *)&_T3BBUF_))

#define _T3BBUF_T3BBUF_POSN 0x0
#define _T3BBUF_T3BBUF_MASK 0xffff

/* Timer4 Config Register */
#define T4CON (*((volatile uint32_t *)&_T4CON_))

/* T4CON bitfield definition */
typedef union
{
    uint32_t T4CONreg;
    struct
    {
        uint8_t T4ON : 1;
        uint8_t T4MODE : 1;
        uint8_t : 3;
        uint8_t T4SET : 1;
        uint8_t : 4;
        uint8_t T4CLRF : 1;
        uint8_t : 1;
        uint32_t : 20;
    };
    struct
    {
        uint8_t : 6;
        uint8_t IC0SPIN0 : 1;
        uint8_t IC0SPIN1 : 1;
        uint8_t IC0PPIN0 : 1;
        uint8_t IC0PPIN1 : 1;
        uint8_t : 2;
        uint32_t : 20;
    };
    struct
    {
        uint8_t TIC0ON : 1;
        uint8_t : 1;
        uint8_t IC0SPOL : 1;
        uint8_t IC0PPOL : 1;
        uint8_t TIC0SET : 1;
        uint8_t : 1;
        uint8_t IC0SPIN : 2;
        uint8_t IC0PPIN : 2;
        uint8_t : 1;
        uint8_t TIC0CLRF : 1;
        uint32_t : 20;
    };
} T4CONbits_t;
#define T4CONbits (*((volatile T4CONbits_t *)&_T4CON_))

#define _T4CON_T4ON_POSN 0x0
#define _T4CON_T4ON_MASK 0x1
#define _T4CON_TIC0ON_POSN 0x0
#define _T4CON_TIC0ON_MASK 0x1
#define _T4CON_T4MODE_POSN 0x1
#define _T4CON_T4MODE_MASK 0x2
#define _T4CON_IC0SPOL_POSN 0x2
#define _T4CON_IC0SPOL_MASK 0x4
#define _T4CON_IC0PPOL_POSN 0x3
#define _T4CON_IC0PPOL_MASK 0x8
#define _T4CON_TIC0SET_POSN 0x4
#define _T4CON_TIC0SET_MASK 0x10
#define _T4CON_T4SET_POSN 0x5
#define _T4CON_T4SET_MASK 0x20
#define _T4CON_IC0SPIN_POSN 0x6
#define _T4CON_IC0SPIN_MASK 0xc0
#define _T4CON_IC0SPIN0_POSN 0x6
#define _T4CON_IC0SPIN0_MASK 0x40
#define _T4CON_IC0SPIN1_POSN 0x7
#define _T4CON_IC0SPIN1_MASK 0x80
#define _T4CON_IC0PPIN_POSN 0x8
#define _T4CON_IC0PPIN_MASK 0x300
#define _T4CON_IC0PPIN0_POSN 0x8
#define _T4CON_IC0PPIN0_MASK 0x100
#define _T4CON_IC0PPIN1_POSN 0x9
#define _T4CON_IC0PPIN1_MASK 0x200
#define _T4CON_T4CLRF_POSN 0xa
#define _T4CON_T4CLRF_MASK 0x400
#define _T4CON_TIC0CLRF_POSN 0xb
#define _T4CON_TIC0CLRF_MASK 0x800

/* Timer4 Input Buffer Low */
#define T4L (*((volatile uint32_t *)&_T4L_))

/* T4L bitfield definition */
typedef union
{
    uint32_t T4Lreg;
} T4Lbits_t;
#define T4Lbits (*((volatile T4Lbits_t *)&_T4L_))

#define _T4L_T4L_POSN 0x0
#define _T4L_T4L_MASK 0xffff

/* Timer4 Input Buffer High */
#define T4H (*((volatile uint32_t *)&_T4H_))

/* T4H bitfield definition */
typedef union
{
    uint32_t T4Hreg;
} T4Hbits_t;
#define T4Hbits (*((volatile T4Hbits_t *)&_T4H_))

#define _T4H_T4H_POSN 0x0
#define _T4H_T4H_MASK 0xffff

/* Timer4 Read Buffer */
#define T4BUF (*((volatile uint32_t *)&_T4BUF_))

/* T4BUF bitfield definition */
typedef union
{
    uint32_t T4BUFreg;
} T4BUFbits_t;
#define T4BUFbits (*((volatile T4BUFbits_t *)&_T4BUF_))

#define _T4BUF_T4BUF_POSN 0x0
#define _T4BUF_T4BUF_MASK 0xffff

/* TimerCapture0 Read Buffer */
#define TC0BUF (*((volatile uint32_t *)&_TC0BUF_))

/* TC0BUF bitfield definition */
typedef union
{
    uint32_t TC0BUFreg;
} TC0BUFbits_t;
#define TC0BUFbits (*((volatile TC0BUFbits_t *)&_TC0BUF_))

#define _TC0BUF_TC0BUF_POSN 0x0
#define _TC0BUF_TC0BUF_MASK 0xffff

/* Timer5 Config Register */
#define T5CON (*((volatile uint32_t *)&_T5CON_))

/* T5CON bitfield definition */
typedef union
{
    uint32_t T5CONreg;
    struct
    {
        uint8_t T5ON : 1;
        uint8_t T5MODE : 1;
        uint8_t : 3;
        uint8_t T5SET : 1;
        uint8_t : 4;
        uint8_t T5CLRF : 1;
        uint8_t : 1;
        uint32_t : 20;
    };
    struct
    {
        uint8_t TIC1ON : 1;
        uint8_t : 1;
        uint8_t IC1SPOL : 1;
        uint8_t IC1PPOL : 1;
        uint8_t TIC1SET : 1;
        uint8_t : 1;
        uint8_t IC1SPIN : 2;
        uint8_t IC1PPIN : 2;
        uint8_t : 1;
        uint8_t TIC1CLRF : 1;
        uint32_t : 20;
    };
} T5CONbits_t;
#define T5CONbits (*((volatile T5CONbits_t *)&_T5CON_))

#define _T5CON_T5ON_POSN 0x0
#define _T5CON_T5ON_MASK 0x1
#define _T5CON_TIC1ON_POSN 0x0
#define _T5CON_TIC1ON_MASK 0x1
#define _T5CON_T5MODE_POSN 0x1
#define _T5CON_T5MODE_MASK 0x2
#define _T5CON_IC1SPOL_POSN 0x2
#define _T5CON_IC1SPOL_MASK 0x4
#define _T5CON_IC1PPOL_POSN 0x3
#define _T5CON_IC1PPOL_MASK 0x8
#define _T5CON_TIC1SET_POSN 0x4
#define _T5CON_TIC1SET_MASK 0x10
#define _T5CON_T5SET_POSN 0x5
#define _T5CON_T5SET_MASK 0x20
#define _T5CON_IC1SPIN_POSN 0x6
#define _T5CON_IC1SPIN_MASK 0xc0
#define _T5CON_IC1SPIN0_POSN 0x6
#define _T5CON_IC1SPIN0_MASK 0x40
#define _T5CON_IC1SPIN1_POSN 0x7
#define _T5CON_IC1SPIN1_MASK 0x80
#define _T5CON_IC1PPIN_POSN 0x8
#define _T5CON_IC1PPIN_MASK 0x300
#define _T5CON_IC1PPIN0_POSN 0x8
#define _T5CON_IC1PPIN0_MASK 0x100
#define _T5CON_IC1PPIN1_POSN 0x9
#define _T5CON_IC1PPIN1_MASK 0x200
#define _T5CON_T5CLRF_POSN 0xa
#define _T5CON_T5CLRF_MASK 0x400
#define _T5CON_TIC1CLRF_POSN 0xb
#define _T5CON_TIC1CLRF_MASK 0x800

/* Timer5 Input Buffer Low */
#define T5L (*((volatile uint32_t *)&_T5L_))

/* T5L bitfield definition */
typedef union
{
    uint32_t T5Lreg;
} T5Lbits_t;
#define T5Lbits (*((volatile T5Lbits_t *)&_T5L_))

#define _T5L_T5L_POSN 0x0
#define _T5L_T5L_MASK 0xffff

/* Timer5 Input Buffer High */
#define T5H (*((volatile uint32_t *)&_T5H_))

/* T5H bitfield definition */
typedef union
{
    uint32_t T5Hreg;
} T5Hbits_t;
#define T5Hbits (*((volatile T5Hbits_t *)&_T5H_))

#define _T5H_T5H_POSN 0x0
#define _T5H_T5H_MASK 0xffff

/* Timer5 Read Buffer */
#define T5BUF (*((volatile uint32_t *)&_T5BUF_))

/* T5BUF bitfield definition */
typedef union
{
    uint32_t T5BUFreg;
} T5BUFbits_t;
#define T5BUFbits (*((volatile T5BUFbits_t *)&_T5BUF_))

#define _T5BUF_T5BUF_POSN 0x0
#define _T5BUF_T5BUF_MASK 0xffff

/* TimerCapture1 Read Buffer */
#define TC1BUF (*((volatile uint32_t *)&_TC1BUF_))

/* TC1BUF bitfield definition */
typedef union
{
    uint32_t TC1BUFreg;
} TC1BUFbits_t;
#define TC1BUFbits (*((volatile TC1BUFbits_t *)&_TC1BUF_))

#define _TC1BUF_TC1BUF_POSN 0x0
#define _TC1BUF_TC1BUF_MASK 0xffff

/* Timer Flag Register */
#define TFREG (*((volatile uint32_t *)&_TFREG_))

/* TFREG bitfield definition */
typedef union
{
    uint32_t TFREGreg;
    struct
    {
        uint8_t T0AF : 1;
        uint8_t T0BF : 1;
        uint8_t T1AF : 1;
        uint8_t T1BF : 1;
        uint8_t T2AF : 1;
        uint8_t T2BF : 1;
        uint8_t T3AF : 1;
        uint8_t T3BF : 1;
        uint8_t T4F : 1;
        uint8_t T4ICF : 1;
        uint8_t T5F : 1;
        uint8_t T5ICF : 1;
        uint32_t : 20;
    };
} TFREGbits_t;
#define TFREGbits (*((volatile TFREGbits_t *)&_TFREG_))

#define _TFREG_T0AF_POSN 0x0
#define _TFREG_T0AF_MASK 0x1
#define _TFREG_T0BF_POSN 0x1
#define _TFREG_T0BF_MASK 0x2
#define _TFREG_T1AF_POSN 0x2
#define _TFREG_T1AF_MASK 0x4
#define _TFREG_T1BF_POSN 0x3
#define _TFREG_T1BF_MASK 0x8
#define _TFREG_T2AF_POSN 0x4
#define _TFREG_T2AF_MASK 0x10
#define _TFREG_T2BF_POSN 0x5
#define _TFREG_T2BF_MASK 0x20
#define _TFREG_T3AF_POSN 0x6
#define _TFREG_T3AF_MASK 0x40
#define _TFREG_T3BF_POSN 0x7
#define _TFREG_T3BF_MASK 0x80
#define _TFREG_T4F_POSN 0x8
#define _TFREG_T4F_MASK 0x100
#define _TFREG_T4ICF_POSN 0x9
#define _TFREG_T4ICF_MASK 0x200
#define _TFREG_T5F_POSN 0xa
#define _TFREG_T5F_MASK 0x400
#define _TFREG_T5ICF_POSN 0xb
#define _TFREG_T5ICF_MASK 0x800

/* DCT Class masks */
#define _DCT_TCON_TAON_POSN 0x0
#define _DCT_TCON_TAON_MASK 0x1
#define _DCT_TCON_TBON_POSN 0x1
#define _DCT_TCON_TBON_MASK 0x2
#define _DCT_TCON_TASET_POSN 0x2
#define _DCT_TCON_TASET_MASK 0x4
#define _DCT_TCON_TBSET_POSN 0x3
#define _DCT_TCON_TBSET_MASK 0x8
#define _DCT_TCON_TACLRF_POSN 0x4
#define _DCT_TCON_TACLRF_MASK 0x10
#define _DCT_TCON_TBCLRF_POSN 0x5
#define _DCT_TCON_TBCLRF_MASK 0x20

/* ICT Class masks */
#define _ICT_TCON_TON_POSN 0x0
#define _ICT_TCON_TON_MASK 0x1
#define _ICT_TCON_TICON_POSN 0x0
#define _ICT_TCON_TICON_MASK 0x1
#define _ICT_TCON_TMODE_POSN 0x1
#define _ICT_TCON_TMODE_MASK 0x2
#define _ICT_TCON_ICSPOL_POSN 0x2
#define _ICT_TCON_ICSPOL_MASK 0x4
#define _ICT_TCON_ICPPOL_POSN 0x3
#define _ICT_TCON_ICPPOL_MASK 0x8
#define _ICT_TCON_TICSET_POSN 0x4
#define _ICT_TCON_TICSET_MASK 0x10
#define _ICT_TCON_TSET_POSN 0x5
#define _ICT_TCON_TSET_MASK 0x20
#define _ICT_TCON_ICSPIN_POSN 0x6
#define _ICT_TCON_ICSPIN_MASK 0xc0
#define _ICT_TCON_ICSPIN0_POSN 0x6
#define _ICT_TCON_ICSPIN0_MASK 0x40
#define _ICT_TCON_ICSPIN1_POSN 0x7
#define _ICT_TCON_ICSPIN1_MASK 0x80
#define _ICT_TCON_ICPPIN_POSN 0x8
#define _ICT_TCON_ICPPIN_MASK 0x300
#define _ICT_TCON_ICPPIN0_POSN 0x8
#define _ICT_TCON_ICPPIN0_MASK 0x100
#define _ICT_TCON_ICPPIN1_POSN 0x9
#define _ICT_TCON_ICPPIN1_MASK 0x200
#define _ICT_TCON_TCLRF_POSN 0xa
#define _ICT_TCON_TCLRF_MASK 0x400
#define _ICT_TCON_TICCLRF_POSN 0xb
#define _ICT_TCON_TICCLRF_MASK 0x800

/*************************************************************/
/* Interrupt Mapping Registers */

/* Interrupt0 Map */
#define INT0MAP (*((volatile uint32_t *)&_INT0MAP_))

/* INT0MAP bitfield definition */
typedef union
{
    uint32_t INT0MAPreg;
} INT0MAPbits_t;
#define INT0MAPbits (*((volatile INT0MAPbits_t *)&_INT0MAP_))

#define _INT0MAP_INT0MAP_POSN 0x0
#define _INT0MAP_INT0MAP_MASK 0x1f

/* Interrupt1 Map */
#define INT1MAP (*((volatile uint32_t *)&_INT1MAP_))

/* INT1MAP bitfield definition */
typedef union
{
    uint32_t INT1MAPreg;
} INT1MAPbits_t;
#define INT1MAPbits (*((volatile INT1MAPbits_t *)&_INT1MAP_))

#define _INT1MAP_INT1MAP_POSN 0x0
#define _INT1MAP_INT1MAP_MASK 0x1f

/* Interrupt2 Map */
#define INT2MAP (*((volatile uint32_t *)&_INT2MAP_))

/* INT2MAP bitfield definition */
typedef union
{
    uint32_t INT2MAPreg;
} INT2MAPbits_t;
#define INT2MAPbits (*((volatile INT2MAPbits_t *)&_INT2MAP_))

#define _INT2MAP_INT2MAP_POSN 0x0
#define _INT2MAP_INT2MAP_MASK 0x1f

/* Interrupt3 Map */
#define INT3MAP (*((volatile uint32_t *)&_INT3MAP_))

/* INT3MAP bitfield definition */
typedef union
{
    uint32_t INT3MAPreg;
} INT3MAPbits_t;
#define INT3MAPbits (*((volatile INT3MAPbits_t *)&_INT3MAP_))

#define _INT3MAP_INT3MAP_POSN 0x0
#define _INT3MAP_INT3MAP_MASK 0x1f

/* Interrupt4 Map */
#define INT4MAP (*((volatile uint32_t *)&_INT4MAP_))

/* INT4MAP bitfield definition */
typedef union
{
    uint32_t INT4MAPreg;
} INT4MAPbits_t;
#define INT4MAPbits (*((volatile INT4MAPbits_t *)&_INT4MAP_))

#define _INT4MAP_INT4MAP_POSN 0x0
#define _INT4MAP_INT4MAP_MASK 0x1f

/* Interrupt5 Map */
#define INT5MAP (*((volatile uint32_t *)&_INT5MAP_))

/* INT5MAP bitfield definition */
typedef union
{
    uint32_t INT5MAPreg;
} INT5MAPbits_t;
#define INT5MAPbits (*((volatile INT5MAPbits_t *)&_INT5MAP_))

#define _INT5MAP_INT5MAP_POSN 0x0
#define _INT5MAP_INT5MAP_MASK 0x1f

/* Interrupt6 Map */
#define INT6MAP (*((volatile uint32_t *)&_INT6MAP_))

/* INT6MAP bitfield definition */
typedef union
{
    uint32_t INT6MAPreg;
} INT6MAPbits_t;
#define INT6MAPbits (*((volatile INT6MAPbits_t *)&_INT6MAP_))

#define _INT6MAP_INT6MAP_POSN 0x0
#define _INT6MAP_INT6MAP_MASK 0x1f

/* Interrupt7 Map */
#define INT7MAP (*((volatile uint32_t *)&_INT7MAP_))

/* INT7MAP bitfield definition */
typedef union
{
    uint32_t INT7MAPreg;
} INT7MAPbits_t;
#define INT7MAPbits (*((volatile INT7MAPbits_t *)&_INT7MAP_))

#define _INT7MAP_INT7MAP_POSN 0x0
#define _INT7MAP_INT7MAP_MASK 0x1f

/*************************************************************/
/* Serial Peripheral Module Registers */

/* Uart0 Config Register */
#define URT0CON (*((volatile uint32_t *)&_URT0CON_))

/* URT0CON bitfield definition */
typedef union
{
    uint32_t URT0CONreg;
    struct
    {
        uint8_t TXEN : 1;
        uint8_t RXEN : 1;
        uint8_t ENBIT9 : 1;
        uint8_t TXIF : 1;
        uint8_t RXIF : 1;
        uint8_t FERR : 1;
        uint8_t TXPIN0 : 1;
        uint8_t TXPIN1 : 1;
        uint8_t TXPIN2 : 1;
        uint8_t TXPIN3 : 1;
        uint8_t RXPIN0 : 1;
        uint8_t RXPIN1 : 1;
        uint8_t RXPIN2 : 1;
        uint8_t RXPIN3 : 1;
        uint32_t : 18;
    };
    struct
    {
        uint8_t : 6;
        uint8_t TXPIN : 4;
        uint8_t RXPIN : 4;
        uint32_t : 18;
    };
} URT0CONbits_t;
#define URT0CONbits (*((volatile URT0CONbits_t *)&_URT0CON_))

#define _URT0CON_TXEN_POSN 0x0
#define _URT0CON_TXEN_MASK 0x1
#define _URT0CON_RXEN_POSN 0x1
#define _URT0CON_RXEN_MASK 0x2
#define _URT0CON_ENBIT9_POSN 0x2
#define _URT0CON_ENBIT9_MASK 0x4
#define _URT0CON_TXIF_POSN 0x3
#define _URT0CON_TXIF_MASK 0x8
#define _URT0CON_RXIF_POSN 0x4
#define _URT0CON_RXIF_MASK 0x10
#define _URT0CON_FERR_POSN 0x5
#define _URT0CON_FERR_MASK 0x20
#define _URT0CON_TXPIN_POSN 0x6
#define _URT0CON_TXPIN_MASK 0x3c0
#define _URT0CON_TXPIN0_POSN 0x6
#define _URT0CON_TXPIN0_MASK 0x40
#define _URT0CON_TXPIN1_POSN 0x7
#define _URT0CON_TXPIN1_MASK 0x80
#define _URT0CON_TXPIN2_POSN 0x8
#define _URT0CON_TXPIN2_MASK 0x100
#define _URT0CON_TXPIN3_POSN 0x9
#define _URT0CON_TXPIN3_MASK 0x200
#define _URT0CON_RXPIN_POSN 0xa
#define _URT0CON_RXPIN_MASK 0x3c00
#define _URT0CON_RXPIN0_POSN 0xa
#define _URT0CON_RXPIN0_MASK 0x400
#define _URT0CON_RXPIN1_POSN 0xb
#define _URT0CON_RXPIN1_MASK 0x800
#define _URT0CON_RXPIN2_POSN 0xc
#define _URT0CON_RXPIN2_MASK 0x1000
#define _URT0CON_RXPIN3_POSN 0xd
#define _URT0CON_RXPIN3_MASK 0x2000

/* Uart0 Baud Rate Register */
#define URT0BRG (*((volatile uint32_t *)&_URT0BRG_))

/* URT0BRG bitfield definition */
typedef union
{
    uint32_t URT0BRGreg;
    struct
    {
        uint32_t BRG : 16;
        uint32_t : 16;
    };
} URT0BRGbits_t;
#define URT0BRGbits (*((volatile URT0BRGbits_t *)&_URT0BRG_))

#define _URT0BRG_BRG_POSN 0x0
#define _URT0BRG_BRG_MASK 0xffff

/* Uart0 Transmit Register */
#define URT0TX (*((volatile uint32_t *)&_URT0TX_))

/* URT0TX bitfield definition */
typedef union
{
    uint32_t URT0TXreg;
    struct
    {
        uint8_t TXDATA;
        uint8_t TXBIT9 : 1;
        uint32_t : 23;
    };
} URT0TXbits_t;
#define URT0TXbits (*((volatile URT0TXbits_t *)&_URT0TX_))

#define _URT0TX_TXDATA_POSN 0x0
#define _URT0TX_TXDATA_MASK 0xff
#define _URT0TX_TXBIT9_POSN 0x8
#define _URT0TX_TXBIT9_MASK 0x100

/* Uart0 Receive Register */
#define URT0RX (*((volatile uint32_t *)&_URT0RX_))

/* URT0RX bitfield definition */
typedef union
{
    uint32_t URT0RXreg;
    struct
    {
        uint8_t RXDATA;
        uint8_t RXBIT9 : 1;
        uint32_t : 23;
    };
} URT0RXbits_t;
#define URT0RXbits (*((volatile URT0RXbits_t *)&_URT0RX_))

#define _URT0RX_RXDATA_POSN 0x0
#define _URT0RX_RXDATA_MASK 0xff
#define _URT0RX_RXBIT9_POSN 0x8
#define _URT0RX_RXBIT9_MASK 0x100

/* Uart1 Config Register */
#define URT1CON (*((volatile uint32_t *)&_URT1CON_))

/* URT1CON bitfield definition */
typedef union
{
    uint32_t URT1CONreg;
    struct
    {
        uint8_t TXEN : 1;
        uint8_t RXEN : 1;
        uint8_t ENBIT9 : 1;
        uint8_t TXIF : 1;
        uint8_t RXIF : 1;
        uint8_t FERR : 1;
        uint8_t TXPIN0 : 1;
        uint8_t TXPIN1 : 1;
        uint8_t TXPIN2 : 1;
        uint8_t TXPIN3 : 1;
        uint8_t RXPIN0 : 1;
        uint8_t RXPIN1 : 1;
        uint8_t RXPIN2 : 1;
        uint8_t RXPIN3 : 1;
        uint32_t : 18;
    };
    struct
    {
        uint8_t : 6;
        uint8_t TXPIN : 4;
        uint8_t RXPIN : 4;
        uint32_t : 18;
    };
} URT1CONbits_t;
#define URT1CONbits (*((volatile URT1CONbits_t *)&_URT1CON_))

#define _URT1CON_TXEN_POSN 0x0
#define _URT1CON_TXEN_MASK 0x1
#define _URT1CON_RXEN_POSN 0x1
#define _URT1CON_RXEN_MASK 0x2
#define _URT1CON_ENBIT9_POSN 0x2
#define _URT1CON_ENBIT9_MASK 0x4
#define _URT1CON_TXIF_POSN 0x3
#define _URT1CON_TXIF_MASK 0x8
#define _URT1CON_RXIF_POSN 0x4
#define _URT1CON_RXIF_MASK 0x10
#define _URT1CON_FERR_POSN 0x5
#define _URT1CON_FERR_MASK 0x20
#define _URT1CON_TXPIN_POSN 0x6
#define _URT1CON_TXPIN_MASK 0x3c0
#define _URT1CON_TXPIN0_POSN 0x6
#define _URT1CON_TXPIN0_MASK 0x40
#define _URT1CON_TXPIN1_POSN 0x7
#define _URT1CON_TXPIN1_MASK 0x80
#define _URT1CON_TXPIN2_POSN 0x8
#define _URT1CON_TXPIN2_MASK 0x100
#define _URT1CON_TXPIN3_POSN 0x9
#define _URT1CON_TXPIN3_MASK 0x200
#define _URT1CON_RXPIN_POSN 0xa
#define _URT1CON_RXPIN_MASK 0x3c00
#define _URT1CON_RXPIN0_POSN 0xa
#define _URT1CON_RXPIN0_MASK 0x400
#define _URT1CON_RXPIN1_POSN 0xb
#define _URT1CON_RXPIN1_MASK 0x800
#define _URT1CON_RXPIN2_POSN 0xc
#define _URT1CON_RXPIN2_MASK 0x1000
#define _URT1CON_RXPIN3_POSN 0xd
#define _URT1CON_RXPIN3_MASK 0x2000

/* Uart1 Baud Rate Register */
#define URT1BRG (*((volatile uint32_t *)&_URT1BRG_))

/* URT1BRG bitfield definition */
typedef union
{
    uint32_t URT1BRGreg;
    struct
    {
        uint32_t BRG : 16;
        uint32_t : 16;
    };
} URT1BRGbits_t;
#define URT1BRGbits (*((volatile URT1BRGbits_t *)&_URT1BRG_))

#define _URT1BRG_BRG_POSN 0x0
#define _URT1BRG_BRG_MASK 0xffff

/* Uart1 Transmit Register */
#define URT1TX (*((volatile uint32_t *)&_URT1TX_))

/* URT1TX bitfield definition */
typedef union
{
    uint32_t URT1TXreg;
    struct
    {
        uint8_t TXDATA;
        uint8_t TXBIT9 : 1;
        uint32_t : 23;
    };
} URT1TXbits_t;
#define URT1TXbits (*((volatile URT1TXbits_t *)&_URT1TX_))

#define _URT1TX_TXDATA_POSN 0x0
#define _URT1TX_TXDATA_MASK 0xff
#define _URT1TX_TXBIT9_POSN 0x8
#define _URT1TX_TXBIT9_MASK 0x100

/* Uart1 Receive Register */
#define URT1RX (*((volatile uint32_t *)&_URT1RX_))

/* URT1RX bitfield definition */
typedef union
{
    uint32_t URT1RXreg;
    struct
    {
        uint8_t RXDATA;
        uint8_t RXBIT9 : 1;
        uint32_t : 23;
    };
} URT1RXbits_t;
#define URT1RXbits (*((volatile URT1RXbits_t *)&_URT1RX_))

#define _URT1RX_RXDATA_POSN 0x0
#define _URT1RX_RXDATA_MASK 0xff
#define _URT1RX_RXBIT9_POSN 0x8
#define _URT1RX_RXBIT9_MASK 0x100

/* UART Class masks */
#define _URTCON_TXEN_POSN 0x0
#define _URTCON_TXEN_MASK 0x1
#define _URTCON_RXEN_POSN 0x1
#define _URTCON_RXEN_MASK 0x2
#define _URTCON_ENBIT9_POSN 0x2
#define _URTCON_ENBIT9_MASK 0x4
#define _URTCON_TXIF_POSN 0x3
#define _URTCON_TXIF_MASK 0x8
#define _URTCON_RXIF_POSN 0x4
#define _URTCON_RXIF_MASK 0x10
#define _URTCON_FERR_POSN 0x5
#define _URTCON_FERR_MASK 0x20
#define _URTCON_TXPIN_POSN 0x6
#define _URTCON_TXPIN_MASK 0x3c0
#define _URTCON_TXPIN0_POSN 0x6
#define _URTCON_TXPIN0_MASK 0x40
#define _URTCON_TXPIN1_POSN 0x7
#define _URTCON_TXPIN1_MASK 0x80
#define _URTCON_TXPIN2_POSN 0x8
#define _URTCON_TXPIN2_MASK 0x100
#define _URTCON_TXPIN3_POSN 0x9
#define _URTCON_TXPIN3_MASK 0x200
#define _URTCON_RXPIN_POSN 0xa
#define _URTCON_RXPIN_MASK 0x3c00
#define _URTCON_RXPIN0_POSN 0xa
#define _URTCON_RXPIN0_MASK 0x400
#define _URTCON_RXPIN1_POSN 0xb
#define _URTCON_RXPIN1_MASK 0x800
#define _URTCON_RXPIN2_POSN 0xc
#define _URTCON_RXPIN2_MASK 0x1000
#define _URTCON_RXPIN3_POSN 0xd
#define _URTCON_RXPIN3_MASK 0x2000

#define _URTTX_TXDATA_POSN 0x0
#define _URTTX_TXDATA_MASK 0xff
#define _URTTX_TXBIT9_POSN 0x8
#define _URTTX_TXBIT9_MASK 0x100

#define _URTRX_RXDATA_POSN 0x0
#define _URTRX_RXDATA_MASK 0xff
#define _URTRX_RXBIT9_POSN 0x8
#define _URTRX_RXBIT9_MASK 0x100

/* I2C0 Config Registers */
#define I2C0CON0 (*((volatile uint32_t *)&_I2C0CON0_))

/* I2C0CON0 bitfield definition */
typedef union
{
    uint32_t I2C0CON0reg;
    struct
    {
        uint8_t I2CEN : 1;
        uint8_t SEN : 1;
        uint8_t RSEN : 1;
        uint8_t PEN : 1;
        uint8_t TXEN : 1;
        uint8_t RXEN : 1;
        uint8_t ACKEN : 1;
        uint8_t ACKDAT : 1;
        uint8_t ACKSTAT : 1;
        uint8_t I2CIF : 1;
        uint8_t I2CBCLF : 1;
        uint8_t I2CTOTF : 1;
        uint8_t I2CDNF : 1;
        uint8_t CLRF : 1;
        uint32_t : 18;
    };
} I2C0CON0bits_t;
#define I2C0CON0bits (*((volatile I2C0CON0bits_t *)&_I2C0CON0_))

#define _I2C0CON0_I2CEN_POSN 0x0
#define _I2C0CON0_I2CEN_MASK 0x1
#define _I2C0CON0_SEN_POSN 0x1
#define _I2C0CON0_SEN_MASK 0x2
#define _I2C0CON0_RSEN_POSN 0x2
#define _I2C0CON0_RSEN_MASK 0x4
#define _I2C0CON0_PEN_POSN 0x3
#define _I2C0CON0_PEN_MASK 0x8
#define _I2C0CON0_TXEN_POSN 0x4
#define _I2C0CON0_TXEN_MASK 0x10
#define _I2C0CON0_RXEN_POSN 0x5
#define _I2C0CON0_RXEN_MASK 0x20
#define _I2C0CON0_ACKEN_POSN 0x6
#define _I2C0CON0_ACKEN_MASK 0x40
#define _I2C0CON0_ACKDAT_POSN 0x7
#define _I2C0CON0_ACKDAT_MASK 0x80
#define _I2C0CON0_ACKSTAT_POSN 0x8
#define _I2C0CON0_ACKSTAT_MASK 0x100
#define _I2C0CON0_I2CIF_POSN 0x9
#define _I2C0CON0_I2CIF_MASK 0x200
#define _I2C0CON0_I2CBCLF_POSN 0xa
#define _I2C0CON0_I2CBCLF_MASK 0x400
#define _I2C0CON0_I2CTOTF_POSN 0xb
#define _I2C0CON0_I2CTOTF_MASK 0x800
#define _I2C0CON0_I2CDNF_POSN 0xc
#define _I2C0CON0_I2CDNF_MASK 0x1000
#define _I2C0CON0_CLRF_POSN 0xd
#define _I2C0CON0_CLRF_MASK 0x2000

#define I2C0CON1 (*((volatile uint32_t *)&_I2C0CON1_))

/* I2C0CON1 bitfield definition */
typedef union
{
    uint32_t I2C0CON1reg;
    struct
    {
        uint32_t BRG : 10;
        uint8_t TOT : 6;
        uint32_t : 16;
    };
} I2C0CON1bits_t;
#define I2C0CON1bits (*((volatile I2C0CON1bits_t *)&_I2C0CON1_))

#define _I2C0CON1_BRG_POSN 0x0
#define _I2C0CON1_BRG_MASK 0x3ff
#define _I2C0CON1_TOT_POSN 0xa
#define _I2C0CON1_TOT_MASK 0xfc00

#define I2C0CON2 (*((volatile uint32_t *)&_I2C0CON2_))

/* I2C0CON2 bitfield definition */
typedef union
{
    uint32_t I2C0CON2reg;
    struct
    {
        uint8_t SDAPIN0 : 1;
        uint8_t SDAPIN1 : 1;
        uint8_t SDAPIN2 : 1;
        uint8_t SDAPIN3 : 1;
        uint8_t SCLPIN0 : 1;
        uint8_t SCLPIN1 : 1;
        uint8_t SCLPIN2 : 1;
        uint8_t SCLPIN3 : 1;
        uint8_t SHTM0 : 1;
        uint8_t SHTM1 : 1;
        uint8_t SHTM2 : 1;
        uint8_t SHTM3 : 1;
        uint32_t : 20;
    };
    struct
    {
        uint8_t SDAPIN : 4;
        uint8_t SCLPIN : 4;
        uint8_t SHTM : 4;
        uint32_t : 20;
    };
} I2C0CON2bits_t;
#define I2C0CON2bits (*((volatile I2C0CON2bits_t *)&_I2C0CON2_))

#define _I2C0CON2_SDAPIN_POSN 0x0
#define _I2C0CON2_SDAPIN_MASK 0xf
#define _I2C0CON2_SDAPIN0_POSN 0x0
#define _I2C0CON2_SDAPIN0_MASK 0x1
#define _I2C0CON2_SDAPIN1_POSN 0x1
#define _I2C0CON2_SDAPIN1_MASK 0x2
#define _I2C0CON2_SDAPIN2_POSN 0x2
#define _I2C0CON2_SDAPIN2_MASK 0x4
#define _I2C0CON2_SDAPIN3_POSN 0x3
#define _I2C0CON2_SDAPIN3_MASK 0x8
#define _I2C0CON2_SCLPIN_POSN 0x4
#define _I2C0CON2_SCLPIN_MASK 0xf0
#define _I2C0CON2_SCLPIN0_POSN 0x4
#define _I2C0CON2_SCLPIN0_MASK 0x10
#define _I2C0CON2_SCLPIN1_POSN 0x5
#define _I2C0CON2_SCLPIN1_MASK 0x20
#define _I2C0CON2_SCLPIN2_POSN 0x6
#define _I2C0CON2_SCLPIN2_MASK 0x40
#define _I2C0CON2_SCLPIN3_POSN 0x7
#define _I2C0CON2_SCLPIN3_MASK 0x80
#define _I2C0CON2_SHTM_POSN 0x8
#define _I2C0CON2_SHTM_MASK 0xf00
#define _I2C0CON2_SHTM0_POSN 0x8
#define _I2C0CON2_SHTM0_MASK 0x100
#define _I2C0CON2_SHTM1_POSN 0x9
#define _I2C0CON2_SHTM1_MASK 0x200
#define _I2C0CON2_SHTM2_POSN 0xa
#define _I2C0CON2_SHTM2_MASK 0x400
#define _I2C0CON2_SHTM3_POSN 0xb
#define _I2C0CON2_SHTM3_MASK 0x800

/* I2C0 Transmit Register */
#define I2C0TX (*((volatile uint32_t *)&_I2C0TX_))

/* I2C0TX bitfield definition */
typedef union
{
    uint32_t I2C0TXreg;
    struct
    {
        uint8_t TXDATA;
        uint32_t : 24;
    };
} I2C0TXbits_t;
#define I2C0TXbits (*((volatile I2C0TXbits_t *)&_I2C0TX_))

#define _I2C0TX_TXDATA_POSN 0x0
#define _I2C0TX_TXDATA_MASK 0xff

/* I2C0 Receive Register */
#define I2C0RX (*((volatile uint32_t *)&_I2C0RX_))

/* I2C0RX bitfield definition */
typedef union
{
    uint32_t I2C0RXreg;
    struct
    {
        uint8_t RXDATA;
        uint32_t : 24;
    };
} I2C0RXbits_t;
#define I2C0RXbits (*((volatile I2C0RXbits_t *)&_I2C0RX_))

#define _I2C0RX_RXDATA_POSN 0x0
#define _I2C0RX_RXDATA_MASK 0xff

/* SPI0 Config Registers */
#define SPI0CON0 (*((volatile uint32_t *)&_SPI0CON0_))

/* SPI0CON0 bitfield definition */
typedef union
{
    uint32_t SPI0CON0reg;
    struct
    {
        uint8_t SPIEN : 1;
        uint8_t CKE : 1;
        uint8_t CKP : 1;
        uint8_t SPIIF : 1;
        uint8_t CLRF : 1;
        uint32_t BRG : 10;
        uint32_t : 17;
    };
} SPI0CON0bits_t;
#define SPI0CON0bits (*((volatile SPI0CON0bits_t *)&_SPI0CON0_))

#define _SPI0CON0_SPIEN_POSN 0x0
#define _SPI0CON0_SPIEN_MASK 0x1
#define _SPI0CON0_SPIMODE_POSN 0x1
#define _SPI0CON0_SPIMODE_MASK 0x6
#define _SPI0CON0_CKE_POSN 0x1
#define _SPI0CON0_CKE_MASK 0x2
#define _SPI0CON0_CKP_POSN 0x2
#define _SPI0CON0_CKP_MASK 0x4
#define _SPI0CON0_SPIIF_POSN 0x3
#define _SPI0CON0_SPIIF_MASK 0x8
#define _SPI0CON0_CLRF_POSN 0x4
#define _SPI0CON0_CLRF_MASK 0x10
#define _SPI0CON0_BRG_POSN 0x5
#define _SPI0CON0_BRG_MASK 0x7fe0

#define SPI0CON1 (*((volatile uint32_t *)&_SPI0CON1_))

/* SPI0CON1 bitfield definition */
typedef union
{
    uint32_t SPI0CON1reg;
    struct
    {
        uint8_t SCLKPIN0 : 1;
        uint8_t SCLKPIN1 : 1;
        uint8_t SCLKPIN2 : 1;
        uint8_t SCLKPIN3 : 1;
        uint8_t SDOPIN0 : 1;
        uint8_t SDOPIN1 : 1;
        uint8_t SDOPIN2 : 1;
        uint8_t SDOPIN3 : 1;
        uint8_t SDIPIN0 : 1;
        uint8_t SDIPIN1 : 1;
        uint8_t SDIPIN2 : 1;
        uint8_t SDIPIN3 : 1;
        uint8_t SSPIN0 : 1;
        uint8_t SSPIN1 : 1;
        uint8_t SSPIN2 : 1;
        uint8_t SSPIN3 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint32_t SCLKPIN : 4;
        uint32_t SDOPIN : 4;
        uint32_t SDIPIN : 4;
        uint32_t SSPIN : 4;
        uint32_t : 16;
    };
} SPI0CON1bits_t;
#define SPI0CON1bits (*((volatile SPI0CON1bits_t *)&_SPI0CON1_))

#define _SPI0CON1_SCLKPIN_POSN 0x0
#define _SPI0CON1_SCLKPIN_MASK 0xf
#define _SPI0CON1_SCLKPIN0_POSN 0x0
#define _SPI0CON1_SCLKPIN0_MASK 0x1
#define _SPI0CON1_SCLKPIN1_POSN 0x1
#define _SPI0CON1_SCLKPIN1_MASK 0x2
#define _SPI0CON1_SCLKPIN2_POSN 0x2
#define _SPI0CON1_SCLKPIN2_MASK 0x4
#define _SPI0CON1_SCLKPIN3_POSN 0x3
#define _SPI0CON1_SCLKPIN3_MASK 0x8
#define _SPI0CON1_SDOPIN_POSN 0x4
#define _SPI0CON1_SDOPIN_MASK 0xf0
#define _SPI0CON1_SDOPIN0_POSN 0x4
#define _SPI0CON1_SDOPIN0_MASK 0x10
#define _SPI0CON1_SDOPIN1_POSN 0x5
#define _SPI0CON1_SDOPIN1_MASK 0x20
#define _SPI0CON1_SDOPIN2_POSN 0x6
#define _SPI0CON1_SDOPIN2_MASK 0x40
#define _SPI0CON1_SDOPIN3_POSN 0x7
#define _SPI0CON1_SDOPIN3_MASK 0x80
#define _SPI0CON1_SDIPIN_POSN 0x8
#define _SPI0CON1_SDIPIN_MASK 0xf00
#define _SPI0CON1_SDIPIN0_POSN 0x8
#define _SPI0CON1_SDIPIN0_MASK 0x100
#define _SPI0CON1_SDIPIN1_POSN 0x9
#define _SPI0CON1_SDIPIN1_MASK 0x200
#define _SPI0CON1_SDIPIN2_POSN 0xa
#define _SPI0CON1_SDIPIN2_MASK 0x400
#define _SPI0CON1_SDIPIN3_POSN 0xb
#define _SPI0CON1_SDIPIN3_MASK 0x800
#define _SPI0CON1_SSPIN_POSN 0xc
#define _SPI0CON1_SSPIN_MASK 0xf000
#define _SPI0CON1_SSPIN0_POSN 0xc
#define _SPI0CON1_SSPIN0_MASK 0x1000
#define _SPI0CON1_SSPIN1_POSN 0xd
#define _SPI0CON1_SSPIN1_MASK 0x2000
#define _SPI0CON1_SSPIN2_POSN 0xe
#define _SPI0CON1_SSPIN2_MASK 0x4000
#define _SPI0CON1_SSPIN3_POSN 0xf
#define _SPI0CON1_SSPIN3_MASK 0x8000

/* SPI0 Transmit Register */
#define SPI0TX (*((volatile uint32_t *)&_SPI0TX_))

/* SPI0TX bitfield definition */
typedef union
{
    uint32_t SPI0TXreg;
    struct
    {
        uint8_t TXDATA;
        uint32_t : 24;
    };
} SPI0TXbits_t;
#define SPI0TXbits (*((volatile SPI0TXbit_t *)&_SPI0TX_))

#define _SPI0TX_TXDATA_POSN 0x0
#define _SPI0TX_TXDATA_MASK 0xff

/* SPI0 Receive Register */
#define SPI0RX (*((volatile uint32_t *)&_SPI0RX_))

/* SPI0RX bitfield definition */
typedef union
{
    uint32_t SPI0RXreg;
    struct
    {
        uint8_t RXDATA;
        uint32_t : 24;
    };
} SPI0RXbits_t;
#define SPI0RXbits (*((volatile SPI0RXbits_t *)&_SPI0RX_))

#define _SPI0RX_RXDATA_POSN 0x0
#define _SPI0RX_RXDATA_MASK 0xff

/*************************************************************/
/* External Interrupt Registers */

/* External Interrupt0 Config Register */
#define EXT0CON (*((volatile uint32_t *)&_EXT0CON_))

/* EXT0CON bitfield definition */
typedef union
{
    uint32_t EXT0CONreg;
    struct
    {
        uint8_t TRIG0EN : 1;
        uint8_t EDGE : 1;
        uint8_t TRIGPIN0 : 1;
        uint8_t TRIGPIN1 : 1;
        uint8_t TRIGPIN2 : 1;
        uint8_t TRIGPIN3 : 1;
        uint32_t : 26;
    };
    struct
    {
        uint8_t : 2;
        uint8_t TRIGPIN : 4;
        uint32_t : 26;
    };
} EXT0CONbits_t;
#define EXT0CONbits (*((volatile EXT0CONbits_t *)&_EXT0CON_))

#define _EXT0CON_TRIG0EN_POSN 0x0
#define _EXT0CON_TRIG0EN_MASK 0x1
#define _EXT0CON_EDGE_POSN 0x1
#define _EXT0CON_EDGE_MASK 0x2
#define _EXT0CON_TRIGPIN_POSN 0x2
#define _EXT0CON_TRIGPIN_MASK 0x3c
#define _EXT0CON_TRIGPIN0_POSN 0x2
#define _EXT0CON_TRIGPIN0_MASK 0x4
#define _EXT0CON_TRIGPIN1_POSN 0x3
#define _EXT0CON_TRIGPIN1_MASK 0x8
#define _EXT0CON_TRIGPIN2_POSN 0x4
#define _EXT0CON_TRIGPIN2_MASK 0x10
#define _EXT0CON_TRIGPIN3_POSN 0x5
#define _EXT0CON_TRIGPIN3_MASK 0x20

/* External Interrupt1 Config Register */
#define EXT1CON (*((volatile uint32_t *)&_EXT1CON_))

/* EXT1CON bitfield definition */
typedef union
{
    uint32_t EXT1CONreg;
    struct
    {
        uint8_t TRIG1EN : 1;
        uint8_t EDGE : 1;
        uint8_t TRIGPIN0 : 1;
        uint8_t TRIGPIN1 : 1;
        uint8_t TRIGPIN2 : 1;
        uint8_t TRIGPIN3 : 1;
        uint32_t : 26;
    };
    struct
    {
        uint8_t : 2;
        uint8_t TRIGPIN : 4;
        uint32_t : 26;
    };
} EXT1CONbits_t;
#define EXT1CONbits (*((volatile EXT1CONbits_t *)&_EXT1CON_))

#define _EXT1CON_TRIG1EN_POSN 0x0
#define _EXT1CON_TRIG1EN_MASK 0x1
#define _EXT1CON_EDGE_POSN 0x1
#define _EXT1CON_EDGE_MASK 0x2
#define _EXT1CON_TRIGPIN_POSN 0x2
#define _EXT1CON_TRIGPIN_MASK 0x3c
#define _EXT1CON_TRIGPIN0_POSN 0x2
#define _EXT1CON_TRIGPIN0_MASK 0x4
#define _EXT1CON_TRIGPIN1_POSN 0x3
#define _EXT1CON_TRIGPIN1_MASK 0x8
#define _EXT1CON_TRIGPIN2_POSN 0x4
#define _EXT1CON_TRIGPIN2_MASK 0x10
#define _EXT1CON_TRIGPIN3_POSN 0x5
#define _EXT1CON_TRIGPIN3_MASK 0x20

/* External Interrupt2 Config Register */
#define EXT2CON (*((volatile uint32_t *)&_EXT2CON_))

/* EXT2CON bitfield definition */
typedef union
{
    uint32_t EXT2CONreg;
    struct
    {
        uint8_t TRIG2EN : 1;
        uint8_t EDGE : 1;
        uint8_t TRIGPIN0 : 1;
        uint8_t TRIGPIN1 : 1;
        uint8_t TRIGPIN2 : 1;
        uint8_t TRIGPIN3 : 1;
        uint32_t : 26;
    };
    struct
    {
        uint8_t : 2;
        uint8_t TRIGPIN : 4;
        uint32_t : 26;
    };
} EXT2CONbits_t;
#define EXT2CONbits (*((volatile EXT2CONbits_t *)&_EXT2CON_))

#define _EXT2CON_TRIG2EN_POSN 0x0
#define _EXT2CON_TRIG2EN_MASK 0x1
#define _EXT2CON_EDGE_POSN 0x1
#define _EXT2CON_EDGE_MASK 0x2
#define _EXT2CON_TRIGPIN_POSN 0x2
#define _EXT2CON_TRIGPIN_MASK 0x3c
#define _EXT2CON_TRIGPIN0_POSN 0x2
#define _EXT2CON_TRIGPIN0_MASK 0x4
#define _EXT2CON_TRIGPIN1_POSN 0x3
#define _EXT2CON_TRIGPIN1_MASK 0x8
#define _EXT2CON_TRIGPIN2_POSN 0x4
#define _EXT2CON_TRIGPIN2_MASK 0x10
#define _EXT2CON_TRIGPIN3_POSN 0x5
#define _EXT2CON_TRIGPIN3_MASK 0x20

/* External Interrupt3 Config Register */
#define EXT3CON (*((volatile uint32_t *)&_EXT3CON_))

/* EXT3CON bitfield definition */
typedef union
{
    uint32_t EXT3CONreg;
    struct
    {
        uint8_t TRIG3EN : 1;
        uint8_t EDGE : 1;
        uint8_t TRIGPIN0 : 1;
        uint8_t TRIGPIN1 : 1;
        uint8_t TRIGPIN2 : 1;
        uint8_t TRIGPIN3 : 1;
        uint32_t : 26;
    };
    struct
    {
        uint8_t : 2;
        uint8_t TRIGPIN : 4;
        uint32_t : 26;
    };
} EXT3CONbits_t;
#define EXT3CONbits (*((volatile EXT3CONbits_t *)&_EXT3CON_))

#define _EXT3CON_TRIG3EN_POSN 0x0
#define _EXT3CON_TRIG3EN_MASK 0x1
#define _EXT3CON_EDGE_POSN 0x1
#define _EXT3CON_EDGE_MASK 0x2
#define _EXT3CON_TRIGPIN_POSN 0x2
#define _EXT3CON_TRIGPIN_MASK 0x3c
#define _EXT3CON_TRIGPIN0_POSN 0x2
#define _EXT3CON_TRIGPIN0_MASK 0x4
#define _EXT3CON_TRIGPIN1_POSN 0x3
#define _EXT3CON_TRIGPIN1_MASK 0x8
#define _EXT3CON_TRIGPIN2_POSN 0x4
#define _EXT3CON_TRIGPIN2_MASK 0x10
#define _EXT3CON_TRIGPIN3_POSN 0x5
#define _EXT3CON_TRIGPIN3_MASK 0x20

/*************************************************************/
/* PWM Registers */

/* PWM0 Config Register */
#define PWM0CON (*((volatile uint32_t *)&_PWM0CON_))

/* PWM0CON bitfield definition */
typedef union
{
    uint32_t PWM0CONreg;
    struct
    {
        uint32_t PWM0PR : 12;
        uint8_t PWM0PIN0 : 1;
        uint8_t PWM0PIN1 : 1;
        uint8_t PWM0PIN2 : 1;
        uint8_t PWM0PIN3 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint32_t : 12;
        uint8_t PWM0PIN : 4;
        uint32_t : 16;
    };
} PWM0CONbits_t;
#define PWM0CONbits (*((volatile PWM0CONbits_t *)&_PWM0CON_))

#define _PWM0CON_PWM0PR_POSN 0x0
#define _PWM0CON_PWM0PR_MASK 0xfff
#define _PWM0CON_PWM0PIN_POSN 0xc
#define _PWM0CON_PWM0PIN_MASK 0xf000
#define _PWM0CON_PWM0PIN0_POSN 0xc
#define _PWM0CON_PWM0PIN0_MASK 0x1000
#define _PWM0CON_PWM0PIN1_POSN 0xd
#define _PWM0CON_PWM0PIN1_MASK 0x2000
#define _PWM0CON_PWM0PIN2_POSN 0xe
#define _PWM0CON_PWM0PIN2_MASK 0x4000
#define _PWM0CON_PWM0PIN3_POSN 0xf
#define _PWM0CON_PWM0PIN3_MASK 0x8000

/* PWM0 Duty Cycle Register */
#define PWM0DC (*((volatile uint32_t *)&_PWM0DC_))

/* PWM0DC bitfield definition */
typedef union
{
    uint32_t PWM0DCreg;
    struct
    {
        uint32_t PWM0DTYCYC : 12;
        uint32_t : 20;
    };
} PWM0DCbits_t;
#define PWM0DCbits (*((volatile PWM0DCbits_t *)&_PWM0DC_))

#define _PWM0DC_PWM0DTYCYC_POSN 0x0
#define _PWM0DC_PWM0DTYCYC_MASK 0xfff

/* PWM1 Config Register */
#define PWM1CON (*((volatile uint32_t *)&_PWM1CON_))

/* PWM1CON bitfield definition */
typedef union
{
    uint32_t PWM1CONreg;
    struct
    {
        uint32_t PWM1PR : 12;
        uint8_t PWM1PIN0 : 1;
        uint8_t PWM1PIN1 : 1;
        uint8_t PWM1PIN2 : 1;
        uint8_t PWM1PIN3 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint32_t : 12;
        uint8_t PWM1PIN : 4;
        uint32_t : 16;
    };
} PWM1CONbits_t;
#define PWM1CONbits (*((volatile PWM1CONbits_t *)&_PWM1CON_))

#define _PWM1CON_PWM1PR_POSN 0x0
#define _PWM1CON_PWM1PR_MASK 0xfff
#define _PWM1CON_PWM1PIN_POSN 0xc
#define _PWM1CON_PWM1PIN_MASK 0xf000
#define _PWM1CON_PWM1PIN0_POSN 0xc
#define _PWM1CON_PWM1PIN0_MASK 0x1000
#define _PWM1CON_PWM1PIN1_POSN 0xd
#define _PWM1CON_PWM1PIN1_MASK 0x2000
#define _PWM1CON_PWM1PIN2_POSN 0xe
#define _PWM1CON_PWM1PIN2_MASK 0x4000
#define _PWM1CON_PWM1PIN3_POSN 0xf
#define _PWM1CON_PWM1PIN3_MASK 0x8000

/* PWM1 Duty Cycle Register */
#define PWM1DC (*((volatile uint32_t *)&_PWM1DC_))

/* PWM1DC bitfield definition */
typedef union
{
    uint32_t PWM1DCreg;
    struct
    {
        uint32_t PWM1DTYCYC : 12;
        uint32_t : 20;
    };
} PWM1DCbits_t;
#define PWM1DCbits (*((volatile PWM1DCbits_t *)&_PWM1DC_))

#define _PWM1DC_PWM1DTYCYC_POSN 0x0
#define _PWM1DC_PWM1DTYCYC_MASK 0xfff

/* PWM2 Config Register */
#define PWM2CON (*((volatile uint32_t *)&_PWM2CON_))

/* PWM2CON bitfield definition */
typedef union
{
    uint32_t PWM2CONreg;
    struct
    {
        uint32_t PWM2PR : 12;
        uint8_t PWM2PIN0 : 1;
        uint8_t PWM2PIN1 : 1;
        uint8_t PWM2PIN2 : 1;
        uint8_t PWM2PIN3 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint32_t : 12;
        uint8_t PWM2PIN : 4;
        uint32_t : 16;
    };
} PWM2CONbits_t;
#define PWM2CONbits (*((volatile PWM2CONbits_t *)&_PWM2CON_))

#define _PWM2CON_PWM2PR_POSN 0x0
#define _PWM2CON_PWM2PR_MASK 0xfff
#define _PWM2CON_PWM2PIN_POSN 0xc
#define _PWM2CON_PWM2PIN_MASK 0xf000
#define _PWM2CON_PWM2PIN0_POSN 0xc
#define _PWM2CON_PWM2PIN0_MASK 0x1000
#define _PWM2CON_PWM2PIN1_POSN 0xd
#define _PWM2CON_PWM2PIN1_MASK 0x2000
#define _PWM2CON_PWM2PIN2_POSN 0xe
#define _PWM2CON_PWM2PIN2_MASK 0x4000
#define _PWM2CON_PWM2PIN3_POSN 0xf
#define _PWM2CON_PWM2PIN3_MASK 0x8000

/* PWM2 Duty Cycle Register */
#define PWM2DC (*((volatile uint32_t *)&_PWM2DC_))

/* PWM2DC bitfield definition */
typedef union
{
    uint32_t PWM2DCreg;
    struct
    {
        uint32_t PWM2DTYCYC : 12;
        uint32_t : 20;
    };
} PWM2DCbits_t;
#define PWM2DCbits (*((volatile PWM2DCbits_t *)&_PWM2DC_))

#define _PWM2DC_PWM2DTYCYC_POSN 0x0
#define _PWM2DC_PWM2DTYCYC_MASK 0xfff

/* PWM3 Config Register */
#define PWM3CON (*((volatile uint32_t *)&_PWM3CON_))

/* PWM3CON bitfield definition */
typedef union
{
    uint32_t PWM3CONreg;
    struct
    {
        uint32_t PWM3PR : 12;
        uint8_t PWM3PIN0 : 1;
        uint8_t PWM3PIN1 : 1;
        uint8_t PWM3PIN2 : 1;
        uint8_t PWM3PIN3 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint32_t : 12;
        uint8_t PWM3PIN : 4;
        uint32_t : 16;
    };
} PWM3CONbits_t;
#define PWM3CONbits (*((volatile PWM3CONbits_t *)&_PWM3CON_))

#define _PWM3CON_PWM3PR_POSN 0x0
#define _PWM3CON_PWM3PR_MASK 0xfff
#define _PWM3CON_PWM3PIN_POSN 0xc
#define _PWM3CON_PWM3PIN_MASK 0xf000
#define _PWM3CON_PWM3PIN0_POSN 0xc
#define _PWM3CON_PWM3PIN0_MASK 0x1000
#define _PWM3CON_PWM3PIN1_POSN 0xd
#define _PWM3CON_PWM3PIN1_MASK 0x2000
#define _PWM3CON_PWM3PIN2_POSN 0xe
#define _PWM3CON_PWM3PIN2_MASK 0x4000
#define _PWM3CON_PWM3PIN3_POSN 0xf
#define _PWM3CON_PWM3PIN3_MASK 0x8000

/* PWM3 Duty Cycle Register */
#define PWM3DC (*((volatile uint32_t *)&_PWM3DC_))

/* PWM3DC bitfield definition */
typedef union
{
    uint32_t PWM3DCreg;
    struct
    {
        uint32_t PWM3DTYCYC : 12;
        uint32_t : 20;
    };
} PWM3DCbits_t;
#define PWM3DCbits (*((volatile PWM3DCbits_t *)&_PWM3DC_))

#define _PWM3DC_PWM3DTYCYC_POSN 0x0
#define _PWM3DC_PWM3DTYCYC_MASK 0xfff

/* PWM4 Config Register */
#define PWM4CON (*((volatile uint32_t *)&_PWM4CON_))

/* PWM4CON bitfield definition */
typedef union
{
    uint32_t PWM4CONreg;
    struct
    {
        uint32_t PWM4PR : 12;
        uint8_t PWM4PIN0 : 1;
        uint8_t PWM4PIN1 : 1;
        uint8_t PWM4PIN2 : 1;
        uint8_t PWM4PIN3 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint32_t : 12;
        uint8_t PWM4PIN : 4;
        uint32_t : 16;
    };
} PWM4CONbits_t;
#define PWM4CONbits (*((volatile PWM4CONbits_t *)&_PWM4CON_))

#define _PWM4CON_PWM4PR_POSN 0x0
#define _PWM4CON_PWM4PR_MASK 0xfff
#define _PWM4CON_PWM4PIN_POSN 0xc
#define _PWM4CON_PWM4PIN_MASK 0xf000
#define _PWM4CON_PWM4PIN0_POSN 0xc
#define _PWM4CON_PWM4PIN0_MASK 0x1000
#define _PWM4CON_PWM4PIN1_POSN 0xd
#define _PWM4CON_PWM4PIN1_MASK 0x2000
#define _PWM4CON_PWM4PIN2_POSN 0xe
#define _PWM4CON_PWM4PIN2_MASK 0x4000
#define _PWM4CON_PWM4PIN3_POSN 0xf
#define _PWM4CON_PWM4PIN3_MASK 0x8000

/* PWM4 Duty Cycle Register */
#define PWM4DC (*((volatile uint32_t *)&_PWM4DC_))

/* PWM4DC bitfield definition */
typedef union
{
    uint32_t PWM4DCreg;
    struct
    {
        uint32_t PWM4DTYCYC : 12;
        uint32_t : 20;
    };
} PWM4DCbits_t;
#define PWM4DCbits (*((volatile PWM4DCbits_t *)&_PWM4DC_))

#define _PWM4DC_PWM4DTYCYC_POSN 0x0
#define _PWM4DC_PWM4DTYCYC_MASK 0xfff

/* PWM5 Config Register */
#define PWM5CON (*((volatile uint32_t *)&_PWM5CON_))

/* PWM5CON bitfield definition */
typedef union
{
    uint32_t PWM5CONreg;
    struct
    {
        uint32_t PWM5PR : 12;
        uint8_t PWM5PIN0 : 1;
        uint8_t PWM5PIN1 : 1;
        uint8_t PWM5PIN2 : 1;
        uint8_t PWM5PIN3 : 1;
        uint32_t : 16;
    };
    struct
    {
        uint32_t : 12;
        uint8_t PWM5PIN : 4;
        uint32_t : 16;
    };
} PWM5CONbits_t;
#define PWM5CONbits (*((volatile PWM5CONbits_t *)&_PWM5CON_))

#define _PWM5CON_PWM5PR_POSN 0x0
#define _PWM5CON_PWM5PR_MASK 0xfff
#define _PWM5CON_PWM5PIN_POSN 0xc
#define _PWM5CON_PWM5PIN_MASK 0xf000
#define _PWM5CON_PWM5PIN0_POSN 0xc
#define _PWM5CON_PWM5PIN0_MASK 0x1000
#define _PWM5CON_PWM5PIN1_POSN 0xd
#define _PWM5CON_PWM5PIN1_MASK 0x2000
#define _PWM5CON_PWM5PIN2_POSN 0xe
#define _PWM5CON_PWM5PIN2_MASK 0x4000
#define _PWM5CON_PWM5PIN3_POSN 0xf
#define _PWM5CON_PWM5PIN3_MASK 0x8000

/* PWM5 Duty Cycle Register */
#define PWM5DC (*((volatile uint32_t *)&_PWM5DC_))

/* PWM5DC bitfield definition */
typedef union
{
    uint32_t PWM5DCreg;
    struct
    {
        uint32_t PWM5DTYCYC : 12;
        uint32_t : 20;
    };
} PWM5DCbits_t;
#define PWM5DCbits (*((volatile PWM5DCbits_t *)&_PWM5DC_))

#define _PWM5DC_PWM5DTYCYC_POSN 0x0
#define _PWM5DC_PWM5DTYCYC_MASK 0xfff

/* PWM Class masks */
#define _PWMCON_PWMPR_POSN 0x0
#define _PWMCON_PWMPR_MASK 0xfff
#define _PWMCON_PWMPIN_POSN 0xc
#define _PWMCON_PWMPIN_MASK 0xf000
#define _PWMCON_PWMPIN0_POSN 0xc
#define _PWMCON_PWMPIN0_MASK 0x1000
#define _PWMCON_PWMPIN1_POSN 0xd
#define _PWMCON_PWMPIN1_MASK 0x2000
#define _PWMCON_PWMPIN2_POSN 0xe
#define _PWMCON_PWMPIN2_MASK 0x4000
#define _PWMCON_PWMPIN3_POSN 0xf
#define _PWMCON_PWMPIN3_MASK 0x8000

#define _PWMDC_PWMDTYCYC_POSN 0x0
#define _PWMDC_PWMDTYCYC_MASK 0xfff

#endif /* _PRV_HWREG_H_*/
