#include "Touchscreen.h"
#include "GUI.h"

extern I2C_HandleTypeDef hi2c1;
#define Orientation90	0x01

uint16_t X_SIZE_Touch = 480*TS_Callib;
uint16_t Y_SIZE_Touch= 272*TS_Callib;

void Error(void)
{
	while(1)
	{
		GUI_Error_Screen();
	}
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
	uint16_t temp;
  coord = (TS_IO_Read(DeviceAddr, TOUCH1_XH) << 8) & 0x0F00;
	coord |= TS_IO_Read(DeviceAddr, TOUCH1_XL);
	
	if (Orientation90)
	{
		temp = coord;
		*Y = X_SIZE_Touch - coord;
	}
	else{
		*X = coord;
	}
	
  coord = (TS_IO_Read(DeviceAddr, TOUCH1_YH) << 8) & 0x0F00;
	coord |= TS_IO_Read(DeviceAddr, TOUCH1_YL);
	
		if (Orientation90)
	{
		*X = coord;
	}
	else{
		*Y = coord;
	}
	
}

void TS_Reg_Read()
{
//	uint8_t lib_h = 0;
//	uint8_t lib_l = 0;
//	uint8_t firm = 0;

//	lib_h = TS_IO_Read(TS_I2C_ADDRESS, ID_G_LIB_VERSION_H);
//	lib_l = TS_IO_Read(TS_I2C_ADDRESS, ID_G_LIB_VERSION_L);
//	firm = TS_IO_Read(TS_I2C_ADDRESS, ID_G_FIRMID);

}

void TS_AutoCalib()
{
	unsigned char uc_temp = 0x00;
	uint16_t xres = 272, yres = 480;
	uint8_t buf = 0;

//	uint8_t mode = 0, state = 0;

	/*	???	 */
	TS_IO_Write(TS_I2C_ADDRESS, ID_G_AUTO_CLB_MODE, 0);
	HAL_Delay(100);
//
//	TS_IO_Write(TS_I2C_ADDRESS, ID_G_STATE, AUTO_CALIBRATION);
//	HAL_Delay(1);


	/*	???	 */

	TS_IO_Write(TS_I2C_ADDRESS, TS_DEVICE_MODE, 0x100);
	HAL_Delay(100);

	TS_IO_Write(TS_I2C_ADDRESS, 2, 0x4);
	HAL_Delay(100);

	for(uint8_t i=0;i<100;i++)
	{
		TS_IO_Read(TS_I2C_ADDRESS, 0);
		if (0x0 == ((uc_temp&0x70)>>4))
		{
				break;
		}
		HAL_Delay(100);
	}

	TS_IO_Write(TS_I2C_ADDRESS, TS_DEVICE_MODE, 0x100);
	HAL_Delay(200);
	TS_IO_Write(TS_I2C_ADDRESS, 2, 0x5);
	HAL_Delay(300);
	TS_IO_Write(TS_I2C_ADDRESS, TS_DEVICE_MODE, 0x0);
	HAL_Delay(100);

//	state = TS_IO_Read(TS_I2C_ADDRESS, ID_G_STATE);
	buf = (uint8_t)(xres >> 8);
	TS_IO_Write(TS_I2C_ADDRESS,ID_G_MAX_X_HIGH, buf);
	HAL_Delay(100);
	buf = (uint8_t)(xres & 0xFF);
	TS_IO_Write(TS_I2C_ADDRESS,ID_G_MAX_X_LOW, buf);
	HAL_Delay(100);

	buf = (uint8_t)(yres >> 8);
	TS_IO_Write(TS_I2C_ADDRESS,ID_G_MAX_Y_HIGH, buf);
	HAL_Delay(100);
	buf = (uint8_t)(yres & 0xFF);
	TS_IO_Write(TS_I2C_ADDRESS,ID_G_MAX_Y_LOW, buf);
	HAL_Delay(100);


}
