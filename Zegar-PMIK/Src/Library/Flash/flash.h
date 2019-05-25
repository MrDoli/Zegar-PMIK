/*
 * flash.h
 *
 * Author: Marcin Dolicher, Micha³ Stolarz
*/

/**
 * \file flash.h
 * \brief Plik naglowkowy z metodami odpowiadajacymi za zapis do pamieci flash.
 */

#include "main.h"
#ifndef LIBRARY_FLASH_FLASH_H_
#define LIBRARY_FLASH_FLASH_H_

uint32_t flash_addresses[3];
void saveAlarmFlash(uint32_t* Flash_Data);
void readAlarmFlash(uint32_t* Flash_Data);

#endif /* LIBRARY_FLASH_FLASH_H_ */
