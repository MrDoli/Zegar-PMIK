/*
 * alarm.c
 *
 *  Created on: 05.04.2019
 *      Author: Marcin Dolicher
 */

#include "alarm.h"
#include "..\Library\Display\ssd1306.h"
#include "clock.h"

/**
  * @brief  Wyswietlenie ekranu do ustawienia alarmu.
  */
void showAlarmScreen(){
	//ssd1306_Fill(Black);

	showMenuButtons();

	char setButton[15] = "Alarm SET-A";
	char onOffButton[9] = "|B-O/I|";
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(setButton, Font_11x18, White);
	ssd1306_SetCursor(20, 45);
	ssd1306_WriteString(onOffButton, Font_11x18, White);
	ssd1306_UpdateScreen();
}
