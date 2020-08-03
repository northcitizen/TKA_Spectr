#include <stdio.h>
#include "GUI_Measure_Elements.h"
#include <math.h>
extern uint8_t Language_status, Mode_EL, preGUI_screen_state, GUI_screen_state;

void GUI_Bar_Measure(uint16_t X, uint16_t Y, float Value)
{
	TFT_FillRectangle(X, Y, X+110, Y+10, TFT_White);	
	TFT_FillRectangle(X, Y, X+110*Value, Y+10, TFT_Blue_Off);
}



uint8_t  old_num_e = 10, old_num_n = 10, old_deg_e = 0xFF;
uint8_t old_meas_type_L = 2, old_numL_e = 10, old_numL_n = 10, old_rulx = 0, old_nan_Ee = 0, old_nan_El = 0; 
void GUI_Text_E_Measure(uint16_t X, uint16_t Y, float Value, uint8_t energy_light, uint8_t nope, uint8_t grey)
{
	if(preGUI_screen_state != GUI_screen_state){old_nan_Ee = 0; old_nan_El = 0; old_deg_e = 0xFF;}
	
	char buffer[9] = {0};
	uint8_t	delta_pos = 122, number = 0, meas_type=0, deg = 0; 
	uint32_t dec = 10;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_big);
	TFT_DrawChar(X, Y+2, 'E'-33);
	

		if((Value/1000.0) >= 1.0)
	{
		Value = Value/(1000.0);
		deg = 1;
		meas_type = 1;
	}else {meas_type = 0;}
	if(nope)
		{	
			if(energy_light & !old_nan_Ee){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+35, Y, X+195, Y+26, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
				old_nan_Ee = 1;
			}
			else if(!energy_light & !old_nan_El){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+35, Y, X+195, Y+26, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
				old_nan_El = 1;
			}
		}
	else{
		old_nan_Ee = 0; old_nan_El = 0;
			if(energy_light) {old_nan_Ee = 0;}
	if(!energy_light) {old_nan_El = 0;}
		Value = floor(Value*10)/10.0;

	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	
	if(energy_light){
		sprintf (buffer, "%.1f", Value);}
	else{
		sprintf (buffer, "%.1f", Value);
	}
	
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((Value/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(energy_light && number < old_num_e )
	{
		TFT_FillRectangle(X+40, Y, X+127, Y+26, TFT_Black_Bkgr);
	} 
	else if(!energy_light && number < old_num_n)
	{
		TFT_FillRectangle(X+40, Y, X+127, Y+26, TFT_Black_Bkgr);
	}
	
	if(energy_light){
		old_num_e = number;}
	else{
		old_num_n = number;
	}
	
	buffer[8] = 0;
	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
}

	if (Language_status == Ru && !energy_light)
	{
			if(deg != old_deg_e){
			TFT_FillRectangle(X+198, Y+3, X+250, Y+26, TFT_Black_Bkgr);
			TFT_SetTextColor(TFT_White);
			TFT_SetFont(&Font26RU_arch_small);
			if(deg){
			TFT_DrawCharRus(X+200, Y+4, 'к');
			TFT_DrawCharRus(X+215, Y+4, 'л');
			TFT_DrawCharRus(X+232, Y+4, 'к');} else{
			TFT_DrawCharRus(X+200, Y+4, 'л');
			TFT_DrawCharRus(X+215, Y+4, 'к');}
			}
			
			
			old_deg_e = deg;
	} else if (Language_status == En && !energy_light)
	{
		if(deg != old_deg_e){
			TFT_FillRectangle(X+198, Y+3, X+250, Y+26, TFT_Black_Bkgr);
			if (deg){
			TFT_SetTextColor(TFT_White);
			TFT_SetFont(&Font26EN_arch_small);
			TFT_DrawChar(X+214, Y+4, 'l'-65);
			TFT_DrawChar(X+200, Y+4, 'k'-65);
			TFT_DrawChar(X+226, Y+4, 'x'-65);
			old_rulx = 0;
		}else{
			TFT_SetTextColor(TFT_White);
			TFT_SetFont(&Font26EN_arch_small);
			TFT_DrawChar(X+200, Y+4, 'l'-65);
			TFT_DrawChar(X+212, Y+4, 'x'-65);
			
		}
			}
		
		old_deg_e = deg;
	}else if (Language_status == Ru && energy_light)
	{	
		GUI_TextRu_W_m2(234, Y);
	}else if (Language_status == En && energy_light)
	{
		GUI_TextEn_W_m2(234, Y);
	}
	
		if(energy_light) {
			TFT_SetTextColor(TFT_White);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+20, Y+14, 'e');}
	else {
		TFT_SetTextColor(TFT_White);
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(X+23, Y+13, 'z'+1);
	}

}

