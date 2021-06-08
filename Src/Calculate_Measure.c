#include "Calculate_Measure.h"
float sum;
uint16_t iq;
uint8_t	Calculate_deltaEab_Done = 0;
extern uint8_t Measure_Color_xy, Source_Type;
extern uint16_t colorimetry_XYZ1964[3], lambda_c_Measure, lambda_d_Measure, Measure_Field, colorimetry_XYZ1931[3];
extern int16_t colorimetry_LAB[3];
extern float colorimetry_xy1964[2], colorimetry_uv[2], colorimetry_uv1976[2], colorimetry_xy1931[2];
extern float calibratre_x_1931[1024], Spectral_day[1024], calibratre_z_1931[1024];
	
float Calculate_EL_Day(float R_data[], float Spectral_Day_const[])
{
	sum = 0;
	for ( iq = 0; iq < 1024; iq++)
	{
		sum = sum + (R_data[iq]*Spectral_Day_const[iq]);
	}
	return 683*sum;
}


float Calculate_EL_Day_Wt(float R_data[])
{
	sum = 0;
	for ( iq = 0; iq < 1024; iq++)
	{
		sum = sum + (R_data[iq]);
	}
	return sum;
}

float Calculate_EL_Night(float R_data[], float Spectral_Night_const[])
{
	sum = 0;
	for (iq = 0; iq < 1024; iq++)
	{
		sum = sum + (R_data[iq]*Spectral_Night_const[iq]);
	}
	return 1700*sum;
}

float Calculate_SP(float EL_day_data, float EL_Night_data)
{
	return (EL_day_data !=0) ? EL_Night_data/EL_day_data: 0;
}

float Calculate_PPFD_PPL(float R_data[], float Wavelenght[])
{
	uint16_t it = 0, beg = 0, end = 1024;

	while(Wavelenght[it]<400)
	{
		it++;
	}
	beg = it+1;

	it = 1024;
	while(Wavelenght[it]>700)
	{
		it--;
	}
	end = it-1;


	sum = 0;
	for (iq = beg; iq < end; iq++)
	{
		sum = sum + (R_data[iq]*Wavelenght[iq]*0.00835936108917328);
	}
	return sum;
}

float Calculate_PPFD_PPL_Range(float R_data[], float Wavelenght[], uint8_t Range)
{
	uint16_t Range_min, Range_max;
	sum = 0;
	
	if (Range == BLUE_RANGE)
	{
		Range_min = 400;
		Range_max = 500;
	} else if (Range == GREEN_RANGE)
	{
		Range_min = 500;
		Range_max = 600;
	} else if (Range == RED_RANGE)
	{
		Range_min = 600;
		Range_max = 700;
	}else if (Range == FAR_RED_RANGE)
	{
		Range_min = 700;
		Range_max = 1000;
	}
	
	for(iq = 0; iq < 1024; iq++)
	{
		if(Wavelenght[iq] > Range_min && Wavelenght[iq] < Range_max)
		{
			if(Wavelenght[iq] == Range_max || Wavelenght[iq] == Range_min)
			{
				sum = sum + (0.5 * R_data[iq]*Wavelenght[iq]*0.00835936108917328);
			} else
			{			
				sum = sum + (R_data[iq]*Wavelenght[iq]*0.00835936108917328);
			}
		}
	}
	return sum;
}

float Calculate_ELr(float R_data[], float Hazard_Retina[])
{
	sum = 0;
	for (iq = 0; iq < 1024; iq++)
	{
		sum = sum + (R_data[iq]*Hazard_Retina[iq]);
	}
	
	return sum;
}

float Calculate_ELb(float R_data[], float Hazard_Blue[])
{
		sum = 0;
	for (iq = 0; iq < 1024; iq++)
	{
		sum = sum + (R_data[iq]*Hazard_Blue[iq]);
	}
	return sum;
}

void Calculate_XYZ1964(float R_data[], float colorimetry_x[], float colorimetry_y[], float colorimetry_z[])
{
	double k;
	float X_sum = 0, Y_sum = 0, Z_sum = 0;
	
	colorimetry_XYZ1964[0] = 0;
	colorimetry_XYZ1964[2] = 0;	
	
	for (iq = 0; iq < 1024; iq++)
	{
		X_sum = X_sum + (R_data[iq]*colorimetry_x[iq]);
		Y_sum = Y_sum + (R_data[iq]*colorimetry_y[iq]);
		Z_sum = Z_sum + (R_data[iq]*colorimetry_z[iq]);
	}
	
	k = 100/Y_sum;
	
	colorimetry_XYZ1964[0] = k*X_sum;
	colorimetry_XYZ1964[1] = 100;
	colorimetry_XYZ1964[2] = k*Z_sum;	
}

