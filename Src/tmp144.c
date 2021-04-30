/*
 * tmp144.c
 *
 *  Created on: 25 ���. 2021 �.
 *      Author: Lab-prog
 */

#include "tmp144.h"
extern UART_HandleTypeDef huart2;
volatile uint16_t temperature_measure = 0;
volatile bool usart2_ready = false, usart2_wait = false;
//float temperature_C = 0; //2021.03.24
float temperature_degree = 0;	//2021.03.26
volatile uint8_t u2_receive[4] = {};
uint8_t u2 = 0;

void Temperature_Measure_Func(void)
{
	uint8_t command[2] = {0x55, 0xF1};



	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
#ifdef SERVICE
 	HAL_Delay(1);
#endif
	HAL_UART_Transmit(&huart2, (uint8_t *) &command, 2, 1);


	usart2_wait = false;
	while(!usart2_ready)
	{
		if(usart2_wait) break;
		__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	}

	usart2_ready = false;
//	usart2_wait = false;

	//temperature_degree = temperature_measure * 0.0625;



}

void USART2_IRQHandler(void)
{
	CLEAR_BIT(USART2->ISR, USART_ISR_ORE);

			u2_receive[u2] = USART2 -> RDR;

			if(u2 == 4)
			{
				usart2_ready = true;
				u2 = 0;
				if((u2_receive[0] == 0x55) & (u2_receive[1] == 0xF1))
				{
					temperature_measure = (*(int16_t*)(&u2_receive[2])) >> 4;
				    temperature_degree = temperature_measure * 0.0625;
				}

			}else
			{
				u2++;
			}


	  /* USER CODE END USART2_IRQn 0 */
	  HAL_UART_IRQHandler(&huart2);
}

