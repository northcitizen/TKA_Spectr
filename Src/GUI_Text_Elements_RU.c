#include "stdio.h"
#include "GUI_Text_Elements_RU.h"

extern volatile uint8_t TFT_direction;

void GUI_TitleString_Name(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(0x0084);
	
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X, 		Y, 'T');
	TFT_DrawChar(X+15, 	Y, 'K');
	TFT_DrawChar(X+30, 	Y, 'A');
	TFT_DrawChar(X+45, 	Y, '-');
	TFT_DrawChar(X+60, 	Y, 'S');
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X+75, 	Y, 'p');
	TFT_DrawChar(X+88, 	Y, 'e');
	TFT_DrawChar(X+99, 	Y, 'c');
	TFT_DrawChar(X+109, 	Y, 't');
	TFT_DrawChar(X+120, 	Y, 'r');
}

void GUI_TitleString_Version(uint16_t X, uint16_t Y, float Version)
{
	char buffer[5] = {0};
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(0x0084);
	TFT_SetFont(&Font16EN_arch_small);
	TFT_DrawChar(X, 		Y, 'v');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+13, 		Y, '.');
	sprintf (buffer, "%.1f",  Version);
	TFT_SetFont(&Font16);
	TFT_DisplayString(X+24, Y, (uint8_t *)buffer, LEFT_MODE);
}

void GUI_TextRu_Language(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Я');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+15, Y+5, 'з');
	TFT_DrawCharRus(X+28, Y+5, 'ы');
	TFT_DrawCharRus(X+41, Y+5, 'к');
}

void GUI_TextRu_Russian(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Р');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+15, Y+5, 'у');
	TFT_DrawCharRus(X+28, Y+5, 'с');
	TFT_DrawCharRus(X+40, Y+5, 'с');
	TFT_DrawCharRus(X+52, Y+5, 'к');
	TFT_DrawCharRus(X+64, Y+5, 'и');
	TFT_DrawCharRus(X+77, Y+5, 'й');
}



void GUI_TextRu_Info(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'И');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+15, Y+5, 'н');
	TFT_DrawCharRus(X+28, Y+5, 'ф');
	TFT_DrawCharRus(X+41, Y+5, 'о');
	TFT_DrawCharRus(X+53, Y+5, 'р');
	TFT_DrawCharRus(X+65, Y+5, 'м');
	TFT_DrawCharRus(X+78, Y+5, 'а');
	TFT_DrawCharRus(X+90, Y+5, 'ц');
	TFT_DrawCharRus(X+102, Y+5, 'и');
	TFT_DrawCharRus(X+114, Y+5, 'я');
	TFT_DrawCharRus(X+126, Y+5, 0x01);
	TFT_DrawCharRus(X+138, Y+5, 'о');
	TFT_DrawCharRus(X+150, Y+5, 0x01);
	TFT_DrawCharRus(X+162, Y+5, 'п');
	TFT_DrawCharRus(X+174, Y+5, 'р');
	TFT_DrawCharRus(X+186, Y+5, 'и');
	TFT_DrawCharRus(X+198, Y+5, 'б');
	TFT_DrawCharRus(X+210, Y+5, 'о');
	TFT_DrawCharRus(X+222, Y+5, 'р');
	TFT_DrawCharRus(X+234, Y+5, 'е');
}

void GUI_TextRu_Mode(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Р');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+15, Y+5, 'е');
	TFT_DrawCharRus(X+28, Y+5, 'ж');
	TFT_DrawCharRus(X+41, Y+5, 'и');
	TFT_DrawCharRus(X+54, Y+5, 'м');
}

void GUI_TextRu_LxFl(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Л');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+15, Y+5, 'к');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+28, Y+5, '/');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+46, Y+5, 'ф');
	TFT_DrawCharRus(X+59, Y+5, 'у');
	TFT_DrawCharRus(X+73, Y+5, 'т');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+87, Y, '-');
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X+104, Y, 'Л');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+118, Y+5, 'б');
}

void GUI_TextRu_Illuminance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'О');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+15, Y+5, 'с');
	TFT_DrawCharRus(X+26, Y+5, 'в');
	TFT_DrawCharRus(X+38, Y+5, 'е');
	TFT_DrawCharRus(X+50, Y+5, 'щ');
	TFT_DrawCharRus(X+62, Y+5, 'е');
	TFT_DrawCharRus(X+73, Y+5, 'н');
	TFT_DrawCharRus(X+85, Y+5, 'н');
	TFT_DrawCharRus(X+97, Y+5, 'о');
	TFT_DrawCharRus(X+109, Y+5, 'с');
	TFT_DrawCharRus(X+118, Y+5, 'т');
	TFT_DrawCharRus(X+130, Y+5, 'ь');
}

