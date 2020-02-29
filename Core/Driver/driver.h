#ifndef __DRIVER_H
#define __DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx_hal.h"
#include "stm32f0xx_it.h"
#include "main.h"

void stepperSetRpm (int rpm);
void stepperHalfDrive (int step);
void startMotorByButton (float angle, int direction, int rpm);
void stopMotorByButton();

#ifdef __cplusplus
}
#endif

#endif // __DRIVER_H
