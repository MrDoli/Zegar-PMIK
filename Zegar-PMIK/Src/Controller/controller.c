/*
 * controller.c
 *
 *  Created on: 06.04.2019
 *      Author: Marcin Dolicher
 */

#include "controller.h"
#include <stdbool.h>
#include "../Library/Display/ssd1306.h"
#include <stdint.h>

//extern bool actualScreen[3];
extern int counterKpad;
extern bool keypad_number_flag;

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
  * @brief  Obsluga przemieszczania siê miedzy ekranami.
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

void setTimeUser()
{
	char znak = getCharKeypad();
	//int counter = 0;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	int tempTime[2] = {0, 0};
	while(getCharKeypad() != '*' && getCharKeypad() != 'D')
	{
		if(getCharKeypad() != ' ' && getCharKeypad() != 'A')
		{
			hours = getIntKeypad();
			counterKpad++;
			if(keypad_number_flag == true)
			{
				setTimeInRTC(hours, minutes, seconds);
				keypad_number_flag = false;
				/*
				 * dziala dopisac potwierdzanie przyjecia liczby za pomoc B i wtedy wpisywac do setTimeInRTC
				 */
			}
			/*if(counter == 0)
			{
				tempTime[0] = getIntKeyPad();
				counter = 1;
				continue;
			}
			if(counter == 1)
			{
				tempTime[1] = getIntKeyPad();
				counter = 2;
				continue;
			}
			if(counter == 2)
			{
				hours = tempTime[0]*10 + tempTime[1];
				setTimeInRTC(hours, minutes, seconds);
				counter = 0;
				continue;
			}*/
		}
	}
/*
	while( counter < 2 )
	{
		znak = getCharKeypad();
		if(znak == 'A')
		{
			counter++;
			ssd1306_SetCursor(10, 20);
			ssd1306_WriteString("1", Font_11x18, White);
			return;
		}
		//counter++;
		showCity();
	}
	*/
}

void setTimeInRTC(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	  RTC_HandleTypeDef hrtc;
	  RTC_TimeTypeDef sTime = {0};

	  hrtc.Instance = RTC;
	    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	    hrtc.Init.AsynchPrediv = 127;
	    hrtc.Init.SynchPrediv = 255;
	    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	    if (HAL_RTC_Init(&hrtc) != HAL_OK)
	    {
	      Error_Handler();
	    }

	  sTime.Hours = hours;
	  sTime.Minutes = minutes;
	  sTime.Seconds = seconds;
	  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2);
}
