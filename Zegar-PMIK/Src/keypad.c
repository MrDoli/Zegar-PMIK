/*
 * keypad.c
 *
 *  Created on: 16.03.2019
 *      Author: Marcin Dolicher
 */

#include "stdint.h"
#include "main.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == KEYPAD_PIN_3_Pin) //sprawdzic
    {
		HAL_GPIO_WritePin(GPIOD, LED_ORANGE_PIN_GPIO_Port, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(GPIOD, LED_ORANGE_PIN_GPIO_Port, GPIO_PIN_RESET);
	}

	if(GPIO_Pin == KEYPAD_PIN_4_Pin) //sprawdzic czy to dziala
	{
		HAL_GPIO_WritePin(GPIOD, LED_GREEN_PIN_GPIO_Port, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(GPIOD, LED_GREEN_PIN_GPIO_Port, GPIO_PIN_RESET);
	}

	if(GPIO_Pin == KEYPAD_PIN_5_Pin)
	{
		HAL_GPIO_WritePin(GPIOD, LED_RED_PIN_GPIO_Port, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(GPIOD, LED_RED_PIN_GPIO_Port, GPIO_PIN_RESET);
	}
}
