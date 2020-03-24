#include "stdio.h"
#include "GUI_Text_Elements_EN.h"


void GUI_Text_CIE_XYZ(uint16_t X, uint16_t Y)
{
TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_DrawChar(X+135, Y, '9');
}



void GUI_Text_CIE_Luv(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'A');
}

void GUI_Text_D65(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'D');
	TFT_DrawChar(X+15, Y, '6');
	TFT_DrawChar(X+32, Y, '5');
}

void GUI_Text_C(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
}

void GUI_Text_D50(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'D');
	TFT_DrawChar(X+15, Y, '5');
	TFT_DrawChar(X+31, Y, '0');
}

void GUI_Text_D55(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'D');
	TFT_DrawChar(X+15, Y, '5');
	TFT_DrawChar(X+31, Y, '5');
}

void GUI_Text_D75(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'D');
	TFT_DrawChar(X+15, Y, '7');
	TFT_DrawChar(X+31, Y, '5');
}


void GUI_Text_CIE_xy(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+27, Y, 'I');
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'R');
}

void GUI_Text_CQS(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'C');
	TFT_DrawChar(X+13, Y, 'Q');
	TFT_DrawChar(X+28, Y, 'S');
}



void GUI_Text_SP(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+13, Y, '/');
	TFT_DrawChar(X, Y, 'S');
	TFT_DrawChar(X+28, Y, 'P');
}



void GUI_Text_lambda_d(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, '~'+1);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+15, Y+7, 'd');
}

void GUI_Text_lambda_c(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, '~'+1);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+15, Y+7, 'c');
}

void GUI_Text_V_lambda(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	
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
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);

	TFT_DrawChar(X, Y, '~'+2);
	TFT_DrawChar(X+14, Y, 'E');
}

void GUI_TextEn_umol(uint16_t X, uint16_t Y, uint8_t deg)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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

void GUI_Text_On(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'O');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+16, Y+2, 'n');
	
}

void GUI_Text_Off(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+13, Y+2, 'f');
	TFT_DrawChar(X+23, Y+2, 'f');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'O');
}

void GUI_Text_EbEr(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
void GUI_TextEn_Luminance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'M');
	TFT_SetFont(&Font16EN_arch_small_A);
	TFT_DrawChar(X+19, Y+2, 'o');
	TFT_DrawChar(X+30, Y+2, 'd');
	TFT_DrawChar(X+43, Y+2, 'e');
}
/*void GUI_TextEn_BlueTooth(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_Blue);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, Y, 'B');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+16, Y+2, 'l');
	TFT_DrawChar(X+21, Y+2, 'u');
	TFT_DrawChar(X+34, Y+2, 'e');
		TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+46, Y, 'T');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+62, Y+2, 'o');
	TFT_DrawChar(X+74, Y+2, 'o');
	TFT_DrawChar(X+85, Y+2, 't');
	TFT_DrawChar(X+92, Y+2, 'h');
}
*/
void GUI_TextEn_PPFD(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X+48, Y, 'D');
	TFT_DrawChar(X+31, Y, 'F');
	TFT_DrawChar(X+16, Y, 'P');
	TFT_DrawChar(X, Y, 'P');
}
void GUI_TextEn_PPL(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X+31, Y, 'L');
	TFT_DrawChar(X+16, Y, 'P');
	TFT_DrawChar(X, Y, 'P');
}
void GUI_TextEn_PARwavebands(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'T');
	TFT_SetFont(&Font11EN_arch_big);
	TFT_DrawChar(X+14, Y+7, 'C');
}
void GUI_TextEn_LB(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'L');
	TFT_SetFont(&Font11EN_arch_big);
	TFT_DrawChar(X+17, Y+7, 'B');
}
void GUI_TextEn_LR(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big_A);
	TFT_DrawChar(X, Y, 'L');
	TFT_SetFont(&Font11EN_arch_big);
	TFT_DrawChar(X+17, Y+7, 'R');
}
void GUI_TextEn_CCT(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font26EN_arch_big);
	TFT_DrawChar(X, Y, 'C'-33);
	TFT_DrawChar(X+23, Y, 'C'-33);
	TFT_DrawChar(X+46, Y, 'T'-33);
}

/* Measure dimensions */
void GUI_TextEn_W_m2(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X+3, Y, 'W');
	TFT_DrawChar(X+1, Y+17, 'm');
	TFT_SetFont(&Font6EN_arch_big);
	TFT_DrawChar(X+11, Y+16, '2');	
  TFT_DrawLine(X, Y+14, X+17, Y+14, TFT_White);
}
void GUI_TextEn_W_m2_sr(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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
void GUI_TextEn_cd_m2(uint16_t X, uint16_t Y, uint8_t deg)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
	
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

void GUI_TextEn_Info_Callibration(uint16_t X, uint16_t Y, uint8_t date, uint8_t month, uint16_t year)
{
	char buffer[5] = {0};
	
	X = 70;
	Y = 100;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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
	TFT_SetBackColor(TFT_Black_Bkgr);
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