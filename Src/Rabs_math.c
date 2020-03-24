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

void Rabs_calc_main(uint16_t R_data[], uint16_t Rdark, float Factor1, float Factor2, float Sn[], float Rabs[])
{	
	uint16_t r = 1023;
	
	for (uint16_t i = 0; i < 1024; i++)
	{
		Factor3 = R_data[i] - Rdark - Factor1;
		
		if(Factor3 <= 0)
		{	
			Rabs[1023-i] = 0;
		} else 
		{
			Rabs[1023-i] = Factor3*Factor2*(Sn[r]);
		}
		
		r--;
	}
}


float Rabs_calc_MAX(uint16_t Rdark, float Factor1, float Factor2)
{	
	Factor3 = 50500 - Rdark - Factor1;
	return Factor3*Factor2;
}

float Rabs_find_MAX(float Rabs[])
{	
	float max = 0;
	
	for (uint16_t i = 0; i < 1024; i++)
	{
		max = Rabs[i] > max ? Rabs[i] : max;
	}
	return max;
}