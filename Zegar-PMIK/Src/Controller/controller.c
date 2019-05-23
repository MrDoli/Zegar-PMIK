/*
 * controller.c
 *
 *  Created on: 06.04.2019
 *      Author: Marcin Dolicher
 */

#include "controller.h"
#include "../Menu/clock.h"
#include "../Library/Flash/flash.h"
#include <stdbool.h>
#include "../Library/Display/ssd1306.h"
#include <stdint.h>

//extern bool actualScreen[3];
extern int counterKpad;
extern int counterKpad2;
extern char time_clock[8];
extern char alarm_clock[8];
extern bool keypad_number_flag;
extern bool keypad_number_2_flag;

//__________________________________OBGADAC___________________________________________________________________
//Raz u�ywasz (setHourMinOrSecInAlarm()) a raz tworzysz nowe w danej funkcji (turnOnAlarm()), dlaczego?
//My�l� ze powinni�my u�ywac jednej struktury konfiguracyjnej RTC_HandleTypeDef, najlepiej z maina
//Za bardzo powielamy kod w przeciwnym wypadku
RTC_HandleTypeDef hrtc;
//____________________________________________________________________________________________________________


// gdy to globalne to dziala, sprobowac to wrzucic do funckji
RTC_TimeTypeDef gTime;
RTC_DateTypeDef gDate;
RTC_AlarmTypeDef sAlarm;

/**
  * @brief  Zmiana ekranu.
  */
void changeScreen(){

}

/**
 * Inicjalizacja wyswietlacza zegara.
 * @param time Czas do wyswietlenia.
 */
void controllerInit(char time[]){
	showMenuButtons();
	showCity();
	updateTime(time);
	bool timerScreen = {true, false, false};
	setActualScreen(&timerScreen);
}

/**
 * Zmiana wyswietlanego ekranu.
 * @param gotCharacter Wcisniety znak na klawiaturze.
 * @param alarmIsSet Flaga oznaczajaca ze alarm jest ustawiony.
 * @return Flaga oznaczajaca ze alarm jest ustawiony.
 */
