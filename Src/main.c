#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"
#include "Qspi_func.h"
#include "usb_device.h"
#include "ltdc.h"
#include "usbd_customhid.h"
#include "Touchscreen.h"
#include "stdint.h"
#include <stdlib.h>
#include "GUI.h"
#include "CRC_check.h"
#include "Calibration_Address.h"
#include "Rabs_math.h"
#include "fatfs.h"
#include "CQS_Calculate.h"
#include "CRI_Calculate.h"
#include "Calculate_Measure.h"


#include "Buttons.h"

#define MEASURE 0x01

//CMD DEFINITION
#define CMD_DATA_TRANSMIT 				0x01
#define CMD_RABS_DATA_TRANSMIT 		0x01
#define CMD_CNFG 									0x02
#define CMD_CAPTURE 							0x03
#define CMD_CRC_LOAD_STATUS				0x66
#define CMD_CALCULATED_DATA_TRANSMIT	0x04

#define CMD_FLASH_SET_WR_ADDR	 		0x0A
#define CMD_FLASH_WR_DATA			 		0x0B
#define CMD_FLASH_READ_DATA			 	0x0C
#define CMD_FLASH_ERASE_DATA			0x0D

//FLASH DATA ADDRESS
#define FLASH_DATA_START 		0x08100000
#define FLASH_DATA_SIZE			21514 //number of uint64_t data
#define FLASH_CRC_ADDR 			0x0812A050 //addr for FLASH CRC check 


uint8_t dataToSend[64]= {0};
uint8_t dataToReceive[12]= {0};
uint8_t flag_EOS = 0;

uint64_t	flash_data_write, flash_data_read;
uint32_t	flash_address;
uint8_t		flash_data_read_SND[8]= {0};

uint16_t Calibration_year, Serial_part_device, Serial_number_device, Calibration_date, Calibration_month;

extern FATFS SDFatFs;

uint16_t PARGraph_B, PARGraph_G, PARGraph_R, PARGraph_IR;
uint8_t BluetoothStat = 0;

UART_HandleTypeDef hlpuart1;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;
LTDC_HandleTypeDef hltdc;
DMA2D_HandleTypeDef hdma2d;

SD_HandleTypeDef hsd1;
static void MX_SDMMC1_SD_Init(void);
extern char SDPath[4];

uint8_t wtext[] = "TKA spectrometry SD CARD TEST"; /* File write buffer */
uint8_t rtext[100];  

 const sImageFlash bmTKA_logo2 = {
  270, // xSize
  181, // ySize
  0x0000  // Pointer to picture data
};

extern USBD_HandleTypeDef hUsbDeviceFS;
FLASH_EraseInitTypeDef EraseInitStruct, EraseInitStruct2;
CRC_Check_StatusTypeDef CRC_STATUS;

uint8_t RxBuf[2];
extern uint8_t  GUI_screen_state, Graph_Field, Source_Type, Color_Field, Measure_Color_xy, pause, flag_spectral, direction, Language_status, Bluetooth;
extern uint16_t Measure_Field, sdfile_cnt;
//Line recieve data
uint16_t Line[1024] = {0}, Line_buff[1024] = {0}; 
float Line_Rabs_buff[1024] = {0}, Line_Rabs_buff_graph_test[1024] = {0};
float max_Rabs_graph, max_Rabs;
//Calibration factors data
float Spectral_Corection_Buff[1024] = {0}, WaveLenght[1024] = {0}, Scattering_Light = 0, Exposure_Factor = 0, Hazard_Blue[1024] = {0}, Hazard_Retina[1024] = {0};
float Factor1 = 0, Factor2 = 0, EnergyFactor_E = 0, EnergyFactor_L = 0;
float S0_lambda[1024] = {0}, S1_lambda[1024] = {0}, S2_lambda[1024] = {0};
float E_day, E_day_Wt, E_Night, SP_Measure, PPFD_PPL_Measure, PPFD_PPL_Blue_Measure, PPFD_PPL_Green_Measure, PPFD_PPL_Red_Measure, PPFD_PPL_Far_Red_Measure,
	ELr_Measure, ELb_Measure, CCT_Measure;

float calibratre_x_1964[1024] = {0}, calibratre_z_1964[1024] = {0}, calibratre_x_1931[1024] = {0}, calibratre_y_1931[1024] = {0}, calibratre_z_1931[1024] = {0};
uint16_t  WaveLenght_Graph[4] = {0},  DarkSignal = 0; 
uint8_t Mode_EL = 1, SD_Detect, old_sd_detect = 10, write_FileNum = 0;
uint16_t colorimetry_XYZ[3] = {0}, lambda_d_Measure, lambda_c_Measure, Tc_Measure = 0;
int16_t colorimetry_LAB[3] = {0};
extern int16_t delta_Eab_Measure;
float colorimetry_xy[2] = {0}, colorimetry_uv[2] = {0}, colorimetry_uv1976[2] = {0};
uint16_t max_el = 0;
uint16_t cnt_delay_bar = 0;
extern uint8_t Rotation_Screen_Spectral, Rotation_Screen_Spectral_Old, Calculate_deltaEab_Done, Color_rend_Field, preGUI_screen_state;

//Calibration table factors data
float Spectral_day[1024] = {0}, Spectral_night[1024] = {0}, Spectral_B[1024] = {0}, Spectral_R[1024] = {0};

//																					7.812ms	15.625ms	31.25ms	62.5ms	125ms	250ms	500ms	1s			2s			4s
const uint16_t exposure_timer_period[10] = {93,			186,			372,		744,		1488,	2976,	5952,	11905,	23810,	47619}; //93 = 7.812ms
	
volatile uint16_t	i=0, j=0;
volatile uint8_t	exp_num = 0, VGain = 0, LaserOnOff = 0, TFT_ON_OFF = 1, temp = 0, send_usb_block = 0, MeasureFlag_display = 0;
double percentage_charge; //battry charge
volatile uint16_t RGB565_480x272[130560] = {0x00000000};

uint16_t bmp[108000] = {0x0000}; //buffer for image max 270х400
extern sImage Locus;

uint8_t pause_button = 0;
/*bluetooth variable*/
const char ready[] = "TKA_SPECTROMETRY\r\n";
const char format[] = "\r\n";
char send[30];


uint8_t buff_i2c[3] = {0,0x0A,0x00};
volatile uint32_t cnt_touch_delay =0;


uint8_t str1[60]={0};
typedef struct USART_prop{
	uint8_t usart_buf[13];
	uint8_t usart_cnt;
	uint8_t is_tcp_connect;
	uint8_t is_text;
} USART_prop_ptr;
USART_prop_ptr usartprop;
uint8_t ii=0;

uint8_t adcResult = 0;

uint8_t buff_i2c_b = 0;
uint16_t Touch_x = 0, Touch_y = 0;
double buf_pix;
uint16_t button_pos_x = 155, button_pos_y = 165;

uint32_t n;
extern uint16_t i_old_color;
uint16_t Cl, Cl_mass[350];
////////////////////////////////////////////////////////

uint8_t mode = 0, state = 0, ac_mode = 0, chip_id = 0;
volatile uint16_t xres = 0;
volatile uint16_t yres = 0;
uint8_t firm = 0;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void); 
static void MX_TIM4_Init(void); 
static void MX_TIM5_Init(void);
static void MX_TIM6_Init(void);
static void MX_SPI1_Init(void);      
static void MX_LPUART1_UART_Init(void);
static void MX_LTDC_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_DMA2D_Init(void);
static void MX_TIM7_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void auto_exposure(void);
void exposure_display(uint16_t X, uint16_t Y);
void Rabs_graph_to_int(void);

