/*
 * clock.c
 *
 *  Created on: 05.04.2019
 *      Author: Marcin Dolicher
 */

#include "..\Inc\clock.h"
#include "..\Library\Display\ssd1306.h"

void updateTime(char time[])
{
	ssd1306_SetCursor(15, 22);
	ssd1306_WriteString(time, Font_11x18, White);
	ssd1306_UpdateScreen();
}

void showMenuButtons()
{
	char leftButton[6] = "<*";
	char rightButton[6] = "D>";
	ssd1306_SetCursor(0, 45);
	ssd1306_WriteString(leftButton, Font_11x18, White);
	ssd1306_SetCursor(100, 45);
	ssd1306_WriteString(rightButton, Font_11x18, White);
	ssd1306_UpdateScreen();
}

void showCity(){
	char city[13] = "   Warsaw   ";
	char space[8] = "       ";
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(city, Font_11x18, White);
	ssd1306_SetCursor(20, 45);
	ssd1306_WriteString(space, Font_11x18, White);
	ssd1306_UpdateScreen();
}

void setTimeScreen(){
	//ssd1306_Fill(Black);

	showMenuButtons();

	char setButton[15] = " SET TIME  ";
	char onOffButton[9] = "|SET-A|";
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(setButton, Font_11x18, White);
	ssd1306_SetCursor(20, 45);
	ssd1306_WriteString(onOffButton, Font_11x18, White);
	ssd1306_UpdateScreen();
}

void clearScreen(){
	char space[15] = "           ";
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(space, Font_11x18, White);
	ssd1306_SetCursor(0, 22);
	ssd1306_WriteString(space, Font_11x18, White);
	ssd1306_SetCursor(0, 45);
	ssd1306_WriteString(space, Font_11x18, White);
	ssd1306_UpdateScreen();
}
