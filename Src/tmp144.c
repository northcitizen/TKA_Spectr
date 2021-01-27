/*
 * tmp144.c
 *
 *  Created on: 25 џэт. 2021 у.
 *      Author: Lab-prog
 */

#include "tmp144.h"
extern UART_HandleTypeDef huart2;

volatile uint16_t temperature_measure = 0;
volatile bool usart2_ready = false;
float temperature_C = 0;
uint8_t u2_receive[4] = {};
uint8_t u2 = 0;

void Temperature_Measure_Func(void)
{
	uint8_t command[2] = {0x55, 0xF1};

	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);

	HAL_UART_Transmit(&huart2, (uint8_t *) &command, 2, 1);

	temperature_C = temperature_measure * 0.0625;

}

void USART2_IRQHandler(void)
{

	HAL_UART_Receive(&huart2, u2_receive, 4, 100);

	if(u2_receive[0] == 0x55)
	{
		if(u2_receive[1] == 0xF1)
		{
			temperature_measure = (u2_receive[2] >> 4) | ((u2_receive[3]) << 4);
		}
	}

	HAL_UART_IRQHandler(&huart2);
}

