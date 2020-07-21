/*
 * BlueTooth.c
 *
 *  Created on: Jul 9, 2020
 *      Author: Lab
 */

#include "BlueTooth.h"

void BlueTooth_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* PB8 - Res 3 (BT Vcc enable pin), PB9 - Res 4 (BT programming pin) */
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOF, BT_VCC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF, BT_PROG_PIN, GPIO_PIN_RESET);
}

void BlueTooth_On(void)
{
	HAL_GPIO_WritePin(GPIOF, BT_VCC_PIN, GPIO_PIN_SET);
	HAL_Delay(3);

	hlpuart1.Init.BaudRate = 9600;
	if (HAL_UART_Init(&hlpuart1) != HAL_OK)
	{
	_Error_Handler(__FILE__, __LINE__);
	}
}

void BlueTooth_Off(void)
{
	HAL_GPIO_WritePin(GPIOF, BT_VCC_PIN, GPIO_PIN_RESET);
	HAL_Delay(3);

	hlpuart1.Init.BaudRate = 9600;
	if (HAL_UART_Init(&hlpuart1) != HAL_OK)
	{
	_Error_Handler(__FILE__, __LINE__);
	}
}

void BlueTooth_AT_Mode(void)
{
	HAL_GPIO_WritePin(GPIOF, BT_VCC_PIN, GPIO_PIN_RESET);
	HAL_Delay(3);
	HAL_GPIO_WritePin(GPIOF, BT_PROG_PIN, GPIO_PIN_SET);
	HAL_Delay(3);
	HAL_GPIO_WritePin(GPIOF, BT_VCC_PIN, GPIO_PIN_SET);
	HAL_Delay(3);

	hlpuart1.Init.BaudRate = 38400;
	if (HAL_UART_Init(&hlpuart1) != HAL_OK)
	{
	_Error_Handler(__FILE__, __LINE__);
	}

}

void BlueTooth_Param_Init(uint32_t baud_rate, uint8_t stop_bit, uint8_t parity)
{
	uint8_t buf[32];
	char str[] = "AT+UART";

	sprintf(buf, "%s=%d,%d,%d", str, baud_rate, stop_bit, parity);

	HAL_UART_Transmit(&hlpuart1, buf, sizeof(buf), 1);

//	sprintf(buf, "%s%s", str, "?");

}

void BlueTooth_Module_Name(char* name)
{
	uint8_t buf[32];

}


void BlueTooth_Module_Init(void)
{
	BlueTooth_GPIO_Init();
	BlueTooth_AT_Mode();
	BlueTooth_Param_Init(9600, 1, 2);

}




