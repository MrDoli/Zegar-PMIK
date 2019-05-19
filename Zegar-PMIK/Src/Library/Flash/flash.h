/*
 * flash.h
 *
 * Author: Marcin Dolicher, Micha³ Stolarz
*/
#include "main.h"
//#include "stm32f4xx_hal_flash_ex.h"
//#include "stm32f4xx_hal_flash.h"
#ifndef LIBRARY_FLASH_FLASH_H_
#define LIBRARY_FLASH_FLASH_H_

uint32_t flash_addresses[3];
void saveAlarmFlash(uint32_t* Flash_Data);
void readAlarmFlash(uint32_t* Flash_Data);

#endif /* LIBRARY_FLASH_FLASH_H_ */
