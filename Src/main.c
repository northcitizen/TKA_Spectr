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
#include "BlueTooth.h"
#include "tmp144.h"
#include "stm32_hal_legacy.h"


//CMD DEFINITION
#define CMD_DATA_TRANSMIT 						0x01
#define CMD_RABS_DATA_TRANSMIT 					0x01
#define CMD_CNFG 								0x02
#define CMD_CAPTURE 							0x03
#define CMD_CRC_LOAD_STATUS						0x66
#define CMD_CALCULATED_DATA_TRANSMIT			0x04

#define CMD_FLASH_SET_WR_ADDR	 				0x0A
#define CMD_FLASH_WR_DATA			 			0x0B
#define CMD_FLASH_READ_DATA			 			0x0C
#define CMD_FLASH_ERASE_DATA					0x0D

//FLASH DATA ADDRESS
#define FLASH_DATA_START 							0x08100000
#define FLASH_DATA_SIZE								21514				//number of uint64_t data 
#define FLASH_CRC_ADDR 								0x0812A050	//addr for FLASH CRC check 

#define SERVICE
#define BT

extern volatile float progress_bar;

extern volatile uint8_t SD_CARD_FLAG, GRAPH_FLAG = 0;

extern uint8_t measure_number;
extern volatile uint8_t SPECTRAL_DONE, START_MEASURE_VALUE_FLAG;
 volatile uint8_t exp_stable;
 extern volatile uint32_t cnt_delay;
 volatile  uint8_t start;
 uint8_t USB_MEASURE = 0x0, TOUCH_SCREEN = 0x0;
 extern volatile uint8_t Rotation_Screen_Rend, CRICQS_done;
 extern int8_t Ra, Rall, R9, Ri[14], Q_i[15], Qf, Qa, Qp;
 uint8_t Calc_ColorRend;

//USB
uint8_t dataToSend[64]= {0}, dataToReceive[12]= {0};

uint64_t	flash_data_write, flash_data_read;
uint32_t	flash_address;
uint8_t		flash_data_read_SND[8]= {0};

uint16_t Calibration_year, Serial_part_device, Serial_number_device,
		Calibration_date, Calibration_month,
		PARGraph_B, PARGraph_G, PARGraph_R, PARGraph_IR;

uint8_t BluetoothStat = 0;

UART_HandleTypeDef huart3;
UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim15;
ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;
LTDC_HandleTypeDef hltdc;
DMA2D_HandleTypeDef hdma2d;
DMA_HandleTypeDef hdma_usart3_tx;
SD_HandleTypeDef hsd1;

static void MX_SDMMC1_SD_Init(void);
extern char SDPath[4];
extern FATFS SDFatFs;

const sImageFlash bmTKA_logo2 = {
  270, // xSize
  181, // ySize
  0x0000  // Pointer to picture data
};

extern USBD_HandleTypeDef hUsbDeviceFS;
FLASH_EraseInitTypeDef EraseInitStruct, EraseInitStruct2;
CRC_Check_StatusTypeDef CRC_STATUS;

extern volatile uint8_t old_exp_num = 0, exp_set = 1;
volatile uint8_t pause;

uint8_t RxBuf[2];
volatile extern uint8_t  GUI_screen_state, Graph_Field, Source_Type, Color_Field, Measure_Color_xy, flag_spectral, direction, Language_status, Bluetooth;
extern uint16_t Measure_Field, sdfile_cnt;

//Line recieve data
extern uint16_t Line[1024] = {0}, Line_buff[1024] = {0}, buff_set2;
extern float Line_Rabs_buff[1024] = {0}, Line_Rabs_buff_graph_test[1024] = {0};
extern float max_Rabs_graph, max_Rabs;

//Calibration factors data
extern float Spectral_Corection_Buff[1024] = {0}, WaveLenght[1024] = {0}, Scattering_Light = 0, Exposure_Factor = 0, Hazard_Blue[1024] = {0}, Hazard_Retina[1024] = {0};
extern float Factor1 = 0, Factor2 = 0, EnergyFactor_E = 0, EnergyFactor_L = 0;
float S0_lambda[1024] = {0}, S1_lambda[1024] = {0}, S2_lambda[1024] = {0};
float E_day, E_day_Wt, E_Night, SP_Measure, PPFD_PPL_Measure, PPFD_PPL_Blue_Measure, PPFD_PPL_Green_Measure, PPFD_PPL_Red_Measure, PPFD_PPL_Far_Red_Measure,
ELr_Measure, ELb_Measure, CCT_Measure, SREF;
extern uint8_t buff_set,block_graph = 0, exp_start = 1;
extern uint8_t Rotation_Screen_Spectral_Old3 = 0xFF;
extern uint16_t Line_Rabs_buff_graph2[355];

float calibratre_x_1964[1024] = {0}, calibratre_y_1964[1024] = {0}, calibratre_z_1964[1024] = {0}, calibratre_x_1931[1024] = {0}, calibratre_z_1931[1024] = {0};
uint16_t  WaveLenght_Graph[4] = {0};
//uint16_t  DarkSignal = 0;
extern uint16_t  DarkSignal[1024] = {0};

uint16_t colorimetry_XYZ1964[3] = {0}, lambda_d_Measure, lambda_c_Measure, Tc_Measure = 0, colorimetry_XYZ1931[3] = {0};
float colorimetry_xy1964[2] = {0}, colorimetry_uv[2] = {0}, colorimetry_uv1976[2] = {0}, colorimetry_xy1931[2] = {0};
int16_t colorimetry_LAB[3] = {0};
extern int16_t delta_Eab_Measure;
volatile extern uint16_t max_el = 0, cnt_delay_bar = 0;
extern uint8_t Rotation_Screen_Spectral, Rotation_Screen_Spectral_Old, Calculate_deltaEab_Done, Color_rend_Field, preGUI_screen_state;
extern volatile uint8_t highSignal, lowSignal;
uint8_t Mode_EL = 1, SD_Detect, old_sd_detect = 10, write_FileNum = 0;

//Calibration Ranges Values
extern uint16_t Range_Value_MAX = 0;
extern uint16_t Range_Value_MIN = 0;

//Calibration table factors data
float Spectral_day[1024] = {0}, Spectral_night[1024] = {0}, Spectral_B[1024] = {0}, Spectral_R[1024] = {0};
//																					7.812ms	15.625ms	31.25ms	62.5ms	125ms	250ms	500ms	1s			2s			4s
const uint16_t exposure_timer_period[10] = {93,			186,			372,		744,		1488,	2976,	5952,	11905,	23810,	47619}; //93 = 7.812ms
	
