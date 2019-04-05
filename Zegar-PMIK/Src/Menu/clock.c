/*
 * clock.c
 *
 *  Created on: 05.04.2019
 *      Author: Marcin Dolicher
 */

#include "..\Inc\clock.h"
#include "..\Library\Display\ssd1306.h"

extern char time[7];
extern char date[7];



char* get_time(RTC_HandleTypeDef* hrtc)
{
  RTC_TimeTypeDef gTime;

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);

  /* Display time Format: hh:mm:ss */
  sprintf((char*)time,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds);

  return time;
}

char* get_date(RTC_HandleTypeDef* hrtc){
	RTC_DateTypeDef gDate;

	/* Get the RTC current Date */
	HAL_RTC_GetDate(hrtc, &gDate, RTC_FORMAT_BIN);

	/* Display date Format: dd-mm-yy */
	sprintf((char*)date,"%02d-%02d-%2d",gDate.Date, gDate.Month, 2000 + gDate.Year);

	return date;
}

void show_time(RTC_HandleTypeDef* hrtc ){
	 ssd1306_SetCursor(15, 22);
	 ssd1306_WriteString(get_time(hrtc), Font_11x18, White);
	 ssd1306_UpdateScreen();
}
