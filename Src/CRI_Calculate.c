#include "CRI_Calculate.h"
#include "GUI_Measure_Elements.h"

double Ra_temp = 0, Rall_temp = 0, R9_temp = 0, Ri_temp[15];
int8_t Ra = 0, Rall= 0, R9= 0, Ri[15]= {0};
// float tc = 2782.69542;
extern float WaveLenght[1024];
double bar_CRI;
float s_test_CRI[1024] = {0};
extern float max_Rabs, calibratre_x_1931[1024],calibratre_y_1931[1024],calibratre_z_1931[1024];
extern float S0_lambda[1024], S1_lambda[1024], S2_lambda[1024];
extern float colorimetry_uv[2];
double delta_E_CRI, delta_L, delta_u, delta_v;
float norm_560_CRI, M1_CRI=0, M2_CRI = 0;
double Mcct_CRI = 1;
double xD_CRI, yD_CRI;

double u_test_s;
double v_test_s;
double L_i_test;
double u_i_test;
double v_i_test;
double u_ref_s ;
double v_ref_s ;
double L_i_ref ;
double u_i_ref ;
double v_i_ref ;

void calcNorm560_CRI(uint16_t CCT_measure)
{
	norm_560_CRI = pow(0.00000056, -5) / (exp(0.014388 / (0.00000056 *CCT_measure)) - 1);
}


float calcSref_CRI(int idx, uint16_t CCT_measure)
{
	float ans;
	if (CCT_measure < 5000)
	{
		ans = exp(0.014388 / (WaveLenght[idx] * 0.000000001 * CCT_measure)) - 1;
		ans = pow(WaveLenght[idx] * 0.000000001, -5) / ans;
		ans /= norm_560_CRI;
	}
	else
	{
		ans = S0_lambda[idx] + M1_CRI*S1_lambda[idx] + M2_CRI*S2_lambda[idx];
	}
	return ans;
}

		double x_i_test = 0;
		double y_i_test = 0;
		double z_i_test = 0;
		double x_i_ref = 0;
		double y_i_ref = 0;
		double z_i_ref = 0;