volatile uint16_t	i=0, j=0;
extern volatile uint8_t	exp_num;
volatile uint8_t VGain = 0, LaserOnOff = 0, TFT_ON_OFF = 1, temp = 0, send_usb_block = 0, MeasureFlag_display = 0;
volatile double percentage_charge = 0.0, percentage_charge_prev = 101.0; //battery charge
volatile uint16_t RGB565_480x272[130560] = {0x00000000};

uint16_t bmp[108000] = {0x0000}; //buffer for image max 270х400
extern sImage Locus;

uint8_t pause_button = 0;

/*bluetooth variable*/
char send[30];
uint8_t str1[60]={0};

uint8_t buff_i2c[3] = {0,0x0A,0x00};
volatile uint32_t cnt_touch_delay =0;


typedef struct USART_prop{
	uint8_t usart_buf[13];
	uint8_t usart_cnt;
	uint8_t is_tcp_connect;
	uint8_t is_text;
} USART_prop_ptr;

USART_prop_ptr usartprop;

uint16_t adcResult = 0;
uint16_t Touch_x = 0, Touch_y = 0;
uint16_t xt = 0, yt = 0;

float temperature_a = 0, temperature_b = 0, temperature_c = 0, temperature_d = 0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void); 

static void MX_TIM5_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM15_Init(void);
static void MX_SPI1_Init(void);      
static void MX_LTDC_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_DMA2D_Init(void);
static void MX_TIM7_Init(void);
static void MX_DMA_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USART2_UART_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void auto_exposure(void);
void exposure_display(uint16_t X, uint16_t Y);
void Rabs_graph_to_int(void);


void Test_T_coef_write(void)
{
	float a_array[10] = {0.0, 0.0, 0.0, 0.000000444444, 0.00000133333, 0.00000211111, 0.00000411111, 0.0000068889, 0.0000157778, 0.000020556};
	float b_array[10] = {0.0, 0.0, 0.0000154762, -0.00000214286, -0.0000409524, -0.000037381, -0.0000754762, -0.000086905, -0.000425238, -0.00041524 };
	float c_array[10] = {0.0000857142857, 0.000228571429, -0.000327381, 0.000135317, 0.00119286, 0.0012627, 0.00256746, 0.0036552, 0.0118675, 0.013948};
	float d_array[10] = {0.998071429, 0.996071429, 0.99825, 0.990893, 0.975179, 0.958786, 0.918964, 0.85504, 0.714179, 0.5845};

	uint64_t buf = 0;
	int32_t buf32 = 0;

	HAL_FLASH_Unlock();

	for(uint8_t i = 0; i < 10; i++)
	{
		buf32 = (int32_t)(b_array[i] * 100000000);
		buf |= buf32 & 0x00000000FFFFFFFF;
		buf = buf << 32;
		buf32 = (int32_t)(a_array[i] * 100000000);
		buf |= buf32 & 0x00000000FFFFFFFF;
		HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, address_temp_array[i], buf);
		buf = 0;

		buf32 = (int32_t)(d_array[i] * 100000000);
		buf |= buf32 & 0x00000000FFFFFFFF;
		buf = buf << 32;
		buf32 = (int32_t)(c_array[i] * 100000000);
		buf |= buf32 & 0x00000000FFFFFFFF;
		HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, address_temp_array[i] + 8, buf);
		buf = 0;

	}

	HAL_FLASH_Lock();
}


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
 
//__inline
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
	//1964
	Calculate_XYZ1964(Line_Rabs_buff, calibratre_x_1964, calibratre_y_1964, calibratre_z_1964);
	Calculate_xy1964(colorimetry_XYZ1964);
	//1931
	Calculate_XYZ1931(Line_Rabs_buff, calibratre_x_1931, Spectral_day, calibratre_z_1931);
	Calculate_xy1931(colorimetry_XYZ1931);
	
	Tc_Measure = Calculate_Tc(Line_Rabs_buff, Measure_Color_xy);
	
	if(GUI_screen_state == Color_Screen)
	{
		if(Color_Field&Color_CIE_Luv) {Calculate_uv1976((Measure_Color_xy == 0x00) ? colorimetry_xy1964 : colorimetry_xy1931);Calculate_uv((Measure_Color_xy == 0x00) ? colorimetry_xy1964 : colorimetry_xy1931);} else 
		if(Color_Field&Color_CIE_Lab){Calculate_Lab((Measure_Color_xy == 0x00) ? colorimetry_XYZ1964 : colorimetry_XYZ1931, Measure_Color_xy, Source_Type);}
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
			if(Measure_Field&CIE_Luv){Calculate_uv1976((Measure_Color_xy == 0x00) ? colorimetry_xy1964 : colorimetry_xy1931);Calculate_uv((Measure_Color_xy == 0x00) ? colorimetry_xy1964 : colorimetry_xy1931);}
			if(Measure_Field&CIE_Lab){Calculate_Lab((Measure_Color_xy == 0x00) ? colorimetry_XYZ1964 : colorimetry_XYZ1931, Measure_Color_xy, Source_Type);}
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
	if (adcResult >= 3455) adcResult = 3455;
	if (adcResult <= 2750) adcResult = 2750;
	return percentage_charge = (double)(adcResult - 2750)*100.0 / 705;
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
				
				if(cnt == 1023)
				{
					dataToSend[q] = (temperature_measure >> 8) & 0x00FF;
					dataToSend[q+1] = temperature_measure & 0x00FF;
				}

				if(q >= 62 || cnt == 1023){
					dataToSend[3] = (packet_number>> 8) & 0x00FF;
					dataToSend[4] = packet_number & 0x00FF;
					dataToSend[63] = (CRC_pack+dataToSend[0]+dataToSend[1]+dataToSend[2] + packet_number);
					


					CRC_pack = 0;
					q = 5;
					packet_number = packet_number + 1;
					
					USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
					HAL_Delay(3);
				}
			}
			memset(dataToReceive, 0, sizeof(dataToReceive));
}

void packet_generator_Rabs_data_send(void) //send Rabs data
{
			uint8_t q = 0;
			uint16_t CRC_pack = 0, packet_number = 0;
			uint32_t buff_float;
			uint8_t usb_status = 99;
	
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
					
					while(usb_status!=USBD_OK)
					{
						usb_status = USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
					}
					usb_status = 99;;
				}
			}
			memset(dataToReceive, 0, sizeof(dataToReceive));
}

