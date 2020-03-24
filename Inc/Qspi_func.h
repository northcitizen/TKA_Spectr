#include "main.h"
/* W25Q commands */

#define write_enable			0x06
#define write_disable			0x04
#define page_program			0x02
#define read_data				0x03
#define device_id				0xAB
#define manuf_id				0x90
#define chip_erase				0xC7
#define sector_erase			0x20
#define block_erase32			0x52
#define block_erase64			0xD8


#define write_sr1				0x01
#define write_sr2				0x31
#define write_sr3				0x11

#define deviceid_quad			0x94
#define fastread_quad_o		0x6B
#define fastread_quad_io	0xEB
#define	q_page_program		0x32

/* Pins */

#define CS_PIN                GPIO_PIN_2
#define CS_GPIO_PORT          GPIOA

#define CLK_PIN               GPIO_PIN_10
#define CLK_GPIO_PORT         GPIOF

#define IO0_PIN               GPIO_PIN_1
#define IO0_GPIO_PORT         GPIOB
#define IO1_PIN               GPIO_PIN_0
#define IO1_GPIO_PORT         GPIOB
#define IO2_PIN               GPIO_PIN_7
#define IO2_GPIO_PORT         GPIOF
#define IO3_PIN               GPIO_PIN_6
#define IO3_GPIO_PORT         GPIOF

typedef enum
{
	io0=0x01,
	io1=0x02,
	io2=0x03,
	io3=0x04,
	cs=0x05,
	clk=0x06
} pinStr;
//extern OSPI_RegularCmdTypeDef idread;

void Cmd_ID_Read(void);

void Single_Mode(void);

void GPIO_QSPI_Init(void);
void QSPI_Recieve_Init(void);
void QSPI_Transmit_Init(void);

void Reset(uint8_t pin);
void Set(uint8_t pin);

void SPI_Instruction(uint8_t cmd);
void SPI_Dummy(uint8_t n);
void SPI_Check_Busy(void);
void SPI_Byte_T(uint8_t byte);
void SPI_Transmit(uint8_t* data, uint32_t address, uint32_t size);
void SPI_Receive(uint8_t* arr, uint32_t address, uint32_t size);
void SPI_Receive_ID(uint8_t* arr);
void SPI_Manuf_ID(uint8_t* arr);
void SPI_Chip_Erase(void);
void SPI_Sector_Erase(uint32_t address);
uint8_t SPI_Read_SR(uint8_t sr);

void QSPI_Recieve_IO(uint8_t* arr, uint32_t address, uint32_t size);
void QSPI_Recieve_O(uint8_t* arr, uint32_t address, uint32_t size);
void QSPI_Transmit(uint8_t* data, uint32_t address, uint32_t size);
void QSPI_Recieve_IO_16(uint16_t* arr, uint32_t address, uint32_t size);
void QSPI_Recieve_O_16(uint16_t* arr, uint32_t address, uint32_t size);
void QSPI_Transmit_16(uint16_t* data, uint32_t address, uint32_t size);
void QSPI_Recieve_IO_32(uint32_t* arr, uint32_t address, uint32_t size);
void QSPI_Recieve_O_32(uint32_t* arr, uint32_t address, uint32_t size);
void QSPI_Transmit_32(uint32_t* data, uint32_t address, uint32_t size);
void QSPI_Array(uint8_t* data, uint32_t address, uint32_t size);
void QSPI_Array_16(uint16_t* data, uint32_t address, uint32_t size);
void QSPI_Array_32(uint32_t* data, uint32_t address, uint32_t size);
