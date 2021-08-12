#include "stdio.h"
#include "GUI_Active_Elements.h"
#include "stm32l4xx_hal.h"
#include "BlueTooth.h"

//extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart3;
extern uint8_t BluetoothStat;
extern uint8_t pause;

void GUI_Bluetooth_Logo(uint16_t X, uint16_t Y)
{
	TFT_DrawFilledRoundedRectangle(X, Y, X+20, Y+30, 5, TFT_Blue_Off); 
	TFT_DrawLine(X+10, Y+4, X+10, Y+26, TFT_White);
	TFT_DrawLine(X+10, Y+5, X+15, Y+11, TFT_White);
	TFT_DrawLine(X+6, Y+20, X+15, Y+11, TFT_White);
	TFT_DrawLine(X+6, Y+11, X+15, Y+20, TFT_White);
	TFT_DrawLine(X+10, Y+26, X+15, Y+20,TFT_White);
}


void GUI_Button_Settings(uint16_t X, uint16_t Y)
{
	TFT_FillRectangle(X, Y, X+54, Y+54, TFT_Blue_Off);
	TFT_DrawFilledRoundedRectangle(X+8, Y+13, X+47, Y+19, 2, TFT_White);
	TFT_DrawFilledRoundedRectangle(X+8, Y+25, X+47, Y+31, 2, TFT_White);
	TFT_DrawFilledRoundedRectangle(X+8, Y+37, X+47, Y+43, 2, TFT_White);
}

void GUI_Button_Down(uint16_t X, uint16_t Y)
{
	TFT_FillRectangle(X, Y, X+54, Y+54, TFT_Blue_Off);
	TFT_DrawLine(X+12, Y+18, X+28, Y+40, TFT_White);
	TFT_DrawLine(X+13, Y+18, X+29, Y+40, TFT_White);
	TFT_DrawLine(X+43, Y+18, X+28, Y+40, TFT_White);
	TFT_DrawLine(X+42, Y+18, X+27, Y+40, TFT_White);
}

void GUI_Button_Down_Active(uint16_t X, uint16_t Y, uint8_t Active)
{
	if(Active){TFT_FillRectangle(X, Y, X+54, Y+54, TFT_Blue_Off);}
	else {TFT_FillRectangle(X, Y, X+54, Y+54, TFT_GreyMain);}
	
	TFT_DrawLine(X+12, Y+18, X+28, Y+40, TFT_White);
	TFT_DrawLine(X+13, Y+18, X+29, Y+40, TFT_White);
	TFT_DrawLine(X+43, Y+18, X+28, Y+40, TFT_White);
	TFT_DrawLine(X+42, Y+18, X+27, Y+40, TFT_White);
}

void GUI_Button_Right(uint16_t X, uint16_t Y)
{
	TFT_FillRectangle(X, Y, X+54, Y+54, TFT_Blue_Off);
	TFT_DrawLine(X+19, Y+12, X+40, Y+27, TFT_White);
	TFT_DrawLine(X+18, Y+12, X+39, Y+27, TFT_White);
	TFT_DrawLine(X+40, Y+27, X+19, Y+42, TFT_White);
	TFT_DrawLine(X+39, Y+27, X+18, Y+42, TFT_White);
}

void GUI_Button_TFT_On_Off(uint16_t X, uint16_t Y)
{
	TFT_FillRectangle(X, Y, X+54, Y+54, TFT_Blue_Off);
	TFT_DrawRectangle(X+8, Y+16, X+48, Y+39, TFT_White);
	TFT_DrawLine(X+6, Y+5, X+51, Y+48, TFT_White);
}

void GUI_Button_TFT_Rotate(uint16_t X, uint16_t Y)
{
	TFT_FillRectangle(X, Y, X+54, Y+54, TFT_Blue_Off);
	TFT_DrawRectangle(X+9, Y+9, X+28, Y+43, TFT_White);
	TFT_DrawRectangle(X+18, Y+30, X+49, Y+48, TFT_White);
	TFT_DrawCircleCorner(X+28, Y+30, 16, 2, TFT_White);
	
	TFT_DrawLine(X+29, Y+14, X+33, Y+19, TFT_White); //arrow up left
	TFT_DrawLine(X+29, Y+14, X+33, Y+11, TFT_White);
	
	TFT_DrawLine(X+44, Y+29, X+39, Y+25, TFT_White); //arrow down right
	TFT_DrawLine(X+44, Y+29, X+47, Y+25, TFT_White);
}

