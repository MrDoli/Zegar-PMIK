/*
 * controller.c
 *
 *  Created on: 06.04.2019
 *      Author: Marcin Dolicher
 */

/**
 * \file controller.c
 * \brief Plik implementujacy metody controllera, ktore sluza do realizacji logiki programu.
 */

#include "controller.h"
#include "../Menu/clock.h"
#include "../Library/Flash/flash.h"
#include <stdbool.h>
#include "../Library/Display/ssd1306.h"
#include <stdint.h>

/**
 * Deklaracje zmiennych extern zostaly utworzone w pliku main.c
 */
extern int counterKpad;
extern int counterKpad2;
extern char time_clock[8];
extern char alarm_clock[8];
extern bool keypad_number_flag;
extern bool keypad_number_2_flag;

RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef gTime;
RTC_DateTypeDef gDate;
RTC_AlarmTypeDef sAlarm;
bool alarmIsOn = true;

/**
 * Inicjalizacja wyswietlacza zegara.
 * @param time Czas do wyswietlenia.
 */
void controllerInit(char time[]){
	showMenuButtons();
	showCity();
	updateTime(time);
	bool timerScreen[3] = {true, false, false};
	setActualScreen(&timerScreen);
}

/**
 * Realizuje logike programu
 * w zaleznosci dzialan uzytkownika na klawiaturze realizuje funkcjonalnosci zegarka i budzika
 * za pomoca zmiennej \param actualScreen jest wybierany ekran do wyswietlania na wyswietlaczu LCD
 * @param gotCharacter Wcisniety znak na klawiaturze.
 * @param alarmIsSet Flaga oznaczajaca ze alarm jest wlaczony.
 * @return flaga z informacja na temat stanu alarmu.
 */
bool controller(char gotCharacter){
	bool alarmIsSet;
	// Mozemy sprawdzac rowniez inne elementy tablicy (w nastepnej wersji)
	if(actualScreen[0] == true)
	{
		showMenuButtons();
		showAlarmState(alarmIsOn);
		showCity();
		getTime();
		updateTime(time_clock);
	}
	else if (actualScreen[1] == true)
	{
		showAlarmScreen();
		getAlarm();
		updateTime(alarm_clock);
		if(gotCharacter == 'A')
		{
			setAlarmUser();
		}

		if(gotCharacter == 'B')
		{
			turnOnAlarm();
			alarmIsOn = true;
		}

		else if(gotCharacter == 'C')
		{
			turnOffAlarm();
			alarmIsOn = false;
		}
	}
	else if (actualScreen[2] == true)
	{
		setTimeScreen();
		updateTime(time_clock);
		if(gotCharacter == 'A' )
		{
			setTimeUser();
		}
	}

	return alarmIsSet;
}

/**
 * Pobranie tablicy ze statusem ekranow.
 * @return Tablica ze statusem ekranow.
 */
bool* getActualScreen(void)
{
    return actualScreen;
}

/**
 * Ustawia zmienne bool w tablicy actualScreen, na podstawie ktorej jest wybierany ekran do wyswietlania
 * \param screenArray przechowuje informacje o ekranie, który ma zostac wyswietlony
 */
void setActualScreen(bool screenArray[])
{
	actualScreen[0] = screenArray[0];
	actualScreen[1] = screenArray[1];
	actualScreen[2] = screenArray[2];
}

/**
 * Obsluga przemieszczania siê miedzy ekranami.
 * @param sign Znak zwrocony z klawiatury.
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

/**
 * Funkcja sluzaca do wylaczenia przez uzytkownika
 */
void turnOffAlarm()
{
	RTC_HandleTypeDef hrtc;
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

	uint32_t alarmType = RTC_ALARM_A;
	HAL_RTC_DeactivateAlarm(&hrtc, alarmType);
}

/**
 * Funkcja sluzaca do wlaczenia i ustawienia alarmu na czas wpisany przez uzytkownika
 */