void DWT_Init(void) 
{
  if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) 
  {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  }
}
 
uint32_t DWT_Get(void)
{
  return DWT->CYCCNT;
}
 
__inline
uint8_t DWT_Compare(int32_t tp)
{
  return (((int32_t)DWT_Get() - tp) < 0);
}
 
void DWT_Delay(uint32_t us) // useconds
{
  int32_t tp = DWT_Get() + us * (SystemCoreClock/1000000);
  while (DWT_Compare(tp));
}

void Calculate_Data()
{
	Calculate_XYZ(Line_Rabs_buff, Measure_Color_xy ? calibratre_x_1931 : calibratre_x_1964, Measure_Color_xy ? calibratre_y_1931:Spectral_day, Measure_Color_xy ? calibratre_z_1931:calibratre_z_1964);
	Calculate_xy(colorimetry_XYZ);
	Tc_Measure = Calculate_Tc(Line_Rabs_buff, Measure_Color_xy);
	if(GUI_screen_state == Color_Screen)
	{
		if(Color_Field&Color_CIE_Luv) {Calculate_uv1976(colorimetry_xy);Calculate_uv(colorimetry_xy);} else 
		if(Color_Field&Color_CIE_Lab){Calculate_Lab(colorimetry_XYZ, Measure_Color_xy, Source_Type);}
	}
	if(GUI_screen_state == Measure_Screen || GUI_screen_state == Measure2_Screen|| GUI_screen_state == Measure3_Screen)
	{
			if(Measure_Field&Illuminance) {E_day = Calculate_EL_Day(Line_Rabs_buff, Spectral_day);}
			if(Measure_Field&Irradiance) {E_day_Wt = Calculate_EL_Day_Wt(Line_Rabs_buff);}
			
			if(Measure_Field&SP_measure) {E_Night = Calculate_EL_Night(Line_Rabs_buff, Spectral_night);
														E_day = (Measure_Field&Illuminance) ? E_day : Calculate_EL_Day(Line_Rabs_buff, Spectral_day);
														SP_Measure = (Calculate_SP(E_day, E_Night));}
			if(Measure_Field&PPFD) {PPFD_PPL_Measure = (Calculate_PPFD_PPL(Line_Rabs_buff, WaveLenght));//*100000
																	}
			if(Measure_Field&PPFD_BGR) {PPFD_PPL_Blue_Measure = (Calculate_PPFD_PPL_Range(Line_Rabs_buff, WaveLenght, BLUE_RANGE));//*100000
																	PPFD_PPL_Green_Measure = (Calculate_PPFD_PPL_Range(Line_Rabs_buff, WaveLenght, GREEN_RANGE));//*100000
																	PPFD_PPL_Red_Measure = (Calculate_PPFD_PPL_Range(Line_Rabs_buff, WaveLenght, RED_RANGE));//*100000
																	PPFD_PPL_Far_Red_Measure = (Calculate_PPFD_PPL_Range(Line_Rabs_buff, WaveLenght, FAR_RED_RANGE));//*100000
			}
			if(Measure_Field&delta_E){delta_Eab_Measure = Calculate_deltaEab();}
			if(Measure_Field&CIE_Luv){Calculate_uv1976(colorimetry_xy);Calculate_uv(colorimetry_xy);}
			if(Measure_Field&CIE_Lab){Calculate_Lab(colorimetry_XYZ, Measure_Color_xy, Source_Type);}
			if(Measure_Field&lambda_d){Calculate_Lambda_Dominant(Line_Rabs_buff, Measure_Color_xy);}	
			if(Measure_Field&lambda_c){Calculate_Lambda_Dominant(Line_Rabs_buff, Measure_Color_xy);}	
			if(Measure_Field&EbEr){ELr_Measure = Calculate_ELr(Line_Rabs_buff,Hazard_Retina);
														 ELb_Measure = Calculate_ELb(Line_Rabs_buff, Hazard_Blue);}

	
	}
}
double Get_Battery_Level()
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 2);
	adcResult = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	return percentage_charge = 100.0*adcResult/190;
}

void packet_generator_data_send(void) //send ADC data
{
			uint8_t q = 0, byte_low, byte_high;
			uint16_t CRC_pack = 0, packet_number = 0;
			packet_number = 0;
	
			memset(dataToSend, 0, sizeof(dataToSend));
	
			dataToSend[0] = 0xAB;
			dataToSend[1] = 0x12;
			dataToSend[2] = 0x01;
			q = 5;

			for (uint16_t cnt = 0; cnt < 1024; cnt++){
				
				byte_high = (Line_buff[cnt] >> 8) & 0x00FF;
				byte_low = Line_buff[cnt] & 0x00FF;
				
				dataToSend[q] = byte_high;
				dataToSend[q+1] = byte_low;
				CRC_pack = CRC_pack + byte_high + byte_low;
				q = q + 2;
				
				if(q >= 62 || cnt == 1023){
					dataToSend[3] = (packet_number>> 8) & 0x00FF;
					dataToSend[4] = packet_number & 0x00FF;
					dataToSend[63] = (CRC_pack+dataToSend[0]+dataToSend[1]+dataToSend[2] + packet_number);
					
					CRC_pack = 0;
					q = 5;
					packet_number = packet_number + 1;
					
					USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
					HAL_Delay(2);
				}
			}
			memset(dataToReceive, 0, sizeof(dataToReceive));
}

void packet_generator_Rabs_data_send(void) //send Rabs data
{
			uint8_t q = 0;
			uint16_t CRC_pack = 0, packet_number = 0;
			uint32_t buff_float;
	
			packet_number = 0;
	
			memset(dataToSend, 0, sizeof(dataToSend));
	
			Factor1 = Rabs_calc_Factor1(DarkSignal, Scattering_Light, Line_buff);
			Rabs_calc_main(Line_buff, DarkSignal, Factor1, Factor2, Spectral_Corection_Buff, Line_Rabs_buff);
			
	
			dataToSend[0] = 0xAB;
			dataToSend[1] = 0x12;
			dataToSend[2] = 0x03;
	
			dataToSend[5] = (Mode_EL == 0)? 0 : 1;
			dataToSend[6] = 0;
	
			q = 7;
			
			for (uint16_t cnt = 0; cnt < 1024; cnt++){
				
				memcpy(&buff_float, &Line_Rabs_buff[1023-cnt], sizeof(float));

				dataToSend[q] = (buff_float >> 24) & 0x000000FF;
				dataToSend[q+1] = (buff_float >> 16) & 0x000000FF;
				dataToSend[q+2] = (buff_float >> 8) & 0x000000FF;
				dataToSend[q+3] = (buff_float) & 0x000000FF;
				
				CRC_pack = CRC_pack + dataToSend[q] + dataToSend[q+1] + dataToSend[q+2] + dataToSend[q+3];
				q = q + 4;
				
				if(q >= 62 || cnt == 1023){
					dataToSend[3] = (packet_number>> 8) & 0x00FF;
					dataToSend[4] = packet_number & 0x00FF;
					dataToSend[63] = (CRC_pack+dataToSend[0]+dataToSend[1]+dataToSend[2] + packet_number);
					
					CRC_pack = 0;
					q = 7;
					packet_number = packet_number + 1;
					
					USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
					HAL_Delay(2);
				}
			}
			memset(dataToReceive, 0, sizeof(dataToReceive));
}


