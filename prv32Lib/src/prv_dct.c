/**
 * @file    prv_dct.c
 * @brief   APIs for Dual Compare Timer modules.
 * @version 0.1
 * @date    2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "prv_dct.h"

/**
 * @brief API to Setup DCT Module.
 * 
 * @param module Constant pointer to DCT modules to access hardware registers. Pass DCT0, DCT1, DCT2, DCT3 as module parameters.
 * @param config DCT module configurations. Use DCT_CONFIG_t structure to set the required configurations.
 */
void DCT_SetTimer(TIMER_DCT_t *const module, DCT_CONFIG_t *config)
{
    DCT_MODULE_SEG_t name = config->seg_name;
    uint32_t prescale = config->timer_param.prescale;
    uint32_t match_value = config->timer_param.match_value;

    module->TL = prescale;
    module->TH = match_value;
    module->TCON |= (name == DCT_MODULE_SEGA) ? _DCT_TCON_TASET_MASK : _DCT_TCON_TBSET_MASK;
}