uint8_t old_nan_Le = 0, old_nan_Ll = 0, old_deg_L = 0xFF;
void GUI_Text_L_Measure(uint16_t X, uint16_t Y, float Value, uint8_t energy_light, uint8_t nope, uint8_t grey)
{
	if(preGUI_screen_state != GUI_screen_state){old_nan_Le = 0; old_nan_Ll = 0; old_deg_L = 0xFF;}
	char buffer[9] = {0};
	uint8_t	delta_pos = 117, deg = 0, number = 0, meas_type;
	uint32_t dec = 10;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_big);
	TFT_DrawChar(X, Y+2, 'L'-33);
	
	if(energy_light) {
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+20, Y+14, 'e');}
	else {
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(X+23, Y+13, 'z'+1);
	}
	
	if(nope) 
		{	
			if(energy_light & !old_nan_Le){
			TFT_SetTextColor(TFT_White);
			TFT_SetBackColor(TFT_Black_Bkgr);
			TFT_SetFont(&Font26EN_arch_digit);
			TFT_FillRectangle(X+40, Y, X+197, Y+26, TFT_Black_Bkgr);
			buffer[0] = '-';buffer[1] = '-';
			TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
			old_nan_Le = 1;}
			
			if(!energy_light & !old_nan_Ll){
			TFT_SetTextColor(TFT_White);
			TFT_SetBackColor(TFT_Black_Bkgr);
			TFT_SetFont(&Font26EN_arch_digit);
			TFT_FillRectangle(X+40, Y, X+197, Y+26, TFT_Black_Bkgr);
			buffer[0] = '-';buffer[1] = '-';
			TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
			old_nan_Ll = 1;}
		}
	else{
	if(energy_light) {old_nan_Le = 0;}
	if(!energy_light) {old_nan_Ll = 0;}
	Value = floor(Value*10)/10.0;
	
	if((Value/1000.0) >= 1.0)
	{
		Value = Value/(1000.0);
		deg = 1;
		meas_type = 1;
	}else {meas_type = 0;}
	
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	
	sprintf (buffer, "%.1f", Value);


for (uint8_t i = 1; i <= 4; i++)
	{
		if((Value/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(energy_light && number < old_numL_e )
	{
		TFT_FillRectangle(X+40, Y, X+197, Y+26, TFT_Black_Bkgr);
	} 
	else if(!energy_light && number < old_numL_n)
	{
		TFT_FillRectangle(X+40, Y, X+197, Y+26, TFT_Black_Bkgr);
	}
	
	if(energy_light){
		old_numL_e = number;}
	else{
		old_numL_n = number;
	}
	
	buffer[8] = 0;
	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
	
}
	if (Language_status == Ru && !energy_light)
	{
		if (deg && old_deg_L != 1){
			old_deg_L = 1;
			TFT_FillRectangle(X+195, Y+3, X+250, Y+26, TFT_Black_Bkgr);
			GUI_TextRu_Cd_m2(X+205, Y, 1);
		}else if(!deg && old_deg_L != 0){
			old_deg_L = 0;
			TFT_FillRectangle(X+193, Y, X+251, Y+26, TFT_Black_Bkgr);
			GUI_TextRu_Cd_m2(X+205, Y, 0);
		}
	} 
	else if (Language_status == En && !energy_light)
	{
		if (deg && old_deg_L != 1){
			old_deg_L = 1;
			TFT_FillRectangle(X+195, Y-5, X+251, Y+26, TFT_Black_Bkgr);
			GUI_TextEn_cd_m2(X+210, Y-4, 1);
		}else if(!deg && old_deg_L != 0){
			old_deg_L = 0;
			TFT_FillRectangle(X+195, Y-5, X+251, Y+26, TFT_Black_Bkgr);
			GUI_TextEn_cd_m2(X+215, Y-4, 0);
		}
		
	}
	else if (Language_status == Ru && energy_light)
	{	
		GUI_TextRu_W_m2_sr(X+210, Y);
	}else if (Language_status == En && energy_light)
	{
		GUI_TextEn_W_m2_sr(X+210, Y);
	}
}
uint8_t old_numPPF = 10, old_nan_PPF = 0;
void GUI_Text_PPF_Measure(uint16_t X, uint16_t Y, float Value, uint8_t nope, uint8_t grey)
{	
	if(preGUI_screen_state != GUI_screen_state){old_nan_PPF = 0;}
	char buffer[9] = {0};
	uint8_t	delta_pos = 122, deg = 0, number = 0;
	uint32_t dec = 10;
	
		if(nope) 
		{	
			if(!old_nan_PPF){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+70, Y, X+197, Y+26, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+117, Y, (uint8_t *)buffer, LEFT_MODE);
				old_nan_PPF = 1;
			}
		}
	else{
		if(old_nan_PPF){TFT_FillRectangle(X+70, Y, X+197, Y+26, TFT_Black_Bkgr);}
	old_nan_PPF = 0;
	Value = floor(Value*10)/10.0;
	
	if((Value/1000) >= 1.0)
	{
		Value = Value/(1000);
		deg = 1;
	}
	
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%.1f", Value);

	for (uint8_t i = 1; i <= 4; i++)
	{
		if((Value/((float)dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_numPPF )
	{
		TFT_FillRectangle(X+70, Y, X+228, Y+26, TFT_Black_Bkgr);
	} 

	old_numPPF = number;

	buffer[8] = 0;
	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
}
	
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	if(Language_status == Ru ){
			TFT_SetFont(&Font26RU_arch_big);
			if(preGUI_screen_state != GUI_screen_state){
				TFT_DrawCharRus(X, Y, 'Ф'-17);
				TFT_DrawCharRus(X+24, Y, 'А'-17);
				TFT_DrawCharRus(X+48, Y, 'Р'-17);}
		(Mode_EL) ? GUI_TextRu_umol(X+200, Y+2, deg) : GUI_TextRu_umol_sr(X+200, Y+2);
		} else
		{
			TFT_SetFont(&Font16EN_arch_big);
			if(Mode_EL){
				if(preGUI_screen_state != GUI_screen_state){
				TFT_DrawChar(X-10, Y+2, 'P');
				TFT_DrawChar(X+5, Y+2, 'P');
				TFT_DrawChar(X+20, Y+2, 'F');
				TFT_DrawChar(X+35, Y+2, 'D');}
				GUI_TextEn_umol(X+200, Y+2, deg);
			} else
			{
				if(preGUI_screen_state != GUI_screen_state){
				TFT_DrawChar(X-10, Y+2, 'P');
				TFT_DrawChar(X+5, Y+2, 'P');
				TFT_DrawChar(X+20, Y+2, 'L');}
				GUI_TextEn_umol_sr(X+200, Y+2, deg);
			}
		}	}
}
uint8_t old_numPPFR = 10, old_numPPFG = 10, old_numPPFB = 10, old_numPPFFR = 10, test = 0, test2 = 0, delta_pos2 = 140, old_nan_PPFRGB = 0;
float ValueB2 = 10;
void GUI_Text_PPFRGB_Measure(uint16_t X, uint16_t Y, float ValueR, float ValueG, float ValueB, float ValueFR, uint8_t nope, uint8_t grey)
{
	if(preGUI_screen_state != GUI_screen_state){old_nan_PPFRGB = 0;}
	
	char buffer[9] = {0};
	uint8_t	delta_pos = 140, deg = 0, number=0;
	uint32_t dec = 10;

		if(nope) 
		{	
			if(!old_nan_PPFRGB){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+98, Y+0, X+195, Y+20, TFT_Black_Bkgr);
				TFT_FillRectangle(X+98, Y+21, X+195, Y+41, TFT_Black_Bkgr);
				TFT_FillRectangle(X+98, Y+42, X+195, Y+63, TFT_Black_Bkgr);
				TFT_FillRectangle(X+98, Y+65, X+195, Y+87, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+117, Y, (uint8_t *)buffer, LEFT_MODE);
				TFT_DisplayString(X+117, Y+22, (uint8_t *)buffer, LEFT_MODE);
				TFT_DisplayString(X+117, Y+44, (uint8_t *)buffer, LEFT_MODE);
				TFT_DisplayString(X+117, Y+66, (uint8_t *)buffer, LEFT_MODE);
				old_nan_PPFRGB = 1;
			}
		}
	else{
		
		if(old_nan_PPFRGB) 
		{
			TFT_FillRectangle(X+98, Y+0, X+195, Y+20, TFT_Black_Bkgr);
			TFT_FillRectangle(X+98, Y+21, X+195, Y+41, TFT_Black_Bkgr);
			TFT_FillRectangle(X+98, Y+42, X+195, Y+63, TFT_Black_Bkgr);
			TFT_FillRectangle(X+98, Y+65, X+195, Y+87, TFT_Black_Bkgr);
		}
	old_nan_PPFRGB = 0;
	ValueB = floor(ValueB*10)/10.0;
	
	if((ValueB/1000) > 1.0)
	{
		ValueB = ValueB/(1000);
		deg = 1;
	}
	else deg=0;
	
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	sprintf (buffer, "%.1f", ValueB);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueB/((float)dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-= 22 - i*2;
			number++;
		}
	}

	if(number < old_numPPFB )
	{
		TFT_FillRectangle(X+98, Y, X+197, Y+20, TFT_Black_Bkgr);
	} 
	old_numPPFB = number;
	number = 0;
	buffer[8] = 0;
	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
	
	ValueG = floor(ValueG*10)/10.0;
	if((ValueG/1000) > 1.0)
	{
		ValueG = ValueG/(1000);
		deg = 1;
	}
	else deg=0;
	
	delta_pos = 140;
	dec = 10;
	TFT_SetFont(&Font16EN_arch_big);
	sprintf (buffer, "%.1f", ValueG);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueG/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-= 22 - i*2;
			number++;
		}
	}
	
		if(number < old_numPPFG )
	{
		TFT_FillRectangle(X+98, Y+21, X+197, Y+41, TFT_Black_Bkgr);
	} 
	old_numPPFG = number;
	number = 0;
	buffer[8] = 0;
	TFT_DisplayString(X+delta_pos, Y+22, (uint8_t *)buffer, LEFT_MODE);
	
	ValueR = floor(ValueR*10)/10.0;
	if((ValueR/1000) > 1.0)
	{
		ValueR = ValueR/(1000);
		deg = 1;
	}
	else deg=0;
	
	delta_pos = 140;
	dec = 10;
	TFT_SetFont(&Font16EN_arch_big);
	sprintf (buffer, "%.1f", ValueR);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueR/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-= 22 - i*2;
			number++;
		}
	}
	
	if(number < old_numPPFR )
	{
		TFT_FillRectangle(X+98, Y+42, X+197, Y+63, TFT_Black_Bkgr);
	} 
	old_numPPFR = number;
	number = 0;
	buffer[8] = 0;
	TFT_DisplayString(X+delta_pos, Y+44, (uint8_t *)buffer, LEFT_MODE);
	

	ValueFR = floor(ValueFR*10)/10.0;
	if((ValueFR/1000) > 1.0)
	{
		ValueFR = ValueFR/(1000);
		deg = 1;
	}
	else deg=0;
	
	delta_pos = 140;
	dec = 10;
	TFT_SetFont(&Font16EN_arch_big);
	sprintf (buffer, "%.1f", ValueFR);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueFR/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-= 22 - i*2;
			number++;
		}
	}
	
	if(number < old_numPPFFR )
	{
		TFT_FillRectangle(X+98, Y+65, X+197, Y+87, TFT_Black_Bkgr);
	} 
	old_numPPFFR = number;
	number = 0;
	
	buffer[8] = 0;
	TFT_DisplayString(X+delta_pos, Y+66, (uint8_t *)buffer, LEFT_MODE);
}
	if(preGUI_screen_state != GUI_screen_state){
if (Language_status==Ru)
	{	TFT_SetTextColor(TFT_White);
		TFT_SetFont(&Font16RU_arch_big);
		TFT_DrawCharRus(X+40, Y, 'С');
		TFT_SetFont(&Font16RU_arch_small);
		TFT_DrawCharRus(X+54, Y+5, 'и');
		TFT_DrawCharRus(X+66, Y+5, 'н');
		(Mode_EL) ? GUI_TextRu_umol(X+202, Y, deg) : GUI_TextRu_umol_sr(X+202, Y) ;
	}
	else if (Language_status==En)
	{TFT_SetTextColor(TFT_White);
		GUI_TextEn_Blue(X+34, Y);
		(Mode_EL) ? GUI_TextEn_umol(X+200, Y, deg) : GUI_TextEn_umol_sr(X+200, Y, deg);	
	}
	
	if (Language_status==Ru)
	{	TFT_SetTextColor(TFT_White);
		TFT_SetFont(&Font16RU_arch_big);
		TFT_DrawCharRus(X+40, Y+22, 'З');
		TFT_SetFont(&Font16RU_arch_small);
		TFT_DrawCharRus(X+54, Y+27, 'е');
		TFT_DrawCharRus(X+66, Y+27, 'л');
		(Mode_EL) ? GUI_TextRu_umol(X+202, Y+22, deg) : GUI_TextRu_umol_sr(X+202, Y+22) ;	
	}
	else if (Language_status==En)
	{	TFT_SetTextColor(TFT_White);
		GUI_TextEn_Green(X+17, Y+22);
		(Mode_EL) ? GUI_TextEn_umol(X+200, Y+22, deg) : GUI_TextEn_umol_sr(X+200, Y+22, deg);	
	}
	
	
	if (Language_status==Ru)
	{	TFT_SetTextColor(TFT_White);
		TFT_SetFont(&Font16RU_arch_big);
		TFT_DrawCharRus(X+40, Y+44, 'К');
		TFT_SetFont(&Font16RU_arch_small);
		TFT_DrawCharRus(X+55, Y+49, 'р');
		(Mode_EL) ? GUI_TextRu_umol(X+202, Y+44, deg) : GUI_TextRu_umol_sr(X+202, Y+44) ;	
	}
	else if (Language_status==En)
	{	TFT_SetTextColor(TFT_White);
		GUI_TextEn_Red(X+37, Y+44);
		(Mode_EL) ? GUI_TextEn_umol(X+200, Y+44, deg) : GUI_TextEn_umol_sr(X+200, Y+44, deg);	
	}
	TFT_SetTextColor(TFT_White);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+37, Y+66, 'F');
	TFT_DrawChar(X+53, Y+66, 'R');
	if (Language_status==Ru) (Mode_EL) ? GUI_TextRu_umol(X+202, Y+66, deg) : GUI_TextRu_umol_sr(X+202, Y+66) ;	
	else if (Language_status==En) (Mode_EL) ? GUI_TextEn_umol(X+200, Y+66, deg) : GUI_TextEn_umol_sr(X+200, Y+66, deg);	;
}
}
uint8_t old_numX = 10, old_numY = 10, old_numZ = 10, old_nanXYZ = 0;
void GUI_Text_XYZ_Measure(uint16_t X, uint16_t Y, uint16_t ValueX, uint16_t ValueY, uint16_t ValueZ, uint8_t nope, uint8_t grey)
{
	char buffer[5] = {0};
	uint8_t	delta_pos = 190, number = 0;
	uint32_t dec = 10;
	
	if((ValueX ==0 && ValueY ==100 && ValueZ ==0)||nope)
	{
		if(!old_nanXYZ){TFT_FillRectangle(X+40, Y, X+250, Y+95, TFT_Black_Bkgr);}
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black_Bkgr);
		TFT_SetFont(&Font26EN_arch_big);  TFT_DrawChar(X+135, Y, 'N'-33);TFT_DrawChar(X+160, Y, 'A'-33);TFT_DrawChar(X+185, Y, 'N'-33);
		TFT_DrawChar(X+135, Y+35, 'N'-33);TFT_DrawChar(X+160, Y+35, 'A'-33);TFT_DrawChar(X+185, Y+35, 'N'-33);
		TFT_DrawChar(X+135, Y+70, 'N'-33);TFT_DrawChar(X+160, Y+70, 'A'-33);TFT_DrawChar(X+185, Y+70, 'N'-33);
		old_nanXYZ = 1;
	}else{
	
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%d", ValueX);
	
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueX/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_numX || old_nanXYZ )
	{
		TFT_FillRectangle(X+40, Y, X+197, Y+24, TFT_Black_Bkgr);
	} 
	old_numX = number;
	number = 0;
	
		TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
	
	delta_pos = 190;
	dec = 10;
	
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%d", ValueY);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueY/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_numY || old_nanXYZ)
	{
		TFT_FillRectangle(X+40, Y+35, X+197, Y+59, TFT_Black_Bkgr);
	} 
	old_numY = number;
	number = 0;
	

			TFT_DisplayString(X+delta_pos, Y+35, (uint8_t *)buffer, LEFT_MODE);
	
		delta_pos = 190;
	 dec = 10;
	
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%d", ValueZ);
		for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueZ/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_numZ || old_nanXYZ)
	{
		TFT_FillRectangle(X+40, Y+70, X+197, Y+94, TFT_Black_Bkgr);
	} 
	old_numZ = number;
	number = 0;
	TFT_DisplayString(X+delta_pos, Y+70, (uint8_t *)buffer, LEFT_MODE);
	old_nanXYZ = 0;
}
			TFT_SetTextColor(TFT_White);
			TFT_SetBackColor(TFT_Black_Bkgr);
			TFT_SetFont(&Font26EN_arch_big);
			TFT_DrawChar(X, Y, 'X'-34);
			TFT_DrawChar(X, Y+35, 'Y'-34);
			TFT_DrawChar(X, Y+70, 'Z'-34);
}	
uint8_t old_nanxy = 0;
void GUI_Text_xy_Measure(uint16_t X, uint16_t Y, float Valuex, float Valuey, uint8_t nope, uint8_t grey)
{
	char buffer[5] = {0};
	uint8_t	delta_pos = 70;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);

	if((Valuex == 0 && Valuey ==1) || nope){
		if(!old_nanxy){TFT_FillRectangle(X+40, Y, X+250, Y+60, TFT_Black_Bkgr);}
		TFT_SetFont(&Font26EN_arch_big);  TFT_DrawChar(X+135, Y, 'N'-33);TFT_DrawChar(X+160, Y, 'A'-33);TFT_DrawChar(X+185, Y, 'N'-33);
		TFT_DrawChar(X+135, Y+35, 'N'-33);TFT_DrawChar(X+160, Y+35, 'A'-33);TFT_DrawChar(X+185, Y+35, 'N'-33);
		old_nanxy = 1;
	}else{
		TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
		TFT_SetFont(&Font26EN_arch_digit);
		sprintf (buffer, "%.4f", Valuex);
		TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
		
		sprintf (buffer, "%.4f", Valuey);
		TFT_DisplayString(X+delta_pos, Y+35, (uint8_t *)buffer, LEFT_MODE);
		old_nanxy = 0;
	}
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_small);
	TFT_DrawChar(X, Y, 'x'-65);
	TFT_DrawChar(X, Y+35, 'y'-65);
	
}	
uint8_t old_nanuv = 0;
void GUI_Text_uv_Measure(uint16_t X, uint16_t Y, float ValueU, float ValueV, uint8_t nope, uint8_t grey)
{
	char buffer[5] = {0};
	uint8_t	delta_pos = 70;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	
	if((ValueU == 0 && (ValueV >0.6 && ValueV <0.6001)) || nope){
		if(!old_nanuv){TFT_FillRectangle(X+40, Y, X+250, Y+60, TFT_Black_Bkgr);}
		TFT_SetFont(&Font26EN_arch_big);  TFT_DrawChar(X+135, Y, 'N'-33);TFT_DrawChar(X+160, Y, 'A'-33);TFT_DrawChar(X+185, Y, 'N'-33);
		TFT_DrawChar(X+135, Y+35, 'N'-33);TFT_DrawChar(X+160, Y+35, 'A'-33);TFT_DrawChar(X+185, Y+35, 'N'-33);
		old_nanuv = 1;
	}else{	
		TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
		TFT_SetFont(&Font26EN_arch_digit);
		sprintf (buffer, "%.4f", ValueU);
		TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
		sprintf (buffer, "%.4f", ValueV);
		TFT_DisplayString(X+delta_pos, Y+35, (uint8_t *)buffer, LEFT_MODE);
		old_nanuv = 0;
	}
	TFT_SetTextColor(TFT_White);
	TFT_SetFont(&Font26EN_arch_small);
	TFT_DrawChar(X+15, Y, 'z'-64);
	TFT_DrawChar(X, Y, 'u'-65);
	TFT_DrawChar(X+15, Y+35, 'z'-64);
	TFT_DrawChar(X, Y+35, 'v'-65);
}	

