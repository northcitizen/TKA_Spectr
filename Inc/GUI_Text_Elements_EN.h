#ifndef __GUI_TEXT_ELEMENTS_EN_H
#define __GUI_TEXT_ELEMENTS_EN_H

#include <string.h>
#include <stdlib.h>
#include "DRAWIMAGE.h"
#include "fonts.h"
#include "ltdc.h"
#include "Buttons.h"
#include "Touchscreen.h"

void GUI_Text_CIE_XYZ(uint16_t X, uint16_t Y);
void GUI_Text_CIE_x_y(uint16_t X, uint16_t Y);
void GUI_Text_CIE_xy_1931(uint16_t X, uint16_t Y);
void GUI_Text_CIE_xy_1964(uint16_t X, uint16_t Y);
void GUI_Text_CIE_Luv(uint16_t X, uint16_t Y);
void GUI_Text_CIE_Lab(uint16_t X, uint16_t Y);
void GUI_Text_Bluetooth(uint16_t X, uint16_t Y);
void GUI_Text_A(uint16_t X, uint16_t Y);
void GUI_Text_D65(uint16_t X, uint16_t Y);
void GUI_Text_C(uint16_t X, uint16_t Y);
void GUI_Text_D50(uint16_t X, uint16_t Y);
void GUI_Text_D55(uint16_t X, uint16_t Y);
void GUI_Text_D75(uint16_t X, uint16_t Y);
void GUI_Text_CIE_xy(uint16_t X, uint16_t Y);
void GUI_Text_CQS(uint16_t X, uint16_t Y);
void GUI_Text_CRI(uint16_t X, uint16_t Y);
void GUI_Text_SP(uint16_t X, uint16_t Y);
void GUI_Text_lambda_d(uint16_t X, uint16_t Y);
void GUI_Text_lambda_c(uint16_t X, uint16_t Y);
void GUI_Text_V_lambda(uint16_t X, uint16_t Y);
void GUI_Text_deltaE(uint16_t X, uint16_t Y);
void GUI_TextEn_umol(uint16_t X, uint16_t Y, uint8_t deg);
void GUI_Text_Off(uint16_t X, uint16_t Y);
void GUI_Text_On(uint16_t X, uint16_t Y);
void GUI_Text_EbEr(uint16_t X, uint16_t Y);
void GUI_Text_LbLr(uint16_t X, uint16_t Y);

void GUI_TextEn_Language(uint16_t X, uint16_t Y);
void GUI_TextEn_English(uint16_t X, uint16_t Y);
void GUI_TextEn_Info(uint16_t X, uint16_t Y);
void GUI_TextEn_Radiance(uint16_t X, uint16_t Y);
void GUI_TextEn_Irradiance(uint16_t X, uint16_t Y);
void GUI_TextEn_Luminance(uint16_t X, uint16_t Y);
void GUI_TextEn_Illuminance(uint16_t X, uint16_t Y);
void GUI_TextEn_Mode(uint16_t X, uint16_t Y);
void GUI_TextEN_LxFl(uint16_t X, uint16_t Y);
void GUI_TextEn_Green(uint16_t X, uint16_t Y);
void GUI_TextEn_Blue(uint16_t X, uint16_t Y);
void GUI_TextEn_Red(uint16_t X, uint16_t Y);
//void GUI_TextEn_BlueTooth(uint16_t X, uint16_t Y);
void GUI_TextEn_PPFD(uint16_t X, uint16_t Y);
void GUI_TextEn_PPL(uint16_t X, uint16_t Y);
void GUI_TextEn_PARwavebands(uint16_t X, uint16_t Y);
void GUI_TextEn_B_G_R_FR(uint16_t X, uint16_t Y);
void GUI_TextEn_Tc(uint16_t X, uint16_t Y);
void GUI_TextEn_LB(uint16_t X, uint16_t Y); 
void GUI_TextEn_LR(uint16_t X, uint16_t Y);
void GUI_TextEn_CCT(uint16_t X, uint16_t Y);
void GUI_TextEn_W_m2(uint16_t X, uint16_t Y);
void GUI_TextEn_mW_m2(uint16_t X, uint16_t Y);
void GUI_TextEn_W_m2_sr(uint16_t X, uint16_t Y);
void GUI_TextEn_mW_m2_sr(uint16_t X, uint16_t Y);
void GUI_TextEn_cd_m2(uint16_t X, uint16_t Y, uint8_t deg);
void GUI_TextEn_mol_s_2(uint16_t X, uint16_t Y);
void GUI_TextEn_umol_sr(uint16_t X, uint16_t Y, uint8_t deg);
void GUI_TextEn_WriteSD(uint16_t X, uint16_t Y);

void GUI_TextEn_Info_Callibration(uint16_t X, uint16_t Y, uint8_t date, uint8_t month, uint16_t year);
void GUI_TextEn_Info_Serial(uint16_t X, uint16_t Y, uint16_t Part, uint16_t Number);
void GUI_TextEn_Info_Ver(uint16_t X, uint16_t Y, float Version);

void GUI_TextMsgEn_HighIrradiance(uint16_t X, uint16_t Y);
void GUI_TextMsgEn_HighRadiance(uint16_t X, uint16_t Y);
void GUI_TextMsgEn_LowRadiance(uint16_t X, uint16_t Y);
void GUI_TextMsgEn_LowIrradiance(uint16_t X, uint16_t Y);
void GUI_TextEn_CRI_no(uint16_t X, uint16_t Y);
#endif
