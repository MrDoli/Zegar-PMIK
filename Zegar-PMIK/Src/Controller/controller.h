/*
 * controller.h
 *
 *  Created on: 06.04.2019
 *      Author: Marcin Dolicher
 */

#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "main.h"
#include <stdbool.h>

//static bool actualScreen[3] = {true, false, false};
extern bool actualScreen[3];
void controllerInit();
void changeScreen();
bool controller(char gotCharacter, bool alarmIsSet);

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
bool turnOnAlarm(bool alarmIsSet);


#endif /* CONTROLLER_CONTROLLER_H_ */