uint8_t old_numCCT = 10, old_nan_CCT = 0;
void GUI_Text_CCT_Measure(uint16_t X, uint16_t Y, uint16_t Value, uint8_t nope, uint8_t grey)
{	
	if(preGUI_screen_state != GUI_screen_state){old_nan_CCT = 0; }
	char buffer[9] = {0};
	uint8_t	delta_pos = 180, number = 0;
	uint32_t dec = 10;
	
	
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%d", Value);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((Value/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if((Value == 0 || nope) & !old_nan_CCT){old_nan_CCT = 1; TFT_FillRectangle(X+40, Y, X+205, Y+25, TFT_Black_Bkgr);TFT_SetTextColor(TFT_White); TFT_SetFont(&Font26EN_arch_big);  TFT_DrawChar(X+125, Y+4, 'N'-33);TFT_DrawChar(X+150, Y+4, 'A'-33);TFT_DrawChar(X+175, Y+4, 'N'-33);}
	else if(!nope & Value != 0){
	if(number < old_numCCT )
	{
		TFT_FillRectangle(X+40, Y, X+205, Y+25, TFT_Black_Bkgr);
	} 
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	old_numCCT = number;
		
	TFT_DisplayString(X+delta_pos, Y+2, (uint8_t *)buffer, LEFT_MODE); old_nan_CCT = 0; 
	}
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	if(Language_status == Ru ){
			TFT_SetFont(&Font26RU_arch_big);
			TFT_DrawCharRus(X, Y, 'К'-17);
			TFT_DrawCharRus(X+24, Y, 'Ц'-17);
			TFT_DrawCharRus(X+45, Y, 'Т'-17);
			TFT_DrawCharRus(X+215, Y, 'К'-17);
		} else
		{
			GUI_TextEn_CCT(X, Y+4);

			TFT_DrawChar(X+215, Y+4, 'K'-33);
		}	
}
uint8_t old_lambdaD = 10, old_nan_lambdaD = 0;
void GUI_Text_lambdaD_Measure(uint16_t X, uint16_t Y, float Value, uint8_t nope, uint8_t grey)
{	
	if(preGUI_screen_state != GUI_screen_state){old_nan_lambdaD = 0;}
	Value = floor(Value*10)/10.0;
	char buffer[9] = {0};
	uint8_t	delta_pos = 122, number = 0;
	uint32_t dec = 10;
	
	if(nope) 
		{	
			if(!old_nan_lambdaD){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+40, Y, X+197, Y+26, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+117, Y, (uint8_t *)buffer, LEFT_MODE);
				old_nan_lambdaD = 1;
			}
		}
	else{
	old_nan_lambdaD = 0;
	
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%.1f", Value);

		for (uint8_t i = 1; i <= 4; i++)
	{
		if((Value/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_lambdaD )
	{
		TFT_FillRectangle(X+40, Y, X+197, Y+25, TFT_Black_Bkgr);
	} 
	old_lambdaD = number;
	
	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
}
	if(preGUI_screen_state != GUI_screen_state){
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	GUI_Text_lambda_d(X, Y+5);
	if(Language_status == Ru ){
			TFT_SetFont(&Font26RU_arch_small);
			TFT_DrawCharRus(X+200, Y+5, 'н');
			TFT_DrawCharRus(X+216, Y+5, 'м');
		} else
		{
			TFT_SetFont(&Font16EN_arch_small);
			TFT_DrawChar(X+200, Y+10, 'n');
			TFT_DrawChar(X+216, Y+10, 'm');
		}	
	}
}
uint8_t old_lambdaC = 10, old_nan_lambdaC = 0;
void GUI_Text_lambdaC_Measure(uint16_t X, uint16_t Y, float Value, uint8_t nope, uint8_t grey)
{	
	if(preGUI_screen_state != GUI_screen_state){old_nan_lambdaC = 0;}
	char buffer[9] = {0};
	uint8_t	delta_pos = 122, number = 0;
	uint32_t dec = 10;
	if(nope) 
		{	
			if(!old_nan_lambdaC){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+40, Y, X+197, Y+26, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+117, Y, (uint8_t *)buffer, LEFT_MODE);
				old_nan_lambdaC = 1;
			}
		}
	else{
	old_nan_lambdaC = 0;
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	Value = floor(Value*10)/10.0;
	sprintf (buffer, "%.1f", Value);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((Value/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_lambdaC )
	{
		TFT_FillRectangle(X+40, Y, X+197, Y+25, TFT_Black_Bkgr);
	} 
	old_lambdaC = number;

	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
}
	
if(preGUI_screen_state != GUI_screen_state){
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	GUI_Text_lambda_c(X, Y+5);


	if(Language_status == Ru ){
			TFT_SetFont(&Font26RU_arch_small);
			TFT_DrawCharRus(X+200, Y+5, 'н');
			TFT_DrawCharRus(X+216, Y+5, 'м');
		} else
		{
			TFT_SetFont(&Font16EN_arch_small);
			TFT_DrawChar(X+200, Y, 'n');
			TFT_DrawChar(X+216, Y, 'm');
		}	
	}
}


uint8_t old_deltaE = 10, old_nan_deltaE = 0;
void GUI_Text_deltaE_Measure(uint16_t X, uint16_t Y, float Value, uint8_t nope, uint8_t grey)
{	
	if(preGUI_screen_state != GUI_screen_state){old_nan_deltaE = 0;}
	char buffer[9] = {0};
	uint8_t	delta_pos = 140, sign = 0, number = 0;
	uint32_t dec = 10;
	
	if(nope) 
		{	
			if(!old_nan_deltaE){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+40, Y, X+250, Y+26, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+117, Y, (uint8_t *)buffer, LEFT_MODE);
				old_nan_deltaE = 1;
			}
		}
	else{
		if(old_nan_deltaE){TFT_FillRectangle(X+40, Y, X+250, Y+26, TFT_Black_Bkgr);}
	old_nan_deltaE = 0;
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	Value = floor(Value*10)/10.0;
	if(Value < 0){Value *= -1; sign = 1;}
	
	sprintf (buffer, "%.2f", Value);
	
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((Value/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_deltaE )
	{
		TFT_FillRectangle(X+40, Y, X+197, Y+25, TFT_Black_Bkgr);
	} 
	old_deltaE = number;
	
	if(sign){TFT_DrawChar(X+delta_pos-18, Y, '-');}

	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
}
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);

	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y+6, '~'+2);
	
	TFT_SetFont(&Font26EN_arch_big);
	TFT_DrawChar(X+18, Y+2, 'E'-33);

}
uint8_t old_num_EB = 10, old_num_ER = 10, old_nan_EBER = 0;
void GUI_Text_EbEr_Measure(uint16_t X, uint16_t Y, float ValueEB, float ValueER, uint8_t nope, uint8_t grey)
{
	if(preGUI_screen_state != GUI_screen_state){old_nan_EBER = 0;}
	char buffer[9] = {0};
	uint8_t	delta_pos = 150, number = 0;
	uint32_t dec = 10;
	
	if(nope) 
		{	
			if(!old_nan_EBER){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+40, Y, X+250, Y+26, TFT_Black_Bkgr);
				TFT_FillRectangle(X+40, Y+35, X+250, Y+59, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+117, Y, (uint8_t *)buffer, LEFT_MODE);
				TFT_DisplayString(X+117, Y+35, (uint8_t *)buffer, LEFT_MODE);
				old_nan_EBER = 1;
			}
		}
	else{
		if(old_nan_EBER){TFT_FillRectangle(X+40, Y, X+250, Y+26, TFT_Black_Bkgr);
				TFT_FillRectangle(X+40, Y+35, X+250, Y+59, TFT_Black_Bkgr);}
	old_nan_EBER = 0;
	ValueEB = floor(ValueEB*100)/100.0;
	ValueER = floor(ValueER*100)/100.0;
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	
	sprintf (buffer, "%.2f", ValueEB);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueEB/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_num_EB )
	{
		TFT_FillRectangle(X+40, Y, X+197, Y+25, TFT_Black_Bkgr);
	} 
	old_num_EB = number;
	number = 0;

	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
	
	sprintf (buffer, "%.2f", ValueER);
		for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueER/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_num_ER )
	{
		TFT_FillRectangle(X+40, Y+33, X+197, Y+59, TFT_Black_Bkgr);
	} 
	old_num_ER = number;
	number = 0;

	TFT_DisplayString(X+delta_pos, Y+35, (uint8_t *)buffer, LEFT_MODE);
}
	TFT_SetTextColor(TFT_White);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+21, Y+12, 'B');
	TFT_DrawChar(X+21, Y+47, 'R');
	
	TFT_SetFont(&Font26EN_arch_big);
	TFT_DrawChar(X, Y+2, 'E'-33);
	TFT_DrawChar(X, Y+37, 'E'-33);
}
uint8_t old_num_LB = 10, old_num_LR = 10, old_nan_LBLR = 0;
void GUI_Text_LbLr_Measure(uint16_t X, uint16_t Y, float ValueLB, float ValueLR, uint8_t nope, uint8_t grey)
{
	if(preGUI_screen_state != GUI_screen_state){old_nan_LBLR = 0;}
	char buffer[9] = {0};
	uint8_t	delta_pos = 150, number = 0;
	uint32_t dec = 10;
	if(nope) 
		{	
			if(!old_nan_LBLR){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+40, Y, X+250, Y+26, TFT_Black_Bkgr);
				TFT_FillRectangle(X+40, Y+35, X+250, Y+59, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+117, Y, (uint8_t *)buffer, LEFT_MODE);
				TFT_DisplayString(X+117, Y+35, (uint8_t *)buffer, LEFT_MODE);
				old_nan_LBLR = 1;
			}
		}
	else{
				if(old_nan_LBLR){TFT_FillRectangle(X+40, Y, X+250, Y+26, TFT_Black_Bkgr);
				TFT_FillRectangle(X+40, Y+35, X+250, Y+59, TFT_Black_Bkgr);}
		
	old_nan_LBLR = 0;
	ValueLB = floor(ValueLB*100)/100.0;
	ValueLR = floor(ValueLR*100)/100.0;
	
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%.2f", ValueLB);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueLB/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_num_LB )
	{
		TFT_FillRectangle(X+40, Y, X+197, Y+25, TFT_Black_Bkgr);
	} 
	old_num_LB = number;
	number = 0;

	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
	
	sprintf (buffer, "%.2f", ValueLR);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueLR/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_num_LR )
	{
		TFT_FillRectangle(X+40, Y+33, X+197, Y+59, TFT_Black_Bkgr);
	} 
	old_num_LR = number;
	number = 0;

	TFT_DisplayString(X+delta_pos, Y+35, (uint8_t *)buffer, LEFT_MODE);
}
	TFT_SetFont(&Font26EN_arch_digit);

	TFT_SetTextColor(TFT_White);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+21, Y+12, 'B');
	TFT_DrawChar(X+21, Y+47, 'R');
	
	TFT_SetFont(&Font26EN_arch_big);
	TFT_DrawChar(X, Y+2, 'L'-33);
	TFT_DrawChar(X, Y+37, 'L'-33);
}