void packet_generator_Calculated_data_send(void) //send Calculated data
{
			uint8_t q = 0;
			uint16_t CRC_pack = 0, packet_number = 0;
			uint32_t buff_float;
	
			packet_number = 0;
	
			memset(dataToSend, 0, sizeof(dataToSend));
	
		//	Factor1 = Rabs_calc_Factor1(DarkSignal, Scattering_Light, Line_buff);
		//	Rabs_calc_main(Line_buff, DarkSignal, Factor1, Factor2, ((Mode_EL == 0)?Spectral_Corection_Buff_L:Spectral_Corection_Buff_E), Line_Rabs_buff);
				
			dataToSend[0] = 0xAB;
			dataToSend[1] = 0x12;
			dataToSend[2] = 0x04;
	
			dataToSend[5] = (Mode_EL == 0)? 0 : 1;
			dataToSend[6] = 0;
	
			q = 7;
			
			for (uint16_t cnt = 0; cnt < 1024; cnt++){
				
//				memcpy(&buff_float, &test_massive[cnt], sizeof(float));

				dataToSend[q] = (buff_float >> 24) & 0x000000FF;
				dataToSend[q+1] = (buff_float >> 16) & 0x000000FF;
				dataToSend[q+2] = (buff_float >> 8) & 0x000000FF;
				dataToSend[q+3] = (buff_float) & 0x000000FF;
				
				CRC_pack = CRC_pack + dataToSend[q] + dataToSend[q+1] + dataToSend[q+2] + dataToSend[q+3];
				q = q + 4;
				
				if(q >= 62 || cnt == 1023){
					dataToSend[3] = (packet_number>> 8) & 0x00FF;
					dataToSend[4] = packet_number & 0x00FF;
					dataToSend[63] = (CRC_pack+dataToSend[0]+dataToSend[1]+dataToSend[2] + packet_number);
					
					CRC_pack = 0;
					q = 7;
					packet_number = packet_number + 1;
					
					USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
					HAL_Delay(2);
				}

			}
			
			memset(dataToSend, 0, sizeof(dataToSend)); 
			
			colorimetry_xy[0] = 0.133;
				colorimetry_xy[1] = 0.852;
			//send xy color
				memcpy(&buff_float, &colorimetry_xy[0], sizeof(float));
				dataToSend[q] = (buff_float >> 24) & 0x000000FF;
				dataToSend[q+1] = (buff_float >> 16) & 0x000000FF;
				dataToSend[q+2] = (buff_float >> 8) & 0x000000FF;
				dataToSend[q+3] = (buff_float) & 0x000000FF;
				
				memcpy(&buff_float, &colorimetry_xy[1], sizeof(float));
				dataToSend[q+4] = (buff_float >> 24) & 0x000000FF;
				dataToSend[q+5] = (buff_float >> 16) & 0x000000FF;
				dataToSend[q+6] = (buff_float >> 8) & 0x000000FF;
				dataToSend[q+7] = (buff_float) & 0x000000FF;
								
			Tc_Measure = 3555;
				//send CCT
				memcpy(&buff_float, &Tc_Measure, sizeof(uint16_t));
				dataToSend[q+8]= (buff_float >> 8) & 0x000000FF;
				dataToSend[q+9] = (buff_float) & 0x000000FF;
						
						//send delta_Eab 
				Calculate_deltaEab_Done = 0x01;
				delta_Eab_Measure = -79;
			if(Calculate_deltaEab_Done == 0x01)
			{
				memcpy(&buff_float, &delta_Eab_Measure, sizeof(int16_t));
				dataToSend[q+10] = (buff_float >> 8) & 0x000000FF;
				dataToSend[q+11] = (buff_float) & 0x000000FF;
			}
				
					dataToSend[3] = (packet_number>> 8) & 0x00FF;
					dataToSend[4] = packet_number & 0x00FF;
					dataToSend[63] = (CRC_pack+dataToSend[0]+dataToSend[1]+dataToSend[2] + dataToSend[q]+dataToSend[q+1]+dataToSend[q+2] + dataToSend[q+3] + dataToSend[q+4]+
					dataToSend[q+5] + dataToSend[q+6] + dataToSend[q+7] + dataToSend[q+8] + dataToSend[q+9] + dataToSend[q+10] + dataToSend[q+11]+ packet_number);
					
					CRC_pack = 0;
					q = 7;
					packet_number = packet_number + 1;
					
					USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
					HAL_Delay(2);
			
			memset(dataToReceive, 0, sizeof(dataToReceive));
}



