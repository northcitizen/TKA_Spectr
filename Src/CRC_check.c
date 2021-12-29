#include "CRC_check.h"

uint64_t flash_data_read_buff(uint32_t flash_addr_buff) 
{ 
	return ( *(__IO uint64_t*) flash_addr_buff);
}

uint64_t CRC_buff = 0, crcr_flash = 0;
uint32_t addr_i;

CRC_Check_StatusTypeDef CRC_Check(uint32_t start_flash_addr, uint32_t flash_size, uint32_t CRC_addr)
{

	for (addr_i = start_flash_addr; addr_i < start_flash_addr + (flash_size*8); addr_i+=8)
	{
		CRC_buff += flash_data_read_buff(addr_i);
	}
	crcr_flash = flash_data_read_buff(CRC_addr);
	
	if(CRC_buff == flash_data_read_buff(CRC_addr))
	{
		return	CRC_OK;
	} else
	{
		return	CRC_ERROR;
	}
};
