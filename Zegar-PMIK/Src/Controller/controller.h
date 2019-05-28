/*
 * controller.h
 *
 *  Created on: 06.04.2019
 *      Author: Marcin Dolicher
 */

/**
 * \file controller.h
 * \brief Plik naglowkowy z metodami controllera
 */

#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "main.h"
#include <stdbool.h>

extern bool actualScreen[3];
extern char global_char;
extern int global_int;
void controllerInit();
bool controller(char gotCharacter);

// Getters and setters
void setActualScreen(bool screenArray[]);
bool* getActualScreen(void);
void handleDirectionButton(char sign);
void setTimeUser();
void setAlarmUser();
void setTimeInRTC(uint8_t hours, uint8_t minutes, uint8_t seconds);
void setAlarmInRTC(uint8_t hours, uint8_t minutes, uint8_t seconds);
bool setHourMinOrSecInTime(char whichPartToSet);
bool setHourMinOrSecInAlarm(char whichPartToSet);
void turnOnAlarm();
void turnOffAlarm();


#endif /* CONTROLLER_CONTROLLER_H_ */
