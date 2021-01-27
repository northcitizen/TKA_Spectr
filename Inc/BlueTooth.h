#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "main.h"
#include <stdio.h>
#include <string.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"


#define BT_VCC_PIN		GPIO_PIN_8
#define BT_PROG_PIN		GPIO_PIN_9
#define BT_BAUD_RATE	9600

extern UART_HandleTypeDef huart1;

void BlueTooth_Test(void);
void BlueTooth_Module_Init(void);
void BlueTooth_GPIO_Init(void);
void BlueTooth_On(void);
void BlueTooth_Off(void);

#endif
