/*
 * flash.h
 *
 * Author: Marcin Dolicher, Micha� Stolarz
*/
#include "main.h"
//#include "stm32f4xx_hal_flash_ex.h"
//#include "stm32f4xx_hal_flash.h"
#ifndef LIBRARY_FLASH_FLASH_H_
#define LIBRARY_FLASH_FLASH_H_

uint32_t Flash_Address[3];
void Save_Alarm(uint32_t* Flash_Data);
void Read_Alarm(uint32_t* Flash_Data);
/*
void Flash_Write(uint32_t Flash_Data);
uint32_t Flash_Read();
*/

#endif /* LIBRARY_FLASH_FLASH_H_ */