void Calculate_XYZ1931(float R_data[], float colorimetry_x[], float colorimetry_y[], float colorimetry_z[])
{

	double k;
	float X_sum = 0, Y_sum = 0, Z_sum = 0;
	
	colorimetry_XYZ1931[0] = 0;
	colorimetry_XYZ1931[2] = 0;	
	
	for (iq = 0; iq < 1024; iq++)
	{
		X_sum = X_sum + (R_data[iq]*colorimetry_x[iq]);
		Y_sum = Y_sum + (R_data[iq]*colorimetry_y[iq]);
		Z_sum = Z_sum + (R_data[iq]*colorimetry_z[iq]);
	}
	
	k = 100/Y_sum;
	
	colorimetry_XYZ1931[0] = k*X_sum;
	colorimetry_XYZ1931[1] = 100;
	colorimetry_XYZ1931[2] = k*Z_sum;	
}
void Calculate_xy1964(uint16_t colorimetry_XYZ_calculate[])
{
	uint16_t sum = colorimetry_XYZ_calculate[0] + colorimetry_XYZ_calculate[1] + colorimetry_XYZ_calculate[2];
	
	colorimetry_xy1964[0] = fabs(((float)colorimetry_XYZ_calculate[0])/((float)sum));
	colorimetry_xy1964[1] = fabs((float)colorimetry_XYZ_calculate[1])/((float)sum);
}

void Calculate_xy1931(uint16_t colorimetry_XYZ_calculate[])
{
	uint16_t sum = colorimetry_XYZ_calculate[0] + colorimetry_XYZ_calculate[1] + colorimetry_XYZ_calculate[2];
	
	colorimetry_xy1931[0] = fabs(((float)colorimetry_XYZ_calculate[0])/((float)sum));
	colorimetry_xy1931[1] = fabs((float)colorimetry_XYZ_calculate[1])/((float)sum);
}

void Calculate_uv(float colorimetry_xy_calculate[])
{
	float sum = -2*colorimetry_xy_calculate[0] + 12*colorimetry_xy_calculate[1] + 3;
	colorimetry_uv[0] = 4*colorimetry_xy_calculate[0]/sum;
	colorimetry_uv[1] = 6*colorimetry_xy_calculate[1]/sum;
}

void Calculate_uv1976(float colorimetry_xy_calculate[])
{
	float sum = -2*colorimetry_xy_calculate[0] + 12*colorimetry_xy_calculate[1] + 3;
	colorimetry_uv1976[0] = 4*colorimetry_xy_calculate[0]/sum;
	colorimetry_uv1976[1] = 9*colorimetry_xy_calculate[1]/sum;
}

double up = 0, vp = 0, factor_uvp = 0, result_tc, u_dop = 0, v_dop = 0, deltaC = 0;
float Calculate_Tc(float R_data[], uint8_t CIE_Type)
{
	
	float dline = 0, dmin1 = 1000, dmin2 = 1000;
	uint8_t	 i_min1 = 0, i_min2 = 0;
	
	if(CIE_Type == 0x00) //check CIE 1964
	{
		Calculate_XYZ1931(R_data, calibratre_x_1931, Spectral_day, calibratre_z_1931);
	}
	
	factor_uvp = (colorimetry_XYZ1931[0] + 15*colorimetry_XYZ1931[1] + 3*colorimetry_XYZ1931[2]);
	
	up = (4.*colorimetry_XYZ1931[0])/factor_uvp;
	vp = (6.*colorimetry_XYZ1931[1])/factor_uvp;
	
	
	for(uint8_t i = 0; i < 31; i++)
	{
		dline = ((vp - ((float)v0[i])/100000.)- t[i] * (up - ((float)u0[i])/100000.))/t_sqrt[i];
		if (fabs(dmin1) > fabs(dline)) {
				dmin2 = dmin1; 
				dmin1 = dline;
				i_min2 = i_min1;
				i_min1 = i;
			}
	}
	
	u_dop = (u0[i_min1]/100000. + u0[i_min2]/100000.)/2;
	v_dop = (v0[i_min1]/100000. + v0[i_min2]/100000.)/2;
	
	deltaC = sqrt((pow((u_dop - up), 2)+ pow((v_dop - vp), 2)));
	
	if(deltaC > 0.05)
	{
		return 0xFFFF;
	}else
	{
		return result_tc = fabs(1000000./(Tc_tabl[i_min1]+dmin1*((Tc_tabl[i_min2]-Tc_tabl[i_min1])/(dmin1-dmin2))));
	}
}