void GUI_Button_SD_Card(uint16_t X, uint16_t Y, uint8_t Active)
{
	
	if(Active){TFT_FillRectangle(X, Y, X+54, Y+54, TFT_Blue_Off);}
	else{TFT_FillRectangle(X, Y, X+54, Y+54, TFT_GreyMain);}
	
	TFT_FillRectangle(X+21, Y+5, X+46, Y+7, TFT_White); //SD contour
	TFT_FillRectangle(X+44, Y+8, X+46, Y+50, TFT_White);
	TFT_FillRectangle(X+43, Y+48, X+10, Y+50, TFT_White);
	TFT_FillRectangle(X+10, Y+16, X+12, Y+47, TFT_White);
	
	TFT_DrawLine(X+10, Y+16, X+21, Y+5, TFT_White);
	TFT_DrawLine(X+11, Y+16, X+21, Y+6, TFT_White);
	TFT_DrawLine(X+12, Y+16, X+21, Y+7, TFT_White);
	
	TFT_FillRectangle(X+19, Y+13, X+21, Y+19, TFT_White); //SD pins
	TFT_FillRectangle(X+25, Y+13, X+27, Y+19, TFT_White);
	TFT_FillRectangle(X+31, Y+13, X+33, Y+19, TFT_White);
	TFT_FillRectangle(X+37, Y+13, X+39, Y+19, TFT_White);
	
	TFT_SetFont(&Font20);
	TFT_SetTextColor(TFT_White);
	Active ? TFT_SetBackColor(TFT_Blue_Off) : TFT_SetBackColor(TFT_GreyMain);
	TFT_DrawChar(X+16, Y+28, 'S');
	TFT_DrawChar(X+27, Y+28, 'D');
}

void GUI_Button_Measure_Start_Pause(uint16_t X, uint16_t Y)
{
	if(!pause)	TFT_FillRectangle(X, Y, X+54, Y+54, TFT_Blue_Off);
	else  TFT_FillRectangle(X, Y, X+54, Y+54, TFT_PAR_IRed);

	
	TFT_FillRectangle(X+35, Y+11, X+37, Y+43, TFT_White); //Pause
	TFT_FillRectangle(X+48, Y+11, X+50, Y+43, TFT_White);
	
	TFT_DrawLine(X+6, Y+11, X+6, Y+44, TFT_White); //Play
	TFT_DrawLine(X+6, Y+11, X+30, Y+27, TFT_White);
	TFT_DrawLine(X+6, Y+44, X+30, Y+27, TFT_White);
	
	//paint white
	TFT_DrawLine(X+7, Y+12, X+7, Y+43, TFT_White);
	TFT_DrawLine(X+8, Y+12, X+8, Y+43, TFT_White);
	TFT_DrawLine(X+9, Y+13, X+9, Y+42, TFT_White);
	TFT_DrawLine(X+10, Y+14, X+10, Y+41, TFT_White);
	TFT_DrawLine(X+11, Y+14, X+11, Y+40, TFT_White);
	TFT_DrawLine(X+12, Y+15, X+12, Y+40, TFT_White);
	TFT_DrawLine(X+13, Y+16, X+13, Y+39, TFT_White);
	TFT_DrawLine(X+14, Y+16, X+14, Y+38, TFT_White);
	TFT_DrawLine(X+15, Y+17, X+15, Y+38, TFT_White);
	TFT_DrawLine(X+16, Y+18, X+16, Y+37, TFT_White);
	TFT_DrawLine(X+17, Y+18, X+17, Y+36, TFT_White);
	TFT_DrawLine(X+18, Y+19, X+18, Y+36, TFT_White);
	TFT_DrawLine(X+19, Y+20, X+19, Y+35, TFT_White);
	TFT_DrawLine(X+20, Y+20, X+20, Y+34, TFT_White);
	TFT_DrawLine(X+21, Y+21, X+21, Y+33, TFT_White);
	TFT_DrawLine(X+22, Y+22, X+22, Y+33, TFT_White);
	TFT_DrawLine(X+23, Y+22, X+23, Y+32, TFT_White);
	TFT_DrawLine(X+24, Y+23, X+24, Y+31, TFT_White);
	TFT_DrawLine(X+25, Y+24, X+25, Y+31, TFT_White);
	TFT_DrawLine(X+26, Y+24, X+26, Y+30, TFT_White);
	TFT_DrawLine(X+27, Y+25, X+27, Y+29, TFT_White);
	TFT_DrawLine(X+28, Y+25, X+28, Y+28, TFT_White);
	TFT_DrawLine(X+29, Y+26, X+29, Y+28, TFT_White);
	TFT_DrawLine(X+30, Y+27, X+30, Y+27, TFT_White);
}

