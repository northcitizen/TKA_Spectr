#include "stdio.h"
#include "GUI_Text_Elements_EN.h"

volatile uint8_t TFT_direction;

void GUI_Text_CIE_XYZ(uint16_t X, uint16_t Y)
{
TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'I');
	TFT_DrawChar(X+27, Y, 'E');
	TFT_DrawChar(X+49, Y, 'X');
	TFT_DrawChar(X+65, Y, 'Y');
	TFT_DrawChar(X+81, Y, 'Z');
}

void GUI_Text_CIE_x_y(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'I');
	TFT_DrawChar(X+27, Y, 'E');
	TFT_DrawChar(X+58, Y, ',');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+49, Y+1, 'x');
	TFT_DrawChar(X+72, Y+1, 'y');
}

void GUI_Text_CIE_xy_1931(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'I');
	TFT_DrawChar(X+27, Y, 'E');
	TFT_DrawChar(X+58, Y, ',');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+49, Y+1, 'x');
	TFT_DrawChar(X+72, Y+1, 'y');
	TFT_SetFont(&Font16EN_arch_big);
	
	TFT_DrawChar(X+92, Y, '1');
	TFT_DrawChar(X+133, Y, '1');
	TFT_DrawChar(X+105, Y, '9');
	TFT_DrawChar(X+121, Y, '3');


}

void GUI_Text_CIE_xy_1964(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'I');
	TFT_DrawChar(X+27, Y, 'E');
	TFT_DrawChar(X+58, Y, ',');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+49, Y+1, 'x');
	TFT_DrawChar(X+72, Y+1, 'y');
	TFT_SetFont(&Font16EN_arch_big);
	
	TFT_DrawChar(X+92, Y, '1');
	TFT_DrawChar(X+105, Y, '9');
	TFT_DrawChar(X+120, Y, '6');
	TFT_DrawChar(X+135, Y, '4');
}



void GUI_Text_CIE_Luv(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'I');
	TFT_DrawChar(X+27, Y, 'E');
	TFT_DrawChar(X+49, Y, 'L');
	TFT_DrawChar(X+80, Y, '('-1);
	TFT_DrawChar(X+106, Y, '('-1);
	
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+68, Y+2, 'u');
	TFT_DrawChar(X+93, Y+2, 'v');
}

void GUI_Text_CIE_Lab(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'I');
	TFT_DrawChar(X+27, Y, 'E');
	TFT_DrawChar(X+49, Y, 'L');
	TFT_DrawChar(X+80, Y, '*');
	TFT_DrawChar(X+105, Y, '*');
	
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+68, Y+2, 'a');
	TFT_DrawChar(X+93, Y+2, 'b');
}

void GUI_Text_Bluetooth(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+13, Y+2, 'l');
	TFT_DrawChar(X+47, Y+2, 't');
	TFT_DrawChar(X+81, Y+2, 't');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'B');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+23, Y+2, 'u');
	TFT_DrawChar(X+36, Y+2, 'e');
	TFT_DrawChar(X+57, Y+2, 'o');
	TFT_DrawChar(X+70, Y+2, 'o');
	TFT_DrawChar(X+91, Y+2, 'h');
}

void GUI_Text_A(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'A');
}

void GUI_Text_D65(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'D');
	TFT_DrawChar(X+15, Y, '6');
	TFT_DrawChar(X+32, Y, '5');
}

void GUI_Text_C(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
}

void GUI_Text_D50(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'D');
	TFT_DrawChar(X+15, Y, '5');
	TFT_DrawChar(X+31, Y, '0');
}

void GUI_Text_D55(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'D');
	TFT_DrawChar(X+15, Y, '5');
	TFT_DrawChar(X+31, Y, '5');
}

void GUI_Text_D75(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'D');
	TFT_DrawChar(X+15, Y, '7');
	TFT_DrawChar(X+31, Y, '5');
}


void GUI_Text_CIE_xy(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'I');
	TFT_DrawChar(X+27, Y, 'E');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+49, Y+1, 'x');
	TFT_DrawChar(X+61, Y+1, 'y');
}

void GUI_Text_CRI(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+27, Y, 'I');
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'R');
}