void GUI_TextRu_PPF(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Ф');
	TFT_DrawCharRus(X+17, Y, 'А');
	TFT_DrawCharRus(X+32, Y, 'Р');
}

void GUI_TextRu_PPF_RGB(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'С');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+15, Y+5, 'и');
	TFT_DrawCharRus(X+27, Y+5, 'н');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+40, Y, '-');
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X+55, Y, 'З');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+70, Y+5, 'е');
	TFT_DrawCharRus(X+82, Y+5, 'л');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+94, Y, '-');
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X+109, Y, 'К');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+124, Y+5, 'р');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+136, Y, '-');
	TFT_DrawChar(X+152, Y, 'F');
	TFT_DrawChar(X+167, Y, 'R');
}
void GUI_TextRu_PPF_bands(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Ф');
	TFT_DrawCharRus(X+17, Y, 'А');
	TFT_DrawCharRus(X+32, Y, 'Р');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+57, Y+2, 'д');
	TFT_DrawCharRus(X+70, Y+2, 'и');
	TFT_DrawCharRus(X+83, Y+2, 'а');
	TFT_DrawCharRus(X+96, Y+2, 'п');
	TFT_DrawCharRus(X+109, Y+2, 'а');
	TFT_DrawCharRus(X+122, Y+2, 'з');
	TFT_DrawCharRus(X+135, Y+2, 'о');
	TFT_DrawCharRus(X+148, Y+2, 'н');
	TFT_DrawCharRus(X+162, Y+2, 'ы');
}

void GUI_TextRu_Info_Callibration(uint16_t X, uint16_t Y, uint8_t date, uint8_t month, uint16_t year)
{
	char buffer[5] = {0};
	
	X = 70;
	Y = 100;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y-4, 'К');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+17, Y+2, 'а');
	TFT_DrawCharRus(X+30, Y+2, 'л');
	TFT_DrawCharRus(X+43, Y+2, 'и');
	TFT_DrawCharRus(X+56, Y+2, 'б');
	TFT_DrawCharRus(X+69, Y+2, 'р');
	TFT_DrawCharRus(X+82, Y+2, 'о');
	TFT_DrawCharRus(X+95, Y+2, 'в');
	TFT_DrawCharRus(X+108, Y+2, 'к');
	TFT_DrawCharRus(X+118, Y+2, 'а');
	
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

void GUI_TextRu_WriteSD(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'З');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+15, Y+5, 'а');
	TFT_DrawCharRus(X+28, Y+5, 'п');
	TFT_DrawCharRus(X+41, Y+5, 'и');
	TFT_DrawCharRus(X+53, Y+5, 'с');
	TFT_DrawCharRus(X+65, Y+5, 'ь');
}

void GUI_TextRu_Info_Serial(uint16_t X, uint16_t Y, uint16_t Part, uint16_t Number)
{
	char buffer[5] = {0};
	
	X = 60;
	Y = 200;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y-4, 'С');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+17, Y+2, 'е');
	TFT_DrawCharRus(X+30, Y+2, 'р');
	TFT_DrawCharRus(X+43, Y+2, 'и');
	TFT_DrawCharRus(X+56, Y+2, 'й');
	TFT_DrawCharRus(X+69, Y+2, 'н');
	TFT_DrawCharRus(X+82, Y+2, 'ы');
	TFT_DrawCharRus(X+95, Y+2, 'й');
	TFT_DrawCharRus(X+115, Y+2, 'н');
	TFT_DrawCharRus(X+128, Y+2, 'о');
	TFT_DrawCharRus(X+141, Y+2, 'м');
	TFT_DrawCharRus(X+154, Y+2, 'е');
	TFT_DrawCharRus(X+165, Y+2, 'р');

	sprintf (buffer, "%u",  Part);
	TFT_SetFont(&Font26EN_arch_digit);
	TFT_DisplayString(40, Y+30, (uint8_t *)buffer, LEFT_MODE);
	sprintf (buffer, "%04u",  Number);
	TFT_DisplayString(135, Y+30, (uint8_t *)buffer, LEFT_MODE);
}

