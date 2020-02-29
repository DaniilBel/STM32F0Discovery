#include "driver.h"

#define stepsPerRev 4096

void delay (uint16_t us)
{
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  while (__HAL_TIM_GET_COUNTER(&htim1) < us);
}

void stepperSetRpm (int rpm)
{
	delay(60000000/stepsPerRev/rpm);
}

void stepperHalfDrive (int step)
{
	HAL_GPIO_WritePin(GPIOC, PC0_Pin, ((~(2 << step)) & (~(1 << step)) & (~step)) | ((~(2 << step)) & (~(1 << step)) & step) |
			((2 << step) & (1 << step) & step));

	HAL_GPIO_WritePin(GPIOC, PC1_Pin, ((~(2 << step)) & (~(1 << step)) & step) | ((~(2 << step)) & (1 << step) & step) |
			((~(2 << step)) & (1 << step) & (~step)));

	HAL_GPIO_WritePin(GPIOC, PC2_Pin, ((~(2 << step)) & (1 << step) & step) | ((2 << step) & (~(1 << step)) & step) |
			((2 << step) & (~(1 << step)) & step));

	HAL_GPIO_WritePin(GPIOC, PC3_Pin, ((2 << step) & (~(1 << step)) & step) | ((2 << step) & (1 << step) & (~step)) |
			((2 << step) & (1 << step) & step));
}

/*
 * angle - angle of rotation
 * direction - 0 - for clockwise
 * 			   1 - for anti-clockwise
 * 	rpm - Revolution per minute (Wake up! Lenin)
 */
void startMotorByButton(float angle, int direction, int rpm)
{
	float anglePerSequence = 0.703125;  // 360 = 512 sequences
	int numberOfSequences = (int)(angle / anglePerSequence);

	for (int seq = 0; seq < numberOfSequences; seq++)
	{
		if (direction == 0)  // по часовой
		{
			for (int step = 7; step >= 0; step--)
			{
				stepperHalfDrive(step);
				stepperSetRpm(rpm);
			}
		}
		else if (direction == 1)  // против часовой
		{
			for (int step = 0; step < 8; step++)
			{
				stepperHalfDrive(step);
				stepperSetRpm(rpm);
			}
		}
	}
}

void stopMotorByButton()
{
	startMotorByButton(0, 0, 0);
}