void GUI_Text_CQS(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'Q');
	TFT_DrawChar(X+28, Y, 'S');
}



void GUI_Text_SP(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+13, Y, '/');
	TFT_DrawChar(X, Y, 'S');
	TFT_DrawChar(X+28, Y, 'P');
}



void GUI_Text_lambda_d(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, '~'+1);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+15, Y+7, 'd');
}

void GUI_Text_lambda_c(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, '~'+1);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+15, Y+7, 'c');
}

void GUI_Text_V_lambda(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	
	TFT_SetFont(&Font16EN_arch_big);

	TFT_DrawChar(X+13, Y, '(');
	TFT_DrawChar(X+40, Y, ')');
	TFT_DrawChar(X, Y, 'V');
	TFT_DrawChar(X+26, Y, '~'+1);
	TFT_DrawChar(X+53, Y, '/');
		
	TFT_DrawChar(X+80, Y, '('-1);
	TFT_DrawChar(X+90, Y, '(');
	TFT_DrawChar(X+117, Y, ')');
	TFT_DrawChar(X+68, Y, 'V');
	TFT_DrawChar(X+103, Y, '~'+1);
		
}

void GUI_Text_deltaE(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);

	TFT_DrawChar(X, Y, '~'+2);
	TFT_DrawChar(X+14, Y, 'E');
}

void GUI_TextEn_umol(uint16_t X, uint16_t Y, uint8_t deg)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font12EN_arch_small);
	
	if(deg){
			TFT_DrawChar(X, Y, 'm'-65);
	} else
	{
			TFT_DrawChar(X, Y, 'z'-64);
	}
	TFT_DrawChar(X+8, Y, 'm'-65);
	TFT_DrawChar(X+16, Y, 'o'-65);
	TFT_DrawChar(X+22, Y, 'l'-65);
	
	TFT_DrawLine(X, Y+10, X+25, Y+10, TFT_White);
	
	TFT_DrawChar(X+10, Y+11, 'z'-63);
	TFT_DrawChar(X+2, Y+11, 'm'-65);
	TFT_DrawRectangle(X+16, Y+14, X+17, Y+15, TFT_White);
	TFT_DrawChar(X+19, Y+11, 's'-65);
}

void GUI_TextEn_umol_sr(uint16_t X, uint16_t Y, uint8_t deg)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font12EN_arch_small);
	
	if(deg){
			TFT_DrawChar(X+9, Y, 'm'-65);
	} else
	{
			TFT_DrawChar(X+9, Y, 'z'-64);
	}
	TFT_DrawChar(X+17, Y, 'm'-65);
	TFT_DrawChar(X+25, Y, 'o'-65);
	TFT_DrawChar(X+31, Y, 'l'-65);
	
	TFT_DrawLine(X+3, Y+10, X+46, Y+10, TFT_White);
	
	TFT_DrawChar(X+13, Y+11, 'z'-63);
	TFT_DrawChar(X+5, Y+11, 'm'-65);
	TFT_DrawRectangle(X+19, Y+14, X+20, Y+15, TFT_White);
	TFT_DrawChar(X+22, Y+11, 's'-65);
	TFT_DrawRectangle(X+30, Y+14, X+36, Y+15, TFT_White);
	TFT_DrawChar(X+32, Y+11, 's'-65);
	TFT_DrawChar(X+39, Y+11, 'r'-65);
}

void GUI_TextEn_umol_Big(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+40, Y+23, 's');
	TFT_DrawChar(X, Y, 'z'+2);//μ
 	TFT_DrawChar(X+14, Y, 'm');
	TFT_DrawChar(X+28, Y, 'o');
	TFT_DrawChar(X+40, Y, 'l');

	TFT_DrawLine(X, Y+19, X+55, Y+19, TFT_White);

	TFT_DrawChar(X+13, Y+24, 'm');
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+28, Y+21, '2');
	TFT_DrawRectangle(X+40-5-1, Y+36-3-1, X+41-5-1, Y+37-3-1, TFT_White);

}