void packet_generator_Calculated_data_send(void)
{
			uint8_t q = 0;
			uint16_t CRC_pack = 0, packet_number = 0;
			uint32_t buff_float;
			uint8_t usb_status = 99;
	
//			packet_number = 0;
	
			memset(dataToSend, 0, sizeof(dataToSend));
			delta_Eab_Measure = Calculate_deltaEab();

			dataToSend[0] = 0xAB;
			dataToSend[1] = 0x12;
			dataToSend[2] = 0x04;
	
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
					
//					usb_status = hhid->state;
//					USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
//					HAL_Delay(3);

					usb_status = 99;
					while(usb_status!=USBD_OK)
					{
						usb_status = USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
					}
					HAL_Delay(3);

				}

			}
			
			memset(dataToSend, 0, sizeof(dataToSend));
			
			dataToSend[0] = 0xAB;
			dataToSend[1] = 0x12;
			dataToSend[2] = 0x04;
	
			dataToSend[5] = (Mode_EL == 0)? 0 : 1;
			dataToSend[6] = 0;
			//send xy1964 color
				memcpy(&buff_float, &colorimetry_xy1964[0], sizeof(float));
				dataToSend[q] = (buff_float >> 24) & 0x000000FF;
				dataToSend[q+1] = (buff_float >> 16) & 0x000000FF;
				dataToSend[q+2] = (buff_float >> 8) & 0x000000FF;
				dataToSend[q+3] = (buff_float) & 0x000000FF;
				
				memcpy(&buff_float, &colorimetry_xy1964[1], sizeof(float));
				dataToSend[q+4] = (buff_float >> 24) & 0x000000FF;
				dataToSend[q+5] = (buff_float >> 16) & 0x000000FF;
				dataToSend[q+6] = (buff_float >> 8) & 0x000000FF;
				dataToSend[q+7] = (buff_float) & 0x000000FF;

				//send CCT
				memcpy(&buff_float, &Tc_Measure, sizeof(uint16_t));
				dataToSend[q+8]= (buff_float >> 8) & 0x000000FF;
				dataToSend[q+9] = (buff_float) & 0x000000FF;
				
				//send SourceType
				dataToSend[q+10]= Source_Type;
				
				//send delta_Eab 
			if(Calculate_deltaEab_Done == 0x01)
			{
				memcpy(&buff_float, &delta_Eab_Measure, sizeof(int16_t));
				dataToSend[q+11] = (buff_float >> 8) & 0x000000FF;
				dataToSend[q+12] = (buff_float) & 0x000000FF;
			} else {dataToSend[q+11] = 0;
				dataToSend[q+12] = 0;
			}
				
			//send xy1931 color
				memcpy(&buff_float, &colorimetry_xy1931[0], sizeof(float));
				dataToSend[q+13] = (buff_float >> 24) & 0x000000FF;
				dataToSend[q+14] = (buff_float >> 16) & 0x000000FF;
				dataToSend[q+15]= (buff_float >> 8) & 0x000000FF;
				dataToSend[q+16] = (buff_float) & 0x000000FF;
				
				memcpy(&buff_float, &colorimetry_xy1931[1], sizeof(float));
				dataToSend[q+17] = (buff_float >> 24) & 0x000000FF;
				dataToSend[q+18] = (buff_float >> 16) & 0x000000FF;
				dataToSend[q+19] = (buff_float >> 8) & 0x000000FF;
				dataToSend[q+20] = (buff_float) & 0x000000FF;
			
					dataToSend[3] = (packet_number>> 8) & 0x00FF;
					dataToSend[4] = packet_number & 0x00FF;
					dataToSend[63] = (CRC_pack+dataToSend[0]+dataToSend[1]+dataToSend[2] + dataToSend[q]+dataToSend[q+1]+dataToSend[q+2] + dataToSend[q+3] + dataToSend[q+4]+
					dataToSend[q+5] + dataToSend[q+6] + dataToSend[q+7] + dataToSend[q+8] + dataToSend[q+9] + dataToSend[q+10] + dataToSend[q+11]+ packet_number);
					
					CRC_pack = 0;
					q = 7;
					packet_number = packet_number + 1;
					
					USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
					HAL_Delay(3);
			
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
						Temperature_Measure_Func();
						packet_generator_Rabs_data_send();
					}else{
						Temperature_Measure_Func();
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
								HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);//booster
								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET); //LTDC_En on
							}else
							{
								HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);	//TFT_booster SHDN off
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
						EraseInitStruct.NbPages = 49;
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
						//HAL_Delay(3);
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
						//HAL_Delay(3);
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
						dataToSend[6] = flash_data_read_SND[0];
					
						USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
						memset(dataToReceive, 0, sizeof(dataToReceive));
						//HAL_Delay(3);
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
						//HAL_Delay(3);
					break;	
						
				case CMD_CALCULATED_DATA_TRANSMIT : 

					if(USB_MEASURE)
					{
						GUI_Button_Measure_Start_Pause(109, 426);
										//GUI_Display_Refresh();
										GRAPH_FLAG = 1;
										start = 1;
										pause = 0;

										measure_number = 1;
										exp_stable = 0;

										GUI_Bar_Measure(85, 13, 0.1);

										while (start) {
											Factor1 = Rabs_calc_Factor1(DarkSignal, Scattering_Light,
													Line_buff);
											Rabs_calc_main(Line_buff, DarkSignal, Factor1, Factor2, Spectral_Corection_Buff, Line_Rabs_buff);

											if (!block_graph) {
												memcpy(Line_Rabs_buff_graph_test, Line_Rabs_buff, sizeof(Line_Rabs_buff));
											}
											cnt_delay++;
											Temperature_Measure_Func();
											Calculate_Data();
											GUI_SignalLevel();
											if ((cnt_delay > 20 && exp_num < 6)
													|| (cnt_delay > 50 && (exp_num >= 6 && exp_num < 8))
													|| (cnt_delay > 400 && exp_num >= 8)) {
												auto_exposure();
												max_el = 0;
												cnt_delay = 0;
												exp_stable = exp_stable + 1;
												progress_bar = exp_stable;
												exp_start = 1;
												if (exp_stable <= 10)
													GUI_Bar_Measure(85, 13, progress_bar * 0.1);
												if (exp_stable > 10) {
													start = 0;
												}
											}
											delta_Eab_Measure = Calculate_deltaEab(); //12.07.2021
											Calculate_Lambda_Dominant(colorimetry_xy1964, 0);
										}

										if (!exp_set) {
											Factor1 = Rabs_calc_Factor1(DarkSignal, Scattering_Light,
													Line_buff);
											Rabs_calc_main(Line_buff, DarkSignal, Factor1, Factor2,
													Spectral_Corection_Buff, Line_Rabs_buff);
										}

										if (!block_graph) {
											memcpy(Line_Rabs_buff_graph_test, Line_Rabs_buff, sizeof(Line_Rabs_buff));
										}

										exp_start = 0;

										if ((GUI_screen_state == Color_Screen) && !pause) {
											cnt_delay++;

											if ((cnt_delay > 40 && exp_num < 3)
													|| (cnt_delay > 70 && (exp_num >= 3 && exp_num < 4))
													|| (cnt_delay > 500 && exp_num >= 4)) //68
													{
												auto_exposure();
												max_el = 0;
												cnt_delay = 0;
											}
										} else {
											cnt_delay++;

											if ((cnt_delay > 250 && exp_num < 3)
													|| (cnt_delay > 950
															&& (exp_num >= +3 && exp_num < 4))
													|| (cnt_delay > 1450 && exp_num >= 4)) {
												auto_exposure();
												max_el = 0;
												cnt_delay = 0;
											}
										}

										if (GUI_screen_state == Graph_Screen)/*GRAPH SCREEN*/
										{

											block_graph = 1;

											if (preGUI_screen_state == Graph_Screen
													&& Rotation_Screen_Spectral_Old3
															== Rotation_Screen_Spectral) {
												Refresh_screen_Graph(20, 20, Line_Rabs_buff_graph2,
														Rotation_Screen_Spectral_Old3);
											}
											Rotation_Screen_Spectral_Old3 = Rotation_Screen_Spectral;
											max_Rabs_graph = Rabs_find_MAX(Line_Rabs_buff_graph_test,
													Rotation_Screen_Spectral_Old3);
											Rabs_graph_to_display(Rotation_Screen_Spectral_Old3,
													Line_Rabs_buff_graph_test);

											Spectral_DrawGraph_Line2(20, 20, Line_Rabs_buff_graph2,
													TFT_White, Rotation_Screen_Spectral_Old3);
											block_graph = 0;
											GUI_SignalLevel();

										} else {
											__asm("nop");
										}

										if (GUI_screen_state == Graph_Screen)/*GRAPH SCREEN*/
										{

											block_graph = 1;

											if (preGUI_screen_state == Graph_Screen
													&& Rotation_Screen_Spectral_Old3
															== Rotation_Screen_Spectral) {
												//GUI_Display_Refresh();
												if (GUI_screen_state != Color_Screen
														&& GUI_screen_state == Graph_Screen)
													Refresh_screen_Graph(20, 20, Line_Rabs_buff_graph2,
															Rotation_Screen_Spectral_Old3);
											}
											Rotation_Screen_Spectral_Old3 = Rotation_Screen_Spectral;
											max_Rabs_graph = Rabs_find_MAX(Line_Rabs_buff_graph_test,
													Rotation_Screen_Spectral_Old3);
											if (GUI_screen_state == Graph_Screen)
												Rabs_graph_to_display(Rotation_Screen_Spectral_Old3,
														Line_Rabs_buff_graph_test);
											if (GUI_screen_state == Graph_Screen)
												Spectral_DrawGraph_Line2(20, 20, Line_Rabs_buff_graph2,
														TFT_White, Rotation_Screen_Spectral_Old3);
											block_graph = 0;
											GUI_SignalLevel();

										} else {
											__asm("nop");
										}

						//				//CRICQS_done = 0x00;
						//				max_Rabs = Rabs_find_MAX_all(Line_Rabs_buff);
						//				Calculate_XYZ1931(Line_Rabs_buff, calibratre_x_1931,
						//						Spectral_day, calibratre_z_1931);
						//				Calculate_xy1931(colorimetry_XYZ1931);
						//				Calculate_uv(colorimetry_xy1931);
						//				Tc_Measure = Calculate_Tc(Line_Rabs_buff, Measure_Color_xy);
						//				if (Tc_Measure == 0xFFFF) {
						//					Ra = 0;
						//					Rall = 0;
						//					R9 = 0;
						//					memset(Ri, 0, sizeof(Ri));
						//				} else {
						//					CRI_func(Tc_Measure, Line_Rabs_buff);
						//				}
						//				//CRICQS_done = 0x01;
						//
						//				//CRICQS_done = 0x00;
						//				Calculate_XYZ1931(Line_Rabs_buff, calibratre_x_1931,
						//						Spectral_day, calibratre_z_1931);
						//				Calculate_xy1931(colorimetry_XYZ1931);
						//				Tc_Measure = Calculate_Tc(Line_Rabs_buff, Measure_Color_xy);
						//				max_Rabs = Rabs_find_MAX_all(Line_Rabs_buff);
						//				if (Tc_Measure == 0xFFFF) {
						//					Qa = 0;
						//					Qp = 0;
						//					Qf = 0;
						//					memset(Q_i, 0, sizeof(Q_i));
						//				} else {
						//					cqs_func(Tc_Measure, Line_Rabs_buff);
						//				}
																								        						        									//CRICQS_done = 0x01;


									  	pause = 1;
										SPECTRAL_DONE = 1;
										GUI_Bar_Measure_OFF(85, 13);
										GUI_Button_Measure_Start_Pause_For_Button(109, 426, 0);
						//				GUI_Display_Refresh();
					}
				send_usb_block = 1;
						packet_generator_Calculated_data_send();

						memset(dataToReceive, 0, sizeof(dataToReceive));
				send_usb_block = 0;
				USB_MEASURE = 1;
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

