#include "CQS_Calculate.h"
#include "GUI_Measure_Elements.h"

double x_ref[15];		// cqs
double y_ref[15];		// cqs
double z_ref[15];		// cqs
double R_i_test[15];	// cqs
double G_i_test[15];	// cqs
double B_i_test[15];	// cqs
float Q_i_temp, Qf_temp, Qa_temp, Qp_temp;			// cqs
uint8_t Q_i[15] = {0}, Qf = 0, Qa = 0, Qp = 0;
double Mcct = 1;
float s_ref[1024] = {0};
float norm_560;
float M1=0, M2 = 0;
double xD, yD, bar_CQS;
extern float WaveLenght[1024], S0_lambda[1024], S1_lambda[1024], S2_lambda[1024], calibratre_x_1931[1024],Spectral_day[1024],calibratre_z_1931[1024], max_Rabs;
float CQS_R_temp[1024] = {0}, CQS_S_test[1024] = {0};

double M[9] = { 0.7982, 0.3389, -0.1371,
				-0.5918, 1.5512, 0.0406,
				0.0008, 0.0239, 0.9753 };

double M_inv[9] = { 1.07645, -0.237662, 0.161212,
					0.410964, 0.554342, 0.034694,
					-0.010954, -0.013389, 1.024343 };
					
void calcNorm560(uint16_t CCT_measure)
{
	norm_560 = pow(0.00000056, -5) / (exp(0.014388 / (0.00000056 *CCT_measure)) - 1);
}

double ans = 0;
double calcSref(int idx, uint16_t CCT_measure)
{
	if (CCT_measure < 5000)
	{
		ans = exp(0.014388 / (WaveLenght[idx] * 0.000000001 * CCT_measure)) - 1;
		ans = pow(WaveLenght[idx] * 0.000000001, -5) / ans;
		ans /= norm_560;
	}
	else
	{
		ans = S0_lambda[idx] + M1*S1_lambda[idx] + M2*S2_lambda[idx];
	}
	return ans;
}

