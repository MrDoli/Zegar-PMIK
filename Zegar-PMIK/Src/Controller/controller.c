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
extern int counterKpad2;
RTC_HandleTypeDef hrtc;

extern bool keypad_number_flag;
extern bool keypad_number_2_flag;

// gdy to globalne to dziala, sprobowac to wrzucic do funckji
RTC_TimeTypeDef gTime;
RTC_DateTypeDef gDate;

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
	bool hoursIsSet = false;
	bool minutesIsSet = false;
	hoursIsSet = setHourMinOrSec('H');
	if(hoursIsSet == true)
		minutesIsSet = setHourMinOrSec('M');
	if(minutesIsSet == true)
	{
		setHourMinOrSec('S');
		hoursIsSet = false;
		minutesIsSet = false;
	}
}

bool setHourMinOrSec(char whichPartToSet)
{
	char znak = getCharKeypad();
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	int firstNumber = 0;
	int secondNumber = 0;
	bool firstNumberSaved = false;

	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

	hours = (int) gTime.Hours;
	minutes = (int) gTime.Minutes;
	seconds = (int) gTime.Seconds;

	while(getCharKeypad() != '*' && getCharKeypad() != 'D')
	{
		if(getCharKeypad() != ' ' && getCharKeypad() == 'A' && keypad_number_flag == false && firstNumberSaved == false)
		{
			counterKpad++;
		}

		if(getCharKeypad() != ' ' && getCharKeypad() != 'A' && keypad_number_flag == true && firstNumberSaved == false)
		{
			firstNumber = getIntKeypad();
			firstNumberSaved = true;
		}

		if(getCharKeypad() == 'B')
		{
			counterKpad2++;
		}

		if( getCharKeypad() != ' ' && getCharKeypad() != 'B' && keypad_number_2_flag == true)
		{
			secondNumber = getIntKeypad();
			switch (whichPartToSet)
			{
				case 'H':
					hours = firstNumber*10 + secondNumber;
					break;
				case 'M':
					minutes = firstNumber*10 + secondNumber;
					break;
				case 'S':
					seconds = firstNumber*10 + secondNumber;
					break;
				default:
					return false;
			}

			setTimeInRTC(hours, minutes, seconds);
			keypad_number_flag = false;
			keypad_number_2_flag = false;
			firstNumberSaved = false;
			counterKpad2 = 0;
			counterKpad = 0;
			return true;
		}
	}
	return false; // dobrze???
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