void usb_receive_processing(void)
{
	HAL_StatusTypeDef	flash_ok = HAL_ERROR;
	uint16_t CRC_pack = 0;
	uint32_t PAGEError = 0;
		if(dataToReceive[0] == 0xAB)
		{
			if(dataToReceive[1] == 0x12)
			{
			switch(dataToReceive[2])
				{
					case CMD_DATA_TRANSMIT : 
						send_usb_block = 1;
					if(dataToReceive[3] == CMD_RABS_DATA_TRANSMIT)
					{
						packet_generator_Rabs_data_send();
					}else{
						packet_generator_data_send();
					}
						memset(dataToReceive, 0, sizeof(dataToReceive));
						send_usb_block = 0;
					break;
					
					case CMD_CNFG :
						send_usb_block = 0;
						memset(dataToSend, 0, sizeof(dataToSend));
					
						dataToSend[0] = 0xAB;
						dataToSend[1] = 0x12;
						dataToSend[2] = CMD_CNFG;

						if (exp_num != dataToReceive[3]){
							exp_num = dataToReceive[3];
							htim2.Init.Period = exposure_timer_period[exp_num];
							MX_TIM2_Init();
							Calibration_Exposure_Change(exp_num);
						} else{
							__asm("nop");
						}
						
					/*Laser On/Off*/
						if (LaserOnOff != dataToReceive[4]){
							LaserOnOff = (dataToReceive[4] > 0) ? 1 : 0;
							if(LaserOnOff == 0){
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
							}else
							{
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
							}
						} else{
							__asm("nop");
						}
						
				/*	Set videogain*/
						if (VGain != dataToReceive[5]){
							VGain = (dataToReceive[5] > 0) ? 1 : 0;
							if(VGain == 0){
								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_SET);
							}else
							{
								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);
							}
						} else{
							__asm("nop");
						}
						
					/*	Set TFT On/Off*/
						if (TFT_ON_OFF != dataToReceive[6]){
							TFT_ON_OFF = (dataToReceive[6] > 0) ? 1 : 0;
							if(TFT_ON_OFF == 1){
								HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);//TFT_booster SHDN on
								HAL_NVIC_EnableIRQ(TIM4_IRQn); //TFT_booster SHDN on
								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET); //LTDC_En on
							}else
							{
								HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
								HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
							}
						} else{
							__asm("nop");
						}
						
					/*	Set E/L Mode*/
						if (Mode_EL != dataToReceive[7]){
							Mode_EL = (dataToReceive[7] > 0) ? 1 : 0; //Mode_EL=1 -Rabs_E, Mode_EL=0 -Rabs_L
						} else{
							__asm("nop");
						}

						dataToSend[3] = exp_num;
						dataToSend[4] = LaserOnOff;
						dataToSend[5] = VGain;
						dataToSend[6] = TFT_ON_OFF;
						dataToSend[7] = Mode_EL;
						dataToSend[63] = (CRC_pack+dataToSend[0]+dataToSend[1]+dataToSend[2]+dataToSend[3]+dataToSend[4]+dataToSend[5]+dataToSend[6]);
						
						USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
						memset(dataToReceive, 0, sizeof(dataToReceive));
					break;
						
					case	 CMD_FLASH_ERASE_DATA :
						EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
						EraseInitStruct.NbPages = 44; 
						EraseInitStruct.Page = 0;
						EraseInitStruct.Banks = FLASH_BANK_2; 
						HAL_FLASH_Unlock(); 
						if(HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK) {
							//Erase error!
						}
						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						HAL_FLASH_Lock();
						memset(dataToReceive, 0, sizeof(dataToReceive));
					break;
					case CMD_FLASH_SET_WR_ADDR :
						flash_address = ((uint32_t)dataToReceive[3]<<24)|((uint32_t)dataToReceive[4]<<16)|((uint32_t)dataToReceive[5]<<8)|((uint32_t)dataToReceive[6]);

						dataToSend[0] = 0xAB;
						dataToSend[1] = 0x12;
						dataToSend[2] = 0x1A;
						memset(dataToReceive, 0, sizeof(dataToReceive));
						HAL_Delay(2);
					break;
					
					case CMD_FLASH_WR_DATA :
						flash_ok = HAL_ERROR;
						flash_data_write = ((uint64_t)dataToReceive[7]<<56)|((uint64_t)dataToReceive[8]<<48)|\
																((uint64_t)dataToReceive[9]<<40)|((uint64_t)dataToReceive[10]<<32|\
																(uint64_t)dataToReceive[3]<<24)|((uint64_t)dataToReceive[4]<<16)|\
																((uint64_t)dataToReceive[5]<<8)|((uint64_t)dataToReceive[6]);
						HAL_FLASH_Unlock();
						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, flash_address, flash_data_write);
						}
						HAL_FLASH_Lock();
						memset(dataToReceive, 0, sizeof(dataToReceive));
						HAL_Delay(2);
					break;
					
					case CMD_FLASH_READ_DATA :
						flash_address = ((uint32_t)dataToReceive[3]<<24)|((uint32_t)dataToReceive[4]<<16)|((uint32_t)dataToReceive[5]<<8)|((uint32_t)dataToReceive[6]);
						flash_data_read = flash_data_read_buff(flash_address);
						
						memcpy(flash_data_read_SND, &flash_data_read, sizeof(uint64_t));

						dataToSend[0] = 0xAB;
						dataToSend[1] = 0x12;
						dataToSend[2] = 0x1C;
					
						dataToSend[7] = flash_data_read_SND[7];
						dataToSend[8] = flash_data_read_SND[6];
						dataToSend[9] = flash_data_read_SND[5];
						dataToSend[10]= flash_data_read_SND[4];
						dataToSend[3] = flash_data_read_SND[3];
						dataToSend[4] = flash_data_read_SND[2];
						dataToSend[5] = flash_data_read_SND[1];
						dataToSend[6]	= flash_data_read_SND[0];
					
						USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
						memset(dataToReceive, 0, sizeof(dataToReceive));
						HAL_Delay(2);
					break;
					case CMD_CRC_LOAD_STATUS:
						dataToSend[0] = 0xAB;
						dataToSend[1] = 0x12;
						dataToSend[2] = 0x66;
						if(CRC_STATUS == CRC_OK){
							dataToSend[3] = 0x01;
						} else
						{
							dataToSend[3] = 0x00;
						}
						USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
						memset(dataToReceive, 0, sizeof(dataToReceive));
						HAL_Delay(2);
					break;	
						
				case CMD_CALCULATED_DATA_TRANSMIT : 
						send_usb_block = 1;
						
						packet_generator_Calculated_data_send();

						memset(dataToReceive, 0, sizeof(dataToReceive));
						send_usb_block = 0;
					break;

						
					default : __asm("nop");
				}
			}
		}
		else 
		{
			__asm("nop");
		}
}
	uint8_t num = 0;


/*BLUETOOTH UART processing*/
#define START_ADDR_USER_PAGE           ((uint32_t)0x0803F800)
void send_bluetooth_float(uint32_t data)
{
		uint8_t data_bluetooth_send[4] = {0};
		
		data_bluetooth_send[0] = (data >> 24) & 0x000000FF;
		data_bluetooth_send[1] = (data >> 16) & 0x000000FF;
		data_bluetooth_send[2] = (data >> 8) & 0x000000FF;
		data_bluetooth_send[3] = (data) & 0x000000FF;

		HAL_UART_Transmit(&hlpuart1, (uint8_t*)&data_bluetooth_send, 4, 1);
}

void string_parse(uint8_t* buf_str)
{			
	
	uint32_t buff_float;
	uint8_t	data_bluetooth_send[2] = {0};
	
	if(buf_str[0] == 0xAB)
	{
		if(buf_str[1] == 0x12)
		{
			if(buf_str[2] == 0x02)
			{
					/*Laser On/Off*/
							LaserOnOff = (buf_str[4] > 0) ? 1 : 0;
						if(LaserOnOff == 0){
					 			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
							}else
							{
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
							}
//							sprintf(send, "TKA battery level: %.1f%%", Get_Battery_Level());
//							HAL_UART_Transmit(&hlpuart1, (uint8_t*)&send, 30, 5);
							
							//send absolute spectral
							for(i = 0; i < 1024; i++){
//								memcpy(&buff_float, &test_massive[i], sizeof(float));
								send_bluetooth_float(buff_float);
						}
							colorimetry_xy[0] = 0.133;
							colorimetry_xy[1] = 0.852;
							//send xy color
								memcpy(&buff_float, &colorimetry_xy[0], sizeof(float));
								send_bluetooth_float(buff_float);
						
								memcpy(&buff_float, &colorimetry_xy[1], sizeof(float));
								send_bluetooth_float(buff_float);

								//send CCT
								memcpy(&buff_float, &Tc_Measure, sizeof(uint16_t));
								data_bluetooth_send[0] = (buff_float >> 8) & 0x000000FF;
								data_bluetooth_send[1] = (buff_float) & 0x000000FF;
								HAL_UART_Transmit(&hlpuart1, (uint8_t*)&data_bluetooth_send, 2, 1);
						
								//send Source type
								HAL_UART_Transmit(&hlpuart1, &Source_Type, 1, 1);
						
								//send delta_Eab 
						Calculate_deltaEab_Done = 0x01;
						delta_Eab_Measure = -79;
								if(Calculate_deltaEab_Done == 0x01)
								{
									memcpy(&buff_float, &delta_Eab_Measure, sizeof(int16_t));
									data_bluetooth_send[0] = (buff_float >> 8) & 0x000000FF;
									data_bluetooth_send[1] = (buff_float) & 0x000000FF;
									HAL_UART_Transmit(&hlpuart1, (uint8_t*)&data_bluetooth_send, 2, 1);
								}

	
			}
		}
	}else
	{
		__asm("nop");
	}
}


void UART2_RxCpltCallback(void)
{

	uint8_t b;
  b = str1[0];
 if (usartprop.usart_cnt>12)
  {
    usartprop.usart_cnt = 0;
    HAL_UART_Receive_IT(&hlpuart1,(uint8_t*)str1,1);
    return;
  }
  usartprop.usart_buf[usartprop.usart_cnt] = b;
  if(b==0x0A)
  {
    usartprop.usart_buf[usartprop.usart_cnt+1]=0;
    string_parse((uint8_t*)usartprop.usart_buf);
    usartprop.usart_cnt=0;
    HAL_UART_Receive_IT(&hlpuart1,(uint8_t*)str1,1);
		
    return;
  }
  usartprop.usart_cnt++;
  HAL_UART_Receive_IT(&hlpuart1,(uint8_t*)str1,1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart==&hlpuart1)
  {
    UART2_RxCpltCallback();
  }
}

