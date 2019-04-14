/*
 * controller.c
 *
 *  Created on: 06.04.2019
 *      Author: Marcin Dolicher
 */

#include "controller.h"
#include <stdbool.h>
#include "../Library/Display/ssd1306.h"

//extern bool actualScreen[3];

/**
  * @brief  Zmiana ekranu.
  */
void changeScreen(){

}

/**
  * @brief  Inicjalizacja wyswietlacza zegara.
  * @param  Czas do wyswietlenia.
  */
void controllerInit(char time[]){
	showMenuButtons();
	showCity();
	updateTime(time);
	bool timerScreen = {true, false, false};
	setActualScreen(&timerScreen);
}

/**
  * @brief  Zmiana wyswietlanego ekranu.
  */
void controller(){
	// Mozemy sprawdzac rowniez inne elementy tablicy (w nastepnej wersji)
	if(actualScreen[0] == true)
	{
		showMenuButtons();
		showCity();
	}
	else if (actualScreen[1] == true)
	{
		showAlarmScreen();
	}
	else if (actualScreen[2] == true)
	{
		setTimeScreen();
	}
}

/**
  * @brief  Pobranie tablicy ze statusem ekranow.
  * @retval Tablica ze statusem ekranow.
  */
bool* getActualScreen(void)
{
    return actualScreen;
}

/**
  * @brief  Wgranie nowej tablicy ze statusem ekranow.
  * @param  Tablica z nowym statusem ekranow.
  */
void setActualScreen(bool screenArray[])
{
	actualScreen[0] = screenArray[0];
	actualScreen[1] = screenArray[1];
	actualScreen[2] = screenArray[2];
}

/**
  * @brief  Obsluga przemieszczania si� miedzy ekranami.
  * @param  Znak zwrocony z klawiatury.
  */
void handleDirectionButton(char sign)
{
	if(sign == 'D')
	{
		if(actualScreen[0] == true)
		{
			actualScreen[0] = false;
			actualScreen[1] = true;
		}
		else if (actualScreen[1] == true)
		{
			actualScreen[1] = false;
			actualScreen[2] = true;
		}
		else if (actualScreen[2] == true)
		{
			actualScreen[2] = false;
			actualScreen[0] = true;
		}
	}

	if(sign == '*')
	{
		if(actualScreen[0] == true)
		{
			actualScreen[0] = false;
			actualScreen[2] = true;
		}
		else if (actualScreen[1] == true)
		{
			actualScreen[1] = false;
			actualScreen[0] = true;
		}
		else if (actualScreen[2] == true)
		{
			actualScreen[2] = false;
			actualScreen[1] = true;
		}
	}
}