uint8_t txDoneFlag = 0;
/*BLUETOOTH UART processing*/
uint8_t send_bluetooth = 0;
uint8_t	data_bluetooth_send[4122] = {0};
void string_parse(uint8_t* buf_str)
{			
	
	uint32_t buff_float;

	
	if(buf_str[0] == 0xAB)
	{
		if(buf_str[1] == 0x12)
		{
			if(buf_str[2] == 0x02)
			{

//					/*Laser On/Off*/
//							LaserOnOff = (buf_str[4] > 0) ? 1 : 0;
//						if(LaserOnOff == 0){
//					 			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//							}else
//							{
//								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//							}
//							sprintf(send, "TKA battery level: %.1f%%", Get_Battery_Level());
//							HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&send, 30);
							
							//send absolute spectral
							data_bluetooth_send[0] = 0xAB;
							data_bluetooth_send[1] = 0x12;
							data_bluetooth_send[2] = 0x04;
							data_bluetooth_send[3] = (Mode_EL == 0)? 0 : 1;
							data_bluetooth_send[4] = 0;
								
							uint16_t qz = 5;
							for(uint16_t i = 0; i < 1024; i++){
								memcpy(&buff_float, &Line_Rabs_buff[1023-i], sizeof(float));
								data_bluetooth_send[qz+0] =  (buff_float >> 24) & 0x000000FF;
								data_bluetooth_send[qz+1] =  (buff_float >> 16) & 0x000000FF;
								data_bluetooth_send[qz+2] =  (buff_float >> 8) & 0x000000FF;
								data_bluetooth_send[qz+3] = (buff_float) & 0x000000FF;
								qz = qz + 4;
						}					
							
						memcpy(&buff_float, &colorimetry_xy1964[0], sizeof(float));
						data_bluetooth_send[qz] =  (buff_float >> 24) & 0x000000FF;
						data_bluetooth_send[qz+1] = (buff_float >> 16) & 0x000000FF;
						data_bluetooth_send[qz+2] = (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+3] = (buff_float) & 0x000000FF;
				
						memcpy(&buff_float, &colorimetry_xy1964[1], sizeof(float));
						data_bluetooth_send[qz+4] = (buff_float >> 24) & 0x000000FF;
						data_bluetooth_send[qz+5] = (buff_float >> 16) & 0x000000FF;
						data_bluetooth_send[qz+6] = (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+7] = (buff_float) & 0x000000FF;

						//send CCT
						memcpy(&buff_float, &Tc_Measure, sizeof(uint16_t));
						data_bluetooth_send[qz+8]= (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+9] = (buff_float) & 0x000000FF;
						
						//send SourceType
						data_bluetooth_send[qz+10]= Source_Type;
						
						if(Calculate_deltaEab_Done == 0x01)
						{
							memcpy(&buff_float, &delta_Eab_Measure, sizeof(int16_t));
							data_bluetooth_send[qz+11] = (buff_float >> 8) & 0x000000FF;
							data_bluetooth_send[qz+12] = (buff_float) & 0x000000FF;
						} else {data_bluetooth_send[qz+11] = 0x00;
							data_bluetooth_send[qz+12] = 0x00;
						}
						
						//send xy1931 color
						memcpy(&buff_float, &colorimetry_xy1931[0], sizeof(float));
						data_bluetooth_send[qz+13] = (buff_float >> 24) & 0x000000FF;
						data_bluetooth_send[qz+14] = (buff_float >> 16) & 0x000000FF;
						data_bluetooth_send[qz+15]= (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+16] = (buff_float) & 0x000000FF;
						
						memcpy(&buff_float, &colorimetry_xy1931[1], sizeof(float));
						data_bluetooth_send[qz+17] = (buff_float >> 24) & 0x000000FF;
						data_bluetooth_send[qz+18] = (buff_float >> 16) & 0x000000FF;
						data_bluetooth_send[qz+19] = (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+20] = (buff_float) & 0x000000FF;
						
						send_bluetooth = 1;		
			}
		}
	}else
	{
		__asm("nop");
	}
}