float SREF;

	uint8_t buff_set,block_graph = 0;
	uint16_t buff_set2;	

extern uint16_t Line_Rabs_buff_graph2[355];
uint32_t array_recieve[10] = {0};
uint8_t Rotation_Screen_Spectral_Old3 = 0xFF;

int main(void)
{
  HAL_Init();
	HAL_Delay(1);
  SystemClock_Config();
	HAL_Delay(1);
  MX_GPIO_Init();
	HAL_Delay(1);
	DWT_Init();
	HAL_Delay(1);
	MX_TIM2_Init();
	HAL_Delay(1);
	MX_TIM4_Init();
	HAL_Delay(1);
	MX_TIM5_Init();
	HAL_Delay(1);
	MX_USB_DEVICE_Init();
	HAL_Delay(1);
	MX_DMA2D_Init();
	HAL_Delay(1);
	MX_SPI1_Init();
	HAL_Delay(1);
	MX_I2C1_Init();
	HAL_Delay(1);
	MX_LPUART1_UART_Init();
	HAL_Delay(1);
 	MX_LTDC_Init();
	HAL_Delay(1);
	MX_ADC1_Init();
	HAL_Delay(1);
	HAL_TIM_OC_Start(&htim5, TIM_CHANNEL_1);
	HAL_Delay(1);
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1);  //ST Signal
	HAL_Delay(2);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_Delay(1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_Delay(1);
	HAL_NVIC_SetPriority(TIM4_IRQn, 1, 0);  //Booster
	HAL_Delay(2);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	HAL_Delay(1);
	HAL_TIM_Base_Start(&htim4);
	HAL_Delay(1);
	HAL_TIM_OC_Start_IT(&htim4, TIM_CHANNEL_1);
	HAL_Delay(1);
	HAL_TIM_OC_Start_IT(&htim4, TIM_CHANNEL_2);
	HAL_Delay(1);
//	HAL_UART_Receive_IT(&hlpuart1,(uint8_t*)str1,1);
//	HAL_Delay(1);
//	if(BluetoothStat == 0) {HAL_UART_MspDeInit(&hlpuart1);}
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_SET);
	MX_TIM6_Init();
	HAL_Delay(1);
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	HAL_Delay(1);
	HAL_TIM_Base_Start_IT(&htim6);

	HAL_Delay(1);

	HAL_Delay(1);
	HAL_LTDC_SetAddress(&hltdc,(uint32_t) &RGB565_480x272,0);
	HAL_Delay(1);
	


	// ---------------------------------------------------------------------------------------

//	TS_AutoCalib();
//	mode = TS_IO_Read(TS_I2C_ADDRESS, 0);
//	ac_mode = TS_IO_Read(TS_I2C_ADDRESS, ID_G_AUTO_CLB_MODE);
//	state = TS_IO_Read(TS_I2C_ADDRESS, ID_G_STATE);
//
//
//	xres = 0;
//	yres = 0;
//
//	chip_id = TS_IO_Read(TS_I2C_ADDRESS, ID_G_CIPHER);
//
//	xres |= (TS_IO_Read(TS_I2C_ADDRESS, ID_G_MAX_X_HIGH) << 8);
//	HAL_Delay(1);
//	xres |=	TS_IO_Read(TS_I2C_ADDRESS, ID_G_MAX_X_LOW);
//
//	yres |= (TS_IO_Read(TS_I2C_ADDRESS, ID_G_MAX_Y_HIGH) << 8);
//	HAL_Delay(1);
//	yres |=	TS_IO_Read(TS_I2C_ADDRESS, ID_G_MAX_Y_LOW);
//
//	firm = TS_IO_Read(TS_I2C_ADDRESS, ID_G_FIRMID);

	// ---------------------------------------------------------------------------------------

//	Touch_Ini();

	MX_SDMMC1_SD_Init();
	MX_FATFS_Init();
	
	GPIO_QSPI_Init();
	
		Single_Mode();	
		HAL_Delay(20);

//Load calibrations data	
#if MEASURE

	buff_set = Calibration_Load_1byte(SET_MODEEL, 3);
	if(buff_set == 0xFF){Mode_EL = 0;} else{Mode_EL = buff_set;}		
			
	buff_set = Calibration_Load_1byte(SET_GRAPHFIELD, 3);
	if(buff_set == 0xFF){Graph_Field = 0;} else{Graph_Field = buff_set;}
	
	buff_set = Calibration_Load_1byte(SET_COLORFIELD, 3);
	if(buff_set == 0xFF){Color_Field |= Color_CIE_xy;} else{Color_Field = buff_set;}	
	
	buff_set = Calibration_Load_1byte(SET_COLORRENDFIELD, 3);
	if(buff_set == 0xFF){Color_rend_Field = 0;} else{Color_rend_Field = buff_set;}	
	
		buff_set = Calibration_Load_1byte(SET_LANGUAGE, 3);
	if(buff_set == 0xFF){Language_status = Ru;} else{Language_status = buff_set;}	
			
	buff_set = Calibration_Load_1byte(SET_SOURCETYPE, 3);
	if(buff_set == 0xFF){Source_Type |= Source_D55;} else{Source_Type = buff_set;}	
	
		buff_set = Calibration_Load_1byte(SET_BLUETOOTH, 3);
	if(buff_set == 0xFF){Bluetooth = 0x00;} else{Bluetooth = buff_set;}	
	
	buff_set2 = Calibration_Load_2byte(SET_MEASUREFIELD, 1);		
	if(buff_set2 == 0xFFFF){Measure_Field = 0;} else{Measure_Field = buff_set2;}		
	
	buff_set2 = Calibration_Load_2byte(FILENUMBER, 1);		
	if(buff_set2 == 0xFFFF){sdfile_cnt = 0;} else{sdfile_cnt = buff_set2;}	
	
	
	
	Calibration_WaveLenght_Graph();
	Calibration_Exposure_Change(exp_num);
	Calibration_Load_Pack(Mode_EL == 0x00 ? SPECTRAL_CORRECTION_L:SPECTRAL_CORRECTION_E, 0x400, Spectral_Corection_Buff);

	EnergyFactor_E = Calibration_Load_float(ENERGY_FACTOR_E);
	EnergyFactor_L = Calibration_Load_float(ENERGY_FACTOR_L);
	
	Calibration_Load_Pack(SPECTRAL_DAY, 0x400, Spectral_day);
	Calibration_Load_Pack(SPECTRAL_NIGHT, 0x400, Spectral_night);
	
	Calibration_Load_Pack(X2_CIE1931, 0x400, calibratre_x_1931);
	Calibration_Load_Pack(Y2_CIE1931, 0x400, calibratre_y_1931);
	Calibration_Load_Pack(Z2_CIE1931, 0x400, calibratre_z_1931);
	
	Calibration_Load_Pack(X10_CIE1964, 0x400, calibratre_x_1964);
	Calibration_Load_Pack(Z10_CIE1964, 0x400, calibratre_z_1964);

	uint16_t wave_num = 0;
	
	for(uint16_t i = 0; i < 2*1024; i=i+8){
		WaveLenght[wave_num] = ((float)Calibration_Load_2byte(WAVELENGHT+i, 0))/100.0+300.0;
		WaveLenght[wave_num+1] = ((float)Calibration_Load_2byte(WAVELENGHT+i, 1))/100.0+300.0;
		WaveLenght[wave_num+2] = ((float)Calibration_Load_2byte(WAVELENGHT+i, 2))/100.0+300.0;
		WaveLenght[wave_num+3] = ((float)Calibration_Load_2byte(WAVELENGHT+i, 3))/100.0+300.0;
		
		Hazard_Blue[wave_num] = ((float)Calibration_Load_2byte(SPECTRAL_BLUELIGHT+i, 0))/1000.0;
		Hazard_Blue[wave_num+1] = ((float)Calibration_Load_2byte(SPECTRAL_BLUELIGHT+i, 1))/1000.0;
		Hazard_Blue[wave_num+2] = ((float)Calibration_Load_2byte(SPECTRAL_BLUELIGHT+i, 2))/1000.0;
		Hazard_Blue[wave_num+3] = ((float)Calibration_Load_2byte(SPECTRAL_BLUELIGHT+i, 3))/1000.0;
		
		Hazard_Retina[wave_num] = ((float)Calibration_Load_2byte(SPECTRAL_RETINA+i, 0))/1000.0;
		Hazard_Retina[wave_num+1] = ((float)Calibration_Load_2byte(SPECTRAL_RETINA+i, 1))/1000.0;
		Hazard_Retina[wave_num+2] = ((float)Calibration_Load_2byte(SPECTRAL_RETINA+i, 2))/1000.0;
		Hazard_Retina[wave_num+3] = ((float)Calibration_Load_2byte(SPECTRAL_RETINA+i, 3))/1000.0;
		
		S0_lambda[wave_num] = ((float)Calibration_Load_2byte(SPECTRAL_S0+i, 0))/100.0-50;
		S0_lambda[wave_num+1] = ((float)Calibration_Load_2byte(SPECTRAL_S0+i, 1))/100.0-50;
		S0_lambda[wave_num+2] = ((float)Calibration_Load_2byte(SPECTRAL_S0+i, 2))/100.0-50;
		S0_lambda[wave_num+3] = ((float)Calibration_Load_2byte(SPECTRAL_S0+i, 3))/100.0-50;
		
		S1_lambda[wave_num] = ((float)Calibration_Load_2byte(SPECTRAL_S1+i, 0))/100.0-50;
		S1_lambda[wave_num+1] = ((float)Calibration_Load_2byte(SPECTRAL_S1+i, 1))/100.0-50;
		S1_lambda[wave_num+2] = ((float)Calibration_Load_2byte(SPECTRAL_S1+i, 2))/100.0-50;
		S1_lambda[wave_num+3] = ((float)Calibration_Load_2byte(SPECTRAL_S1+i, 3))/100.0-50;
		
		
		S2_lambda[wave_num] = ((float)Calibration_Load_2byte(SPECTRAL_S2+i, 0))/100.0-50;
		S2_lambda[wave_num+1] = ((float)Calibration_Load_2byte(SPECTRAL_S2+i, 1))/100.0-50;
		S2_lambda[wave_num+2] = ((float)Calibration_Load_2byte(SPECTRAL_S2+i, 2))/100.0-50;
		S2_lambda[wave_num+3] = ((float)Calibration_Load_2byte(SPECTRAL_S2+i, 3))/100.0-50;
		
		wave_num = wave_num + 4;
	}
	

	Calibration_date =	Calibration_Load_2byte(CALIBRATION_DATE, 0);
	Calibration_month =	Calibration_Load_2byte(CALIBRATION_DATE, 1);
	Calibration_year =  Calibration_Load_2byte(CALIBRATION_YEAR, 0);
	