uint8_t old_num_SP = 10, old_nan_SP = 0;
void GUI_Text_S_P_Measure(uint16_t X, uint16_t Y, float Value, uint8_t nope, uint8_t grey)
{
		if(preGUI_screen_state != GUI_screen_state){old_nan_SP = 0;}
	char buffer[9] = {0};
	uint8_t	delta_pos = 100, number = 0;
	uint32_t dec = 10;
	
		if(nope) 
		{	
			if(!old_nan_SP){
				TFT_SetTextColor(TFT_White);
				TFT_SetBackColor(TFT_Black_Bkgr);
				TFT_SetFont(&Font26EN_arch_digit);
				TFT_FillRectangle(X+40, Y, X+250, Y+26, TFT_Black_Bkgr);
				buffer[0] = '-';buffer[1] = '-';
				TFT_DisplayString(X+117, Y, (uint8_t *)buffer, LEFT_MODE);
				old_nan_SP = 1;
			}
		}
	else{
	old_nan_SP = 0;
	
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%.4f", Value);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((Value/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_num_SP )
	{
		TFT_FillRectangle(X+40, Y, X+197, Y+25, TFT_Black_Bkgr);
	} 
	old_num_SP = number;

	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
}	
	TFT_SetTextColor(TFT_White);
	TFT_SetFont(&Font26EN_arch_digit);
	TFT_DrawChar(X+22, Y+2, '/');
	
	TFT_SetFont(&Font26EN_arch_big);
	TFT_DrawChar(X, Y+2, 'S'-33);
	TFT_DrawChar(X+46, Y+2, 'P'-33);
}

