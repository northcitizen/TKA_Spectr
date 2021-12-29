#ifndef __TOUCHSCREEN_H
#define __TOUCHSCREEN_H

#include "stm32l4xx_hal.h"
#include <string.h>
#include <stdlib.h>

//-------------------------------------------
#define	TS_I2C_ADDRESS		0x70

#define	GEST_ID				((uint8_t)	0x01)
#define	TD_STATUS			((uint8_t)	0x02)

#define	TOUCH1_XH			((uint8_t)	0x03)
#define	TOUCH1_XL			((uint8_t)	0x04)
#define	TOUCH1_YH			((uint8_t)	0x05)
#define	TOUCH1_YL			((uint8_t)	0x06)
#define	TOUCH1_WEIGHT	((uint8_t)	0x07)
#define	TOUCH1_MISC		((uint8_t)	0x08)

#define	TOUCH2_XH			((uint8_t)	0x09)
#define	TOUCH2_XL			((uint8_t)	0x0A)
#define	TOUCH2_YH			((uint8_t)	0x0B)
#define	TOUCH2_YL			((uint8_t)	0x0C)
#define	TOUCH2_WEIGHT	((uint8_t)	0x0D)
#define	TOUCH2_MISC		((uint8_t)	0x0E)

#define	TOUCH3_XH			((uint8_t)	0x0F)
#define	TOUCH3_XL			((uint8_t)	0x10)
#define	TOUCH3_YH			((uint8_t)	0x11)
#define	TOUCH3_YL			((uint8_t)	0x12)
#define	TOUCH3_WEIGHT	((uint8_t)	0x13)
#define	TOUCH3_MISC		((uint8_t)	0x14)

#define	TOUCH4_XH			((uint8_t)	0x15)
#define	TOUCH4_XL			((uint8_t)	0x16)
#define	TOUCH4_YH			((uint8_t)	0x17)
#define	TOUCH4_YL			((uint8_t)	0x18)
#define	TOUCH4_WEIGHT	((uint8_t)	0x19)
#define	TOUCH4_MISC		((uint8_t)	0x1A)

#define	TOUCH5_XH			((uint8_t)	0x1B)
#define	TOUCH5_XL			((uint8_t)	0x1C)
#define	TOUCH5_YH			((uint8_t)	0x1D)
#define	TOUCH5_YL			((uint8_t)	0x1E)
#define	TOUCH5_WEIGHT	((uint8_t)	0x1F)
#define	TOUCH5_MISC		((uint8_t)	0x20)

#define	ID_G_THGROUP	((uint8_t)	0x80)
#define	ID_G_THPEAK		((uint8_t)	0x81)
#define	ID_G_THCAL		((uint8_t)	0x82)
#define	ID_G_COMPENSATE_STATUS		((uint8_t)	0x83)
#define	ID_G_COMPENSATE_FLAG			((uint8_t)	0x84)
#define	ID_G_THDIFF		((uint8_t)	0x85)
#define	ID_G_CTRL			((uint8_t)	0x86)
#define	ID_G_TIMEENTERMONITOR			((uint8_t)	0x87)
#define	ID_G_PERIODACTIVE					((uint8_t)	0x88)
#define	ID_G_PERIODMONITOR				((uint8_t)	0x89)

#define	ID_G_CIPHER		((uint8_t)	0xA3)
#define	ID_G_VENODRID	((uint8_t)	0xA8)

#define	CHIP_ID				((uint8_t)	0x0A)
#define	VENDOR_ID			((uint8_t)	0x79)

#define	TS_Callib			2.65
#define TS_Callib_x			1
#define TS_Callib_y			1
//------------------------------------------
void Touch_Ini(void);
void Error(void);
uint8_t TS_ReadID(uint8_t DeviceAddr);
uint8_t TS_IO_Read(uint8_t DeviceAddr, uint8_t Reg);
void 		TS_IO_Write(uint8_t DeviceAddr, uint8_t Reg, uint8_t Value);
void		TS_Get_XY1(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y);

//------------------------------------------

#endif /* __TOUCHSCREEN_H */