Serial_part_device =  Calibration_Load_2byte(SERIAL_DEVICE, 0);
Serial_number_device =  Calibration_Load_2byte(SERIAL_DEVICE, 1);
	
	for(uint16_t i = 0; i < 1024; i++){
		if(WaveLenght[i]<=400 && WaveLenght[i+1]>=400)
		{
			PARGraph_B = i;
		} else if (WaveLenght[i]<=500 && WaveLenght[i+1]>=500)
		{
			PARGraph_G = i;
		}else if (WaveLenght[i]<=600 && WaveLenght[i+1]>=600)
		{
			PARGraph_R = i;
		}
		else if (WaveLenght[i]<=700 && WaveLenght[i+1]>=700)
		{
			PARGraph_IR = i;
		}
	}
	
	WaveLenght_Graph[0] = (uint16_t)WaveLenght[0];
	WaveLenght_Graph[1] = (uint16_t)WaveLenght[255];
	WaveLenght_Graph[2] = (uint16_t)WaveLenght[511];
	WaveLenght_Graph[3] = (uint16_t)WaveLenght[1023];
	
	if(Mode_EL == 0){
		Factor2 = Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_L);
	}else
	{
		Factor2 = Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_E);
	}
	
	CRC_STATUS = CRC_Check(FLASH_DATA_START, FLASH_DATA_SIZE, FLASH_CRC_ADDR);
	GUI_screen_state = Calibration_Load_1byte(SCREENADDR, 3);
#endif

Calculate_Data();
uint32_t cnt_delay = 0, scr_refresh = 0;
uint32_t PAGEError = 0;
HAL_StatusTypeDef	flash_ok = HAL_ERROR;
						
	Get_Battery_Level();
	HAL_Delay(1);

Image_load(TKA_LOGO_BMP, TKA_LOGO_BMP_SIZEX*TKA_LOGO_BMP_SIZEY);
	