void string_parse_no_check(void)
{

	uint32_t buff_float;


//	if(buf_str[0] == 0xAB)
//	{
//		if(buf_str[1] == 0x12)
//		{
//			if(buf_str[2] == 0x02)
//			{

//					/*Laser On/Off*/
//							LaserOnOff = (buf_str[4] > 0) ? 1 : 0;
//						if(LaserOnOff == 0){
//					 			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//							}else
//							{
//								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//							}
//							sprintf(send, "TKA battery level: %.1f%%", Get_Battery_Level());
//							HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&send, 30);

							//send absolute spectral
							data_bluetooth_send[0] = 0xAB;
							data_bluetooth_send[1] = 0x12;
							data_bluetooth_send[2] = 0x04;
							data_bluetooth_send[3] = (Mode_EL == 0)? 0 : 1;
							data_bluetooth_send[4] = 0;

					 uint16_t qz = 5;
							for(uint16_t i = 0; i < 1024; i++){
								memcpy(&buff_float, &Line_Rabs_buff[1023-i], sizeof(float));
								data_bluetooth_send[qz+0] =  (buff_float >> 24) & 0x000000FF;
								data_bluetooth_send[qz+1] =  (buff_float >> 16) & 0x000000FF;
								data_bluetooth_send[qz+2] =  (buff_float >> 8) & 0x000000FF;
								data_bluetooth_send[qz+3] = (buff_float) & 0x000000FF;
								qz = qz + 4;
						}

						memcpy(&buff_float, &colorimetry_xy1964[0], sizeof(float));
						data_bluetooth_send[qz] =  (buff_float >> 24) & 0x000000FF;
						data_bluetooth_send[qz+1] = (buff_float >> 16) & 0x000000FF;
						data_bluetooth_send[qz+2] = (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+3] = (buff_float) & 0x000000FF;

						memcpy(&buff_float, &colorimetry_xy1964[1], sizeof(float));
						data_bluetooth_send[qz+4] = (buff_float >> 24) & 0x000000FF;
						data_bluetooth_send[qz+5] = (buff_float >> 16) & 0x000000FF;
						data_bluetooth_send[qz+6] = (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+7] = (buff_float) & 0x000000FF;

						//send CCT
						memcpy(&buff_float, &Tc_Measure, sizeof(uint16_t));
						data_bluetooth_send[qz+8]= (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+9] = (buff_float) & 0x000000FF;

						//send SourceType
						data_bluetooth_send[qz+10]= Source_Type;

						if(Calculate_deltaEab_Done == 0x01)
						{
							memcpy(&buff_float, &delta_Eab_Measure, sizeof(int16_t));
							data_bluetooth_send[qz+11] = (buff_float >> 8) & 0x000000FF;
							data_bluetooth_send[qz+12] = (buff_float) & 0x000000FF;
						} else {data_bluetooth_send[qz+11] = 0x00;
							data_bluetooth_send[qz+12] = 0x00;
						}

						//send xy1931 color
						memcpy(&buff_float, &colorimetry_xy1931[0], sizeof(float));
						data_bluetooth_send[qz+13] = (buff_float >> 24) & 0x000000FF;
						data_bluetooth_send[qz+14] = (buff_float >> 16) & 0x000000FF;
						data_bluetooth_send[qz+15]= (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+16] = (buff_float) & 0x000000FF;

						memcpy(&buff_float, &colorimetry_xy1931[1], sizeof(float));
						data_bluetooth_send[qz+17] = (buff_float >> 24) & 0x000000FF;
						data_bluetooth_send[qz+18] = (buff_float >> 16) & 0x000000FF;
						data_bluetooth_send[qz+19] = (buff_float >> 8) & 0x000000FF;
						data_bluetooth_send[qz+20] = (buff_float) & 0x000000FF;

						send_bluetooth = 1;
//			}
//		}
//	}else
//	{
//		__asm("nop");
//	}
}