void GUI_Button_Measure_Start_Pause_For_Button(uint16_t X, uint16_t Y, uint8_t type)
{
	if(!type)	TFT_FillRectangle(X, Y, X+54, Y+54, TFT_Blue_Off);
	else  TFT_FillRectangle(X, Y, X+54, Y+54, TFT_PAR_IRed);


	TFT_FillRectangle(X+35, Y+11, X+37, Y+43, TFT_White); //Pause
	TFT_FillRectangle(X+48, Y+11, X+50, Y+43, TFT_White);

	TFT_DrawLine(X+6, Y+11, X+6, Y+44, TFT_White); //Play
	TFT_DrawLine(X+6, Y+11, X+30, Y+27, TFT_White);
	TFT_DrawLine(X+6, Y+44, X+30, Y+27, TFT_White);

	//paint white
	TFT_DrawLine(X+7, Y+12, X+7, Y+43, TFT_White);
	TFT_DrawLine(X+8, Y+12, X+8, Y+43, TFT_White);
	TFT_DrawLine(X+9, Y+13, X+9, Y+42, TFT_White);
	TFT_DrawLine(X+10, Y+14, X+10, Y+41, TFT_White);
	TFT_DrawLine(X+11, Y+14, X+11, Y+40, TFT_White);
	TFT_DrawLine(X+12, Y+15, X+12, Y+40, TFT_White);
	TFT_DrawLine(X+13, Y+16, X+13, Y+39, TFT_White);
	TFT_DrawLine(X+14, Y+16, X+14, Y+38, TFT_White);
	TFT_DrawLine(X+15, Y+17, X+15, Y+38, TFT_White);
	TFT_DrawLine(X+16, Y+18, X+16, Y+37, TFT_White);
	TFT_DrawLine(X+17, Y+18, X+17, Y+36, TFT_White);
	TFT_DrawLine(X+18, Y+19, X+18, Y+36, TFT_White);
	TFT_DrawLine(X+19, Y+20, X+19, Y+35, TFT_White);
	TFT_DrawLine(X+20, Y+20, X+20, Y+34, TFT_White);
	TFT_DrawLine(X+21, Y+21, X+21, Y+33, TFT_White);
	TFT_DrawLine(X+22, Y+22, X+22, Y+33, TFT_White);
	TFT_DrawLine(X+23, Y+22, X+23, Y+32, TFT_White);
	TFT_DrawLine(X+24, Y+23, X+24, Y+31, TFT_White);
	TFT_DrawLine(X+25, Y+24, X+25, Y+31, TFT_White);
	TFT_DrawLine(X+26, Y+24, X+26, Y+30, TFT_White);
	TFT_DrawLine(X+27, Y+25, X+27, Y+29, TFT_White);
	TFT_DrawLine(X+28, Y+25, X+28, Y+28, TFT_White);
	TFT_DrawLine(X+29, Y+26, X+29, Y+28, TFT_White);
	TFT_DrawLine(X+30, Y+27, X+30, Y+27, TFT_White);
}