void GUI_TextEn_umol_Big_modeL(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+40-13-3, Y+23, 's');
	TFT_DrawChar(X+42, Y+23, 's');
	TFT_DrawChar(X+54, Y+23, 'r');
	TFT_DrawChar(X+5, Y, 'z'+2);//μ
 	TFT_DrawChar(X+14+5, Y, 'm');
	TFT_DrawChar(X+28+5, Y, 'o');
	TFT_DrawChar(X+40+6, Y, 'l');

	TFT_DrawLine(X, Y+19, X+55, Y+19, TFT_White);

	TFT_DrawChar(X, Y+24, 'm');
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+28-13, Y+21, '2');
	TFT_DrawRectangle(X+21, Y+32, X+22, Y+33, TFT_White);
	TFT_DrawRectangle(X+40, Y+32, X+41, Y+33, TFT_White);

}


void GUI_Text_On(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'O');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+16, Y+2, 'n');
	
}

void GUI_Text_Off(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+13, Y+2, 'f');
	TFT_DrawChar(X+23, Y+2, 'f');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'O');
}

void GUI_Text_EbEr(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+19, Y+2, ',');
	TFT_DrawChar(X, Y, 'E');
	TFT_DrawChar(X+32, Y, 'E');
	TFT_SetFont(&Font8);
	TFT_DrawChar(X+18, Y+12, 'B');
	TFT_DrawChar(X+50, Y+12, 'R');
}

void GUI_Text_LbLr(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+19, Y+2, ',');
	TFT_DrawChar(X, Y, 'L');
	TFT_DrawChar(X+30, Y, 'L');
	TFT_SetFont(&Font8);
	TFT_DrawChar(X+18, Y+12, 'B');
	TFT_DrawChar(X+48, Y+12, 'R');
}
///////////////////////////////////////////////////////////////////////
void GUI_TextEn_Language(uint16_t X, uint16_t Y)
{	/* Print word 'Language' */
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'L');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+14, Y+2, 'a');
	TFT_DrawChar(X+26, Y+2, 'n');
	TFT_DrawChar(X+39, Y+2, 'g');
	TFT_DrawChar(X+65, Y+2, 'a');
	TFT_DrawChar(X+52, Y+2, 'u');
	TFT_DrawChar(X+77, Y+2, 'g');
	TFT_DrawChar(X+90, Y+2, 'e');
}
void GUI_TextEn_English(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'E');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+16, Y+2, 'n');
	TFT_DrawChar(X+29, Y+2, 'g');
	TFT_DrawChar(X+42, Y+2, 'l');
	TFT_DrawChar(X+47, Y+2, 'i');
	TFT_DrawChar(X+53, Y+2, 's');
	TFT_DrawChar(X+65, Y+2, 'h');
	

}
void GUI_TextEn_Info(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'I');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+18, Y+2, 'f');
	TFT_DrawChar(X+8, Y+2, 'n');
	TFT_DrawChar(X+29, Y+2, 'o');
}
void GUI_TextEn_Radiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'R');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+16, Y+2, 'a');
	TFT_DrawChar(X+28, Y+2, 'd');
	TFT_DrawChar(X+41, Y+2, 'i');
	TFT_DrawChar(X+46, Y+2, 'a');
	TFT_DrawChar(X+58, Y+2, 'n');
	TFT_DrawChar(X+71, Y+2, 'c');
	TFT_DrawChar(X+83, Y+2, 'e');
}
void GUI_TextEn_Irradiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'I');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+9, Y+2, 'r');
	TFT_DrawChar(X+21, Y+2, 'r');
	TFT_DrawChar(X+32, Y+2, 'a');
	TFT_DrawChar(X+44, Y+2, 'd');
	TFT_DrawChar(X+57, Y+2, 'i');
	TFT_DrawChar(X+62, Y+2, 'a');
	TFT_DrawChar(X+74, Y+2, 'n');
	TFT_DrawChar(X+87, Y+2, 'c');
	TFT_DrawChar(X+99, Y+2, 'e');
}

