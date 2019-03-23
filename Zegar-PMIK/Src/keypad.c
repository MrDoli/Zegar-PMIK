/*
 * keypad.c
 *
 *  Created on: 16.03.2019
 *      Author: Marcin Dolicher
 */

#include "stdint.h"
//#include "..\Drivers\STM32F4xx_HAL_Driver\Inc\stm32f4xx_hal.h"
#include "main.h" // musi byc bo tam zadeklarowane zmienne pinow
//#include "keypad.h"

void getCharKeypad(){
	if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_7_IN_Pin)==1) //sprawdzic
	    {
			HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_SET);
		}else{
			HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_RESET);
		}

		if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_6_IN_Pin)==1) //sprawdzic czy to dziala
		{
			HAL_GPIO_WritePin(GPIOD, LED_GREEN_Pin, GPIO_PIN_SET);
		}else{
			HAL_GPIO_WritePin(GPIOD, LED_GREEN_Pin, GPIO_PIN_RESET);
		}

		if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_5_IN_Pin)==1)
		{
			HAL_GPIO_WritePin(GPIOD, LED_RED_Pin, GPIO_PIN_SET);
		}else{
			HAL_GPIO_WritePin(GPIOD, LED_RED_Pin, GPIO_PIN_RESET);
		}

		if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_4_IN_Pin)==1)
		{
				HAL_GPIO_WritePin(GPIOD, LED_BLUE_Pin, GPIO_PIN_SET);
		}else{
			HAL_GPIO_WritePin(GPIOD, LED_BLUE_Pin, GPIO_PIN_RESET);
		}
}
	/*if(GPIO_Pin == KEYPAD_PIN_3_Pin) //sprawdzic
    {
		HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_RESET);
	}

	if(GPIO_Pin == KEYPAD_PIN_2_Pin) //sprawdzic czy to dziala
	{
		HAL_GPIO_WritePin(GPIOD, LED_GREEN_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(GPIOD, LED_GREEN_Pin, GPIO_PIN_RESET);
	}

	if(GPIO_Pin == KEYPAD_PIN_1_Pin)
	{
		HAL_GPIO_WritePin(GPIOD, LED_RED_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(GPIOD, LED_RED_Pin, GPIO_PIN_RESET);
	}

	if(GPIO_Pin == KEYPAD_PIN_0_Pin)
	{
			HAL_GPIO_WritePin(GPIOD, LED_BLUE_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(GPIOD, LED_BLUE_Pin, GPIO_PIN_RESET);
	}*/


/* if(isPressed ==0 && HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_4_Pin)==1 ){
		 counter++;
		 isPressed = 1;
		 HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_SET);
	 }
  else if(isPressed ==1 && HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_4_Pin)==0 ){
	  isPressed = 0;
	  HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_RESET);
*/
	 /*if(counter = 50){
		 counter = 0;
		 HAL_GPIO_WritePin(GPIOD, LED_BLUE_Pin, GPIO_PIN_SET);
	 }*/