void turnOnAlarm()
{

	RTC_AlarmTypeDef sAlarm;
	uint32_t alarmType = RTC_ALARM_A;

	HAL_RTC_GetAlarm(&hrtc, &sAlarm, alarmType, RTC_FORMAT_BIN);
	int hours = (int) sAlarm.AlarmTime.Hours;
	int minutes = (int) sAlarm.AlarmTime.Minutes;
	int seconds = (int) sAlarm.AlarmTime.Seconds;
	setAlarmInRTC(hours, minutes, seconds);
}


/**
 * Ustawienie czasu na zegarze.
 */
void setTimeUser()
{
	bool hoursIsSet = false;
	bool minutesIsSet = false;
	hoursIsSet = setHourMinOrSecInTime('H');
	if(hoursIsSet == true)
		minutesIsSet = setHourMinOrSecInTime('M');
	if(minutesIsSet == true)
	{
		setHourMinOrSecInTime('S');
		hoursIsSet = false;
		minutesIsSet = false;
	}
}

/**
 * Ustawienie godziny alarmu budzika.
 */
void setAlarmUser()
{
	bool hoursIsSet = false;
	bool minutesIsSet = false;
	hoursIsSet = setHourMinOrSecInAlarm('H');
	if(hoursIsSet == true)
		minutesIsSet = setHourMinOrSecInAlarm('M');
	if(minutesIsSet == true)
	{
		setHourMinOrSecInAlarm('S');
		hoursIsSet = false;
		minutesIsSet = false;
	}
}

/**
 * Ustawienie godziny, minuty lub sekundy alarmu w budziku.
 * @param whichPartToSet Wartosc mowiaca o tym czy bedzie ustawiana godzina, minuta, lub sekunda.
 * @return Flaga oznaczajaca czy operacje wykonano poprawnie.
 */
bool setHourMinOrSecInAlarm(char whichPartToSet)
{
	uint8_t hours = 0;
	uint8_t minutes = 0;
	uint8_t seconds = 0;
	uint8_t firstNumber = 0;
	uint8_t secondNumber = 0;
	bool firstNumberSaved = false;

	uint32_t alarmType = RTC_ALARM_A;
	HAL_RTC_GetAlarm(&hrtc, &sAlarm, alarmType, RTC_FORMAT_BIN);

	hours = sAlarm.AlarmTime.Hours;
	minutes = sAlarm.AlarmTime.Minutes;
	seconds = sAlarm.AlarmTime.Seconds;

	while(getCharKeypad() != '*' && getCharKeypad() != 'D')
	{
		char gettedChar = getCharKeypad();
		if(gettedChar != ' ' && gettedChar == 'A' && keypad_number_flag == false && firstNumberSaved == false)
		{
			counterKpad++;
		}

		if(gettedChar != ' ' && gettedChar != 'A' && keypad_number_flag == true && firstNumberSaved == false)
		{
			firstNumber = getIntKeypad();
			firstNumberSaved = true;
			switch (whichPartToSet)
			{
				case 'H':
					if(firstNumber>2) return false;
					hours = firstNumber*10 + secondNumber;
					break;
				case 'M':
					if(firstNumber>59) return false;
					minutes = firstNumber*10 + secondNumber;
					break;
				case 'S':
					if(firstNumber>59) return false;
					seconds = firstNumber*10 + secondNumber;
					break;
				default:
					return false;
			}

			setAlarmInRTC(hours, minutes, seconds);
			getAlarm();
			updateTime(alarm_clock);
		}

		if(gettedChar == 'A' && firstNumberSaved == true)
		{
			counterKpad2++;
		}

		if( gettedChar != ' ' && gettedChar != 'A' && keypad_number_2_flag == true)
		{
			secondNumber = getIntKeypad();
			switch (whichPartToSet)
			{
				case 'H':
					hours = firstNumber*10 + secondNumber;
					if(hours>23) return false;
					break;
				case 'M':
					minutes = firstNumber*10 + secondNumber;
					if(minutes>59) return false;
					break;
				case 'S':
					seconds = firstNumber*10 + secondNumber;
					if(seconds>59) return false;
					uint32_t alarm_time[] = {hours, minutes, seconds};
					saveAlarmFlash(alarm_time);
					break;
				default:
					return false;
			}

			setAlarmInRTC(hours, minutes, seconds);
			getAlarm();
			updateTime(alarm_clock);
			keypad_number_flag = false;
			keypad_number_2_flag = false;
			firstNumberSaved = false;
			counterKpad2 = 0;
			counterKpad = 0;
			return true;
		}
	}
	return false;
}

