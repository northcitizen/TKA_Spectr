#include "Rabs_math.h"

float Rabs_calc_Factor2_Settings_change(float Kt, float P)
{
	return Kt * P;
}

float Rabs_calc_Factor1(uint16_t Rdark, float Lt, uint16_t R_data[])
{
	uint32_t sum = 0;
	float Kl = 0;
	
	Kl = Lt/100.00;
	for (uint16_t i = 0; i < 1024; i++)
	{
		sum = sum + (R_data[i] - Rdark);
	}
	return Kl*(((float)sum)/1024.00);
}

float Factor3 = 0;

//void Rabs_calc_main(uint16_t R_data[], uint16_t Rdark, float Factor1, float Factor2, float Sn[], float Rabs[])
//{
//	uint16_t r = 1023;
//
//	for (uint16_t i = 0; i < 1024; i++)
//	{
//		Factor3 = R_data[i] - Rdark - Factor1;
//
//		if(Factor3 <= 0)
//		{
//			Rabs[1023-i] = 0;
//		} else
//		{
//			Rabs[1023-i] = Factor3*Factor2*(Sn[r]);
//		}
//
//		r--;
//	}
//}
void Rabs_calc_main(uint16_t R_data[], uint16_t Rdark, float Factor1, float Factor2, float Sn[], float Rabs[])
{
	uint16_t r = 1023;
	static float Rabs_prev[1024][4];
	static uint8_t n;
	float temp = 0;

	for (uint16_t i = 0; i < 1024; i++)
	{
		Factor3 = R_data[i] - Rdark - Factor1;
		if(Factor3 <= 0)
		{
			temp = 0;
			Rabs[1023-i] = (Rabs_prev[1023-i][0] + Rabs_prev[1023-i][1] + Rabs_prev[1023-i][2] + Rabs_prev[1023-i][3]) / 5;
		} else
		{
//			Rabs[1023-i] = (R_data[i] - Rdark - Factor1)*Factor2*(Sn[r]);
			Rabs[1023-i] = Factor3*Factor2*(Sn[r]);
			temp = Rabs[1023-i];
			Rabs[1023-i] = (Rabs[1023-i] + Rabs_prev[1023-i][0] + Rabs_prev[1023-i][1] + Rabs_prev[1023-i][2] + Rabs_prev[1023-i][3])/5;
		}

		Rabs_prev[1023-i][n] = temp;

		r--;
	}
	n++;
	if (n>3) n = 0;
}

float Rabs_calc_MAX(uint16_t Rdark, float Factor1, float Factor2)
{	
	Factor3 = 50500 - Rdark - Factor1;
	return Factor3*Factor2;
}

float Rabs_find_MAX(float Rabs[], uint8_t direction)
{	
	uint8_t    step = (direction == 0x00)? 4 :3;

	float max = 0;

	for (uint16_t i = 1023; i >= step; i-=step)
	{
		max = Rabs[i] > max ? Rabs[i] : max;
	}
	return max;
}

float Rabs_find_MAX_all(float Rabs[])
{	
	float max = 0;

	for (uint16_t i = 0; i < 1024; i++)
	{
		max = Rabs[i] > max ? Rabs[i] : max;
	}
	return max;
}