//	if(CRC_STATUS == CRC_OK)
//	{
		GUI_Title_Screen();
		for (uint16_t p = 0; p < 65000; p++){
		cnt_delay++;
			if((cnt_delay > 150 && exp_num < 6) || (cnt_delay > 950 && (exp_num >=+ 6 && exp_num < 8))||(cnt_delay > 1550 && exp_num >= 8)){
							auto_exposure();
							max_el = 0;
							cnt_delay = 0;
			}
		}
		
		
		Calculate_Data();
		HAL_Delay(2500);	
		Calculate_Data();
		usb_receive_processing();
		
		Image_load(Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP : XY10_LOCUS_BMP):
		Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP : LAB_LOCUS_BMP,
		Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEX*XY2_LOCUS_BMP_SIZEY : XY10_LOCUS_BMP_SIZEX*XY10_LOCUS_BMP_SIZEY):
		Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEX*LUV_LOCUS_BMP_SIZEY : LAB_LOCUS_SIZEX*LAB_LOCUS_SIZEY);		
		
		Locus.pData = (uint16_t *)bmp;
		Locus.Width = Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEX : XY10_LOCUS_BMP_SIZEX):
		Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEX : LAB_LOCUS_SIZEX;
		Locus.Height = Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEY : XY10_LOCUS_BMP_SIZEY):
		Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEY : LAB_LOCUS_SIZEY;
		
		switch(GUI_screen_state){
		case Measure_Screen: GUI_Measure_Screen();  break;
		case Measure2_Screen: preGUI_screen_state = Measure_Screen; GUI_Measure2_Screen();  break;
		case Measure3_Screen: preGUI_screen_state = Measure2_Screen; GUI_Measure_Screen(); GUI_Measure2_Screen();GUI_Measure3_Screen();  break;
		
		case Graph_Screen: preGUI_screen_state = Measure_Screen; GUI_Graph_Screen(); break;
		case Color_Screen: preGUI_screen_state = ColorSet1_Screen; GUI_Color_Screen();  break; 
		case Color_Rendition_Screen: preGUI_screen_state = Measure_Screen; GUI_ColorRend_Screen();break;
		default: GUI_screen_state =  Measure_Screen; GUI_Measure_Screen();  break;
		}

	MX_TIM7_Init();
	HAL_NVIC_SetPriority(TIM2_IRQn, 1, 4);  //
	HAL_Delay(1);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);
	HAL_Delay(1);
	HAL_TIM_Base_Start(&htim7);
	HAL_Delay(1);
	HAL_TIM_Base_Start_IT(&htim7);


 while (1)
 {        
            usb_receive_processing();
#if MEASURE
   Factor1 = Rabs_calc_Factor1(DarkSignal, Scattering_Light, Line_buff);
	 if(exp_num ==0 && max_el >53000)
	{
		exposure_display(100, 100);
	}
    Rabs_calc_main(Line_buff, DarkSignal, Factor1, Factor2, Spectral_Corection_Buff, Line_Rabs_buff);
		if(!block_graph) {memcpy(Line_Rabs_buff_graph_test, Line_Rabs_buff, sizeof(Line_Rabs_buff));}
		
		
		if((GUI_screen_state == Measure_Screen || GUI_screen_state == Measure2_Screen || GUI_screen_state == Measure3_Screen) && !pause)
		{	
			cnt_delay++;
			if(!pause){Calculate_Data();}
			if((cnt_delay > 40 && exp_num < 6) || (cnt_delay > 70 && (exp_num >= 6 && exp_num < 8))||(cnt_delay > 70 && exp_num >= 8)){
								auto_exposure();
								max_el = 0;
								cnt_delay = 0;
				}
		} 	
		else	if((GUI_screen_state == Color_Screen) && !pause)
		{	
			cnt_delay++;
			if(!pause){Calculate_Data();}
			if((cnt_delay > 40 && exp_num < 6) || (cnt_delay > 70 && (exp_num >= 6 && exp_num < 8))||(cnt_delay > 500 && exp_num >= 8)){
								auto_exposure();
								max_el = 0;
								cnt_delay = 0;
				}
		} 
		
		else {
				cnt_delay++;
				if((cnt_delay > 250 && exp_num < 6) || (cnt_delay > 950 && (exp_num >=+ 6 && exp_num < 8))||(cnt_delay > 1450 && exp_num >= 8)){
								auto_exposure();
								max_el = 0;
								cnt_delay = 0;
				}
		}
		
		


#endif         
        if(GUI_screen_state == Graph_Screen)
        {    
            scr_refresh++;
            if(scr_refresh > 35 ){
							block_graph = 1;
								if(preGUI_screen_state == Graph_Screen && Rotation_Screen_Spectral_Old3 == Rotation_Screen_Spectral){ Refresh_screen_Graph(20, 20, Line_Rabs_buff_graph2, Rotation_Screen_Spectral_Old3);}
								Rotation_Screen_Spectral_Old3 = Rotation_Screen_Spectral;
								max_Rabs_graph = Rabs_find_MAX(Line_Rabs_buff_graph_test, Rotation_Screen_Spectral_Old3);
								Rabs_graph_to_display(Rotation_Screen_Spectral_Old3, Line_Rabs_buff_graph_test);

								Spectral_DrawGraph_Line2(20, 20, Line_Rabs_buff_graph2, TFT_White, Rotation_Screen_Spectral_Old3);
                scr_refresh = 0;
								block_graph = 0;

            }
        } else{__asm("nop");}
  		
        GUI_Display_Refresh();
    }
}



void auto_exposure(void)
{ 
	//uint16_t max_el = 0;
	for (uint16_t i = 5; i<1024; i++){
		max_el = Line_buff[i] > max_el ? Line_buff[i] : max_el;
	}
	
	if(max_el < 20000 && exp_num != 9)
	{
		send_usb_block =1;
		exp_num++;
		htim2.Init.Period = exposure_timer_period[exp_num];
		MX_TIM2_Init();
		Calibration_Exposure_Change(exp_num);
		
		if(Mode_EL == 0){
			Factor2 = Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_L);
		}else
		{
			Factor2 = Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_E);
		}
		
//		exposure_display(100, 40);
		send_usb_block =0;
	} else if(max_el > 50000 && exp_num != 0)
	{
		send_usb_block =1;
		exp_num--;
		htim2.Init.Period = exposure_timer_period[exp_num];
		MX_TIM2_Init();
		Calibration_Exposure_Change(exp_num);
		
		if(Mode_EL == 0){
			Factor2 = Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_L);
		}else
		{
			Factor2 = Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_E);
		}
		
//		exposure_display(100, 40);
		send_usb_block =0;

	}
}
void exposure_display(uint16_t X, uint16_t Y)
{
		char buffer[9] = {0};
		float exposure_text;
		
		TFT_FillRectangle(X, Y, X+60, Y+8, TFT_Black_Bkgr);
		
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black_Bkgr);
		TFT_SetFont(&Font7EN_arch_big);
		
		exposure_text = (exp_num == 0) ? 7.812 : (exp_num == 1) ? 15.625 : (exp_num == 2) ? 31.25 : (exp_num == 3) ? 62.5 : (exp_num == 4) ? 125 :
		(exp_num == 5) ? 250 :(exp_num == 6) ? 500 : (exp_num == 7) ? 1000 : (exp_num == 8) ? 2000 : 4000;
		sprintf (buffer, "%.2f", exposure_text);
		
		TFT_DisplayString(X, Y, (uint8_t *)buffer, LEFT_MODE);
		TFT_DrawChar(X+56, Y, 'm');
		TFT_DrawChar(X+64, Y, 's');
}
																			

/*ST signal generator*/
void TIM2_IRQHandler(void)
{
	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	DWT_Delay(10);
	i = 0;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	
  cnt_delay_bar = 0;
	
	HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
	HAL_TIM_IRQHandler(&htim2);
}																					//	7.812ms	15.625ms	31.25ms	62.5ms	125ms	250ms	500ms	1s			2s			4s
//const uint16_t exposure_timer_period[10] = {93,			186,			372,		744,		1488,	2976,	5952,	11905,	23810,	47619}; //93 = 7.812ms
void TIM6_DAC_IRQHandler(void)
{
	pause_button = 0;
  /* USER CODE BEGIN TIM6_IRQn 0 */
	Get_Battery_Level();
	
	/* USER CODE END TIM6_IRQn 0 */
	HAL_NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
  HAL_TIM_IRQHandler(&htim6);

}


void TIM7_IRQHandler(void)
{
	
			
	if((GUI_screen_state == Measure_Screen || GUI_screen_state == Measure2_Screen || GUI_screen_state == Measure3_Screen||
			GUI_screen_state == Graph_Screen || GUI_screen_state == Color_Screen) && !pause &&  !flag_spectral) 
		{
			cnt_delay_bar++;
			
			if(exp_num > 4){
				
				if(cnt_delay_bar == ((exposure_timer_period[exp_num]/12)/500))
					{
						GUI_Bar_Measure(85, 13, 0.2);
					} 
				else if (cnt_delay_bar == 2*(exposure_timer_period[exp_num]/12)/500)
					{
						GUI_Bar_Measure(85, 13, 0.4);
					} 
					else if (cnt_delay_bar == 3*(exposure_timer_period[exp_num]/12)/500)
					{
						GUI_Bar_Measure(85, 13, 0.6);
					}
					else if (cnt_delay_bar == 4*(exposure_timer_period[exp_num]/12)/500)
					{
						GUI_Bar_Measure(85, 13, 0.8);
					 }
					else if (cnt_delay_bar == 5*((exposure_timer_period[exp_num]/12)/500))
					{

						GUI_Bar_Measure(85, 13, 1);
					}
				} else if(exp_num > 2)
				{
							if(cnt_delay_bar == 1){
								GUI_Bar_Measure(85, 13, 0.5);
							} else if(cnt_delay_bar == 2){
								GUI_Bar_Measure(85, 13, 1);
							}
				} else {
									GUI_Bar_Measure(85, 13, 1);}
			}
		
	SD_Detect = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15);
	if(old_sd_detect != SD_Detect & CRC_STATUS == CRC_OK){
		GUI_Button_SD_Card(55, 426, !SD_Detect);
		old_sd_detect = SD_Detect;
		if(SD_Detect == 0){
				MX_SDMMC1_SD_Init();
				MX_FATFS_Init();
			} else
			{
			FATFS_UnLinkDriver(SDPath);
				HAL_SD_DeInit(&hsd1);
			}
	}
			
	HAL_NVIC_ClearPendingIRQ(TIM7_IRQn);
	HAL_TIM_IRQHandler(&htim7);
}