void GUI_TextMsgEn_HighIrradiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'H');
	TFT_SetFont(&Font16EN_arch_small_A);
  TFT_DrawChar(X+16, Y+2, 'i');
  TFT_DrawChar(X+23, Y+2, 'g');
  TFT_DrawChar(X+36, Y+2, 'h');
  
  TFT_DrawChar(X+59, Y+2, 'i');
  TFT_DrawChar(X+67, Y+2, 'r');
  TFT_DrawChar(X+79, Y+2, 'r');
  TFT_DrawChar(X+90, Y+2, 'a');
  TFT_DrawChar(X+102, Y+2, 'd');
  TFT_DrawChar(X+115, Y+2, 'i');
  TFT_DrawChar(X+120, Y+2, 'a');
  TFT_DrawChar(X+132, Y+2, 'n');
  TFT_DrawChar(X+145, Y+2, 'c');
  TFT_DrawChar(X+157, Y+2, 'e');
}

void GUI_TextMsgEn_HighRadiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'H');
	TFT_SetFont(&Font16EN_arch_small_A);
  TFT_DrawChar(X+16, Y+2, 'i');
  TFT_DrawChar(X+23, Y+2, 'g');
  TFT_DrawChar(X+36, Y+2, 'h');
  
  TFT_DrawChar(X+59, Y+2, 'r');
  TFT_DrawChar(X+70, Y+2, 'a');
  TFT_DrawChar(X+82, Y+2, 'd');
  TFT_DrawChar(X+95, Y+2, 'i');
  TFT_DrawChar(X+100, Y+2, 'a');
  TFT_DrawChar(X+112, Y+2, 'n');
  TFT_DrawChar(X+125, Y+2, 'c');
  TFT_DrawChar(X+137, Y+2, 'e');
}

void GUI_TextMsgEn_LowRadiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'L');
	TFT_SetFont(&Font16EN_arch_small_A);
  TFT_DrawChar(X+16, Y+2, 'o');
  TFT_DrawChar(X+29, Y+2, 'w');
  
  TFT_DrawChar(X+54, Y+2, 'r');
  TFT_DrawChar(X+65, Y+2, 'a');
  TFT_DrawChar(X+77, Y+2, 'd');
  TFT_DrawChar(X+90, Y+2, 'i');
  TFT_DrawChar(X+95, Y+2, 'a');
  TFT_DrawChar(X+107, Y+2, 'n');
  TFT_DrawChar(X+120, Y+2, 'c');
  TFT_DrawChar(X+132, Y+2, 'e');
}

void GUI_TextMsgEn_LowIrradiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'L');
	TFT_SetFont(&Font16EN_arch_small_A);
  TFT_DrawChar(X+16, Y+2, 'o');
  TFT_DrawChar(X+29, Y+2, 'w');
	
  TFT_DrawChar(X+55, Y+2, 'i');
  TFT_DrawChar(X+63, Y+2, 'r');
  TFT_DrawChar(X+75, Y+2, 'r');
  TFT_DrawChar(X+86, Y+2, 'a');
  TFT_DrawChar(X+98, Y+2, 'd');
  TFT_DrawChar(X+111, Y+2, 'i');
  TFT_DrawChar(X+116, Y+2, 'a');
  TFT_DrawChar(X+128, Y+2, 'n');
  TFT_DrawChar(X+141, Y+2, 'c');
  TFT_DrawChar(X+153, Y+2, 'e');
	
	
}
void GUI_TextEn_Luminance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'L');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+13, Y+2, 'u');
	TFT_DrawChar(X+27, Y+2, 'm');
	TFT_DrawChar(X+41, Y+2, 'i');
	TFT_DrawChar(X+59, Y+2, 'a');
	TFT_DrawChar(X+46, Y+2, 'n');
	TFT_DrawChar(X+71, Y+2, 'n');
	TFT_DrawChar(X+84, Y+2, 'c');
	TFT_DrawChar(X+96, Y+2, 'e');
}

void GUI_TextEn_Illuminance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'I');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+8, Y+2, 'l');
	TFT_DrawChar(X+13, Y+2, 'l');
	TFT_DrawChar(X+18, Y+2, 'u');
	TFT_DrawChar(X+32, Y+2, 'm');
	TFT_DrawChar(X+46, Y+2, 'i');
	TFT_DrawChar(X+64, Y+2, 'a');
	TFT_DrawChar(X+51, Y+2, 'n');
	TFT_DrawChar(X+76, Y+2, 'n');
	TFT_DrawChar(X+89, Y+2, 'c');
	TFT_DrawChar(X+101, Y+2, 'e');
}
void GUI_TextEn_Mode(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'M');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+19, Y+2, 'o');
	TFT_DrawChar(X+30, Y+2, 'd');
	TFT_DrawChar(X+43, Y+2, 'e');
}

