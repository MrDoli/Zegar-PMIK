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

static bool actualScreen[3] = {true, false, false};

void changeScreen();
void controller();

// Getters and setters
void setActualScreen(bool screenArray[]);
bool* getActualScreen(void);


#endif /* CONTROLLER_CONTROLLER_H_ */
