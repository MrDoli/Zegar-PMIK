/*
 * flash.c
 *
 *  Created on: 04.04.2019
 *      Author: Michal
 */
#include "flash.h"

uint32_t Flash_Address[3] = {0x08040000,0x08040010,0x08040020};

/*
void Flash_Write(uint8_t Flash_Data, uint32_t Address)
{
	HAL_FLASH_Unlock();
	FLASH_Erase_Sector(FLASH_SECTOR_6,VOLTAGE_RANGE_3);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,Address,Flash_Data);
	HAL_FLASH_Lock();
}


uint8_t Flash_Read(uint32_t Address)
{
	uint32_t Flash_Data;
	Flash_Data = *(uint8_t*)Address;
	return Flash_Data;
}

*/

void Save_Alarm(uint32_t* Flash_Data)
{
	HAL_FLASH_Unlock();
	FLASH_Erase_Sector(FLASH_SECTOR_6,VOLTAGE_RANGE_3);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Flash_Address[0],Flash_Data[0]);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Flash_Address[1],Flash_Data[1]);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Flash_Address[2],Flash_Data[2]);
	HAL_FLASH_Lock();
}

void Read_Alarm(uint32_t* Flash_Data)
{
	Flash_Data[0] = *(uint32_t*)Flash_Address[0];
	Flash_Data[1] = *(uint32_t*)Flash_Address[1];
	Flash_Data[2] = *(uint32_t*)Flash_Address[2];
}