void GUI_TextEN_LxFl(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y+5, 'L');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+15, Y+7, 'x');
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X+28, Y+5, '/');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+46, Y+7, 'f');
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X+59, Y+5, 'L');
}

void GUI_TextEn_PPFD(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X+48, Y, 'D');
	TFT_DrawChar(X+31, Y, 'F');
	TFT_DrawChar(X+16, Y, 'P');
	TFT_DrawChar(X, Y, 'P');
}
void GUI_TextEn_PPL(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X+31, Y, 'L');
	TFT_DrawChar(X+16, Y, 'P');
	TFT_DrawChar(X, Y, 'P');
}
void GUI_TextEn_PARwavebands(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X+32, Y, 'R');
	TFT_DrawChar(X+16, Y, 'A');
	TFT_DrawChar(X, Y, 'P');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+75, Y+2, 'a');
	TFT_DrawChar(X+60, Y+2, 'w');
	TFT_DrawChar(X+101, Y+2, 'e');
	TFT_DrawChar(X+87, Y+2, 'v');
	TFT_DrawChar(X+126, Y+2, 'a');
	TFT_DrawChar(X+113, Y+2, 'b');
	TFT_DrawChar(X+138, Y+2, 'n');
	TFT_DrawChar(X+151, Y+2, 'd');
	TFT_DrawChar(X+165, Y+2, 's');
}
void GUI_TextEn_B_G_R_FR(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X+15, Y, '-');
	TFT_DrawChar(X, Y, 'B');
	TFT_DrawChar(X+44, Y, '-');
	TFT_DrawChar(X+29, Y, 'G');
	TFT_DrawChar(X+74, Y, '-');
	TFT_DrawChar(X+59, Y, 'R');	
	TFT_DrawChar(X+87, Y, 'F');
	TFT_DrawChar(X+103, Y, 'R');
}
void GUI_TextEn_Tc(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'T');
	TFT_SetFont(&Font11EN_arch_big);
	TFT_DrawChar(X+14, Y+7, 'C');
}
void GUI_TextEn_LB(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'L');
	TFT_SetFont(&Font11EN_arch_big);
	TFT_DrawChar(X+17, Y+7, 'B');
}
void GUI_TextEn_LR(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'L');
	TFT_SetFont(&Font11EN_arch_big);
	TFT_DrawChar(X+17, Y+7, 'R');
}
void GUI_TextEn_CCT(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font26EN_arch_big);
	TFT_DrawChar(X, Y, 'C'-33);
	TFT_DrawChar(X+23, Y, 'C'-33);
	TFT_DrawChar(X+46, Y, 'T'-33);
}

/* Measure dimensions */
void GUI_TextEn_W_m2(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X+3, Y, 'W');
	TFT_DrawChar(X+1, Y+17, 'm');
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+11, Y+16, '2');	
  TFT_DrawLine(X, Y+14, X+17, Y+14, TFT_White);
}

void GUI_TextEn_mW_m2_Big(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'm');
	TFT_DrawChar(X+17, Y, 'W');
	TFT_DrawChar(X+13, Y+24, 'm');
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+28, Y+21, '2');
	TFT_DrawLine(X, Y+19, X+39, Y+19, TFT_White);
}

void GUI_TextEn_mW_m2_Big_modeL(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+5, Y, 'm');
	TFT_DrawChar(X+17+5, Y, 'W');
	TFT_DrawChar(X+20, Y+24, 's');
	TFT_DrawChar(X+35, Y+24, 'r');
	TFT_DrawChar(X+13-12, Y+24, 'm');
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+28-12, Y+21, '2');
	TFT_DrawLine(X, Y+19, X+39+5, Y+19, TFT_White);
	TFT_DrawRectangle(X+19, Y+34, X+20, Y+34, TFT_White);
}

void GUI_TextEn_mW_m2(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X-3, Y, 'm');
	TFT_DrawChar(X+7, Y, 'W');
	TFT_DrawChar(X+1, Y+17, 'm');
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+11, Y+16, '2');
	TFT_DrawLine(X, Y+14, X+17, Y+14, TFT_White);
}

