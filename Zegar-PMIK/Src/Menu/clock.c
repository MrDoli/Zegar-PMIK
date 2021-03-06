/*
 * clock.c
 *
 * Author: Marcin Dolicher, Micha� Stolarz
*/

/**
 * \file clock.c
 * \brief Plik implementujacy metody odpowiadajace za wyswietlanie
 * 		ekranow zwiazanych z czasem (wyswietlanie, ustawianie).
 */

#include "clock.h"
#include "..\Library\Display\ssd1306.h"

/**
  * @brief  Wskazanie uzytkownikowi czy ustawia godzine, minuty lub sekundy.
  * @param  partToSet Wartosc mowiaca o tym czy jest ustawiana godzina, minuta, lub sekunda.
  */
void showPlaceToSet(char partToSet)
{
	uint8_t space = 11;
	uint8_t actualXPlace = 20;
	uint8_t actualYPlace = 22;
	char checkToWrite = '_';

	switch (partToSet)
	{
		case 'H':
			ssd1306_SetCursor(actualXPlace, actualYPlace);
			ssd1306_WriteChar(checkToWrite, Font_11x18, White);
			ssd1306_SetCursor(actualXPlace+space, actualYPlace);
			ssd1306_WriteChar(checkToWrite, Font_11x18, White);
		break;
		case 'M':
			ssd1306_SetCursor(actualXPlace+space*3, actualYPlace);
			ssd1306_WriteChar(checkToWrite, Font_11x18, White);
			ssd1306_SetCursor(actualXPlace+space*4, actualYPlace);
			ssd1306_WriteChar(checkToWrite, Font_11x18, White);
		break;
		case 'S':
			ssd1306_SetCursor(actualXPlace+space*6, actualYPlace);
			ssd1306_WriteChar(checkToWrite, Font_11x18, White);
			ssd1306_SetCursor(actualXPlace+space*7, actualYPlace);
			ssd1306_WriteChar(checkToWrite, Font_11x18, White);
		break;
	}
	ssd1306_UpdateScreen();
}

/**
  * @brief  Zaktualizowanie czasu na wyswietlaczu.
  * @param  Aktualny czas do wyswietlenia.
  */
void updateTime(char time[])
{
	char space[15] = "           ";
	ssd1306_SetCursor(0, 22);
	ssd1306_WriteString(space, Font_11x18, White);
	ssd1306_SetCursor(20, 22);//15
	ssd1306_WriteString(time, Font_11x18, White);
	ssd1306_UpdateScreen();
}

/**
  * @brief  Wyswietlanie przyciskow do zmiany ekranu w aplikacji.
  */
void showMenuButtons()
{
	char leftButton[3] = "<*";
	char rightButton[3] = "D>";
	ssd1306_SetCursor(0, 45);
	ssd1306_WriteString(leftButton, Font_11x18, White);
	ssd1306_SetCursor(100, 45);
	ssd1306_WriteString(rightButton, Font_11x18, White);
	ssd1306_UpdateScreen();
}

/**
 * @ brief Wyswietlenie informacji czy budzik wlaczony.
 * @param  Flaga czy alarm jest wlaczany.
 */
void showAlarmState(bool alarmSet)
{
	ssd1306_SetCursor(30, 49);
	if(alarmSet){
		char alarmState[10] = "ALARM ON ";
		ssd1306_WriteString(alarmState, Font_7x10, White);
	}
	else{
		char alarmState[10] = "ALARM OFF";
		ssd1306_WriteString(alarmState, Font_7x10, White);
	}

	ssd1306_UpdateScreen();
}

/**
  * @brief  Wyswietlanie nazwy miasta.
  */
void showCity(){
	char city[13] = "   Warsaw   ";
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(city, Font_11x18, White);
	ssd1306_UpdateScreen();
}

/**
  * @brief  Wy�wietlanie ekranu do ustawienia czasu w zegarze.
  */
void setTimeScreen(){
	showMenuButtons();
	char setButton[15] = "  SET TIME  ";
	char onOffButton[10] = " |SET-A| ";
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(setButton, Font_11x18, White);
	ssd1306_SetCursor(28, 49);
	ssd1306_WriteString(onOffButton, Font_7x10, White);
	ssd1306_UpdateScreen();
}