void CRI_func(uint16_t CCT_measure, float *Rabs)
{
	
	float s_ref_CRI[1024] = {0};
	float CRI_R_temp[1024] = {0};

	memset(Ri_temp, 0, sizeof(Ri_temp));
	
	double k_ref = 0;
	double k_test = 0;

	double x_ref = 0;
	double y_ref = 0;
	double z_ref = 0;
	double u_ref = 0;
	double v_ref = 0;

	if (CCT_measure < 5000)
	{
		calcNorm560_CRI(CCT_measure);
	}

	if (CCT_measure >= 5000)
	{

		if (CCT_measure < 7000)
		{
			xD_CRI = -4.6070*pow(10, 9) / ((float)CCT_measure*(float)CCT_measure*(float)CCT_measure) + 2.9678*pow(10, 6) / ((float)CCT_measure*(float)CCT_measure)
					+ 0.09911*pow(10, 3) / (float)CCT_measure + 0.244063;
		}
		else 
		{
			xD_CRI = -2.0064*pow(10, 9) / pow(CCT_measure, 3) + 1.9018*pow(10, 6) / ((float)CCT_measure*(float)CCT_measure)
			+ 0.24748*pow(10, 3) / (float)CCT_measure + 0.23704;
		}
		yD_CRI = -3 * xD_CRI*xD_CRI + 2.87*xD_CRI - 0.275;
		M1_CRI = -1.3515 - 1.7703*xD_CRI + 5.9114*yD_CRI;
		M1_CRI /= (0.0241 + 0.2562*xD_CRI - 0.7341*yD_CRI);
		M2_CRI = 0.03 - 31.4424*xD_CRI + 30.0717*yD_CRI;
		M2_CRI /= (0.0241 + 0.2562*xD_CRI - 0.7341*yD_CRI);
	}
	
	
	float u_test = colorimetry_uv[0];	
	float v_test = colorimetry_uv[1];
	
	bar_CRI = 0.1;
	GUI_Bar_Measure(85, 13, bar_CRI);
	
	for (uint16_t y = 0; y < 1024; y++){
		s_test_CRI[y] = Rabs[y]/max_Rabs;
	}
	
	for (uint8_t i = 0; i < 15; i++)
	{
		bar_CRI += 0.05;
		GUI_Bar_Measure(85, 13, bar_CRI);
		
		 x_i_test = 0;
		 y_i_test = 0;
		 z_i_test = 0;
		 x_i_ref = 0;
		 y_i_ref = 0;
		 z_i_ref = 0;

		Calibration_Load_Pack(CRI_R1+i*0x1000, 0x400, CRI_R_temp);
	
		for (int j = 0; j < 1024; j++)
		{
			if (i == 0)
			{
				s_ref_CRI[j] = calcSref_CRI(j, CCT_measure);
				k_test += s_test_CRI[j] * calibratre_y_1931[j];
				x_ref += s_ref_CRI[j] * calibratre_x_1931[j];
				y_ref += s_ref_CRI[j] * calibratre_y_1931[j];
				z_ref += s_ref_CRI[j] * calibratre_z_1931[j];
			}

			x_i_test += s_test_CRI[j] * CRI_R_temp[j] * calibratre_x_1931[j];
			y_i_test += s_test_CRI[j] * CRI_R_temp[j] * calibratre_y_1931[j];
			z_i_test += s_test_CRI[j] * CRI_R_temp[j] * calibratre_z_1931[j];

			x_i_ref += s_ref_CRI[j] * CRI_R_temp[j] * calibratre_x_1931[j];
			y_i_ref += s_ref_CRI[j] * CRI_R_temp[j] * calibratre_y_1931[j];
			z_i_ref += s_ref_CRI[j] * CRI_R_temp[j] * calibratre_z_1931[j];
		}
		if (i == 0) 
		{
			k_ref = 100 / y_ref;
			k_test = 100 / k_test;
			x_ref *= k_ref;
			y_ref *= k_ref;
			z_ref *= k_ref;
			u_ref = 4 * x_ref / (x_ref + 15 * y_ref + 3 * z_ref);
			v_ref = 6 * y_ref / (x_ref + 15 * y_ref + 3 * z_ref); 

		}	
		x_i_test *= k_test;	
		y_i_test *= k_test;
		z_i_test *= k_test;
		
		x_i_ref *= k_ref;
		y_i_ref *= k_ref;
		z_i_ref *= k_ref;	
	
		 u_test_s = 4 * x_i_test / (x_i_test + 15 * y_i_test + 3 * z_i_test);
		 v_test_s = 6 * y_i_test / (x_i_test + 15 * y_i_test + 3 * z_i_test);
		 L_i_test = 25 * cbrt(y_i_test) - 17;
		 u_i_test = 13 * L_i_test * (u_test_s - u_test);
		 v_i_test = 13 * L_i_test * (v_test_s - v_test);

		 u_ref_s = 4 * x_i_ref / (x_i_ref + 15 * y_i_ref + 3 * z_i_ref);
		 v_ref_s = 6 * y_i_ref / (x_i_ref + 15 * y_i_ref + 3 * z_i_ref);
		 L_i_ref = 25 * cbrt(y_i_ref) - 17;
		 u_i_ref = 13 * L_i_ref * (u_ref_s - u_ref);
		 v_i_ref = 13 * L_i_ref * (v_ref_s - v_ref);

		 delta_L = L_i_ref - L_i_test;
		 delta_u = u_i_ref - u_i_test;
		 delta_v = v_i_ref - v_i_test;	
		
		delta_E_CRI = sqrt(delta_L*delta_L + delta_u*delta_u + delta_v*delta_v);
		Ri_temp[i] = 100 - 4.6*delta_E_CRI;
		Ri[i] = (int8_t)Ri_temp[i];
		
		if (i < 8)
			Ra_temp += Ri_temp[i];
		if (i == 8)
			R9_temp = (int8_t)Ri_temp[i];
			R9 = (int8_t)R9_temp;
		if(i < 14)
			Rall_temp += Ri_temp[i];
		
		memset(CRI_R_temp, 0, sizeof(CRI_R_temp));		
	}
	
	bar_CRI = 0.9;
	GUI_Bar_Measure(85, 13, bar_CRI);
	
	Rall_temp /= 14;
	Rall = (int8_t)Rall_temp;
	
	Ra_temp /= 8;
	Ra = (int8_t)Ra_temp;
	
	bar_CRI = 1.0;
	GUI_Bar_Measure(85, 13, bar_CRI);
}