void UART2_RxCpltCallback(void)
{
	uint8_t b;
	  b = str1[0];
	 if (usartprop.usart_cnt>12)
	  {
	    usartprop.usart_cnt = 0;
	    HAL_UART_Receive_IT(&huart3,(uint8_t*)str1,1);
	    return;
	  }
	  usartprop.usart_buf[usartprop.usart_cnt] = b;
	  if(b==0x0A)
	  {
	    usartprop.usart_buf[usartprop.usart_cnt+1]=0;
	    string_parse((uint8_t*)usartprop.usart_buf);
	    usartprop.usart_cnt=0;
	    HAL_UART_Receive_IT(&huart3,(uint8_t*)str1,1);

	    return;
	  }
	  usartprop.usart_cnt++;
	  HAL_UART_Receive_IT(&huart3,(uint8_t*)str1,1);


}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	  if(huart==&huart1)
//		  {
//		  	  USART1_IRQHandler();
//		  }
}

void Test_GUI(void)
{
//	exp_start = 0;
//	exp_set = 0;
//	E_day = 1337;
//	E_day_Wt = 1337;
//	PPFD_PPL_Measure = 1488;


	char buf[16]={0};
	uint16_t xc = 10, yc = 10;
//	uint16_t xt = 0, yt = 0;


	TFT_FillScreen_DMA(TFT_Black_Bkgr);
	TFT_FillRectangle(0, 400, 271, 479, TFT_Red);
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16);

	while(1)
	{
		xc = 10, yc = 10;


//		TFT_FillRectangle(0, 100, 100, 100, TFT_Red);

		for (uint8_t i=0; i<12; i++)
		{
			sprintf(buf, "  %x", dataToReceive[i]);
			TFT_DisplayString(xc, yc, (uint8_t *)buf, LEFT_MODE);
			xc+=16*5;
			if (xc>= (272 - 16*5))
			{
				xc = 10;
				yc += 32;
			}

		}

		if (xt >= 0*TS_Callib && yt >= 400)
		{
			memset(dataToReceive, 0, 12);
			xt = 0;
			yt = 0;
			TFT_FillScreen_DMA(TFT_Black_Bkgr);
			TFT_FillRectangle(0, 400, 271, 479, TFT_Red);
		}

//		HAL_Delay(500);

	//	sprintf(buf, "%f", hz);
//		TFT_DisplayString(100, 150, (uint8_t *)buf, LEFT_MODE);

	}
}
uint32_t start_time = 1000000;
int main(void)
{
	while(start_time > 0)
		start_time--;
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
		MX_SPI1_Init();
		HAL_Delay(1);
		MX_TIM15_Init();
		HAL_Delay(1);
		MX_TIM5_Init();
		HAL_Delay(1);
		MX_USB_DEVICE_Init();
		HAL_Delay(1);
		MX_DMA2D_Init();
		HAL_Delay(1);
		MX_I2C1_Init();
		HAL_Delay(1);
	#ifdef BT
		MX_USART3_UART_Init();
		HAL_Delay(1);
	#endif
	  	MX_USART2_UART_Init();
	  	HAL_NVIC_SetPriority(USART2_IRQn, 1, 3);
	    HAL_NVIC_EnableIRQ(USART2_IRQn);
	    __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);


		HAL_Delay(1);
	 	MX_LTDC_Init();
		HAL_Delay(1);
		MX_ADC1_Init();
		MX_DMA_Init();
		HAL_Delay(1);
		HAL_TIM_OC_Start(&htim5, TIM_CHANNEL_1);
		HAL_Delay(1);
		HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);  //ST Signal0,1
		HAL_Delay(1);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
		HAL_Delay(1);
		HAL_TIM_Base_Start_IT(&htim2);
		HAL_Delay(1);
		HAL_NVIC_SetPriority(LTDC_IRQn, 1, 3);  //
		HAL_Delay(2);
		HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);	//booster
		TIM15->CCR2 = 50;
		HAL_Delay(1);
		HAL_UART_Receive_IT(&huart3,(uint8_t*)str1,1);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_SET);
		MX_TIM6_Init();
		HAL_Delay(1);
		HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
		HAL_Delay(1);
		HAL_TIM_Base_Start_IT(&htim6);
		HAL_NVIC_SetPriority(TIM6_IRQn, 1, 4);
		HAL_Delay(1);
		HAL_LTDC_SetAddress(&hltdc,(uint32_t) &RGB565_480x272,0);
		HAL_Delay(1);
		Touch_Ini();

		MX_SDMMC1_SD_Init();
		MX_FATFS_Init();

		GPIO_QSPI_Init();
		Single_Mode();
		HAL_Delay(20);

		BlueTooth_GPIO_Init();


//Load screen data
	buff_set = Calibration_Load_1byte(SET_MODEEL, 3);
	if(buff_set == 0xFF){Mode_EL = 0;} else{Mode_EL = buff_set;}

	buff_set = Calibration_Load_1byte(SET_GRAPHFIELD, 3);
	if(buff_set == 0xFF){Graph_Field = 0;} else{Graph_Field = buff_set;}

	buff_set = Calibration_Load_1byte(SET_COLORFIELD, 3);
	if(buff_set == 0xFF){Color_Field |= Color_CIE_xy;} else{Color_Field = buff_set;}

	//buff_set = Calibration_Load_1byte(SET_COLORRENDFIELD, 3);
	//if(buff_set == 0xFF){Color_rend_Field = 0;} else{Color_rend_Field = buff_set;}

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


