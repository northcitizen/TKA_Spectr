#ifndef __CALIBRATION_ADDRESS_H
#define __CALIBRATION_ADDRESS_H
#include "stm32l4xx_hal.h"
#include "CRC_check.h"
#include "string.h"

#define WAVELENGHT							0x08100000
//Rt dark OLD
//Unused since 15.02.21
//#define 	DARK_SIGNAL_7_812			0x08100800
//#define 	DARK_SIGNAL_15_625			0x08100802
//#define 	DARK_SIGNAL_31_25			0x08100804
//#define 	DARK_SIGNAL_62_5			0x08100806
//#define 	DARK_SIGNAL_125				0x08100808
//#define 	DARK_SIGNAL_250				0x0810080A
//#define 	DARK_SIGNAL_500				0x0810080C
//#define 	DARK_SIGNAL_1000			0x0810080E
//#define 	DARK_SIGNAL_2000			0x08100810
//#define 	DARK_SIGNAL_4000			0x08100812
//Lt
#define 	SCATTERING_LIGHT_7_812			0x08100828
#define 	SCATTERING_LIGHT_15_625			0x08100829
#define 	SCATTERING_LIGHT_31_25			0x0810082A
#define 	SCATTERING_LIGHT_62_5			0x0810082B
#define 	SCATTERING_LIGHT_125			0x0810082C
#define 	SCATTERING_LIGHT_250			0x0810082D
#define 	SCATTERING_LIGHT_500			0x0810082E
#define 	SCATTERING_LIGHT_1000			0x0810082F
#define 	SCATTERING_LIGHT_2000			0x08100830
#define 	SCATTERING_LIGHT_4000			0x08100831
//Kt
//#define 	EXPOSURE_FACTOR_7_812		0x08100814	//2021.03.31
#define 	EXPOSURE_FACTOR_7_812		0x08100800
#define 	EXPOSURE_FACTOR_15_625		0x08100816
#define 	EXPOSURE_FACTOR_31_25		0x08100818
#define 	EXPOSURE_FACTOR_62_5		0x0810081A
#define 	EXPOSURE_FACTOR_125			0x0810081C
#define 	EXPOSURE_FACTOR_250			0x0810081E
#define 	EXPOSURE_FACTOR_500			0x08100820
#define 	EXPOSURE_FACTOR_1000		0x08100822
#define 	EXPOSURE_FACTOR_2000		0x08100824
#define 	EXPOSURE_FACTOR_4000		0x08100826
//Sn
#define 	SPECTRAL_CORRECTION_E		0x08100838
#define 	SPECTRAL_CORRECTION_L		0x08101838
//P
#define 	ENERGY_FACTOR_E					0x08102838
#define 	ENERGY_FACTOR_L					0x0810283C

//Spectral Day V(lambda)
#define 	SPECTRAL_DAY						0x08102840	//float
//Spectral Night V'(lambda)
#define 	SPECTRAL_NIGHT					0x08103840  //float

//Spectral Hazard - Blue_light B(lambda) and retina R(lambda)
#define 	SPECTRAL_BLUELIGHT			0x08104840 //uint16_t*1000
#define 	SPECTRAL_RETINA					0x08105040 //uint16_t*1000

//Colorimetry
#define		X2_CIE1931							0x08105840 //float
#define		Z2_CIE1931							0x08106840 //float

#define		X10_CIE1964							0x08107840 //float
#define		Y10_CIE1964							0x08108840 //float
#define		Z10_CIE1964							0x08109840 //float

//CQS
#define		SPECTRAL_S0							0x0810A840 //uint16_t*100+50000
#define		SPECTRAL_S1							0x0810B040 //uint16_t*100+50000
#define		SPECTRAL_S2							0x0810B840 //uint16_t*100+50000
#define		CQS_R1									0x0810C040//float

//CRI
#define		CRI_R1									0x0811B040//float

#define		SERIAL_DEVICE 					0x0812A040 //uint16
#define		CALIBRATION_DATE				0x0812A048	//uint16
#define		CALIBRATION_MONTH				0x0812A04A	//uint16
#define		CALIBRATION_YEAR				0x0812A04C	//uint16
	
// dark signal
#define 	DARK_SIGNAL_7_812				0x0812A050
#define 	DARK_SIGNAL_15_625				0x0812A850
#define 	DARK_SIGNAL_31_25				0x0812B050
#define 	DARK_SIGNAL_62_5				0x0812B850
#define 	DARK_SIGNAL_125					0x0812C050
#define 	DARK_SIGNAL_250					0x0812C850
#define 	DARK_SIGNAL_500					0x0812D050
#define 	DARK_SIGNAL_1000				0x0812D850
#define 	DARK_SIGNAL_2000				0x0812E050
#define 	DARK_SIGNAL_4000				0x0812E850


#define		TEMP_7_812						0x0812F050
#define		TEMP_15_625						0x0812F060
#define		TEMP_31_25						0x0812F070
#define		TEMP_62_5						0x0812F080
#define		TEMP_125						0x0812F090
#define		TEMP_250						0x0812F0A0
#define		TEMP_500						0x0812F0B0
#define		TEMP_1000						0x0812F0C0
#define		TEMP_2000						0x0812F0D0
#define		TEMP_4000						0x0812F0E0


//dynamic settings_data
//#define		FILENUMBER							0x0812B020
//#define		SET_MODEEL							0x0812B030
//#define		SET_MEASUREFIELD					0x0812B038
//#define		SET_GRAPHFIELD						0x0812B040
//#define		SET_COLORFIELD						0x0812B048
//#define		SET_COLORRENDFIELD					0x0812B050
//#define		SET_LANGUAGE						0x0812B058
//#define		SET_SOURCETYPE						0x0812B060
//#define		SET_BLUETOOTH						0x0812B068
//#define 		SCREENADDR							0x0812C020

#define		FILENUMBER							0x08130000
#define		SET_MODEEL							0x08130008
#define		SET_MEASUREFIELD					0x08130010
#define		SET_GRAPHFIELD						0x08130018
#define		SET_COLORFIELD						0x08130020
#define		SET_COLORRENDFIELD					0x08130028
#define		SET_LANGUAGE						0x08130030
#define		SET_SOURCETYPE						0x08130038
#define		SET_BLUETOOTH						0x08130040

#define 	SCREENADDR							0x08131000



extern  const uint16_t Tc[31];
extern uint32_t address_temp_array[10];


void Calibration_Load_Pack(uint32_t Address, uint16_t size, float data[]);
uint8_t Calibration_Load_1byte(uint32_t Address, uint8_t num);
uint16_t Calibration_Load_2byte(uint32_t Address, uint8_t num);
void Calibration_WaveLenght_Graph();
void Calibration_Exposure_Change(uint8_t Exp);
float Calibration_Load_float(uint32_t Address);
void Calibration_Load_16bit_Pack(uint32_t Address, uint16_t size, uint16_t* data);
void Calibration_Load_Temperature_Coef(uint32_t Address);
//void Calibration_Load_Table1024();
void Calibration_Ranges_Values();
#endif
