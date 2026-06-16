/**
 * @file    prv_plic.h
 * @brief   APIs for Interrupt configurations.
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_PLIC_H_
#define _PRV_PLIC_H_

#include "prv_interrupt.h"

#define PLIC_PRIORITY ((PLIC_PRIORITY_t *)_PLIC_PRIORITY_)
#define INTMAP ((PLIC_INTMAP_t *)_INTMAP_)

/* Interrupt Mapping definition - assigns number to each peripherals to map it to the interrupts */
typedef enum
{
    NO_INTERRUPT = 0,
    ATTACH_TIMER0A_TO_INTERRUPT,
    ATTACH_TIMER0B_TO_INTERRUPT,
    ATTACH_TIMER1A_TO_INTERRUPT,
    ATTACH_TIMER1B_TO_INTERRUPT,
    ATTACH_TIMER2A_TO_INTERRUPT,
    ATTACH_TIMER2B_TO_INTERRUPT,
    ATTACH_TIMER3A_TO_INTERRUPT,
    ATTACH_TIMER3B_TO_INTERRUPT,
    ATTACH_TIMER4_TO_INTERRUPT,
    ATTACH_TIMER4ICF_TO_INTERRUPT,
    ATTACH_TIMER5_TO_INTERRUPT,
    ATTACH_TIMER5ICF_TO_INTERRUPT,
    ATTACH_UART0RX_TO_INTERRUPT,
    ATTACH_UART0TX_TO_INTERRUPT,
    ATTACH_UART1RX_TO_INTERRUPT,
    ATTACH_UART1TX_TO_INTERRUPT,
    ATTACH_I2C0IF_TO_INTERRUPT,
    ATTACH_I2C0BCLF_TO_INTERRUPT,
    ATTACH_I2C0TOTF_TO_INTERRUPT,
    ATTACH_I2C0DNF_TO_INTERRUPT,
    ATTACH_SPI0IF_TO_INTERRUPT,
    ATTACH_EXTINT0_TO_INTERRUPT,
    ATTACH_EXTINT1_TO_INTERRUPT,
    ATTACH_EXTINT2_TO_INTERRUPT,
    ATTACH_EXTINT3_TO_INTERRUPT,
} INT_MAP_t;

/* Interrupt Priority definition */
typedef enum
{
    INTERRUPT_OFF = 0,
    INTERRUPT_PRIORITY_1,
    INTERRUPT_PRIORITY_2,
    INTERRUPT_PRIORITY_3,
    INTERRUPT_PRIORITY_4,
    INTERRUPT_PRIORITY_5,
    INTERRUPT_PRIORITY_6,
    INTERRUPT_PRIORITY_7,
    INTERRUPT_PRIORITY_MINIMUM = 1,
    INTERRUPT_PRIORITY_MAXIMUM = 7,
} INT_PRIORITY_LEVEL_t;

/* Structure defining the Configuration of Interrupts */
typedef struct
{
    INT_MAP_t attach_interrupt_module;
    INT_PRIORITY_LEVEL_t set_priority;
} PLIC_INTERRUPT_CONFIG_t;

/*************************************************************/
/* *** Mapped to Hardware *** */

/* Structure defining the PLIC Interrupt Priority Registers accessible to the user - mapped to the hardware */
typedef struct
{
    _IO_ uint32_t INT0PRIORITY;
    _IO_ uint32_t INT1PRIORITY;
    _IO_ uint32_t INT2PRIORITY;
    _IO_ uint32_t INT3PRIORITY;
    _IO_ uint32_t INT4PRIORITY;
    _IO_ uint32_t INT5PRIORITY;
    _IO_ uint32_t INT6PRIORITY;
    _IO_ uint32_t INT7PRIORITY;
} PLIC_PRIORITY_t;

/* Structure defining the Interrupt Mapping Registers - mapped to the hardware */
typedef struct
{
    _IO_ uint32_t INT0ATCH;
    _IO_ uint32_t INT1ATCH;
    _IO_ uint32_t INT2ATCH;
    _IO_ uint32_t INT3ATCH;
    _IO_ uint32_t INT4ATCH;
    _IO_ uint32_t INT5ATCH;
    _IO_ uint32_t INT6ATCH;
    _IO_ uint32_t INT7ATCH;
} PLIC_INTMAP_t;

/*************************************************************/
/* API to attach and set the interrupt priority */

/**
 * @brief API to attach peripheral to Interrupt0 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt0(const PLIC_INTERRUPT_CONFIG_t *config);

/**
 * @brief API to attach peripheral to Interrupt1 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt1(const PLIC_INTERRUPT_CONFIG_t *config);

/**
 * @brief API to attach peripheral to Interrupt2 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt2(const PLIC_INTERRUPT_CONFIG_t *config);

/**
 * @brief API to attach peripheral to Interrupt3 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt3(const PLIC_INTERRUPT_CONFIG_t *config);

/**
 * @brief API to attach peripheral to Interrupt4 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt4(const PLIC_INTERRUPT_CONFIG_t *config);

/**
 * @brief API to attach peripheral to Interrupt5 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt5(const PLIC_INTERRUPT_CONFIG_t *config);

/**
 * @brief API to attach peripheral to Interrupt6 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt6(const PLIC_INTERRUPT_CONFIG_t *config);

/**
 * @brief API to attach peripheral to Interrupt7 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt7(const PLIC_INTERRUPT_CONFIG_t *config);

/*************************************************************/
/* API to Set the Interrupt Priorities after it has been already configured */

/**
 * @brief API to set Interrupt0 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt0Priority(const INT_PRIORITY_LEVEL_t priority);

/**
 * @brief API to set Interrupt1 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt1priority(const INT_PRIORITY_LEVEL_t priority);

/**
 * @brief API to set Interrupt2 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt2Priority(const INT_PRIORITY_LEVEL_t priority);

/**
 * @brief API to set Interrupt3 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt3Priority(const INT_PRIORITY_LEVEL_t priority);

/**
 * @brief API to set Interrupt4 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt4Priority(const INT_PRIORITY_LEVEL_t priority);

/**
 * @brief API to set Interrupt5 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt5Priority(const INT_PRIORITY_LEVEL_t priority);

/**
 * @brief API to set Interrupt6 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt6Priority(const INT_PRIORITY_LEVEL_t priority);

/**
 * @brief API to set Interrupt7 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt7Priority(const INT_PRIORITY_LEVEL_t priority);

#endif /* _PRV_PLIC_H_ */