uint8_t old_num_L = 10, old_num_A = 10, old_num_B = 10, old_nan = 0;
void GUI_Text_LAB_Measure(uint16_t X, uint16_t Y, int16_t ValueL, int16_t ValueA, int16_t ValueB, uint8_t nope, uint8_t grey)
{
	char buffer[5] = {0};
	uint8_t	delta_pos = 180, sign = 0, number = 0;
	uint32_t dec = 10;
	
	if(ValueA <= -431 || nope){
		if(!old_nan){TFT_FillRectangle(X+40, Y, X+250, Y+95, TFT_Black_Bkgr);}
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black_Bkgr);
		TFT_SetFont(&Font26EN_arch_big);  TFT_DrawChar(X+135, Y, 'N'-33);TFT_DrawChar(X+160, Y, 'A'-33);TFT_DrawChar(X+185, Y, 'N'-33);
		TFT_DrawChar(X+135, Y+35, 'N'-33);TFT_DrawChar(X+160, Y+35, 'A'-33);TFT_DrawChar(X+185, Y+35, 'N'-33);
		TFT_DrawChar(X+135, Y+70, 'N'-33);TFT_DrawChar(X+160, Y+70, 'A'-33);TFT_DrawChar(X+185, Y+70, 'N'-33);
		old_nan = 1;
	} else{
	TFT_SetTextColor(grey ? TFT_Grey : TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_digit);
	
	if(ValueL < 0){ValueL *= -1; sign = 1;}
	
	sprintf (buffer, "%d", ValueL);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueL/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_num_L || old_nan == 1 )
	{
		TFT_FillRectangle(X+40, Y, X+250, Y+25, TFT_Black_Bkgr);
	} 
	old_num_L = number;
	number = 0;
	
	if(sign){TFT_DrawChar(X+delta_pos-18, Y, '-'); sign = 0;}
	TFT_DisplayString(X+delta_pos, Y, (uint8_t *)buffer, LEFT_MODE);
	delta_pos = 180;
	dec = 10;
			
	if(ValueA < 0){ValueA *= -1; sign = 1;}
			
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%d", ValueA);
		for (uint8_t i = 1; i <= 4; i++)
	{
		if((ValueA/(dec)) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_num_A || old_nan == 1 )
	{
		TFT_FillRectangle(X+40, Y+35, X+250, Y+62, TFT_Black_Bkgr);
	} 
	old_num_A = number;
	number = 0;
	
	if(sign){TFT_DrawChar(X+delta_pos-18, Y+35, '-'); sign = 0;}
			TFT_DisplayString(X+delta_pos, Y+35, (uint8_t *)buffer, LEFT_MODE);
	
		delta_pos = 180;
	 dec = 10;
	
	if(ValueB < 0){ValueB *= -1; sign = 1;}
	
	TFT_SetFont(&Font26EN_arch_digit);
	sprintf (buffer, "%d", ValueB);
	for (uint8_t i = 1; i <= 4; i++)
	{
		if(abs((ValueB/(dec))) >= 1.0)
		{
			dec *= 10;
			delta_pos-=23;
			number++;
		}
	}
	
	if(number < old_num_B || old_nan == 1)
	{
		TFT_FillRectangle(X+40, Y+70, X+250, Y+95, TFT_Black_Bkgr);
	} 
	old_num_B = number;
	number = 0;

		if(sign){TFT_DrawChar(X+delta_pos-18, Y+70, '-'); sign = 0;}
			TFT_DisplayString(X+delta_pos, Y+70, (uint8_t *)buffer, LEFT_MODE);
		old_nan = 0;
	} 
	
	if(preGUI_screen_state != GUI_screen_state || GUI_screen_state == Color_Screen){
			TFT_SetTextColor(TFT_White);
			TFT_SetFont(&Font26EN_arch_digit);
			TFT_DrawChar(X+17, Y, '*');
			TFT_DrawChar(X+17, Y+35, '*');
			TFT_DrawChar(X+17, Y+70, '*');
			TFT_SetFont(&Font26EN_arch_big);
			TFT_DrawChar(X, Y, 'L'-33);
			TFT_SetFont(&Font26EN_arch_small);
			TFT_DrawChar(X, Y+35, 'a'-65);
			TFT_DrawChar(X, Y+70, 'b'-65);}
}	
			

			