/**
 * Ustawienie godziny, minuty lub sekundy w zegarze.
 * @param whichPartToSet Wartosc mowiaca o tym czy bedzie ustawiana godzina, minuta, lub sekunda.
 * @return Flaga oznaczajaca czy operacje wykonano poprawnie.
 */
bool setHourMinOrSecInTime(char whichPartToSet)
{
	uint8_t hours = 0;
	uint8_t minutes = 0;
	uint8_t seconds = 0;
	uint8_t firstNumber = 0;
	uint8_t secondNumber = 0;
	bool firstNumberSaved = false;

	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

	hours = gTime.Hours;
	minutes = gTime.Minutes;
	seconds = gTime.Seconds;

	while(getCharKeypad() != '*' && getCharKeypad() != 'D')
	{
		char gettedChar = getCharKeypad();
		if(gettedChar != ' ' && gettedChar == 'A' && keypad_number_flag == false && firstNumberSaved == false)
		{
			counterKpad++;
		}

		if(gettedChar != ' ' && gettedChar != 'A' && keypad_number_flag == true && firstNumberSaved == false)
		{
			firstNumber = getIntKeypad();
			firstNumberSaved = true;
			switch (whichPartToSet)
			{
				case 'H':
					if(firstNumber>2) return false;
					hours = firstNumber*10 + secondNumber;
					break;
				case 'M':
					if(firstNumber>59) return false;
					minutes = firstNumber*10 + secondNumber;
					break;
				case 'S':
					if(firstNumber>59) return false;
					seconds = firstNumber*10 + secondNumber;
					break;
				default:
					return false;
			}

			setTimeInRTC(hours, minutes, seconds);
			getTime();
			updateTime(time_clock);
		}

		if(gettedChar == 'A' && firstNumberSaved == true)
		{
			counterKpad2++;
		}

		if( gettedChar != ' ' && gettedChar != 'A' && keypad_number_2_flag == true)
		{
			secondNumber = getIntKeypad();
			switch (whichPartToSet)
			{
				case 'H':
					hours = firstNumber*10 + secondNumber;
					if(hours>23) return false;
					break;
				case 'M':
					minutes = firstNumber*10 + secondNumber;
					if(minutes>59) return false;
					break;
				case 'S':
					seconds = firstNumber*10 + secondNumber;
					if(seconds>59) return false;
					break;
				default:
					return false;
			}

			setTimeInRTC(hours, minutes, seconds);
			getTime();
			updateTime(time_clock);
			keypad_number_flag = false;
			keypad_number_2_flag = false;
			firstNumberSaved = false;
			counterKpad2 = 0;
			counterKpad = 0;
			return true;
		}
	}
	return false;
}

/**
 * Ustawienie czasu zegara w RTC.
 * @param hours Godzina do zapisania.
 * @param minutes Minuty do zapisania.
 * @param seconds Sekundy do zapisania.
 */
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


/**
 * Ustawienie czasu alarmu budzika w RTC.
 * @param hours Godzina do zapisania.
 * @param minutes Minuty do zapisania.
 * @param seconds Sekundy do zapisania.
 */
void setAlarmInRTC(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	RTC_HandleTypeDef hrtc;
	RTC_AlarmTypeDef sAlarm = {0};


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

	sAlarm.AlarmTime.Hours = hours;//0x0;
	sAlarm.AlarmTime.Minutes = minutes;//0x0;
	sAlarm.AlarmTime.Seconds = seconds;//0x10;
	sAlarm.AlarmTime.SubSeconds = 0x0;
	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
	sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	sAlarm.AlarmDateWeekDay = 1;
	sAlarm.Alarm = RTC_ALARM_A;

	//Set alarm
	if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
	{
	   Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2);
	/* USER CODE END RTC_Init 2 */
}