void GUI_Button_Measure_deltaE_Small(uint16_t X, uint16_t Y, uint16_t Active, uint8_t color)
{
		if(Active){
			TFT_FillRectangle(X, Y, X+35, Y+35, color == 0 ? TFT_Blue_Off:TFT_Green);
		}
		else{TFT_FillRectangle(X, Y, X+35, Y+35,  TFT_GreyMain);}
	
	
	TFT_DrawLine(X+10, Y+7, X+10, Y+30, TFT_White); //Play
	TFT_DrawLine(X+10, Y+7, X+28, Y+18, TFT_White);
	TFT_DrawLine(X+10, Y+30, X+28, Y+18, TFT_White);
	
	//paint
	TFT_DrawLine(X+11, Y+8, X+11, Y+29, TFT_White);
	TFT_DrawLine(X+12, Y+9, X+12, Y+28, TFT_White);
	TFT_DrawLine(X+13, Y+10, X+13, Y+28, TFT_White);
	TFT_DrawLine(X+14, Y+10, X+14, Y+27, TFT_White);
	TFT_DrawLine(X+15, Y+11, X+15, Y+26, TFT_White);
	TFT_DrawLine(X+16, Y+12, X+16, Y+26, TFT_White);
	TFT_DrawLine(X+17, Y+12, X+17, Y+25, TFT_White);
	TFT_DrawLine(X+18, Y+13, X+18, Y+24, TFT_White);
	TFT_DrawLine(X+19, Y+14, X+19, Y+23, TFT_White);
	TFT_DrawLine(X+20, Y+14, X+20, Y+23, TFT_White);
	TFT_DrawLine(X+21, Y+15, X+21, Y+22, TFT_White);
	TFT_DrawLine(X+22, Y+15, X+22, Y+22, TFT_White);
	TFT_DrawLine(X+23, Y+16, X+23, Y+21, TFT_White);
	TFT_DrawLine(X+24, Y+16, X+24, Y+20, TFT_White);
	TFT_DrawLine(X+25, Y+17, X+25, Y+20, TFT_White);
	TFT_DrawLine(X+26, Y+17, X+26, Y+19, TFT_White);
	TFT_DrawLine(X+27, Y+18, X+27, Y+19, TFT_White);
}

void GUI_CheckBox(uint16_t X, uint16_t Y, uint16_t Check)
{
	TFT_DrawRectangle(X, Y, X+35, Y+35, TFT_Blue_Off);
	if(Check)
		{
			TFT_DrawLine(X+8, Y+17, X+16, Y+26, TFT_Blue_Off);
			TFT_DrawLine(X+16, Y+26, X+29, Y+5, TFT_Blue_Off);
		} else {
			TFT_FillRectangle(X+2, Y+2, X+32, Y+32, TFT_Black_Bkgr); //Pause
		}
}



void GUI_RadioBox(uint16_t X, uint16_t Y, uint16_t Check, uint16_t Active)
{
	if(Active){
		TFT_DrawCircle(X+17, Y+17, 15, TFT_Blue_Off);
	} else
	{
		TFT_DrawCircle(X+17, Y+17, 15, TFT_GreyMain);
	}
	if(Check)
		{
			if(Active)
				{	TFT_DrawFilledCircle(X+17, Y+17, 10, TFT_Blue_Off);} else
				{	TFT_DrawFilledCircle(X+17, Y+17, 10, TFT_GreyMain);}
		} else
		{
			TFT_DrawFilledCircle(X+17, Y+17, 10, TFT_Black_Bkgr);
		}
}

void GUI_Switch_Button(uint16_t X, uint16_t Y, uint8_t Check)
{
	TFT_FillRectangle(X, Y, X+36, Y+28, TFT_Black_Bkgr);
	if(Check)
		{
			TFT_DrawFilledRoundedRectangle(X, Y+10, X+35, Y+24, 10, TFT_Blue_On);
			TFT_DrawFilledCircle(X+25, Y+17, 10, TFT_Blue_Off);
			if(BluetoothStat == 0x00){
				BlueTooth_On(); //Enable Bluetooth
				BluetoothStat = 0x01;
			}
		} else
		{
			TFT_DrawFilledRoundedRectangle(X, Y+10, X+35, Y+24, 10, TFT_LightGrey);
			TFT_DrawFilledCircle(X+10, Y+17, 10, TFT_White);
			if(BluetoothStat == 0x01){
				BlueTooth_Off(); //Disable Bluetooth
				BluetoothStat = 0x00;
			}
		}
}