void Calculate_Lab(uint16_t colorimetry_XYZ_calculate[], uint8_t CIE_Type, uint8_t Source_Type)
{
	float Xref, Yref = 100, Zref;
	uint8_t i;
	double factor_x = 0, factor_y = 0, factor_z = 0, fx = 0, fy = 0, fz = 0;
	i = (Source_Type == Source_A)?0:(Source_Type == Source_D65)?1:(Source_Type == Source_C)?2:(Source_Type == Source_D50)?3:(Source_Type == Source_D55)?4:(Source_Type == Source_D75)?5:0;
	
	if (CIE_Type == 0x01) //check CIE 1931
	{
		Xref = Xref_CIE1931[i]/100.0;
		Zref = Zref_CIE1931[i]/100.0;
	
	} else if(CIE_Type == 0x00) ////check CIE 1964
	{
		Xref = Xref_CIE1964[i]/100.0;
		Zref = Zref_CIE1964[i]/100.0;
	}
	factor_x = (float)colorimetry_XYZ_calculate[0]/Xref;
	factor_y = (float)colorimetry_XYZ_calculate[1]/Yref;
	factor_z = (float)colorimetry_XYZ_calculate[2]/Zref;
	
		if(factor_x > 0.00885645)
	{
		fx = pow(factor_x, 1./3.);
	} else 
	{
		fx = (903.3*factor_x + 16.) / 116.;
	}
	
		if(factor_y > 0.00885645)
	{
		fy = pow(factor_y, 1./3.);
	} else 
	{
		fy = (903.3*factor_y + 16.) / 116.;
	}
	
		if(factor_z > 0.00885645)
	{
		fz = pow(factor_z, 1./3.);
	} else 
	{
		fz = (903.3*factor_z + 16.) / 116.;
	}
	
	colorimetry_LAB[0] = (int16_t)(116.*fy-16.);
	colorimetry_LAB[1] = (int16_t)(500.*(fx-fy));
	colorimetry_LAB[2] = (int16_t)(200.*(fy-fz));
	
}


void Calculate_Lambda_Dominant(float R_data[], uint8_t CIE_Type)
{	
	float Px, Py, x1 = 0.3333, y1 = 0.3333, x2, y2, divider;
	int8_t triangle_p1, triangle_p2, triangle_p3, triangle_out, ld;
	
	x2 = colorimetry_xy1931[0];
	y2 = colorimetry_xy1931[1];
	
	triangle_p1 = (((x1-x2)*(y34_dominant[0]-y1) - (x34_dominant[0] - y1)*(y1 - y2)) > 0)? 1 : -1;
	triangle_p2 = (((x34_dominant[0] - x2)*(y34_dominant[64]-y34_dominant[0]) - (x34_dominant[64]-x34_dominant[0])*(y34_dominant[0]-y2)) > 0)? 1 : -1;
	triangle_p3 = (((x34_dominant[64] - x2)*(y1 - y34_dominant[64]) - (x1 - x34_dominant[64])*(y34_dominant[64] - y2)) > 0)? 1 : -1;
		
	triangle_out = (triangle_p1 == triangle_p2 && triangle_p2 == triangle_p3) ? -1 : 1;
	
	for(uint8_t i = 0; i < 65; i++)
	{
		divider = (x1-x2)*(y34_dominant[i] - y34_dominant[i+1]) - (y1 - y2)*(x34_dominant[i] - x34_dominant[i+1]);
		Px = ((x1*y2 - y1*x2)*(x34_dominant[i] - x34_dominant[i+1]) - (x1 - x2)*(x34_dominant[i]*y34_dominant[i+1] - y34_dominant[i]*x34_dominant[i+1]))/divider;
		Py = ((x1*y2 - y1*x2)*(y34_dominant[i] - y34_dominant[i+1]) - (y1 - y2)*(x34_dominant[i]*y34_dominant[i+1] - y34_dominant[i]*x34_dominant[i+1]))/divider;
		
		if(Px > MIN(x34_dominant[i], x34_dominant[i+1]) && Px < MAX(x34_dominant[i], x34_dominant[i+1]) && Py > MIN(y34_dominant[i], y34_dominant[i+1]) && Py < MAX(y34_dominant[i], y34_dominant[i+1]))
		{
			ld = (x2 > MIN(Px, x1) && x2 < MAX(Px, x1))? 1:-1;
			
			if((ld*triangle_out) > 0)
			{
				lambda_d_Measure = lamda_dominant[i+1];
			} else {
				lambda_d_Measure = triangle_out < 0 ? 0 : lamda_dominant[i+1];
			}
		}
	}
}

extern int16_t colorimetry_LAB_mem[3];
float result, res1, res2, res3;

int16_t Calculate_deltaEab() {
	if((Measure_Field&CIE_Lab) == 0){
		Calculate_Lab(Measure_Color_xy == 0x00 ? colorimetry_XYZ1964 : colorimetry_XYZ1931, Measure_Color_xy, Source_Type);
	}
	res1 = ((float)(colorimetry_LAB[0]) - (float)(colorimetry_LAB_mem[0]));
	res2 = ((float)(colorimetry_LAB[1]) - (float)(colorimetry_LAB_mem[1]));
	res3 = ((float)(colorimetry_LAB[2]) - (float)(colorimetry_LAB_mem[2]));
	Calculate_deltaEab_Done = 0x01;
	return (int16_t)sqrtf(res1*res1+res2*res2+res3*res3);
}
