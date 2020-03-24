#include "Calibration_Address.h"

extern uint16_t WaveLenght_Graph[7], DarkSignal;
extern float Unit_nm[7], Spectral_Corection_Buff[1024], Scattering_Light, Exposure_Factor;
extern float Spectral_day[1024], Spectral_night[1024], Spectral_B[1024], Spectral_R[1024];
	
uint16_t buff2_array[4] = {0};
uint16_t Calibration_Load_2byte(uint32_t Address, uint8_t num)
{
	uint64_t buff = 0;

	uint16_t byte_array[4] = {0};
	uint8_t i = 0;
	
	i = num > 3 ? (num - 4*(num/4)) : num;
	buff = flash_data_read_buff(Address);
	memcpy(buff2_array, &buff, sizeof(uint64_t));
	
	byte_array[0] = buff2_array[1];
	byte_array[1] = buff2_array[0];
	byte_array[2] = buff2_array[3];
	byte_array[3] = buff2_array[2];
	
	return byte_array[i];
}
	

	uint8_t byte1[8] = {0};
uint8_t Calibration_Load_1byte(uint32_t Address, uint8_t num)
{
	uint64_t buff = 0;
	uint8_t buff_array[8] = {0};

	uint8_t i = 0;
	
	i = num > 7 ? (num - 8) : num;
	buff = flash_data_read_buff(Address);
	memcpy(buff_array, &buff, sizeof(uint64_t));
	
	byte1[0] =  buff_array[3];
	byte1[1] =  buff_array[2];
	byte1[2] =  buff_array[1];
	byte1[3] =  buff_array[0];
	byte1[4] =  buff_array[7];
	byte1[5] =  buff_array[6];
	byte1[6] =  buff_array[5];
	byte1[7] =  buff_array[4];
	
	return byte1[i];
}


	
float Calibration_Load_float(uint32_t Address)
{
	uint8_t buff_array[8] = {0};
	uint32_t buff_float = 0;
	float res = 0;
	uint64_t buff = 0;
	buff = flash_data_read_buff(Address);
	memcpy(buff_array, &buff, sizeof(uint64_t));
	buff_float = (uint32_t)buff_array[0]<<24 | (uint32_t)buff_array[1] << 16 | (uint32_t)buff_array[2] << 8 | (uint32_t)buff_array[3];
	memcpy(&res, &buff_float, sizeof(uint32_t));
	return res;
}
	

	uint32_t addr;
	uint8_t buff_array[8] = {0};
	uint64_t buff = 0;
	uint32_t buff_float = 0;
	
void Calibration_Load_Pack(uint32_t Address, uint16_t size, float data[])
{
	uint16_t idx = 0;
	
	for (uint16_t i = 0; i < (4*size); i+=8){
		addr = Address + i;
		buff = flash_data_read_buff(Address+i);
		memcpy(buff_array, &buff, sizeof(uint64_t));

		buff_float	= (uint32_t)buff_array[0]<<24 | (uint32_t)buff_array[1] << 16 | (uint32_t)buff_array[2] << 8 | (uint32_t)buff_array[3];
		memcpy(&data[idx]	, &buff_float, sizeof(uint32_t));
		buff_float	= (uint32_t)buff_array[4]<<24 | (uint32_t)buff_array[5] << 16 | (uint32_t)buff_array[6] << 8 | (uint32_t)buff_array[7];
		memcpy(&data[idx+1]	, &buff_float, sizeof(uint32_t));
		idx+=2;
	}
}


void Calibration_Exposure_Change(uint8_t Exp)
{
	Scattering_Light = ((float)Calibration_Load_1byte((SCATTERING_LIGHT_7_812+8*(Exp/8)), Exp)) /10.0;
	DarkSignal = Calibration_Load_2byte(DARK_SIGNAL_7_812+8*(Exp/4), Exp);
	Exposure_Factor = ((float)Calibration_Load_2byte(EXPOSURE_FACTOR_7_812+8*(Exp/4), Exp))/100.0;
}

void Calibration_WaveLenght_Graph()
{
	for (uint8_t i = 0; i <= 7; i++){
		WaveLenght_Graph[i] = Calibration_Load_2byte(WAVELENGHT+i*292, 0); //step*2
		Unit_nm[i] = ((float)WaveLenght_Graph[i])/100.0+300.0;
	}
}


