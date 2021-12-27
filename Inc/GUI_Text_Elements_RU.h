#ifndef __GUI_TEXT_ELEMENTS_RU_H
#define __GUI_TEXT_ELEMENTS_RU_H

#include <string.h>
#include <stdlib.h>
#include "DRAWIMAGE.h"
#include "fonts.h"
#include "ltdc.h"
#include "Buttons.h"
#include "Touchscreen.h"


void GUI_TitleString_Name(uint16_t X, uint16_t Y);
void GUI_TitleString_Version(uint16_t X, uint16_t Y, float Version);
void GUI_TextRu_Language(uint16_t X, uint16_t Y);
void GUI_TextRu_Russian(uint16_t X, uint16_t Y);
void GUI_TextRu_Info(uint16_t X, uint16_t Y);
void GUI_TextRu_Mode(uint16_t X, uint16_t Y);
void GUI_TextRu_LxFl(uint16_t X, uint16_t Y);
void GUI_TextRu_Illuminance(uint16_t X, uint16_t Y);
void GUI_TextRu_PPF(uint16_t X, uint16_t Y);
void GUI_TextRu_PPF_RGB(uint16_t X, uint16_t Y);
void GUI_TextRu_PPF_bands(uint16_t X, uint16_t Y);
void GUI_TextRu_CCT(uint16_t X, uint16_t Y);
void GUI_TextRu_umol(uint16_t X, uint16_t Y, uint8_t deg);
void GUI_TextRu_Irradiance(uint16_t X, uint16_t Y);
void GUI_TextRu_W_m2(uint16_t X, uint16_t Y);
void GUI_TextRu_W_m2_sr(uint16_t X, uint16_t Y);
void GUI_TextRu_mW_m2(uint16_t X, uint16_t Y);
void GUI_TextRu_mW_m2_sr(uint16_t X, uint16_t Y);
void GUI_TextRu_umol_sr(uint16_t X, uint16_t Y);
void GUI_TextRu_Cd_m2(uint16_t X, uint16_t Y, uint8_t deg);
void GUI_TextRu_Cd_m2_Big(uint16_t X, uint16_t Y, uint8_t deg);
void GUI_TextRu_Info_Callibration(uint16_t X, uint16_t Y, uint8_t date, uint8_t month, uint16_t year);
void GUI_TextRu_Info_Serial(uint16_t X, uint16_t Y, uint16_t Part, uint16_t Number);
void GUI_TextRu_Info_Ver(uint16_t X, uint16_t Y, float Version);
void GUI_TextRu_Radiance(uint16_t X, uint16_t Y);
void GUI_TextRu_Luminance(uint16_t X, uint16_t Y);
void GUI_TextRu_WriteSD(uint16_t X, uint16_t Y);

void GUI_TextMsgRu_LowIrradiance(uint16_t X, uint16_t Y);
void GUI_TextMsgRu_LowRadiance(uint16_t X, uint16_t Y);
void GUI_TextMsgRu_HighRadiance(uint16_t X, uint16_t Y);
void GUI_TextMsgRu_HighIrradiance(uint16_t X, uint16_t Y);

void GUI_TextRu_CRI_no(uint16_t X, uint16_t Y);

#endif