void GUI_TextEn_W_m2_sr(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X+12, Y, 'W');
	TFT_DrawChar(X+20, Y+17, 'm');
	TFT_DrawChar(X, Y+17, 's');
	TFT_DrawChar(X+7, Y+17, 'r');
	TFT_FillRectangle(X+17,Y+23,X+18,Y+24,TFT_White);
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+30, Y+16, '2');	
  TFT_DrawLine(X, Y+14, X+36, Y+14, TFT_White);
}

void GUI_TextEn_mW_m2_sr(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X+6, Y, 'm');
	TFT_DrawChar(X+16, Y, 'W');
	TFT_DrawChar(X+20, Y+17, 'm');
	TFT_DrawChar(X, Y+17, 's');
	TFT_DrawChar(X+7, Y+17, 'r');
	TFT_FillRectangle(X+17,Y+23,X+18,Y+24,TFT_White);
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+30, Y+16, '2');
  TFT_DrawLine(X, Y+14, X+36, Y+14, TFT_White);
}
void GUI_TextEn_cd_m2(uint16_t X, uint16_t Y, uint8_t deg)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font9EN_arch_big);
	
	if (deg==1)
	{
		TFT_DrawChar(X, Y, 'k');
		TFT_DrawChar(X+7, Y, 'c');
		TFT_DrawChar(X+14, Y, 'd');
		
		TFT_DrawChar(X+5, Y+17, 'm');
		TFT_SetFont(&Font6EN_arch_big);
		TFT_DrawChar(X+15, Y+16, '2');	
		TFT_DrawLine(X, Y+14, X+22, Y+14, TFT_White);
	}
	else
	{
		TFT_DrawChar(X+2, Y, 'c');
		TFT_DrawChar(X+9, Y, 'd');
		
		TFT_DrawChar(X+2, Y+17, 'm');
		TFT_SetFont(&Font6EN_arch_big);
		TFT_DrawChar(X+12, Y+16, '2');	
		TFT_DrawLine(X, Y+14, X+19, Y+14, TFT_White);
	}
}
void GUI_TextEn_mol_s_m2(uint16_t X, uint16_t Y, uint8_t deg)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	
	TFT_SetFont(&Font12RU_arch_small);
	TFT_DrawCharRus(X+7, Y, '�'+1);
	
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X+4, Y, 'm');
	TFT_DrawChar(X+13, Y, 'o');
	TFT_DrawChar(X+20, Y, 'l');
	TFT_DrawChar(X+13, Y+17, 'm');
	TFT_DrawChar(X, Y+17, 's');
	TFT_FillRectangle(X+10,Y+23,X+11,Y+24,TFT_White);
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+23, Y+16, '2');

  TFT_DrawLine(X, Y+14, X+30, Y+14, TFT_White);	
}
void GUI_TextEn_Green(uint16_t X, uint16_t Y)
{
		TFT_SetFont(&Font16EN_arch_big);
		TFT_DrawChar(X, Y, 'G');
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(X+15, Y+2, 'r');
		TFT_DrawChar(X+26, Y+2, 'e');
		TFT_DrawChar(X+38, Y+2, 'e');
		TFT_DrawChar(X+50, Y+2, 'n');
}
void GUI_TextEn_Blue(uint16_t X, uint16_t Y)
{
		TFT_SetFont(&Font16EN_arch_big);
		TFT_DrawChar(X, Y, 'B');
		TFT_SetFont(&Font16EN_arch_small_A);
		TFT_DrawChar(X+15, Y+2, 'l');
		TFT_DrawChar(X+20, Y+2, 'u');
		TFT_DrawChar(X+33, Y+2, 'e');
}
void GUI_TextEn_Red(uint16_t X, uint16_t Y)
{
		TFT_SetFont(&Font16EN_arch_big);
		TFT_DrawChar(X, Y, 'R');
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(X+16, Y+2, 'e');
		TFT_DrawChar(X+29, Y+2, 'd');
}

void GUI_TextEn_WriteSD(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'W');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+17, Y+2, 'r');
	TFT_DrawChar(X+28, Y+2, 'i');
	TFT_DrawChar(X+41, Y+2, 't');
	TFT_DrawChar(X+53, Y+2, 'e');
}


