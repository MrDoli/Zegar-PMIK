/*
 * flash.c
 *
 * Author: Marcin Dolicher, Micha³ Stolarz
*/

/**
 * \file flash.c
 * \brief Plik implementujacy metody zapisu do pamieci flash
 */

/**
 * \param flas_addresses Tablica z adresami pamieci pod ktore bedzia zapisywany czas.
 * Pierwszy element to adres godziny, drugi - adres minut, trzeci - adres sekund.
 */

#include "flash.h"

uint32_t flash_addresses[3] = {0x08040000,0x08040010,0x08040020};

/**
 * Zapisuje godzine alarmu budzika w pamieci Flash.
 * @param flash_data Tablica z czasem do zapisu, gdzie pierwszy element to godzina, drugi - minuty, trzeci - sekundy.
 */
void saveAlarmFlash(uint32_t* flash_data)
{
	HAL_FLASH_Unlock();
	FLASH_Erase_Sector(FLASH_SECTOR_6,VOLTAGE_RANGE_3);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,flash_addresses[0],flash_data[0]);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,flash_addresses[1],flash_data[1]);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,flash_addresses[2],flash_data[2]);
	HAL_FLASH_Lock();
}

/**
 * Odczytuje zapisana wczesniej godzine alarmu budzika.
 * @param flash_data Tablica z czasem do zapisu, gdzie pierwszy element to godzina, drugi - minuty, trzeci - sekundy.
 */
void readAlarmFlash(uint32_t* flash_data)
{
	flash_data[0] = *(uint32_t*)flash_addresses[0];
	flash_data[1] = *(uint32_t*)flash_addresses[1];
	flash_data[2] = *(uint32_t*)flash_addresses[2];
}