void GUI_TextRu_Info_Ver(uint16_t X, uint16_t Y, float Version)
{
	char buffer[5] = {0};
	
	X = 120;
	Y = 350;
	
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y-1, 'П');
	TFT_DrawCharRus(X+18, Y-1, 'О');
	
	TFT_SetFont(&Font16);
	TFT_DrawChar(X+52, Y, '.');
	TFT_DrawChar(X+42, Y, 'v');
	
	sprintf (buffer, "%.1f",  Version);
	TFT_SetFont(&Font16);
	TFT_DisplayString(185, Y, (uint8_t *)buffer, LEFT_MODE);
}

void GUI_TextRu_CCT(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'К');
	TFT_DrawCharRus(X+17, Y, 'Ц');
	TFT_DrawCharRus(X+33, Y, 'Т');

	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+49, Y, '(');
	TFT_DrawChar(X+104, Y, ')');
	TFT_DrawChar(X+63, Y, 'C');
	TFT_DrawChar(X+76, Y, 'C');
	TFT_DrawChar(X+91, Y, 'T');
}

void GUI_TextRu_umol(uint16_t X, uint16_t Y, uint8_t deg)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font12RU_arch_small);
	
	if(deg){
		TFT_DrawCharRus(X, Y, 'м');
	} else{
		TFT_DrawCharRus(X, Y, 'я'+1);
	}

	TFT_DrawCharRus(X+8, Y, 'м');
	TFT_DrawCharRus(X+16, Y, 'о');
	TFT_DrawCharRus(X+22, Y, 'л');
	TFT_DrawCharRus(X+28, Y, 'ь');

	TFT_DrawLine(X, Y+10, X+35, Y+10, TFT_White);

	TFT_DrawCharRus(X+13, Y+11, 'я'+2);
	TFT_DrawCharRus(X+5, Y+11, 'м');
	TFT_DrawRectangle(X+19, Y+14, X+20, Y+15, TFT_White);
	TFT_DrawCharRus(X+22, Y+11, 'с');
}

void GUI_TextRu_umol_Big(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);


	TFT_SetFont(&Font16RU_arch_small);

	TFT_DrawCharRus(X-12, Y, 'м');
	TFT_DrawCharRus(X, Y, 'к');
	TFT_DrawCharRus(X+12, Y, 'м');
	TFT_DrawCharRus(X+24, Y, 'о');
	TFT_DrawCharRus(X+36, Y, 'л');
	TFT_DrawCharRus(X+48, Y, 'ь');

	TFT_DrawLine(X-12, Y+20, X+60, Y+20, TFT_White);

	//TFT_DrawCharRus(X+13, Y, 'я'+2);
	TFT_DrawCharRus(X+5, Y+30, 'м');
	TFT_DrawRectangle(X+24, Y+36, X+25, Y+37, TFT_White);
	TFT_DrawCharRus(X+30, Y+30, 'с');
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X+21, Y+22, '2');
}

void GUI_TextRu_umol_Big_modeL(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);


	TFT_SetFont(&Font16RU_arch_small);

	TFT_DrawCharRus(X-12, Y, 'м');
	TFT_DrawCharRus(X, Y, 'к');
	TFT_DrawCharRus(X+12, Y, 'м');
	TFT_DrawCharRus(X+24, Y, 'о');
	TFT_DrawCharRus(X+36, Y, 'л');
	TFT_DrawCharRus(X+48, Y, 'ь');
	
	TFT_DrawLine(X-12, Y+20, X+60, Y+20, TFT_White);
	
	//TFT_DrawCharRus(X+13, Y, 'я'+2);
	TFT_DrawCharRus(X-7, Y+30, 'м');
	TFT_DrawRectangle(X+12, Y+36, X+13, Y+37, TFT_White);
	TFT_DrawCharRus(X+18, Y+30, 'с');
	TFT_DrawRectangle(X+33, Y+36, X+34, Y+37, TFT_White);
	TFT_DrawCharRus(X+38, Y+30, 'с');
	TFT_DrawCharRus(X+50, Y+30, 'р');
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X+9, Y+22, '2');
}

