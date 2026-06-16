/**
 * @file    prv_plic.c
 * @brief   APIs for Interrupt configurations.
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "prv_plic.h"

/**
 * @brief API to attach peripheral to Interrupt0 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt0(const PLIC_INTERRUPT_CONFIG_t *config)
{
    INTMAP->INT0ATCH = config->attach_interrupt_module;
    PLIC_PRIORITY->INT0PRIORITY = ( uint32_t ) (config->set_priority & _INT0PRIO_PRIO_MASK);
}

/**
 * @brief API to attach peripheral to Interrupt1 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt1(const PLIC_INTERRUPT_CONFIG_t *config)
{
    INTMAP->INT1ATCH = config->attach_interrupt_module;
    PLIC_PRIORITY->INT1PRIORITY = ( uint32_t ) (config->set_priority & _INT1PRIO_PRIO_MASK);
}

/**
 * @brief API to attach peripheral to Interrupt2 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt2(const PLIC_INTERRUPT_CONFIG_t *config)
{
    INTMAP->INT2ATCH = config->attach_interrupt_module;
    PLIC_PRIORITY->INT2PRIORITY = ( uint32_t ) (config->set_priority & _INT2PRIO_PRIO_MASK);
}

/**
 * @brief API to attach peripheral to Interrupt3 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt3(const PLIC_INTERRUPT_CONFIG_t *config)
{
    INTMAP->INT3ATCH = config->attach_interrupt_module;
    PLIC_PRIORITY->INT3PRIORITY = ( uint32_t ) (config->set_priority & _INT3PRIO_PRIO_MASK);
}

/**
 * @brief API to attach peripheral to Interrupt4 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt4(const PLIC_INTERRUPT_CONFIG_t *config)
{
    INTMAP->INT4ATCH = config->attach_interrupt_module;
    PLIC_PRIORITY->INT4PRIORITY = ( uint32_t ) (config->set_priority & _INT4PRIO_PRIO_MASK);
}

/**
 * @brief API to attach peripheral to Interrupt5 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt5(const PLIC_INTERRUPT_CONFIG_t *config)
{
    INTMAP->INT5ATCH = config->attach_interrupt_module;
    PLIC_PRIORITY->INT5PRIORITY = ( uint32_t ) (config->set_priority & _INT5PRIO_PRIO_MASK);
}

/**
 * @brief API to attach peripheral to Interrupt6 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt6(const PLIC_INTERRUPT_CONFIG_t *config)
{
    INTMAP->INT6ATCH = config->attach_interrupt_module;
    PLIC_PRIORITY->INT6PRIORITY = ( uint32_t ) (config->set_priority & _INT6PRIO_PRIO_MASK);
}

/**
 * @brief API to attach peripheral to Interrupt7 and set priority.
 * 
 * @param config Interrupt configurations. Use PLIC_INTERRUPT_CONFIG_t structure to set the required configurations.
 */
void Set_Interrupt7(const PLIC_INTERRUPT_CONFIG_t *config)
{
    INTMAP->INT7ATCH = config->attach_interrupt_module;
    PLIC_PRIORITY->INT7PRIORITY = ( uint32_t ) (config->set_priority & _INT7PRIO_PRIO_MASK);
}

/*************************************************************/

/**
 * @brief API to set Interrupt0 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt0Priority(const INT_PRIORITY_LEVEL_t priority)
{
    PLIC_PRIORITY->INT0PRIORITY = ( uint32_t ) (priority & _INT0PRIO_PRIO_MASK);
}

/**
 * @brief API to set Interrupt1 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt1priority(const INT_PRIORITY_LEVEL_t priority)
{
    PLIC_PRIORITY->INT1PRIORITY = ( uint32_t ) (priority & _INT1PRIO_PRIO_MASK);
}

/**
 * @brief API to set Interrupt2 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt2Priority(const INT_PRIORITY_LEVEL_t priority)
{
    PLIC_PRIORITY->INT2PRIORITY = ( uint32_t ) (priority & _INT2PRIO_PRIO_MASK);
}

/**
 * @brief API to set Interrupt3 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt3Priority(const INT_PRIORITY_LEVEL_t priority)
{
    PLIC_PRIORITY->INT3PRIORITY = ( uint32_t ) (priority & _INT3PRIO_PRIO_MASK);
}

/**
 * @brief API to set Interrupt4 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt4Priority(const INT_PRIORITY_LEVEL_t priority)
{
    PLIC_PRIORITY->INT4PRIORITY = ( uint32_t ) (priority & _INT4PRIO_PRIO_MASK);
}

/**
 * @brief API to set Interrupt5 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt5Priority(const INT_PRIORITY_LEVEL_t priority)
{
    PLIC_PRIORITY->INT5PRIORITY = ( uint32_t ) (priority & _INT5PRIO_PRIO_MASK);
}

/**
 * @brief API to set Interrupt6 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt6Priority(const INT_PRIORITY_LEVEL_t priority)
{
    PLIC_PRIORITY->INT6PRIORITY = ( uint32_t ) (priority & _INT6PRIO_PRIO_MASK);
}

/**
 * @brief API to set Interrupt7 priority
 * 
 * @param priority Priority value. Use INT_PRIORITY_LEVEL_t enum to set the priority value.
 */
void Set_Interrupt7Priority(const INT_PRIORITY_LEVEL_t priority)
{
    PLIC_PRIORITY->INT7PRIORITY = ( uint32_t ) (priority & _INT7PRIO_PRIO_MASK);
}