#include "sys_config.h"
#include "stm32f10x_flash.h"
#include "extern_var.h"

#define SECTOR_SIZE   2048
#define FLASH_SIZE    1024

uint16_t FLASH_ReadHalfword(uint32_t address);
uint32_t FLASH_ReadWord(uint32_t address);
void FLSH_ReadData(uint32_t startAddress,uint16_t *readbuf,uint16_t cnt2read);
void FLASH_WriteData(uint32_t startAddress,uint16_t*writebuf,uint16_t cnt2write);

uint16_t  SYS_Get_Param()
{  
	
  return FLASH_ReadHalfword((uint32_t)0x08020000);
	
} 

void SYS_Set_Param(uint16_t ID)
{
	Dev_Num = ID;
	FLASH_WriteData((uint32_t)0x08020000,&ID,1);
		
}

uint16_t FLASH_ReadHalfword(uint32_t address)
{
	
	return *(__IO uint16_t *)address;	
	
}

uint32_t FLASH_ReadWord(uint32_t address)
{
	uint16_t temp_h,temp_l;
	temp_l = *(__IO uint16_t *)address;
  temp_h = *(__IO uint16_t *)(address+2);
	
	return  (temp_h<<16)|temp_l;
}

void FLSH_ReadData(uint32_t startAddress,uint16_t *readbuf,uint16_t cnt2read)
{
	uint16_t dataIndex;
	
	for(dataIndex=0;dataIndex<cnt2read;dataIndex++)
  {
		readbuf[dataIndex] = FLASH_ReadHalfword(startAddress+dataIndex*2);		
		
  }	
	
}


void FLASH_WriteData(uint32_t startAddress,uint16_t*writebuf,uint16_t cnt2write)
{
	uint32_t offsetAddress = startAddress - FLASH_BASE;
	uint32_t sectorPosition = offsetAddress/SECTOR_SIZE;
	
	uint32_t sectorStartAddress = sectorPosition*SECTOR_SIZE+FLASH_BASE;
	uint16_t dataIndex;
	
	if(startAddress < FLASH_BASE || (startAddress+cnt2write*2) > (FLASH_BASE + SECTOR_SIZE*FLASH_SIZE/2))
	{
		 return;		
	}
	
	FLASH_Unlock();
	

	
	FLASH_ErasePage(sectorStartAddress);
	
	for(dataIndex=0;dataIndex < cnt2write;dataIndex++)
	{
		
		FLASH_ProgramHalfWord(startAddress+dataIndex*2,*(writebuf+dataIndex));
	}
	
	FLASH_Lock();
	
}


