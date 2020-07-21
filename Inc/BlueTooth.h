#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "main.h"
#include <stdio.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"


#define BT_VCC_PIN		GPIO_PIN_8
#define BT_PROG_PIN		GPIO_PIN_9

extern UART_HandleTypeDef hlpuart1;



#endif
