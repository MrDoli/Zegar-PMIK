/*
 * keypad.c
 *
 * Author: Marcin Dolicher, Micha³ Stolarz
*/

/**
 * \file keypad.c
 * \brief Plik implementujacy metody odpowiadajace za obsluge klawiatury
 */

#include "keypad.h"

/**
  * @brief Pobieranie znakow z klawiatury.
  * @retval Zwraca klikniety znak przez uzytkownika z klawiatury typu char.
*/
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
}

/**
 * @brief Pobieranie znakow z klawiatury.
 * @return Zwraca klikniety znak przez uzytkownika jako zmienna typu int
 */
int getIntKeypad(){
	unsigned int GPIO_Pin_row , GPIO_Pin_col , i, j;
	const unsigned int KBkody [16] = {1,2,3,99 ,\
	4,5,6,99 ,\
	7,8,9,99 ,\
	99,0,99,99};
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
		return 15;
}
