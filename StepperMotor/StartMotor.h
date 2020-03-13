#include "stm32f0xx_hal.h"

void delay (uint16_t us);
void stepper_set_rpm (int rpm);
void stepper_half_drive (int step);
void stepper_step_angle (float angle, int direction, int rpm);

void startStepperMotor(float angle, int direction);
void setHalfDrive();