void GUI_TextRu_umol_sr(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font12RU_arch_small);
	
	TFT_DrawCharRus(X+7, Y, 'я'+1);
	TFT_DrawCharRus(X+15, Y, 'м');
	TFT_DrawCharRus(X+23, Y, 'о');
	TFT_DrawCharRus(X+29, Y, 'л');
	TFT_DrawCharRus(X+35, Y, 'ь');
	
	TFT_DrawLine(X+3, Y+10, X+46, Y+10, TFT_White);
	
	TFT_DrawCharRus(X+13, Y+12, 'я'+2);
	TFT_DrawCharRus(X+5, Y+12, 'м');
	TFT_DrawRectangle(X+19, Y+16, X+20, Y+15, TFT_White);
	TFT_DrawCharRus(X+22, Y+12, 'с');
	TFT_DrawRectangle(X+30, Y+16, X+31, Y+15, TFT_White);
	TFT_DrawCharRus(X+32, Y+12, 'с');
	TFT_DrawCharRus(X+39, Y+12, 'р');

}

void GUI_TextRu_mW_m2(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);

	TFT_SetFont(&Font12RU_arch_small);
	TFT_DrawCharRus(X-1, Y+2, 'м');
	TFT_SetFont(&Font12RU_arch_big);
	TFT_DrawCharRus(X+6, Y, 'В'-17);
	TFT_SetFont(&Font12RU_arch_small);
	TFT_DrawCharRus(X+16, Y+2, 'т');

	TFT_DrawLine(X, Y+10, X+20, Y+10, TFT_White);

	TFT_DrawCharRus(X+12, Y+12, 'я'+2);
	TFT_DrawCharRus(X+4, Y+12, 'м');
}

void GUI_TextRu_mW_m2_Big(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);

	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X-1, Y+2, 'м');
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X+15, Y-5+2, 'В');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+30, Y+2, 'т');

	TFT_DrawLine(X, Y+20, X+40, Y+20, TFT_White);

	TFT_DrawCharRus(X+4, Y+30, 'м');
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X+21, Y+22, '2');
}

void GUI_TextRu_mW_m2_Big_modeL(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);

	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X-1+4, Y+2, 'м');
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X+4+15, Y-5+2, 'В');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+4+30, Y+2, 'т');

	TFT_DrawLine(X, Y+20, X+40+4, Y+20, TFT_White);
	
	TFT_DrawCharRus(X-1, Y+30, 'м');
	TFT_DrawCharRus(X+10+10+5, Y+30, 'с');
	TFT_DrawCharRus(X+22+10+5, Y+30, 'р');
	TFT_DrawRectangle(X+19, Y+36, X+20, Y+37, TFT_White);
	TFT_SetFont(&Font9EN_arch_big);
	TFT_DrawChar(X+16, Y+22, '2');
}

void GUI_TextRu_W_m2(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font12RU_arch_big);
	TFT_DrawCharRus(X+1, Y, 'В'-17);
	TFT_SetFont(&Font12RU_arch_small);
	TFT_DrawCharRus(X+11, Y+2, 'т');
	
	TFT_DrawLine(X, Y+10, X+20, Y+10, TFT_White);
	
	TFT_DrawCharRus(X+12, Y+12, 'я'+2);
	TFT_DrawCharRus(X+4, Y+12, 'м');
}

void GUI_TextRu_W_m2_sr(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font12RU_arch_big);
	TFT_DrawCharRus(X+8, Y, 'В'-17);
	TFT_SetFont(&Font12RU_arch_small);
	TFT_DrawCharRus(X+18, Y+2, 'т');

	TFT_DrawLine(X, Y+10, X+35, Y+10, TFT_White);

	TFT_DrawCharRus(X+10, Y+12, 'я'+2);
	TFT_DrawCharRus(X+2, Y+12, 'м');
	TFT_DrawRectangle(X+17, Y+16, X+18, Y+15, TFT_White);
	TFT_DrawCharRus(X+21, Y+12, 'с');
	TFT_DrawCharRus(X+28, Y+12, 'р');
}

void GUI_TextRu_mW_m2_sr(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font12RU_arch_small);
	TFT_DrawCharRus(X+5, Y+2, 'м');
	TFT_SetFont(&Font12RU_arch_big);
	TFT_DrawCharRus(X+12, Y, 'В'-17);
	TFT_SetFont(&Font12RU_arch_small);
	TFT_DrawCharRus(X+22, Y+2, 'т');
	
	TFT_DrawLine(X, Y+10, X+35, Y+10, TFT_White);
	
	TFT_DrawCharRus(X+10, Y+12, 'я'+2);
	TFT_DrawCharRus(X+2, Y+12, 'м');
	TFT_DrawRectangle(X+17, Y+16, X+18, Y+15, TFT_White);
	TFT_DrawCharRus(X+21, Y+12, 'с');
	TFT_DrawCharRus(X+28, Y+12, 'р');
}



