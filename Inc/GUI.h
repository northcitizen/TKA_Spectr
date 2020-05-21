#ifndef __GUI_H
#define __GUI_H

#include "stm32l4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include "DRAWIMAGE.h"
#include "fonts.h"
#include "ltdc.h"
#include "Buttons.h"
#include "Touchscreen.h"
#include "GUI_Active_Elements.h"
#include "GUI_Text_Elements_EN.h"
#include "GUI_Text_Elements_RU.h"
#include "GUI_Measure_Elements.h"
#include "CRI_graph.h"
#include "CQS_graph.h"
#include "Spectral_graph.h"
#include "SD_CARD.h"
#include "CQS_Calculate.h"
#include "CRI_Calculate.h"
#include "Qspi_func.h"

#define VERSION 1.0

//Main Screen
#define Title_Screen 						0x00
#define	Measure_Screen						0x01
#define	Measure2_Screen						0x02
#define	Measure3_Screen						0x03
#define Graph_Screen 						0x04
#define Color_Screen 						0x05
#define	Color_Rendition_Screen				0x06

//Settings Screen
#define DataSet1_Screen 				0x07
#define DataSet2_Screen 				0x08
#define DataSet3_Screen 				0x09
#define DataSet4_Screen 				0x0A
#define DataSet5_Screen 				0x0B
#define GraphSet1_Screen 				0x0C
#define GraphSet2_Screen 				0x0D
#define ColorSet1_Screen 				0x0E
#define ColorSet2_Screen 				0x0F
#define ColorRendSet_Screen 			0x10

#define Information_Screen 				0x11
#define SD_Write_Screen					0x12

#define Ru									0x00
#define En									0x01

#define ON									0x01
#define OFF									0x00

#define Illuminance 				0x0001
#define Irradiance 					0x0002
#define PPFD						0x0004
#define PPFD_BGR					0x0008
#define CIE_XYZ						0x0010
#define CIE_xy						0x0020
#define CIE_Luv						0x0040
#define CIE_Lab						0x0080
#define CCT							0x0100
#define lambda_d					0x0200
#define lambda_c					0x0400
#define delta_E						0x0800
#define EbEr						0x1000
#define SP_measure					0x2000

#define Source_A		 			0x01
#define Source_D65	 				0x02
#define Source_C		 			0x04
#define Source_D50	 				0x08
#define Source_D55	 				0x10
#define Source_D75	 				0x20

#define PPF_Bands 					0x01
#define EbEr_graph					0x02
#define V_lambda					0x04

#define Color_CIE_xy 				0x01
#define Color_CIE_Lab				0x02
#define Color_CIE_Luv				0x04

#define CRI_CQS						0x01
#define CIE_xy_1931_1964			0x01

typedef enum{
	Deact=0x00,
	Act=0x01
} Measure_State;

void GUI_Up_Panel();
void GUI_Down_Panel();
void GUI_Panels();

void GUI_Title_Screen();
void GUI_Error_Screen();
void GUI_DataSet1_Screen();
void GUI_DataSet2_Screen();
void GUI_DataSet3_Screen();
void GUI_DataSet4_Screen();
void GUI_DataSet5_Screen();
void GUI_GraphSet1_Screen();
void GUI_GraphSet2_Screen();
void GUI_ColorSet1_Screen();
void GUI_ColorSet2_Screen();

void GUI_Measure_Screen();
void GUI_Measure2_Screen();
void GUI_Measure3_Screen();
void GUI_Measure4_Screen();
void GUI_Measure5_Screen();

void GUI_Graph_Screen();
void GUI_ColorRendSet_Screen();
void GUI_Color_Screen();
void GUI_ColorRend_Screen();
void GUI_Touch_Processing();
void GUI_Information_Screen();
void GUI_Display_Refresh();
void Measure_Elements_Draw(uint8_t Measure_Number);
void GUI_OptionMenuRu();
void GUI_OptionMenuEn();

void GUI_SD_Write_Screen();
	
void GUI_LaserOnOff(void);
void GUI_SignalLevel();
#endif /* __GUI_H */
