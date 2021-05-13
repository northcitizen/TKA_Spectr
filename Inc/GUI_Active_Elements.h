#ifndef __GUI_ACTIVE_ELEMENTS_H
#define __GUI_ACTIVE_ELEMENTS_H

#include <string.h>
#include <stdlib.h>
#include "DRAWIMAGE.h"
#include "fonts.h"
#include "ltdc.h"
#include "Buttons.h"
#include "Touchscreen.h"
#include "GUI_Text_Elements_EN.h"
#include "GUI_Text_Elements_RU.h"

void GUI_Button_Start_measure(uint16_t X, uint16_t Y);
void GUI_Button_Settings(uint16_t X, uint16_t Y);
void GUI_Bluetooth_Logo(uint16_t X, uint16_t Y);
void GUI_Button_Down(uint16_t X, uint16_t Y);
void GUI_Button_Right(uint16_t X, uint16_t Y);
void GUI_Button_TFT_On_Off(uint16_t X, uint16_t Y);
void GUI_Button_TFT_Rotate(uint16_t X, uint16_t Y);
void GUI_Button_SD_Card(uint16_t X, uint16_t Y, uint8_t Active);
void GUI_Button_Measure_Start_Pause(uint16_t X, uint16_t Y);
void GUI_CheckBox(uint16_t X, uint16_t Y, uint16_t Check);
void GUI_RadioBox(uint16_t X, uint16_t Y, uint16_t Check, uint16_t Active);
void GUI_Switch_Button(uint16_t X, uint16_t Y, uint8_t Check);
void GUI_Flag_Ru(uint16_t X, uint16_t Y);
void GUI_Flag_En(uint16_t X, uint16_t Y);
void GUI_Switch_ButtonActive(uint16_t X, uint16_t Y, uint8_t Check);
void GUI_Switch_Button_Lx_Fl(uint16_t X, uint16_t Y, uint8_t Check);
void GUI_Button_Down_Active(uint16_t X, uint16_t Y, uint8_t Active);

void GUI_Button_Measure_deltaE_Small(uint16_t X, uint16_t Y, uint16_t Active, uint8_t color);
#endif