void GUI_TextRu_Cd_m2(uint16_t X, uint16_t Y, uint8_t deg)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font12RU_arch_small);
	
	if(deg){
		TFT_DrawCharRus(X+8, Y, 'к');
		TFT_DrawCharRus(X+16, Y, 'к');
		TFT_DrawCharRus(X+24, Y, 'д');

		TFT_DrawLine(X+6, Y+10, X+31, Y+10, TFT_White);

		TFT_DrawCharRus(X+20, Y+12, 'я'+2);
		TFT_DrawCharRus(X+12, Y+12, 'м');}
	else {
		TFT_DrawCharRus(X+8, Y, 'к');
		TFT_DrawCharRus(X+16, Y, 'д');

		TFT_DrawLine(X+6, Y+10, X+23, Y+10, TFT_White);

		TFT_DrawCharRus(X+17, Y+12, 'я'+2);
		TFT_DrawCharRus(X+9, Y+12, 'м');}

}

void GUI_TextRu_Cd_m2_Big(uint16_t X, uint16_t Y, uint8_t deg)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_small);

		TFT_DrawCharRus(X+8, Y, 'к');
		TFT_DrawCharRus(X+26, Y, 'д');
		
		TFT_DrawLine(X+10, Y+20, X+43, Y+20, TFT_White);
		TFT_DrawCharRus(X+19, Y+30, 'м');
		TFT_SetFont(&Font6EN_arch_big);
		TFT_DrawChar(X+33, Y+26, '2');
		
}



void GUI_TextRu_Irradiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'О');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+16, Y+5, 'б');
	TFT_DrawCharRus(X+27, Y+5, 'л');
	TFT_DrawCharRus(X+39, Y+5, 'у');
	TFT_DrawCharRus(X+51, Y+5, 'ч');
	TFT_DrawCharRus(X+63, Y+5, 'е');
	TFT_DrawCharRus(X+74, Y+5, 'н');
	TFT_DrawCharRus(X+86, Y+5, 'н');
	TFT_DrawCharRus(X+98, Y+5, 'о');
	TFT_DrawCharRus(X+110, Y+5, 'с');
	TFT_DrawCharRus(X+119, Y+5, 'т');
	TFT_DrawCharRus(X+131, Y+5, 'ь');
}

void GUI_TextRu_Luminance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Я');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+16, Y+5, 'р');
	TFT_DrawCharRus(X+28, Y+5, 'к');
	TFT_DrawCharRus(X+40, Y+5, 'о');
	TFT_DrawCharRus(X+52, Y+5, 'с');
	TFT_DrawCharRus(X+63, Y+5, 'т');
	TFT_DrawCharRus(X+74, Y+5, 'ь');
}

void GUI_TextRu_Radiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Э');
	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+16, Y+5, 'н');
	TFT_DrawCharRus(X+29, Y+5, 'е');
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(X+46, 		Y, '.');

	TFT_SetFont(&Font16RU_arch_small);
	TFT_DrawCharRus(X+41, Y+5, 'р');
	TFT_DrawCharRus(X+61, Y+5, 'я');
	TFT_DrawCharRus(X+73, Y+5, 'р');
	TFT_DrawCharRus(X+85, Y+5, 'к');
	TFT_DrawCharRus(X+97, Y+5, 'о');
	TFT_DrawCharRus(X+109, Y+5, 'с');
	TFT_DrawCharRus(X+120, Y+5, 'т');
	TFT_DrawCharRus(X+131, Y+5, 'ь');

}

void GUI_TextMsgRu_LowIrradiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'М');
	TFT_SetFont(&Font16RU_arch_small);
  TFT_DrawCharRus(X+16, Y+5, 'а');
  TFT_DrawCharRus(X+28, Y+5, 'л');
  TFT_DrawCharRus(X+40, Y+5, 'а');
  TFT_DrawCharRus(X+52, Y+5, 'я');

  TFT_DrawCharRus(X+73, Y+5, 'о');
	TFT_DrawCharRus(X+87, Y+5, 'б');
  TFT_DrawCharRus(X+98, Y+5, 'л');
  TFT_DrawCharRus(X+110, Y+5, 'у');
  TFT_DrawCharRus(X+122, Y+5, 'ч');
  TFT_DrawCharRus(X+134, Y+5, 'е');
  TFT_DrawCharRus(X+145, Y+5, 'н');
  TFT_DrawCharRus(X+157, Y+5, 'н');
  TFT_DrawCharRus(X+169, Y+5, 'о');
  TFT_DrawCharRus(X+181, Y+5, 'с');
  TFT_DrawCharRus(X+190, Y+5, 'т');
  TFT_DrawCharRus(X+202, Y+5, 'ь');
}

