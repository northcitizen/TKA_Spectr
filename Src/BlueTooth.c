
#include "BlueTooth.h"

////////////////////////////////////////////////////////////

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

	HAL_GPIO_WritePin(GPIOB, BT_VCC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, BT_PROG_PIN, GPIO_PIN_RESET);
}

void BlueTooth_On(void)
{

	////////////////////////////////////
	HAL_UART_MspDeInit(&huart1);
	HAL_UART_DeInit(&huart1);

	huart1.Init.BaudRate = BT_BAUD_RATE;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_UART_MspInit(&huart1);

	HAL_GPIO_WritePin(GPIOB, BT_VCC_PIN, GPIO_PIN_SET);
	HAL_Delay(3);

}

void BlueTooth_Off(void)
{
	HAL_GPIO_WritePin(GPIOB, BT_VCC_PIN, GPIO_PIN_RESET);
	HAL_Delay(3);
	HAL_UART_MspDeInit(&huart1);
	HAL_UART_DeInit(&huart1);

}

void BlueTooth_AT_Mode(void)
{

	HAL_UART_MspDeInit(&huart1);
	HAL_UART_DeInit(&huart1);

	huart1.Init.BaudRate = 38400;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
	_Error_Handler(__FILE__, __LINE__);
	}

	HAL_UART_MspInit(&huart1);

	HAL_GPIO_WritePin(GPIOB, BT_VCC_PIN, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB, BT_PROG_PIN, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB, BT_VCC_PIN, GPIO_PIN_SET);
	HAL_Delay(10);

}

void BlueTooth_Param_Init(uint32_t baud_rate, uint8_t stop_bit, uint8_t parity)
{
	uint8_t buf[32]={0}, *p;
	char str[] = "AT+UART";

	sprintf(buf, "%s=%d,%d,%d\r\n", str, baud_rate, stop_bit, parity);

	p = strchr(buf, '\n');

	HAL_UART_Transmit(&huart1, (uint8_t *)&buf, (p - &buf[0])+1, 10);
	HAL_Delay(10);
//	sprintf(buf, "%s%s", str, "?");

}

void BlueTooth_Module_Name(char* name)
{
	uint8_t buf[32]={0}, *p;
	char str[] = "AT+NAME";

	sprintf(buf, "%s=%s\r\n", str, name);

	p = strchr(buf, '\n');

	HAL_UART_Transmit(&huart1, (uint8_t *)&buf, (p - &buf[0])+1, 10);
	HAL_Delay(10);
}

void BlueTooth_Set_PIN(char* pass)
{
	uint8_t buf[32]={0}, *p;
	char str[] = "AT+PSWD";

	sprintf(buf, "%s=%c%s%c\r\n", str,'"', pass,'"');

	p = strchr(buf, '\n');

	HAL_UART_Transmit(&huart1, (uint8_t *)&buf, (p - &buf[0])+1, 10);
	HAL_Delay(10);

}

void Bluetooth_Reset(void)
{
	char str[] = "AT+RESET\r\n";

	HAL_UART_Transmit(&huart1, (uint8_t *)&str, sizeof(str), 10);
	HAL_Delay(10);
}

void BlueTooth_Module_Init(void)
{


	BlueTooth_GPIO_Init();
	BlueTooth_AT_Mode();
	//HAL_Delay(1000);
	BlueTooth_Param_Init(BT_BAUD_RATE, 1, 0);
	BlueTooth_Module_Name("TKA_SPECTR");
	BlueTooth_Set_PIN("1488");
	Bluetooth_Reset();

	HAL_GPIO_WritePin(GPIOB, BT_PROG_PIN, GPIO_PIN_RESET);
//	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, BT_VCC_PIN, GPIO_PIN_RESET);
//	HAL_Delay(100);


}


void BlueTooth_Test(void)
{
	char str[] = "AT+UART=115200,1,0\r\n";

	/* AT Mode */
	BlueTooth_GPIO_Init();
	BlueTooth_AT_Mode();
	HAL_Delay(1000);

	while(1)
	{
		HAL_UART_Transmit(&huart1, (uint8_t *)&str, sizeof(str), 10);
		HAL_Delay(200);
	}


}




