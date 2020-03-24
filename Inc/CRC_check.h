#ifndef __CRC_CHECK_H
#define __CRC_CHECK_H

#include "stm32l4xx_hal.h"

typedef enum
{
  CRC_OK       = 0x00,
  CRC_ERROR    = 0x01,
} CRC_Check_StatusTypeDef;

uint64_t flash_data_read_buff(uint32_t flash_addr_buff);
CRC_Check_StatusTypeDef CRC_Check(uint32_t start_flash_addr, uint32_t flash_size, uint32_t CRC_addr);

#endif /* CRC_CHECK_H*/