void GUI_Switch_ButtonActive(uint16_t X, uint16_t Y, uint8_t Check)
{
	TFT_FillRectangle(X, Y, X+36, Y+28, TFT_Black_Bkgr);
	if(Check)
		{
			TFT_DrawFilledRoundedRectangle(X, Y+10, X+35, Y+24, 10, TFT_Blue_On);
			TFT_DrawFilledCircle(X+25, Y+17, 10, TFT_Blue_Off);
		} else
		{
			TFT_DrawFilledRoundedRectangle(X, Y+10, X+35, Y+24, 10, TFT_Blue_On);
			TFT_DrawFilledCircle(X+10, Y+17, 10, TFT_White);
		}
}


void GUI_Switch_Button_Lx_Fl(uint16_t X, uint16_t Y, uint8_t Check)
{
	TFT_FillRectangle(X, Y, X+36, Y+28, TFT_Black_Bkgr);
	if(Check)
		{
			TFT_DrawFilledRoundedRectangle(X, Y+10, X+35, Y+24, 10, TFT_Blue_On);
			TFT_DrawFilledCircle(X+25, Y+17, 10, TFT_Blue_Off);
		} else
		{
			TFT_DrawFilledRoundedRectangle(X, Y+10, X+35, Y+24, 10, TFT_Blue_On);
			TFT_DrawFilledCircle(X+10, Y+17, 10, TFT_White);
		}
}

void GUI_Flag_Ru(uint16_t X, uint16_t Y)
{
	TFT_FillRectangle(X, Y, X+35, Y+7, TFT_White);
	TFT_FillRectangle(X, Y+7, X+35, Y+14, TFT_RuBlue);
	TFT_FillRectangle(X, Y+14, X+35, Y+21, TFT_RuRed);
}

void GUI_Flag_En(uint16_t X, uint16_t Y)
{
	TFT_FillRectangle(X, Y, X+15, Y+9, TFT_Navy);
	TFT_FillRectangle(X+20, Y, X+34, Y+9, TFT_Navy);
	TFT_FillRectangle(X, Y+14, X+15, Y+21, TFT_Navy);
	TFT_FillRectangle(X+20, Y+14, X+34, Y+21, TFT_Navy);
	
	TFT_DrawLine(X, Y+2, X+29, Y+21, TFT_White);
	TFT_DrawLine(X, Y+1, X+29, Y+21, TFT_White);
	TFT_DrawLine(X, Y, X+30, Y+21, TFT_White);
	TFT_DrawLine(X+1, Y, X+31, Y+21, TFT_White);
	TFT_DrawLine(X+2, Y, X+31, Y+21, TFT_White);
	TFT_DrawLine(X+3, Y, X+32, Y+21, TFT_White);
	TFT_DrawLine(X+4, Y, X+33, Y+21, TFT_White);
	TFT_DrawLine(X+4, Y, X+34, Y+21, TFT_White);
	
	TFT_DrawLine(X, Y+21, X+31, Y, TFT_White);
	TFT_DrawLine(X+1, Y+21, X+32, Y, TFT_White);
	TFT_DrawLine(X+2, Y+21, X+32, Y, TFT_White);
	TFT_DrawLine(X+3, Y+21, X+33, Y, TFT_White);
	TFT_DrawLine(X+4, Y+21, X+34, Y, TFT_White);
	TFT_DrawLine(X+5, Y+21, X+34, Y+1, TFT_White);
	TFT_DrawLine(X+6, Y+21, X+34, Y+2, TFT_White);
	
	TFT_FillRectangle(X, Y+9, X+34, Y+14, TFT_White);
	TFT_FillRectangle(X+15, Y, X+20, Y+21, TFT_White);
	
	TFT_FillRectangle(X+16, Y, X+19, Y+21, TFT_Red);
	TFT_FillRectangle(X, Y+10, X+34, Y+13, TFT_Red);
	
}