void GUI_TextMsgRu_LowRadiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'М');
	TFT_SetFont(&Font16RU_arch_small);
  TFT_DrawCharRus(X+16, Y+5, 'а');
  TFT_DrawCharRus(X+28, Y+5, 'л');
  TFT_DrawCharRus(X+40, Y+5, 'а');
  TFT_DrawCharRus(X+52, Y+5, 'я');

  TFT_DrawCharRus(X+73, Y+5, 'я');
  TFT_DrawCharRus(X+85, Y+5, 'р');
  TFT_DrawCharRus(X+97, Y+5, 'к');
  TFT_DrawCharRus(X+109, Y+5, 'о');
  TFT_DrawCharRus(X+121, Y+5, 'с');
  TFT_DrawCharRus(X+132, Y+5, 'т');
  TFT_DrawCharRus(X+143, Y+5, 'ь');
}

void GUI_TextMsgRu_HighIrradiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Б');
	TFT_SetFont(&Font16RU_arch_small);
  TFT_DrawCharRus(X+16, Y+5, 'о');
  TFT_DrawCharRus(X+28, Y+5, 'л');
  TFT_DrawCharRus(X+40, Y+5, 'ь');
  TFT_DrawCharRus(X+54, Y+5, 'ш');
  TFT_DrawCharRus(X+67, Y+5, 'а');
  TFT_DrawCharRus(X+79, Y+5, 'я');
	
  TFT_DrawCharRus(X+102, Y+5, 'о');
  TFT_DrawCharRus(X+116, Y+5, 'б');
  TFT_DrawCharRus(X+127, Y+5, 'л');
  TFT_DrawCharRus(X+139, Y+5, 'у');
  TFT_DrawCharRus(X+151, Y+5, 'ч');
  TFT_DrawCharRus(X+163, Y+5, 'е');
  TFT_DrawCharRus(X+174, Y+5, 'н');
  TFT_DrawCharRus(X+186, Y+5, 'н');
  TFT_DrawCharRus(X+198, Y+5, 'о');
  TFT_DrawCharRus(X+210, Y+5, 'с');
  TFT_DrawCharRus(X+219, Y+5, 'т');
  TFT_DrawCharRus(X+231, Y+5, 'ь');
}

void GUI_TextMsgRu_HighRadiance(uint16_t X, uint16_t Y)
{
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black);
	
	TFT_SetFont(&Font16RU_arch_big);
	TFT_DrawCharRus(X, Y, 'Б');
	TFT_SetFont(&Font16RU_arch_small);
  TFT_DrawCharRus(X+16, Y+5, 'о');
  TFT_DrawCharRus(X+28, Y+5, 'л');
  TFT_DrawCharRus(X+40, Y+5, 'ь');
  TFT_DrawCharRus(X+54, Y+5, 'ш');
  TFT_DrawCharRus(X+67, Y+5, 'а');
  TFT_DrawCharRus(X+79, Y+5, 'я');
	
  TFT_DrawCharRus(X+102, Y+5, 'я');
  TFT_DrawCharRus(X+114, Y+5, 'р');
  TFT_DrawCharRus(X+126, Y+5, 'к');
  TFT_DrawCharRus(X+138, Y+5, 'о');
  TFT_DrawCharRus(X+150, Y+5, 'с');
  TFT_DrawCharRus(X+161, Y+5, 'т');
  TFT_DrawCharRus(X+172, Y+5, 'ь');
}