void cqs_func(uint16_t CCT_measure, float *Rabs)
{
	GUI_Bar_Measure_OFF(85, 13);
	double Y_ic_test = 0;
	double X_ic_test = 0;
	double Z_ic_test = 0;
	
	double k_ref = 0;
	double k_test = 0;
	double xw_ref = 0;
	double yw_ref = 0;
	double zw_ref = 0;
	double xw_test = 0;
	double yw_test = 0;
	double zw_test = 0;
					
	double R_ic_test = 0;
	double G_ic_test = 0;
	double B_ic_test = 0;
		
	double x_test = 0;	
	double y_test = 0;		
	double z_test = 0;	
	
	
	memset(CQS_S_test, 0, sizeof(CQS_S_test));
	memset(CQS_R_temp, 0, sizeof(CQS_R_temp));
	
	for (uint16_t i = 0; i < 1024; i++){
		CQS_S_test[i] = Rabs[i]/max_Rabs;
	}

	if (CCT_measure < 3500){
		Mcct = (float)CCT_measure*(float)CCT_measure*(float)CCT_measure*0.000000000092672 - (float)CCT_measure*(float)CCT_measure*0.00000083959 + (float)CCT_measure*0.00255 - 1.612;
	}
	
	if (CCT_measure < 5000)
	{
		calcNorm560(CCT_measure);
	}

	if (CCT_measure >= 5000)
	{

		if (CCT_measure < 7000)
		{
			xD = -4.6070*pow(10, 9) / ((float)CCT_measure*(float)CCT_measure*(float)CCT_measure) + 2.9678*pow(10, 6) / ((float)CCT_measure*(float)CCT_measure)
					+ 0.09911*pow(10, 3) / (float)CCT_measure + 0.244063;
		}
		else 
		{
			xD = -2.0064*pow(10, 9) / pow(CCT_measure, 3) + 1.9018*pow(10, 6) / ((float)CCT_measure*(float)CCT_measure)
			+ 0.24748*pow(10, 3) / (float)CCT_measure + 0.23704;
		}
		yD = -3 * xD*xD + 2.87*xD - 0.275;
		M1 = -1.3515 - 1.7703*xD + 5.9114*yD;
		M1 /= (0.0241 + 0.2562*xD - 0.7341*yD);
		M2 = 0.03 - 31.4424*xD + 30.0717*yD;
		M2 /= (0.0241 + 0.2562*xD - 0.7341*yD);
	}
	
	//bar_CQS = 0.2;
	//GUI_Bar_Measure(85, 13, bar_CQS);

	memset(x_ref, 0, sizeof(x_ref));
	memset(y_ref, 0, sizeof(y_ref));
	memset(z_ref, 0, sizeof(z_ref));
	
	for (uint8_t i = 0; i < 15; i++)
	{
		
		//bar_CQS += 0.04;
		//GUI_Bar_Measure(85, 13, bar_CQS);
		
		 x_test = 0;	
		 y_test = 0;		
		 z_test = 0;	
	
	
		Calibration_Load_Pack(CQS_R1+i*0x1000, 0x400, CQS_R_temp);

		for (int j = 0; j < 1024; j++)
		{
			if (i == 0)
			{
				s_ref[j] = calcSref(j, CCT_measure);
				k_ref += s_ref[j] * Spectral_day[j];
				xw_ref += s_ref[j] * calibratre_x_1931[j];
				yw_ref += s_ref[j] * Spectral_day[j];
				zw_ref += s_ref[j] * calibratre_z_1931[j];
				k_test += CQS_S_test[j] * Spectral_day[j];
				xw_test += CQS_S_test[j] * calibratre_x_1931[j];
				yw_test += CQS_S_test[j] * Spectral_day[j];
				zw_test += CQS_S_test[j] * calibratre_z_1931[j];
			}

			x_ref[i] += calibratre_x_1931[j] * CQS_R_temp[j] * s_ref[j];
			y_ref[i] += Spectral_day[j] * CQS_R_temp[j] * s_ref[j];
			z_ref[i] += calibratre_z_1931[j] * CQS_R_temp[j] * s_ref[j];
			x_test += calibratre_x_1931[j] * CQS_R_temp[j] * CQS_S_test[j];
			y_test += Spectral_day[j] * CQS_R_temp[j] * CQS_S_test[j];
			z_test += calibratre_z_1931[j] * CQS_R_temp[j] * CQS_S_test[j];
		}
		
		memset(CQS_R_temp, 0, sizeof(CQS_R_temp));
		
		if (i == 0) {
			k_ref = 100 / k_ref;
			k_test = 100 / k_test;
		}
			
		x_ref[i] *= k_ref;
		y_ref[i] *= k_ref;
		z_ref[i] *= k_ref;
		x_test *= k_test;
		y_test *= k_test;
		z_test *= k_test;
		R_i_test[i] = x_test * M[0] + y_test * M[1] + z_test * M[2];	
		G_i_test[i] = x_test * M[3] + y_test * M[4] + z_test * M[5];
		B_i_test[i] = x_test * M[6] + y_test * M[7] + z_test * M[8];
	}

	xw_ref *= k_ref;
	yw_ref *= k_ref;
	zw_ref *= k_ref;
	xw_test *= k_test;
	yw_test *= k_test;
	zw_test *= k_test;

	double R_w_ref = xw_ref * M[0] + yw_ref* M[1] + zw_ref * M[2];
	double G_w_ref = xw_ref * M[3] + yw_ref* M[4] + zw_ref * M[5];
	double B_w_ref = xw_ref * M[6] + yw_ref* M[7] + zw_ref * M[8];
	double R_w_test = xw_test * M[0] + yw_test* M[1] + zw_test * M[2];
	double G_w_test = xw_test * M[3] + yw_test* M[4] + zw_test * M[5];
	double B_w_test = xw_test * M[6] + yw_test* M[7] + zw_test * M[8];

	float alpha = yw_test / yw_ref;
	float delta_e_rms = 0;
	float sum_delta_e = 0;
	float sum_delta_c = 0;

	for (int i = 0; i < 15; i++)
	{
		R_ic_test =  R_i_test[i] * alpha * R_w_ref / R_w_test;
		G_ic_test =  G_i_test[i] * alpha * G_w_ref / G_w_test;
		B_ic_test =  B_i_test[i] * alpha * B_w_ref / B_w_test;

		X_ic_test = R_ic_test * M_inv[0] + G_ic_test * M_inv[1] + B_ic_test * M_inv[2];
		Y_ic_test = R_ic_test * M_inv[3] + G_ic_test * M_inv[4] + B_ic_test * M_inv[5];
		Z_ic_test = R_ic_test * M_inv[6] + G_ic_test * M_inv[7] + B_ic_test * M_inv[8];

		float y_tmp = cbrt(y_ref[i] / yw_ref);
		float L_ref = 116* y_tmp - 16;
		float a_ref = 500 * (cbrt(x_ref[i] / xw_ref) - y_tmp);
		float b_ref = 200 * (y_tmp - cbrt(z_ref[i] / zw_ref));

		y_tmp = cbrt(Y_ic_test / yw_test);
		float L_test = 116 * y_tmp - 16;
		float a_test = 500 * (cbrt(X_ic_test / xw_test) - y_tmp);
		float b_test = 200 * (y_tmp - cbrt(Z_ic_test / zw_test));

		float delta_c_test = sqrt(a_test * a_test + b_test * b_test);
		float delta_c_ref = sqrt(a_ref * a_ref + b_ref * b_ref);
		float delta_c = delta_c_test - delta_c_ref;

		//bar_CQS = 0.9;
		//GUI_Bar_Measure(85, 13, bar_CQS);
	
		float delta_E_CQS = sqrt(pow(L_test - L_ref, 2) + pow(a_test - a_ref,2)+ pow(b_test - b_ref,2));
		float E_sat = delta_E_CQS;
		if (delta_c > 0)
		{
			E_sat = sqrt(delta_E_CQS*delta_E_CQS - delta_c*delta_c);
			sum_delta_c += delta_c;
		}			

		delta_e_rms += (E_sat*E_sat);
		sum_delta_e += (delta_E_CQS*delta_E_CQS);
		Q_i_temp = 10 * log(exp((100 - 3.1*E_sat) / 10) + 1) * Mcct;
		Q_i[i] = (uint8_t)Q_i_temp;		
	}
	delta_e_rms /= 15;
	delta_e_rms = sqrt(delta_e_rms);
	sum_delta_e /= 15;
	sum_delta_e = sqrt(sum_delta_e);
	float Qa_rms = 100 - 3.1*delta_e_rms;
	float Qa0_100 = 10 * log(exp(Qa_rms / 10)+ 1);

	 Qa_temp = Mcct * Qa0_100;
	 Qa = (uint8_t)Qa_temp;
	 Qf_temp = Mcct * 10 * log(exp((100 - 2.93*sum_delta_e) / 10) - 1);
		Qf = (uint8_t)Qf_temp;
	 Qp_temp = Mcct * 10 * log(exp((100 - 3.78*(delta_e_rms - sum_delta_c/15))/10)-1);
		Qp = (uint8_t)Qp_temp;
	
		//bar_CQS = 1.0;
		//GUI_Bar_Measure(85, 13, bar_CQS);
}