//Load calibration data
	Calibration_WaveLenght_Graph();
	Calibration_Ranges_Values();
	Calibration_Exposure_Change(exp_num);
	Calibration_Load_Pack(Mode_EL == 0x00 ? SPECTRAL_CORRECTION_L:SPECTRAL_CORRECTION_E, 0x400, Spectral_Corection_Buff);

	EnergyFactor_E = Calibration_Load_float(ENERGY_FACTOR_E);
	EnergyFactor_L = Calibration_Load_float(ENERGY_FACTOR_L);

	Calibration_Load_Pack(SPECTRAL_DAY, 0x400, Spectral_day);
	Calibration_Load_Pack(SPECTRAL_NIGHT, 0x400, Spectral_night);

	Calibration_Load_Pack(X10_CIE1964, 0x400, calibratre_x_1964);
	Calibration_Load_Pack(Y10_CIE1964, 0x400, calibratre_y_1964);
	Calibration_Load_Pack(Z10_CIE1964, 0x400, calibratre_z_1964);

	Calibration_Load_Pack(X2_CIE1931, 0x400, calibratre_x_1931);
	Calibration_Load_Pack(Z2_CIE1931, 0x400, calibratre_z_1931);


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

	WaveLenght_Graph[0] = (uint16_t)WaveLenght[5];//0-? 1-379 2-379 3-379 5 -380
	WaveLenght_Graph[1] = (uint16_t)WaveLenght[325];//500
	WaveLenght_Graph[2] = (uint16_t)WaveLenght[642];//620
	WaveLenght_Graph[3] = (uint16_t)WaveLenght[963];//740

	if(Mode_EL == 0){
		Factor2 = Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_L);
	}else
	{
		Factor2 = Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_E);
	}

	GUI_screen_state = Calibration_Load_1byte(SCREENADDR, 3);

	Image_load(TKA_LOGO_BMP, TKA_LOGO_BMP_SIZEX*TKA_LOGO_BMP_SIZEY);

#ifdef BT
	BlueTooth_Module_Init();
#endif

	GUI_Title_Screen();
	uint8_t p = 0;
	HAL_Delay(2000);
	usb_receive_processing();


#ifdef BT
		if(Bluetooth == 0)
		{
			BlueTooth_Off();
			HAL_Delay(200);
		}
		else
		{
			BlueTooth_On();
			HAL_Delay(200);
		}
#endif

	//Load Locus Image
		Image_load(Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP : XY10_LOCUS_BMP):
		Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP : LAB_LOCUS_BMP,
		Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEX*XY2_LOCUS_BMP_SIZEY : XY10_LOCUS_BMP_SIZEX*XY10_LOCUS_BMP_SIZEY):
		Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEX*LUV_LOCUS_BMP_SIZEY : LAB_LOCUS_SIZEX*LAB_LOCUS_SIZEY);

		Locus.pData = (uint16_t *)bmp;
		Locus.Width = Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEX : XY10_LOCUS_BMP_SIZEX):
		Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEX : LAB_LOCUS_SIZEX;
		Locus.Height = Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEY : XY10_LOCUS_BMP_SIZEY):
		Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEY : LAB_LOCUS_SIZEY;

	// Switch screen (dependency Flash load)
		switch(GUI_screen_state){
		case Measure_Screen: GUI_Measure_Screen();  break;
		case Measure2_Screen: preGUI_screen_state = Measure_Screen; GUI_Measure2_Screen();  break;
		case Measure3_Screen: preGUI_screen_state = Measure2_Screen; GUI_Measure_Screen(); GUI_Measure2_Screen();GUI_Measure3_Screen();  break;

		case Graph_Screen: preGUI_screen_state = Measure_Screen; GUI_Graph_Screen(); break;
		case Color_Screen: preGUI_screen_state = ColorSet1_Screen; GUI_Color_Screen();  break;
		case Color_Rendition_Screen: preGUI_screen_state = Measure_Screen; GUI_ColorRend_Screen();	break;
		default: GUI_screen_state =  Measure_Screen; GUI_Measure_Screen();  break;
		}


// Timer init
	MX_TIM7_Init();
	HAL_Delay(1);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);

#ifdef BT
	HAL_NVIC_EnableIRQ(USART3_IRQn);
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
#endif

	HAL_Delay(1);
	HAL_TIM_Base_Start(&htim7);
	HAL_Delay(1);
	HAL_TIM_Base_Start_IT(&htim7);

pause = 1;
GUI_Button_Measure_Start_Pause_For_Button(109, 426, 0);

	block_graph = 1;

	if (preGUI_screen_state == Graph_Screen
			&& Rotation_Screen_Spectral_Old3 == Rotation_Screen_Spectral) {
		Refresh_screen_Graph(20, 20, Line_Rabs_buff_graph2,
				Rotation_Screen_Spectral_Old3);
	}
Rotation_Screen_Spectral_Old3 = Rotation_Screen_Spectral;
max_Rabs_graph = Rabs_find_MAX(Line_Rabs_buff_graph_test, Rotation_Screen_Spectral_Old3);
Rabs_graph_to_display(Rotation_Screen_Spectral_Old3, Line_Rabs_buff_graph_test);
	block_graph = 0;
uint32_t bat_refresh = 0;

START_MEASURE_VALUE_FLAG = 0;
TOUCH_SCREEN = 0x1;
while (1) {

		usb_receive_processing();

#ifndef SERVICE

		if(SD_CARD_FLAG)
		{
			GUI_Display_Refresh();
			if(GUI_screen_state == Graph_Screen)
			{
				block_graph = 1;
				if (preGUI_screen_state == Graph_Screen && Rotation_Screen_Spectral_Old3 == Rotation_Screen_Spectral)
				{
					if (GUI_screen_state != Color_Screen && GUI_screen_state == Graph_Screen)
							Refresh_screen_Graph(20, 20, Line_Rabs_buff_graph2, Rotation_Screen_Spectral_Old3);
				}
					Rotation_Screen_Spectral_Old3 = Rotation_Screen_Spectral;
					max_Rabs_graph = Rabs_find_MAX(Line_Rabs_buff_graph_test, Rotation_Screen_Spectral_Old3);
					if (GUI_screen_state == Graph_Screen)
					Rabs_graph_to_display(Rotation_Screen_Spectral_Old3, Line_Rabs_buff_graph_test);
					if (GUI_screen_state == Graph_Screen)
						Spectral_DrawGraph_Line2(20, 20, Line_Rabs_buff_graph2, TFT_White, Rotation_Screen_Spectral_Old3);
						block_graph = 0;
						GUI_SignalLevel();
				} else {
				__asm("nop");
				}
			SD_CARD_FLAG = 0;
		}

		if (send_bluetooth) {
			HAL_UART_Transmit_DMA(&huart3, (uint8_t*) &data_bluetooth_send, 4122);
			send_bluetooth = 0;
			HAL_Delay(360);
			HAL_UART_DMAStop(&huart3);
			HAL_DMA_Abort(huart3.hdmatx);
		};

		if (pause && !Mode_EL) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		}

		bat_refresh++;
		if (bat_refresh == 10000000) {
			if (percentage_charge < percentage_charge_prev) {
				GUI_Battery_Level(0, 0, percentage_charge);
				percentage_charge_prev = percentage_charge;
			}
			if (percentage_charge > percentage_charge_prev) {
							GUI_Battery_Level(0, 0, percentage_charge);
							percentage_charge_prev = percentage_charge;
						}
			bat_refresh = 0;
		}
		__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);

