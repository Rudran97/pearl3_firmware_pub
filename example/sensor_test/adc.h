#ifndef _ADC_H
#define _ADC_H

#define ADC_DO    3
#define ADC_nCS   4
#define ADC_CLK   5

#include "stdint.h"

void InitADC();
uint8_t readADC();

#endif /* _ADC_H */