void GUI_TextEn_Info_Callibration(uint16_t X, uint16_t Y, uint8_t date, uint8_t month, uint16_t year)
{
	char buffer[5] = {0};
	
	X = 70;
	Y = 100;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+16, Y+2, 'a');
	TFT_DrawChar(X+29, Y+2, 'l');
	TFT_DrawChar(X+38, Y+2, 'i');
	TFT_DrawChar(X+50, Y+2, 'b');
	TFT_DrawChar(X+63, Y+2, 'r');
	TFT_DrawChar(X+76, Y+2, 'a');
	TFT_DrawChar(X+89, Y+2, 't');
	TFT_DrawChar(X+97, Y+2, 'i');
	TFT_DrawChar(X+108, Y+2, 'o');
	TFT_DrawChar(X+120, Y+2, 'n');
	
	sprintf (buffer, "%02u",  date);
	TFT_SetFont(&Font26EN_arch_digit);
	buffer[2] = '.';
	TFT_DisplayString(30, Y+30, (uint8_t *)buffer, LEFT_MODE);
	
	sprintf (buffer, "%02u",  month);
	buffer[2] = '.';
	TFT_DisplayString(30+60, Y+30, (uint8_t *)buffer, LEFT_MODE);
	
	sprintf (buffer, "%4u",  year);
	TFT_DisplayString(30+125, Y+30, (uint8_t *)buffer, LEFT_MODE);
}

void GUI_TextEn_Info_Serial(uint16_t X, uint16_t Y, uint16_t Part, uint16_t Number)
{
	char buffer[5] = {0};
	
	X = 60;
	Y = 200;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'S');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+17, Y+2, 'e');
	TFT_DrawChar(X+30, Y+2, 'r');
	TFT_DrawChar(X+42, Y+2, 'i');
	TFT_DrawChar(X+54, Y+2, 'a');
	TFT_DrawChar(X+67, Y+2, 'l');
	TFT_DrawChar(X+89, Y+2, 'n');
	TFT_DrawChar(X+102, Y+2, 'u');
	TFT_DrawChar(X+115, Y+2, 'm');
	TFT_DrawChar(X+128, Y+2, 'b');
	TFT_DrawChar(X+141, Y+2, 'e');
	TFT_DrawChar(X+154, Y+2, 'r');

	
	sprintf (buffer, "%u",  Part);
	TFT_SetFont(&Font26EN_arch_digit);
	TFT_DisplayString(40, Y+30, (uint8_t *)buffer, LEFT_MODE);
	sprintf (buffer, "%04u",  Number);
	TFT_DisplayString(135, Y+30, (uint8_t *)buffer, LEFT_MODE);
}

void GUI_TextEn_Info_Ver(uint16_t X, uint16_t Y, float Version)
{
	char buffer[5] = {0};
	
	X = 20;
	Y = 350;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16EN_arch_big);
	
	TFT_DrawChar(X, Y, 'F');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+16, Y+2, 'i');
	TFT_DrawChar(X+27, Y+2, 'r');
	TFT_DrawChar(X+40, Y+2, 'm');
	TFT_DrawChar(X+55, Y+2, 'w');
	TFT_DrawChar(X+70, Y+2, 'a');
	TFT_DrawChar(X+86, Y+2, 'r');
	TFT_DrawChar(X+99, Y+2, 'e');
	
	TFT_SetFont(&Font16);
	TFT_DrawChar(X+152, Y, '.');
	TFT_DrawChar(X+142, Y, 'v');
	
	sprintf (buffer, "%.1f",  Version);
	TFT_SetFont(&Font16);
	TFT_DisplayString(X+172, Y, (uint8_t *)buffer, LEFT_MODE);
}