void GUI_Battery_Level(uint16_t X, uint16_t Y, double charge)
{
	char buffer[5] = {0};
	
	
	TFT_FillRectangle(X+10, Y+10, X+45, Y+26, TFT_Blue_Off); // big battery rect
	TFT_FillRectangle(X+45, Y+15, X+48, Y+20, TFT_Blue_Off); //small battery rect

		if(charge < 12)
		{
			TFT_FillRectangle(X+15, Y+12, X+19, Y+24, TFT_Red);
		}		
		if(charge >= 12)
		{
			TFT_FillRectangle(X+15, Y+12, X+19, Y+24, TFT_White);
		}		
		if(charge >= 25)
		{
			TFT_FillRectangle(X+22, Y+12, X+26, Y+24, TFT_White);
		}		
		if(charge >= 50)
		{
			TFT_FillRectangle(X+29, Y+12, X+33, Y+24, TFT_White);
		}
		if(charge >= 85)
		{
			TFT_FillRectangle(X+36, Y+12, X+40, Y+24, TFT_White);
		}
		
		sprintf (buffer, "%.1f%%", charge);
		TFT_SetFont(&Font8);
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black_Bkgr);
		TFT_DisplayString(X+52, Y+14, (uint8_t *)buffer, LEFT_MODE);

}

