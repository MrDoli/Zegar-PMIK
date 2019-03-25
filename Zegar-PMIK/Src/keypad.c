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
#include "../Drivers/ssd1306/ssd1306.h"


char getCharKeypad(){

	unsigned int GPIO_Pin_row , GPIO_Pin_col , i, j;
	const unsigned char KBkody [16] = {'1','2','3','A' ,\
	'4','5','6','B' ,\
	'7','8','9','C' ,\
	'*','0','#','D'};
	HAL_GPIO_WritePin(GPIOD, KEYPAD_PIN_0_OUT_Pin | KEYPAD_PIN_1_OUT_Pin | KEYPAD_PIN_2_OUT_Pin | KEYPAD_PIN_3_OUT_Pin, GPIO_PIN_SET);
	GPIO_Pin_row = KEYPAD_PIN_0_OUT_Pin;
	for(i=0;i <4;++ i) {
		HAL_GPIO_WritePin(GPIOD, GPIO_Pin_row, GPIO_PIN_RESET);
		//HAL_Delay (5) ;
		GPIO_Pin_col = KEYPAD_PIN_4_IN_Pin;
		for(j=0;j <4;++ j) {
			if( HAL_GPIO_ReadPin(GPIOD, GPIO_Pin_col)== 0) {
				HAL_GPIO_WritePin(GPIOD, KEYPAD_PIN_0_OUT_Pin | KEYPAD_PIN_1_OUT_Pin | KEYPAD_PIN_2_OUT_Pin | KEYPAD_PIN_3_OUT_Pin, GPIO_PIN_RESET) ;
				return KBkody [4*i+j];
			}
		GPIO_Pin_col = GPIO_Pin_col << 1;
		}

		HAL_GPIO_WritePin(GPIOD , GPIO_Pin_row, GPIO_PIN_SET );
		GPIO_Pin_row = GPIO_Pin_row << 1;

		}
		HAL_GPIO_WritePin(GPIOD ,  KEYPAD_PIN_0_OUT_Pin | KEYPAD_PIN_1_OUT_Pin | KEYPAD_PIN_2_OUT_Pin | KEYPAD_PIN_3_OUT_Pin, GPIO_PIN_RESET ) ;
		return ' ';

	/*HAL_GPIO_WritePin(GPIOD, KEYPAD_PIN_3_OUT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, KEYPAD_PIN_2_OUT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, KEYPAD_PIN_1_OUT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, KEYPAD_PIN_0_OUT_Pin, GPIO_PIN_SET);

	char buffer[10];
	if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_4_IN_Pin) == 0)
	    {
			HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_SET);
			ssd1306_SetCursor(24, 32);
			sprintf(buffer, "%s", "*");
			ssd1306_WriteString(buffer, Font_16x26, White);
			ssd1306_UpdateScreen();
		}else{
			HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_RESET);
			ssd1306_SetCursor(24, 32);
						sprintf(buffer, "%s", "#");
						ssd1306_WriteString(buffer, Font_16x26, White);
						ssd1306_UpdateScreen();
		}

	if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_5_IN_Pin) == 0)
		    {
				HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_SET);
				ssd1306_SetCursor(24, 32);
				sprintf(buffer, "%s", "0");
				ssd1306_WriteString(buffer, Font_16x26, White);
				ssd1306_UpdateScreen();
			}else{
				HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_RESET);
				ssd1306_SetCursor(24, 32);
							sprintf(buffer, "%s", "#");
							ssd1306_WriteString(buffer, Font_16x26, White);
							ssd1306_UpdateScreen();
			}

	if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_6_IN_Pin) == 0)
		    {
				HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_SET);
				ssd1306_SetCursor(24, 32);
				sprintf(buffer, "%s", "J");
				ssd1306_WriteString(buffer, Font_16x26, White);
				ssd1306_UpdateScreen();
			}else{
				HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_RESET);
				ssd1306_SetCursor(24, 32);
							sprintf(buffer, "%s", "#");
							ssd1306_WriteString(buffer, Font_16x26, White);
							ssd1306_UpdateScreen();
			}

	if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_7_IN_Pin) == 0)
		    {
				HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_SET);
				ssd1306_SetCursor(24, 32);
				sprintf(buffer, "%s", "D");
				ssd1306_WriteString(buffer, Font_16x26, White);
				ssd1306_UpdateScreen();
			}else{
				HAL_GPIO_WritePin(GPIOD, LED_ORANGE_Pin, GPIO_PIN_RESET);
				ssd1306_SetCursor(24, 32);
							sprintf(buffer, "%s", "#");
							ssd1306_WriteString(buffer, Font_16x26, White);
							ssd1306_UpdateScreen();
			}

		if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_6_IN_Pin)==1)
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

		/*if(HAL_GPIO_ReadPin(GPIOD, KEYPAD_PIN_4_IN_Pin)==1)
		{
				HAL_GPIO_WritePin(GPIOD, LED_BLUE_Pin, GPIO_PIN_SET);
		}else{
			HAL_GPIO_WritePin(GPIOD, LED_BLUE_Pin, GPIO_PIN_RESET);
		}*/
}