void GUI_TextRu_CRI_no(uint16_t X, uint16_t Y, uint8_t direction)
{
	if (direction == 0x00)
	{
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black);
		TFT_SetFont(&Font12RU_arch_small);
		TFT_DrawCharRus(X + 5, Y + 5, 'н');
		TFT_DrawCharRus(X + 16, Y + 5, 'е');
		TFT_DrawCharRus(X + 27, Y + 5, 'в');
		TFT_DrawCharRus(X + 39, Y + 5, 'о');
		TFT_DrawCharRus(X + 51, Y + 5, 'з');
		TFT_DrawCharRus(X + 63, Y + 5, 'м');
		TFT_DrawCharRus(X + 74, Y + 5, 'о');
		TFT_DrawCharRus(X + 86, Y + 5, 'ж');
		TFT_DrawCharRus(X + 98, Y + 5, 'н');
		TFT_DrawCharRus(X + 110, Y + 5, 'о');

		TFT_DrawCharRus(X + 133, Y + 5, 'р');
		TFT_DrawCharRus(X + 145, Y + 5, 'а');
		TFT_DrawCharRus(X + 157, Y + 5, 'с');
		TFT_DrawCharRus(X + 169, Y + 5, 'с');
		TFT_DrawCharRus(X + 181, Y + 5, 'ч');
		TFT_DrawCharRus(X + 193, Y + 5, 'и');
		TFT_DrawCharRus(X + 205, Y + 5, 'т');
		TFT_DrawCharRus(X + 217, Y + 5, 'а');
		TFT_DrawCharRus(X + 229, Y + 5, 'т');
		TFT_DrawCharRus(X + 241, Y + 5, 'ь');

		TFT_SetFont(&Font11EN_arch_big);
		TFT_DrawChar(X + 104, Y + 15, 'C');
		TFT_DrawChar(X + 116, Y + 15, 'R');
		TFT_DrawChar(X + 128, Y + 15, 'I');
		TFT_DrawChar(X + 140, Y + 15, '/');
		TFT_DrawChar(X + 152, Y + 15, 'C');
		TFT_DrawChar(X + 164, Y + 15, 'Q');
		TFT_DrawChar(X + 176, Y + 15, 'S');
	}else if (direction != 0x00)
	{
		if(direction == 0x01){TFT_direction = 0x01;}
			else {TFT_direction = 0x02;}
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black);
		TFT_SetFont(&Font12RU_arch_small);
		TFT_DrawCharRus(X + 85, Y - 87, 'н');
		TFT_DrawCharRus(X + 97, Y - 87, 'е');
		TFT_DrawCharRus(X + 109, Y - 87, 'в');
		TFT_DrawCharRus(X + 121, Y - 87, 'о');
		TFT_DrawCharRus(X + 133, Y - 87, 'з');
		TFT_DrawCharRus(X + 145, Y - 87, 'м');
		TFT_DrawCharRus(X + 157, Y - 87, 'о');
		TFT_DrawCharRus(X + 169, Y - 87, 'ж');
		TFT_DrawCharRus(X + 181, Y - 87, 'н');
		TFT_DrawCharRus(X + 193, Y - 87, 'о');

		TFT_DrawCharRus(X + 217, Y - 87, 'р');
		TFT_DrawCharRus(X + 229, Y - 87, 'а');
		TFT_DrawCharRus(X + 241, Y - 87, 'с');
		TFT_DrawCharRus(X + 253, Y - 87, 'с');
		TFT_DrawCharRus(X + 265, Y - 87, 'ч');
		TFT_DrawCharRus(X + 277, Y - 87, 'и');
		TFT_DrawCharRus(X + 289, Y - 87, 'т');
		TFT_DrawCharRus(X + 301, Y - 87, 'а');
		TFT_DrawCharRus(X + 313, Y - 87, 'т');
		TFT_DrawCharRus(X + 325, Y - 87, 'ь');

		TFT_SetFont(&Font11EN_arch_big);
		TFT_DrawChar(X + 154, Y - 78, 'C');
		TFT_DrawChar(X + 166, Y - 78, 'R');
		TFT_DrawChar(X + 178, Y - 78, 'I');
		TFT_DrawChar(X + 190, Y - 78, '/');
		TFT_DrawChar(X + 202, Y - 78, 'C');
		TFT_DrawChar(X + 214, Y - 78, 'Q');
		TFT_DrawChar(X + 226, Y - 78, 'S');
		TFT_direction = 0x00;
	}
}

void GUI_TextRu_lx(uint16_t X, uint16_t Y)
{
	TFT_SetFont(&Font12RU_arch_small);
	TFT_DrawCharRus(X+230-5, Y+4+2, 'л');
	TFT_DrawCharRus(X+236-5, Y+4+2, 'к');
}