void GUI_Axes_Locus_XY(uint16_t X_center, uint16_t Y_center, uint8_t direction)
{
		TFT_FillRectangle(X_center-2, Y_center-XY2_LOCUS_BMP_SIZEY, X_center, Y_center, TFT_White); //Yline
		TFT_FillRectangle(X_center-2, Y_center+1, X_center+XY2_LOCUS_BMP_SIZEX, Y_center+3, TFT_White);//XLine
		
		TFT_DrawLine(X_center-5, Y_center-300/2, X_center+3, Y_center-300/2, TFT_White);
		TFT_DrawLine(X_center+295/2, Y_center-3, X_center+295/2, Y_center+6, TFT_White);
		
		TFT_SetFont(&Font6EN_arch_big);
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black_Bkgr);
		
		TFT_DrawChar(4,  Y_center-300/2-2, '.');
		TFT_DrawChar(0,  Y_center-300/2-2, '0');
		TFT_DrawChar(8,  Y_center-300/2-2, '5');
		
		TFT_DrawChar(X_center+295/2-6+4,  Y_center+6, '.');
		TFT_DrawChar(X_center+295/2-6+0,  Y_center+6, '0');
		TFT_DrawChar(X_center+295/2-6+8,  Y_center+6, '5');
}

void GUI_Axes_Locus_LUV(uint16_t X_center, uint16_t Y_center, uint8_t direction)
{
		TFT_FillRectangle(X_center-2, Y_center-LUV_LOCUS_BMP_SIZEY, X_center, Y_center, TFT_White); //Yline
		TFT_FillRectangle(X_center-2, Y_center+1, X_center+LUV_LOCUS_BMP_SIZEX, Y_center+3, TFT_White);//XLine
		
		TFT_DrawLine(X_center-5, Y_center-396/2, X_center+3, Y_center-396/2, TFT_White);
		TFT_DrawLine(X_center+403/2, Y_center-3, X_center+403/2, Y_center+6, TFT_White);
		
		TFT_SetFont(&Font6EN_arch_big);
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black_Bkgr);
		
		TFT_DrawChar(4,  Y_center-396/2-2, '.');
		TFT_DrawChar(0,  Y_center-396/2-2, '0');
		TFT_DrawChar(8,  Y_center-396/2-2, '5');
		
		TFT_DrawChar(X_center+403/2-6+4,  Y_center+6, '.');
		TFT_DrawChar(X_center+403/2-6+0,  Y_center+6, '0');
		TFT_DrawChar(X_center+403/2-6+8,  Y_center+6, '5');
}

