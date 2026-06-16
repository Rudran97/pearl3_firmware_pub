/**
 * @file    prv_ict.c
 * @brief   APIs for Input Capture Timer modules.
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "prv_ict.h"

/**
 * @brief API to Setup ICT Module.
 * 
 * @param module Constant pointer to ICT modules to access hardware registers. Pass ICT0, ICT1 as module parameters.
 * @param config ICT module configurations. Use ICT_CONFIG_t structure to set the required configurations.
 */
void ICT_SetTimer(TIMER_ICT_t *const module, ICT_CONFIG_t *config)
{
    uint32_t timer_prescale = config->timer_param.prescale;
    uint32_t timer_match_value = config->timer_param.match_value;
    uint32_t capture_prescale = config->capture_param.prescale;
    uint32_t start_edge = config->capture_param.ic_start_edge;
    uint32_t start_pin = config->capture_param.ic_start_trigger_pin;
    uint32_t end_edge = config->capture_param.ic_end_edge;
    uint32_t end_pin = config->capture_param.ic_end_trigger_pin;

    switch (config->mode)
    {
    case ICT_MODE_TIMER:
        module->TL = timer_prescale;
        module->TH = timer_match_value;
        module->TCON = _ICT_TCON_TSET_MASK;
        break;
    case ICT_MODE_INPUT_CAPTURE:
        module->TL = capture_prescale;
        module->TH = 0xffff;
        module->TCON = _ICT_TCON_TICSET_MASK
                                         | (1 << _ICT_TCON_TMODE_POSN)
                                         | (_ICT_TCON_ICSPIN_MASK & (start_pin << _ICT_TCON_ICSPIN_POSN))
                                         | (_ICT_TCON_ICPPIN_MASK & (end_pin << _ICT_TCON_ICPPIN_POSN))
                                         | (_ICT_TCON_ICSPOL_MASK & (start_edge << _ICT_TCON_ICSPOL_POSN))
                                         | (_ICT_TCON_ICPPOL_MASK & (end_edge << _ICT_TCON_ICPPOL_POSN));
        break;
    default:
        break;
    }
}