#endif

	}

}


void auto_exposure(void)
{ 
	uint16_t i_max = 0;

	for (uint16_t i = 5; i<1024; i++){

		if(Line_buff[i] > max_el)
		{
			max_el = Line_buff[i];
			i_max = i;
		}
	}
	
	if(max_el < Range_Value_MIN && exp_num != 9)//20000
	{
		highSignal = 0;
		lowSignal = 0;
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

		send_usb_block = 0;
	} else if(max_el > Range_Value_MAX && exp_num != 0)//45000
	{
		highSignal = 0;
		lowSignal = 0;
		send_usb_block = 1;
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
		
		send_usb_block =0;
	}	

	if(old_exp_num!=exp_num )
	{
		exp_set = 1;
	}else{
		exp_set = 0;
	}
		
	old_exp_num = exp_num;
	
	if(exp_num == 0 && max_el >= Range_Value_MAX)//50000
	{
		highSignal = 1;
		 //GUI_SignalLevel();
		 pause = 1;
		 start = 0;
//		 exp_num = 0;
//		 max_el=0;
//		 htim2.Init.Period = exposure_timer_period[exp_num];

	} else if((exp_num ==0 && max_el < Range_Value_MAX))//50000
	{
		highSignal = 0;
	} else if((exp_num == 9 && max_el < DarkSignal[i_max]+Range_Value_MIN))//20000
	{
		lowSignal = 1;
		 //GUI_SignalLevel();
		 pause = 1;
		 start = 0;
//		 exp_num = 0;
//		 max_el=0;
//
//		 htim2.Init.Period = exposure_timer_period[exp_num];

	}else if((exp_num == 9 && max_el > DarkSignal[i_max]+ Range_Value_MIN))//20000
	{
		lowSignal = 0;
	}
}
																		

/*ST signal generator*/
void TIM2_IRQHandler(void)
{

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	DWT_Delay(10);
	i = 0;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

	
	HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
	HAL_TIM_IRQHandler(&htim2);
}

void TIM6_DAC_IRQHandler(void)
{
	pause_button = 0;
	percentage_charge = Get_Battery_Level();
	
	HAL_NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
  HAL_TIM_IRQHandler(&htim6);

}


void TIM7_IRQHandler(void)
{
	if(!usart2_wait) usart2_wait = true;//1.07
			
	SD_Detect = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15);
	if(old_sd_detect != SD_Detect & CRC_STATUS == CRC_OK){
		GUI_Button_SD_Card(55, 426, !SD_Detect);
		old_sd_detect = SD_Detect;
		if(SD_Detect == 0){
				MX_SDMMC1_SD_Init();
				MX_FATFS_Init();
			} else{
				FATFS_UnLinkDriver(SDPath);
				HAL_SD_DeInit(&hsd1);
				}
	}
			
	HAL_NVIC_ClearPendingIRQ(TIM7_IRQn);
	HAL_TIM_IRQHandler(&htim7);
}

#define FILTER_SMA_ORDER 5
uint16_t Filter_Buffer[FILTER_SMA_ORDER] = {0};
/*SDO_IRQ interrupt*/
void EXTI9_5_IRQHandler(void)
{
	DWT_Delay(1);
  HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&RxBuf, (uint8_t*)&RxBuf, 2, 0);

  Filter_Buffer[FILTER_SMA_ORDER - 1] = RxBuf[0] << 8 | RxBuf[1];

  	uint32_t Output = 0;

  	for(uint8_t j = 0; j < FILTER_SMA_ORDER; j++) Output += Filter_Buffer[j];

  	Output /= FILTER_SMA_ORDER;

  	for(uint8_t k = 0; k < FILTER_SMA_ORDER; k++)
  	{
  		Filter_Buffer[k] = Filter_Buffer[k+1];
  	}

		Line[i] = Output;

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
	if(TOUCH_SCREEN)
	{
		cnt_touch_delay = cnt_touch_delay + 1;

			Touch_x = 0, Touch_y = 0;

		//	TS_Get_XY1(TS_I2C_ADDRESS, &Touch_x, &Touch_y);

			if((!TFT_ON_OFF) && (cnt_touch_delay >= 50))
			{
					TFT_ON_OFF = 0x01;
					HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);//booster
			}else{

				if(TFT_ON_OFF){
					TS_Get_XY1(TS_I2C_ADDRESS, &Touch_x, &Touch_y);

					if((Mode_EL == 0x00) && ((Touch_x >= 109 & Touch_x <= (109+54) & Touch_y >=426 & Touch_y <=(426+54) )))
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
	HAL_NVIC_ClearPendingIRQ(EXTI3_IRQn);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

void USART3_IRQHandler(void)
{
	uint8_t str[12]={0};

	if(BT_BAUD_RATE < 115200)
	{
		HAL_UART_Receive(&huart3,&str,12,10);
	}
	else if (BT_BAUD_RATE >= 115200)
	{
		HAL_UART_Receive(&huart3,&str, 12, 1);
	}


	if (str[0] == 0x0A)
	{
		if (str[1] == 0xAB)
		{
			if (str[2] == 0x12)
			{
				if (str[3] == 0x02)
				{
					string_parse_no_check();
				}
			}
		}
	}


	HAL_NVIC_ClearPendingIRQ(USART3_IRQn);
	HAL_UART_IRQHandler(&huart3);
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
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV5;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
	  Error_Handler();
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
	  Error_Handler();
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
	  Error_Handler();
  }

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
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
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
  sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
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

static void MX_TIM6_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 48000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 3800;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
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
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET); //VIDEO_GAIN ON

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

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 4); //SDO IRQ//24
	HAL_NVIC_SetPriority(EXTI3_IRQn, 4, 2); //Touchscreen IRQ//42
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
    Error_Handler();
  }

  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
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
    Error_Handler();
  }
  /**Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* SDMMC1 init function */
static void MX_SDMMC1_SD_Init(void)
{
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;//4
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 14;//10/22
  hsd1.Init.Transceiver = SDMMC_TRANSCEIVER_DISABLE;
}

static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

//PWM Timer for booster
static void MX_TIM15_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 1200;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = 100;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 20000;/****///
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim15, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim15);

}

/*timer for Measure Bar*/
static void MX_TIM7_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 60000;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 200;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_USART3_UART_Init(void)
{
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 9600;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

void _Error_Handler(char *file, int line){while(1){}}
void assert_failed(uint8_t* file, uint32_t line){}
