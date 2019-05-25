/*
 * clock.h
 *
 * Author: Marcin Dolicher, Micha³ Stolarz
*/

/**
 * \file clock.h
 * \brief Plik naglowkowy z metodami odpowiadajacymi za wyswietlanie
 * 		ekranow zwiazanych z czasem (wyswietlanie, ustawianie).
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "main.h"

void updateTime(char time[]);
void showMenuButtons();
void showCity();
void setTimeScreen();

#endif /* CLOCK_H_ */
