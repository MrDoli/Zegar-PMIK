/*
 * controller.c
 *
 *  Created on: 06.04.2019
 *      Author: Marcin Dolicher
 */

#include "controller.h"
extern  bool actualScreen[3];

void changeScreen(){

}

void controller(){

}

bool* getActualScreen(void)
{
    return actualScreen;
}

void setActualScreen(bool screenArray[])
{
	actualScreen[0] = screenArray[0];
	actualScreen[1] = screenArray[1];
	actualScreen[2] = screenArray[2];

}