bool controller(char gotCharacter, bool alarmIsSet){
	// Mozemy sprawdzac rowniez inne elementy tablicy (w nastepnej wersji)
	if(actualScreen[0] == true)
	{
		showMenuButtons();
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
		else if(gotCharacter == 'B')
		{
			alarmIsSet = turnOnAlarm(alarmIsSet);
		}
		updateTime(alarm_clock);
	}
	else if (actualScreen[2] == true)
	{
		setTimeScreen();
		if(gotCharacter == 'A' )
		{
			setTimeUser();
		}
		updateTime(time_clock);
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
 * Tablica ze statusem ekranow.
 * @param screenArray Tablica z nowym statusem ekranow.
 */
void setActualScreen(bool screenArray[])
{
	actualScreen[0] = screenArray[0];
	actualScreen[1] = screenArray[1];
	actualScreen[2] = screenArray[2];
}

/**
 * Obsluga przemieszczania si� miedzy ekranami.
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
 * Ustawienie godziny alarmu.
 * @param alarmIsSet Flaga oznaczajaca czy alarm jest wlaczony.
 * @return Flaga oznaczajaca czy alarm jest wlaczony.
 */

//__________________________________OBGADAC___________________________________________________________________
//Po co wylaczac i potem od nowa setowac alarm skoro wystarczy wylaczac i wlaczac audio?
//My�l� ze powinni�my u�ywac jednej struktury konfiguracyjnej RTC_HandleTypeDef, najlepiej z maina
//Za bardzo powielamy kod w przeciwnym wypadku
bool turnOnAlarm(bool alarmIsSet)
{
	if(alarmIsSet == true)
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
		alarmIsSet = false;
		return alarmIsSet;
	}
	else if(alarmIsSet == false)
	{

		RTC_AlarmTypeDef sAlarm;
		uint32_t alarmType = RTC_ALARM_A;

		HAL_RTC_GetAlarm(&hrtc, &sAlarm, alarmType, RTC_FORMAT_BIN);
		int hours = (int) sAlarm.AlarmTime.Hours;
		int minutes = (int) sAlarm.AlarmTime.Minutes;
		int seconds = (int) sAlarm.AlarmTime.Seconds;
		setAlarmInRTC(hours, minutes, seconds);
		alarmIsSet=true;
		return alarmIsSet;
	 }
}
//____________________________________________________________________________________________________________


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

//__________________________________OBGADAC___________________________________________________________________
//W warunku while(getCharKeypad() != '*' && getCharKeypad() != 'D') nie ma odszumiania,
//po co dwa razy odszumianie?
//if(gettedChar == 'A' && firstNumberSaved == true)
//{
//	counterKpadX++;
//}
//Wystarczy chyba raz to robic skoro i tak flaga firstNumberSaved mowi nam ktora cyfra jest wpisywana
//Po co jest char znak = getCharKeypad();? Nie u�ywasz tego.
//W tej funkcji chcia�bym dac zapisywanie do pamieci FLASH.
//W komentarzu jest napisane gdzie.

bool setHourMinOrSecInAlarm(char whichPartToSet)
{
	char znak = getCharKeypad();
	uint32_t hours = 0;
	uint32_t minutes = 0;
	uint32_t seconds = 0;
	uint32_t firstNumber = 0;
	uint32_t secondNumber = 0;
	bool firstNumberSaved = false;

	uint32_t alarmType = RTC_ALARM_A;
	HAL_RTC_GetAlarm(&hrtc, &sAlarm, alarmType, RTC_FORMAT_BIN);

	hours = (uint32_t) sAlarm.AlarmTime.Hours;
	minutes = (uint32_t) sAlarm.AlarmTime.Minutes;
	seconds = (uint32_t) sAlarm.AlarmTime.Seconds;

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
					break;
				case 'M':
					minutes = firstNumber*10 + secondNumber;
					break;
				case 'S':
					seconds = firstNumber*10 + secondNumber;
					//TREZBA POPRAWIC BO POTEM JAK WK�ADAMY DO ALARMU alarm_time TO NIE DZIA�A
					uint32_t alarm_time[] = {hours, minutes, seconds};
					saveAlarmFlash(alarm_time); //TU CHC� ZAPISYWAC DO PAMI�CI FLASH
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
//____________________________________________________________________________________________________________


/**
 * Ustawienie godziny, minuty lub sekundy w zegarze.
 * @param whichPartToSet Wartosc mowiaca o tym czy bedzie ustawiana godzina, minuta, lub sekunda.
 * @return Flaga oznaczajaca czy operacje wykonano poprawnie.
 */

//__________________________________OBGADAC___________________________________________________________________
//W warunku while(getCharKeypad() != '*' && getCharKeypad() != 'D') nie ma odszumiania,
//po co dwa razy odszumianie?
//if(gettedChar == 'A' && firstNumberSaved == true)
//{
//	counterKpadX++;
//}
//Wystarczy chyba raz to robic skoro i tak flaga firstNumberSaved mowi nam ktora cyfra jest wpisywana
//Po co jest char znak = getCharKeypad();? Nie u�ywasz tego.
bool setHourMinOrSecInTime(char whichPartToSet)
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
//____________________________________________________________________________________________________________


/**
 * Ustawienie czasu zegara w RTC.
 * @param hours Godzina do zapisania.
 * @param minutes Minuty do zapisania.
 * @param seconds Sekundy do zapisania.
 */
//__________________________________OBGADAC___________________________________________________________________
//My�l� ze powinni�my u�ywac jednej struktury konfiguracyjnej RTC_HandleTypeDef, najlepiej z maina
//Za bardzo powielamy kod w przeciwnym wypadku
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
//____________________________________________________________________________________________________________


/**
 * Ustawienie czasu alarmu budzika w RTC.
 * @param hours Godzina do zapisania.
 * @param minutes Minuty do zapisania.
 * @param seconds Sekundy do zapisania.
 */

//__________________________________OBGADAC___________________________________________________________________
//My�l� ze powinni�my u�ywac jednej struktury konfiguracyjnej RTC_HandleTypeDef, najlepiej z maina
//Za bardzo powielamy kod w przeciwnym wypadku
void setAlarmInRTC(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	//uint32_t x = time[6] - '0';

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
//____________________________________________________________________________________________________________

