/*
 * clock.h
 *
 *  Created on: 05.04.2019
 *      Author: Marcin Dolicher
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "main.h"

char time[7];
char date[7];

char* get_time(RTC_HandleTypeDef* hrtc);
char* get_date(RTC_HandleTypeDef* hrtc);

void show_time(RTC_HandleTypeDef* hrtc );
#endif /* CLOCK_H_ */
