/*
 * keypad.h
 *
 *  Created on: 14.04.2019
 *      Author: Michal
 */

/**
 * \file keypad.h
 * \brief Plik naglowkowy z metodami odpowiadajacymi za obsluge klawiatury.
 */

#include "stdint.h"
#include "main.h" // musi byc bo tam zadeklarowane zmienne pinow

#ifndef KEYPAD_H_
#define KEYPAD_H_

char getCharKeypad();
int getIntKeypad();

#endif /* KEYPAD_H_ */
