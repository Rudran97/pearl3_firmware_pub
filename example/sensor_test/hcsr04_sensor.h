#ifndef _HCSR04_SENSOR_H
#define _HCSR04_SENSOR_H

#include "prv_pin.h"

#define TRIG_PIN PORTB_PIN_B0
#define ECHO_PIN PORTB_PIN_B1_ICT0_CAP1

void InitUltraSonicSensor();
float getDistance();


#endif /* _HCSR04_SENSOR_H */
