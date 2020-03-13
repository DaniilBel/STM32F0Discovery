#include <stm32f0xx_it.h>
#include "StartMotor.h"

void delay (uint16_t us)
{
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  while (__HAL_TIM_GET_COUNTER(&htim1) < us);
}

#define stepsperrev 4096

void stepper_set_rpm (int rpm)  // Set rpm--> max 13, min 1,,,  went to 14 rev/min
{
	delay(60000000/stepsperrev/rpm);
}

void stepper_half_drive (int step){
	switch(step){
	case 0:
		HAL_GPIO_WritePin(GPIOC, PC0_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, PC1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC3_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOC, PC0_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, PC1_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, PC2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC3_Pin, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOC, PC0_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC1_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, PC2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC3_Pin, 0);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOC, PC0_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC1_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, PC2_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, PC3_Pin, 0);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOC, PC0_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC2_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, PC3_Pin, 0);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOC, PC0_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC2_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, PC3_Pin, 1);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOC, PC0_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC3_Pin, 1);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOC, PC0_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, PC1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, PC3_Pin, 1);
		break;
	}
}

void stepper_step_angle (float angle, int direction, int rpm)
{
	float anglepersequence = 0.703125;  // 360 = 512 sequences
	int numberofsequences = (int) (angle/anglepersequence);

	for (int seq=0; seq<numberofsequences; seq++)
	{
		if (direction == 0)  // for clockwise
		{
			for (int step=7; step>=0; step--)
			{
				stepper_half_drive(step);
				stepper_set_rpm(rpm);
			}

		}

		else if (direction == 1)  // for anti-clockwise
		{
			for (int step=0; step<8; step++)
			{
				stepper_half_drive(step);
				stepper_set_rpm(rpm);
			}
		}
	}
}

void setHalfDrive(){
	HAL_GPIO_WritePin(PC0_GPIO_Port, PC0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC1_GPIO_Port, PC1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC2_GPIO_Port, PC2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC3_GPIO_Port, PC3_Pin, GPIO_PIN_RESET);

	HAL_Delay(3);

	HAL_GPIO_WritePin(PC0_GPIO_Port, PC0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC1_GPIO_Port, PC1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC2_GPIO_Port, PC2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC3_GPIO_Port, PC3_Pin, GPIO_PIN_RESET);

	HAL_Delay(3);

	HAL_GPIO_WritePin(PC0_GPIO_Port, PC0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC1_GPIO_Port, PC1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC2_GPIO_Port, PC2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC3_GPIO_Port, PC3_Pin, GPIO_PIN_RESET);

	HAL_Delay(3);

	HAL_GPIO_WritePin(PC0_GPIO_Port, PC0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC1_GPIO_Port, PC1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC2_GPIO_Port, PC2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC3_GPIO_Port, PC3_Pin, GPIO_PIN_RESET);

	HAL_Delay(3);

	HAL_GPIO_WritePin(PC0_GPIO_Port, PC0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC1_GPIO_Port, PC1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC2_GPIO_Port, PC2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC3_GPIO_Port, PC3_Pin, GPIO_PIN_RESET);

	HAL_Delay(3);

	HAL_GPIO_WritePin(PC0_GPIO_Port, PC0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC1_GPIO_Port, PC1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC2_GPIO_Port, PC2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC3_GPIO_Port, PC3_Pin, GPIO_PIN_SET);

	HAL_Delay(3);

	HAL_GPIO_WritePin(PC0_GPIO_Port, PC0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC1_GPIO_Port, PC1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC2_GPIO_Port, PC2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC3_GPIO_Port, PC3_Pin, GPIO_PIN_SET);

	HAL_Delay(3);

	HAL_GPIO_WritePin(PC0_GPIO_Port, PC0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC1_GPIO_Port, PC1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC2_GPIO_Port, PC2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC3_GPIO_Port, PC3_Pin, GPIO_PIN_SET);

	HAL_Delay(3);
}

void startStepperMotor(float angle, int direction)
{
	float anglePerSequence = 0.703125;  // 360 = 512 sequences
	int sequences = (int)(anglePerSequence*angle);

	for (int i = 0; i < sequences; ++i)
	{
		if (direction == 0) // for clockwise
		{
			setHalfDrive();
			HAL_Delay(1000);
		}
		else if(direction == 1) // for anti-clockwise
		{

		}
	}
}












