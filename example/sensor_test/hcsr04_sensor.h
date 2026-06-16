#ifndef _SONIC_SENSOR_H
#define _SONIC_SENSOR_H

#include "prv_gpio.h"
#include "prv_ict.h"

#define TRIG_PIN 0
#define ECHO_PIN 1

void InitUltraSonicSensor();
float getDistance();


#endif /* _SONIC_SENSOR_H */