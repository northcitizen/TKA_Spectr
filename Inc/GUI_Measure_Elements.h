#ifndef __GUI_MEASURE_ELEMENTS_H
#define __GUI_MEASURE_ELEMENTS_H

#include <string.h>
#include <stdlib.h>
#include "DRAWIMAGE.h"
#include "fonts.h"
#include "ltdc.h"
#include "Buttons.h"
#include "Touchscreen.h"
#include "GUI.h"
#include "GUI_Text_Elements_RU.h"
#include "GUI_Text_Elements_EN.h"

void GUI_Battery_Level(uint16_t X, uint16_t Y, double charge);
void GUI_Bar_Measure(uint16_t X, uint16_t Y, float Value);
void GUI_Text_E_Measure(uint16_t X, uint16_t Y, float Value, uint8_t energy_light);
void GUI_Text_PPF_Measure(uint16_t X, uint16_t Y, float Value);
void GUI_Text_PPFRGB_Measure(uint16_t X, uint16_t Y, float ValueR, float ValueG, float ValueB, float ValueFR);
void GUI_Text_XYZ_Measure(uint16_t X, uint16_t Y, uint16_t ValueX, uint16_t ValueY, uint16_t ValueZ);
void GUI_Text_xy_Measure(uint16_t X, uint16_t Y, float Valuex, float Valuey);
void GUI_Text_uv_Measure(uint16_t X, uint16_t Y, float ValueU, float ValueV);
void GUI_Text_CCT_Measure(uint16_t X, uint16_t Y, uint16_t Value);
void GUI_Text_lambdaD_Measure(uint16_t X, uint16_t Y, float Value);
void GUI_Text_lambdaC_Measure(uint16_t X, uint16_t Y, float Value);
void GUI_Text_deltaE_Measure(uint16_t X, uint16_t Y, float Value);
void GUI_Text_EbEr_Measure(uint16_t X, uint16_t Y, float ValueEB, float ValueER);
void GUI_Text_LbLr_Measure(uint16_t X, uint16_t Y, float ValueLB, float ValueLR);
void GUI_Text_S_P_Measure(uint16_t X, uint16_t Y, float Value);
void GUI_Text_LAB_Measure(uint16_t X, uint16_t Y, int16_t ValueL, int16_t ValueA, int16_t ValueB);
void GUI_Text_L_Measure(uint16_t X, uint16_t Y, float Value, uint8_t energy_light);

uint8_t deg_return(float Value);
#endif