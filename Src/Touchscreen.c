#include "Touchscreen.h"

extern I2C_HandleTypeDef hi2c1;
#define Orientation90	0x01

uint16_t X_SIZE_Touch = 480;
uint16_t Y_SIZE_Touch= 272;

volatile uint16_t temporary_y = 0, temporary_x = 0;

void Error(void)
{

  }

uint8_t TS_IO_Read(uint8_t DeviceAddr, uint8_t Reg)
{
  uint8_t read_value = 0;
  HAL_I2C_Mem_Read(&hi2c1, DeviceAddr, Reg, I2C_MEMADD_SIZE_8BIT, &read_value, 1, 0x100);

  return read_value;
}

void TS_IO_Write(uint8_t DeviceAddr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  HAL_I2C_Mem_Write(&hi2c1, DeviceAddr, (uint8_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x100);
  if(status != HAL_OK) Error();
}

uint8_t TS_ReadID(uint8_t DeviceAddr)
{
  volatile uint8_t ucReadId = 0;
  uint8_t nbReadAttempts = 0;
  int8_t bFoundDevice = 0;

  for(nbReadAttempts = 0; ((nbReadAttempts < 3) && !(bFoundDevice)); nbReadAttempts++)
  {
    ucReadId = TS_IO_Read(DeviceAddr, ID_G_CIPHER);
    if(ucReadId == CHIP_ID)
    {
      bFoundDevice = 1;
    }
  }
  return (ucReadId);
}

void Touch_Ini(void)
{
	if(TS_ReadID(TS_I2C_ADDRESS) != CHIP_ID) Error();
  HAL_Delay(200);
}

void TS_Get_XY1(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y)
{
	static uint16_t coord = 0x0000;

	coord = (TS_IO_Read(DeviceAddr, TOUCH1_XH) << 8) & 0xFF00;
	coord |= TS_IO_Read(DeviceAddr, TOUCH1_XL);
	
	if (Orientation90)
	{
//		*Y = (uint16_t)((X_SIZE_Touch - coord) * TS_Callib_x);
		*Y = (X_SIZE_Touch - coord) * TS_Callib_x;
	}
	else{
//		*X = (uint16_t)(coord * TS_Callib_x);
		*X = coord * TS_Callib_x;
	}
	
  coord = (TS_IO_Read(DeviceAddr, TOUCH1_YH) << 8) & 0xFF00;
	coord |= TS_IO_Read(DeviceAddr, TOUCH1_YL);
	
		if (Orientation90)
	{
//		*X = (uint16_t)(coord * TS_Callib_y);
		*X = coord * TS_Callib_y;
		temporary_x = coord;
	}
	else{
//		*Y = (uint16_t)(coord * TS_Callib_y);
		*Y = coord * TS_Callib_y;
	}
	
}