/*Timer TFT_booster SHDN PWM mode*/
void TIM4_IRQHandler(void) 
{
	
	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_11);
	
	HAL_NVIC_ClearPendingIRQ(TIM4_IRQn);
	HAL_TIM_IRQHandler(&htim4);
}

/*SDO_IRQ interrupt*/
void EXTI9_5_IRQHandler(void)
{
	DWT_Delay(1);
  HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&RxBuf, (uint8_t*)&RxBuf, 2, 0);

	if((RxBuf[0] << 8 | RxBuf[1])>=0xCFFF)
	{
		Line[i] = Line[i-1]; 
	} else if((RxBuf[0] << 8 | RxBuf[1])<=0x0EFF)
	{
		Line[i] = Line[i-1]; 
	} else	
	{
		Line[i] = RxBuf[0] << 8 | RxBuf[1];
	}
	
	
	if(i >= 1023)
	{
		if(send_usb_block == 0 && (!pause))
			{
				memcpy(Line_buff, Line, sizeof(Line));
				
			}
			i = 0;
			
	} else
	{
			i++;
	}
	
	HAL_NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
}


/*Touch_screen interrupt*/
void EXTI3_IRQHandler(void)
{	
	cnt_touch_delay = cnt_touch_delay + 1;
	
	uint16_t Touch_x = 0, Touch_y = 0;
	TS_Get_XY1(TS_I2C_ADDRESS, &Touch_x, &Touch_y);
	
	if((!TFT_ON_OFF) && (cnt_touch_delay >= 50))
	{
			TFT_ON_OFF = 0x01;
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);//TFT_booster SHDN on
			HAL_NVIC_EnableIRQ(TIM4_IRQn); //TFT_booster SHDN on
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET); //LTDC_En on
		}
		else{
		if(TFT_ON_OFF && (cnt_touch_delay >= 0x0B)){
			
			if((Mode_EL == 0x00) && ((Touch_x >= 109*TS_Callib & Touch_x <= (109+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib)))
			{
				pause_button++;
				if(pause_button > 3)
				{	
					LaserOnOff = !LaserOnOff;
					LaserOnOff ? HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET):HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
					cnt_touch_delay = 0;
					pause_button = 0;
				}
				GUI_Touch_Processing();
				cnt_touch_delay = 0;
			} else {
				GUI_Touch_Processing();
				cnt_touch_delay = 0;
			}
		} 
		
		HAL_NVIC_ClearPendingIRQ(EXTI3_IRQn);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
	}
}


void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage 
    */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV5;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_USB|RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_SDMMC1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
	PeriphClkInit.LtdcClockSelection = RCC_LTDCCLKSOURCE_PLLSAI2_DIV4;
	PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
	PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLLP;

	
  PeriphClkInit.PLLSAI2.PLLSAI2Source = RCC_PLLSOURCE_HSE;
	PeriphClkInit.PLLSAI2.PLLSAI2M = 2;
  PeriphClkInit.PLLSAI2.PLLSAI2N = 9;
  PeriphClkInit.PLLSAI2.PLLSAI2P = RCC_PLLP_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2ClockOut = RCC_PLLSAI2_LTDCCLK;
	 
	PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSE;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 2;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 12;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_8B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.NbrOfDiscConversion = 1;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


/* SPI1 init function */
static void MX_SPI1_Init(void){

  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;//SPI_BAUDRATEPRESCALER_2
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_ENABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	__HAL_SPI_ENABLE(&hspi1);
}

/* Timer for Line_CLK generator*/
static void MX_TIM5_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 2;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 30;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.Pulse = 5;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim5);

}

/*Timer for ST_Exposure time*/
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 10000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = exposure_timer_period[exp_num];
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/*Timer TFT_booster SHDn PWM mode*/
static void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
	
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 50;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 2000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	
	 if (HAL_TIM_OC_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }


  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	
	sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 1000; //more cnt - zero; 1000 - 50%
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	
	sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 2000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}

static void MX_TIM6_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 48000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 3800;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }

}
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	
	  HAL_PWREx_EnableVddIO2();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PF5 VIDEO_GAIN*/
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_SET); //VIDEO_GAIN OFF

  /*Configure GPIO pin : PC4 ST LASER*/
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);		//ST init HIGH
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);	//Laser init OFF

    /*Configure GPIO pin : PA7 IRQ*/
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
  /*Configure GPIO pin : PF2 LTDC_Reset*/
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_SET);
	
	/*Configure GPIO pin : PF1 TouchScreen_Reset*/
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);
	
	/*Configure GPIO pin : PF11 LTDC_Display_En*/
	GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET);
	
		/*Configure GPIO pin : PG11 TFT_BOOSTER*/
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);
	
	/*Configure GPIO pin : PF3 Touch_Screen INT*/
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	  
	/*Configure GPIO pin : PC15 SD CARD Detection INT*/
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 2); //SDO IRQ
	HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0); //Touchscreen IRQ
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}



/* LTDC init function */
static void MX_LTDC_Init(void)
{

  LTDC_LayerCfgTypeDef pLayerCfg;

  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 5;
  hltdc.Init.VerticalSync = 30;
  hltdc.Init.AccumulatedHBP = 40;
  hltdc.Init.AccumulatedVBP = 8;
  hltdc.Init.AccumulatedActiveW = 520;
  hltdc.Init.AccumulatedActiveH = 280;
  hltdc.Init.TotalWidth = 525;
  hltdc.Init.TotalHeigh = 288;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 272;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 272;
  pLayerCfg.Backcolor.Blue = 255;
  pLayerCfg.Backcolor.Green = 255;
  pLayerCfg.Backcolor.Red = 255;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

	
}
/* DMA2D init function */
static void MX_DMA2D_Init(void)
{

  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;
  hdma2d.Init.OutputOffset = 0;
	hdma2d.LayerCfg[0].InputOffset = 0;
  hdma2d.LayerCfg[0].InputColorMode = DMA2D_INPUT_RGB565;
  hdma2d.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[0].InputAlpha =125;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 125;

  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }

}
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x307075B1;
  hi2c1.Init.OwnAddress1 = 112;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  /**Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  /**Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/* SDMMC1 init function */
static void MX_SDMMC1_SD_Init(void)
{

  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 10;
  hsd1.Init.Transceiver = SDMMC_TRANSCEIVER_DISABLE;
}


/*timer for Measure Bar*/
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 60000;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 200;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}


/* LPUART1 init function */
static void MX_LPUART1_UART_Init(void)
{

	hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 9600;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}
void _Error_Handler(char *file, int line)
{
  while(1)
  {
  }

}


void assert_failed(uint8_t* file, uint32_t line)
{ 

}