void GUI_Axes_Locus_Lab(uint16_t X_center, uint16_t Y_center, uint8_t direction)
{
		TFT_FillRectangle(X_center-2-LAB_LOCUS_SIZEX/2, Y_center-1, X_center+LAB_LOCUS_SIZEX/2, Y_center+1, TFT_White); //
		TFT_FillRectangle(X_center-2, Y_center-LAB_LOCUS_SIZEY/2, X_center, Y_center+LAB_LOCUS_SIZEY/2, TFT_White);//
		

		TFT_SetFont(&Font6EN_arch_big);
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black_Bkgr);
	
		TFT_DrawChar(X_center-35+5,  Y_center-LAB_LOCUS_SIZEY/2, '+');
		TFT_DrawChar(X_center-35+10,  Y_center-LAB_LOCUS_SIZEY/2, '1');
		TFT_DrawChar(X_center-35+15,  Y_center-LAB_LOCUS_SIZEY/2, '2');
		TFT_DrawChar(X_center-35+21,  Y_center-LAB_LOCUS_SIZEY/2, '8');
		
		TFT_DrawChar(X_center-35+5,  Y_center+LAB_LOCUS_SIZEY/2-8, '-');
		TFT_DrawChar(X_center-35+10,  Y_center+LAB_LOCUS_SIZEY/2-8, '1');
		TFT_DrawChar(X_center-35+15,  Y_center+LAB_LOCUS_SIZEY/2-8, '2');
		TFT_DrawChar(X_center-35+21,  Y_center+LAB_LOCUS_SIZEY/2-8, '8');
		
		TFT_DrawChar(0,  Y_center-11, '-');
		TFT_DrawChar(5,  Y_center-11, '1');
		TFT_DrawChar(10,  Y_center-11, '2');
		TFT_DrawChar(16,  Y_center-11, '8');
		
		TFT_DrawChar(260-15,  Y_center-11, '+');
		TFT_DrawChar(260-10,  Y_center-11, '1');
		TFT_DrawChar(260-5,  Y_center-11, '2');
		TFT_DrawChar(260,  Y_center-11, '8');
		
		//		TFT_DrawLine(X_center-5, Y_center-LAB_LOCUS_SIZEY/4, X_center+3, Y_center-LAB_LOCUS_SIZEY/4, TFT_White);
//		TFT_DrawLine(X_center-5, Y_center+LAB_LOCUS_SIZEY/4, X_center+3, Y_center+LAB_LOCUS_SIZEY/4, TFT_White);
		
		TFT_DrawLine(X_center-5, Y_center-LAB_LOCUS_SIZEY/2, X_center+3, Y_center-LAB_LOCUS_SIZEY/2, TFT_White);
		TFT_DrawLine(X_center-5, Y_center+LAB_LOCUS_SIZEY/2, X_center+3, Y_center+LAB_LOCUS_SIZEY/2, TFT_White);
	
//		TFT_DrawLine(X_center-LAB_LOCUS_SIZEX/4, Y_center-3, X_center-LAB_LOCUS_SIZEX/4, Y_center+6, TFT_White);
//		TFT_DrawLine(X_center+LAB_LOCUS_SIZEX/4, Y_center-3, X_center+LAB_LOCUS_SIZEX/4, Y_center+6, TFT_White);
		
		TFT_DrawLine(X_center-LAB_LOCUS_SIZEX/2+1, Y_center-3, X_center-LAB_LOCUS_SIZEX/2+1, Y_center+6, TFT_White);
		TFT_DrawLine(X_center+LAB_LOCUS_SIZEX/2, Y_center-3, X_center+LAB_LOCUS_SIZEX/2, Y_center+6, TFT_White);
}