void GUI_TextEn_CRI_no(uint16_t X, uint16_t Y, uint8_t direction)
{//CRI/CQS can not be calculated
	if (direction == 0x00)
	{
		TFT_SetFont(&Font11EN_arch_big);
		TFT_DrawChar(X + 5 + 10, Y + 5, 'C');
		TFT_DrawChar(X + 17 + 10, Y + 5, 'R');
		TFT_DrawChar(X + 29 + 10, Y + 5, 'I');
		TFT_DrawChar(X + 41 + 10, Y + 5, '/');
		TFT_DrawChar(X + 53 + 10, Y + 5, 'C');
		TFT_DrawChar(X + 65 + 10, Y + 5, 'Q');
		TFT_DrawChar(X + 77 + 10, Y + 5, 'S');

		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black);
		TFT_SetFont(&Font12EN_arch_small);
		TFT_DrawChar(X + 101 + 10, Y + 5, 'c' - 65);
		TFT_DrawChar(X + 113 + 10, Y + 5, 'a' - 65);
		TFT_DrawChar(X + 125 + 10, Y + 5, 'n' - 65);

		TFT_DrawChar(X + 149 + 10, Y + 5, 'n' - 65);
		TFT_DrawChar(X + 161 + 10, Y + 5, 'o' - 65);
		TFT_DrawChar(X + 173 + 10, Y + 5, 't' - 65);

		TFT_DrawChar(X + 197 + 10, Y + 5, 'b' - 65);
		TFT_DrawChar(X + 209 + 10, Y + 5, 'e' - 65);

		TFT_DrawChar(X + 133 - 50, Y + 20, 'c' - 65);
		TFT_DrawChar(X + 145 - 50, Y + 20, 'a' - 65);
		TFT_DrawChar(X + 157 - 50, Y + 20, 'l' - 65);
		TFT_DrawChar(X + 169 - 50, Y + 20, 'c' - 65);
		TFT_DrawChar(X + 181 - 50, Y + 20, 'u' - 65);
		TFT_DrawChar(X + 193 - 50, Y + 20, 'l' - 65);
		TFT_DrawChar(X + 205 - 50, Y + 20, 'a' - 65);
		TFT_DrawChar(X + 217 - 50, Y + 20, 't' - 65);
		TFT_DrawChar(X + 229 - 50, Y + 20, 'e' - 65);
		TFT_DrawChar(X + 241 - 50, Y + 20, 'd' - 65);
	}else if (direction != 0x00)
	{
		if(direction == 0x01){TFT_direction = 0x01;}
			else {TFT_direction = 0x02;}
		TFT_SetFont(&Font11EN_arch_big);
		TFT_DrawChar(X + 85, Y - 87, 'C');
		TFT_DrawChar(X + 97, Y - 87, 'R');
		TFT_DrawChar(X + 109, Y - 87, 'I');
		TFT_DrawChar(X + 121, Y - 87, '/');
		TFT_DrawChar(X + 133, Y - 87, 'C');
		TFT_DrawChar(X + 145, Y - 87, 'Q');
		TFT_DrawChar(X + 157, Y - 87, 'S');

		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black);
		TFT_SetFont(&Font12EN_arch_small);
		TFT_DrawChar(X + 181, Y - 87, 'c' - 65);
		TFT_DrawChar(X + 193, Y - 87, 'a' - 65);
		TFT_DrawChar(X + 205, Y - 87, 'n' - 65);

		TFT_DrawChar(X + 229, Y - 87, 'n' - 65);
		TFT_DrawChar(X + 241, Y - 87, 'o' - 65);
		TFT_DrawChar(X + 253, Y - 87, 't' - 65);

		TFT_DrawChar(X + 277, Y - 87, 'b' - 65);
		TFT_DrawChar(X + 289, Y - 87, 'e' - 65);

		TFT_DrawChar(X + 133, Y - 70, 'c' - 65);
		TFT_DrawChar(X + 145, Y - 70, 'a' - 65);
		TFT_DrawChar(X + 157, Y - 70, 'l' - 65);
		TFT_DrawChar(X + 169, Y - 70, 'c' - 65);
		TFT_DrawChar(X + 181, Y - 70, 'u' - 65);
		TFT_DrawChar(X + 193, Y - 70, 'l' - 65);
		TFT_DrawChar(X + 205, Y - 70, 'a' - 65);
		TFT_DrawChar(X + 217, Y - 70, 't' - 65);
		TFT_DrawChar(X + 229, Y - 70, 'e' - 65);
		TFT_DrawChar(X + 241, Y - 70, 'd' - 65);
		TFT_direction = 0x00;
	}
}
