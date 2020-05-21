#include "GUI.h"
#include "stdio.h"
#include "Rabs_math.h"
#include "Calculate_Measure.h"
#include "Calibration_Address.h"

uint8_t GUI_screen_state = Title_Screen, Rotation_Screen_Spectral_Old, Rotation_Screen_Rend_Old, Language_status_prev, Mode_EL_Old,
pause = 0x00, Rotation_Screen_Color = 0x00;
volatile uint8_t	preGUI_screen_state = 0xFF;
extern uint8_t exp_num, VGain, LaserOnOff, MeasureFlag_display, Mode_EL, TFT_ON_OFF, Q_i[15], Qf, Qa, Qp;
extern uint8_t  old_meas_type_E,old_meas_type_L, SD_Detect;
extern int8_t Ra, Rall, R9, Ri[14];
int16_t colorimetry_LAB_mem[3];
extern uint8_t SD_Detect, write_FileNum;
extern float E_day, E_day_Wt, E_Night, SP_Measure, PPFD_PPL_Measure, PPFD_PPL_Blue_Measure, PPFD_PPL_Green_Measure, PPFD_PPL_Red_Measure, PPFD_PPL_Far_Red_Measure,
	ELr_Measure, ELb_Measure;
int16_t delta_Eab_Measure;
extern uint16_t	Tc_Measure, lambda_d_Measure, lambda_c_Measure, Calibration_date, Calibration_month, Calibration_year;
extern uint16_t bmp[108000];
extern float Spectral_day[1024], Spectral_night[1024], WaveLenght[1024], Hazard_Blue[1024], Hazard_Retina[1024], calibratre_x_1931[1024], calibratre_y_1931[1024], calibratre_z_1931[1024],
							calibratre_x_1964[1024], calibratre_z_1964[1024], Spectral_Corection_Buff[1024];
extern uint16_t colorimetry_XYZ[3], cnt_delay_bar, Serial_part_device, Serial_number_device;
extern int16_t colorimetry_LAB[3];
extern float colorimetry_xy[2], colorimetry_uv[2], colorimetry_uv1976[2], max_Rabs;

uint16_t Measure_Field = 0x0000, sdfile_cnt = 0x00, Memory_Data_satus = 0x01, graph_spectral_day[355], graph_spectral_night[355], graph_spectral_Retina[355], graph_spectral_Blue[355];
uint8_t Language_status = Ru, Graph_Field = 0x00, Color_Field = 0x00, preColor_Field = 0x00, Measure_Color_xy = 0x00, Color_rend_Field = 0x00, Bluetooth, Source_Type, Prev_Inf_Screen,Prev_Inf_Screen2, Rotation_Screen = 0x00,
Calc_ColorRend = 0x00, Calc_ColorRend_old = 0x00, current_state_Measure_Draw = 0;
uint8_t Rotation_Screen_Spectral = 0x00, Rotation_Screen_Rend = 0x00, CRICQS_done = 0x00;
extern double percentage_charge, bar_CQS, bar_CRI, SDWr_Status_bar;
extern uint16_t graph_data_old[340];
extern TIM_HandleTypeDef htim2;
extern const uint16_t exposure_timer_period[10];
extern float Exposure_Factor, EnergyFactor_E, EnergyFactor_L, Factor2, test_massive[1024], Line_Rabs_buff[1024];
uint8_t screen_count = 0, screen_count_old = 0, state_Measure_Elements = 0;
sImage Locus;
extern volatile uint8_t TFT_direction;

void GUI_OptionMenuRu()
{	
	GUI_TextRu_Language(10, 86);
	GUI_TextRu_Russian(118, 86);
	GUI_Flag_Ru(218, 86);
	TFT_DrawLine(10, 120, 262, 120, TFT_White);
	GUI_TextRu_Info(10, 145);
	TFT_DrawLine(10, 183, 262, 183, TFT_White);
	
	GUI_TextRu_Mode(10, 209);
	GUI_Switch_ButtonActive(182, 202, Mode_EL);
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(225, 210, 'E' );
	TFT_DrawChar(155, 210, 'L');
	
	TFT_DrawLine(10, 248, 262, 248, TFT_White);
	
	GUI_Text_Bluetooth(10, 275);
	GUI_Switch_Button(182, 268, Bluetooth);
	GUI_Text_On(222, 275);
	GUI_Text_Off(140, 275);
	TFT_DrawLine(10, 313, 262, 313, TFT_White);
}
void GUI_OptionMenuEn()
{
	GUI_TextEn_Language(10, 88);
	GUI_TextEn_English(127, 88);
	GUI_Flag_En(218, 86);
	TFT_DrawLine(10, 120, 262, 120, TFT_White);
	GUI_TextEn_Info(10, 147);
	TFT_DrawLine(10, 183, 262, 183, TFT_White);
	
	GUI_TextEn_Mode(10, 211);
	GUI_Switch_ButtonActive(182, 202, Mode_EL);
	TFT_SetTextColor(TFT_White);
	TFT_SetBackColor(TFT_Black_Bkgr);
	TFT_SetFont(&Font16EN_arch_big);
	TFT_DrawChar(225, 210, 'E' );
	TFT_DrawChar(155, 210, 'L');
	
	TFT_DrawLine(10, 248, 262, 248, TFT_White);
	
	GUI_Text_Bluetooth(10, 275);
	GUI_Switch_Button(182, 268, Bluetooth);
	GUI_Text_On(222, 275);
	GUI_Text_Off(140, 275);
	TFT_DrawLine(10, 313, 262, 313, TFT_White);
}
void GUI_Title_Screen()
{
	TFT_FillScreen_DMA(0x0084);
	GUI_TitleString_Name(50, 330);
	GUI_TitleString_Version(180, 420);
	sImage bmTKA_logo_Flash = {
			TKA_LOGO_BMP_SIZEX, // xSize
			TKA_LOGO_BMP_SIZEY, // ySize
			(uint16_t *)bmp,  // Pointer to picture data
		};
	TFT_DrawBitmap(0, 100, bmTKA_logo_Flash);
	Measure_Color_xy |= CIE_xy_1931_1964;
}


void GUI_DataSet1_Screen()
{
	old_meas_type_E = 2; old_meas_type_L = 2;
	if(preGUI_screen_state != GUI_screen_state || Mode_EL_Old != Mode_EL || Language_status_prev != Language_status){
		Mode_EL_Old = Mode_EL;
		Language_status_prev = Language_status;
		GUI_Panels();
		Prev_Inf_Screen2 = DataSet1_Screen;
		
		if(Language_status == Ru){
			
			GUI_OptionMenuRu();
			Mode_EL ? GUI_TextRu_Illuminance(10, 337):GUI_TextRu_Luminance(10, 337);
		}
		else if (Language_status == En) {
			
			GUI_OptionMenuEn();
			Mode_EL ? GUI_TextEn_Illuminance(10, 339):GUI_TextEn_Luminance(10, 339);
		}
		GUI_CheckBox(200, 327, Measure_Field&Illuminance);
		TFT_DrawLine(10, 377, 262, 377, TFT_White);
	}
}

void GUI_DataSet2_Screen()
{
	if(preGUI_screen_state != GUI_screen_state){
	
			GUI_Panels();
			
			if(Language_status == Ru){
				Mode_EL ? 	GUI_TextRu_Irradiance(18, 82):GUI_TextRu_Radiance(18, 82);
				GUI_CheckBox(200, 70, Measure_Field&Irradiance);
				TFT_DrawLine(10, 120, 262, 120, TFT_White);

				GUI_TextRu_PPF(10, 145);
				GUI_CheckBox(200, 133, Measure_Field&PPFD);
				
				GUI_TextRu_PPF_RGB(10, 209);
				GUI_CheckBox(200, 198, Measure_Field&PPFD_BGR);
				TFT_DrawLine(10, 248, 262, 248, TFT_White);
				
				GUI_TextRu_CCT(20, 275);
				GUI_CheckBox(200, 263, Measure_Field&CCT);
				TFT_DrawLine(10, 313, 262, 313, TFT_White);
				
				GUI_Text_deltaE(20, 337);
				GUI_CheckBox(200, 327, Measure_Field&delta_E);
				TFT_DrawLine(10, 377, 262, 377, TFT_White);
				GUI_Button_Measure_deltaE_Small(130, 327, Measure_Field&delta_E, 0);
			}
			else if(Language_status == En){
				Mode_EL ? 	GUI_TextEn_Irradiance(18, 84) : GUI_TextEn_Radiance(18, 84);
				GUI_CheckBox(200, 70, Measure_Field&Irradiance);
				TFT_DrawLine(10, 120, 262, 120, TFT_White);

				GUI_TextEn_PPFD(10, 147);
				GUI_CheckBox(200, 133, Measure_Field&PPFD);
				
				GUI_TextEn_B_G_R_FR(10, 211);
				GUI_CheckBox(200, 198, Measure_Field&PPFD_BGR);
				TFT_DrawLine(10, 248, 262, 248, TFT_White);
				
				GUI_TextEn_CCT(20, 277);
				GUI_CheckBox(200, 263, Measure_Field&CCT);
				TFT_DrawLine(10, 313, 262, 313, TFT_White);
				
				GUI_Text_deltaE(20, 337);
				GUI_CheckBox(200, 327, Measure_Field&delta_E);
				TFT_DrawLine(10, 377, 262, 377, TFT_White);
				GUI_Button_Measure_deltaE_Small(130, 327, Measure_Field&delta_E, 0);
			}
		}
}

void GUI_DataSet3_Screen()
{
	if(preGUI_screen_state != GUI_screen_state){
		GUI_Panels();

		GUI_Text_CIE_XYZ(20, 82);
		GUI_CheckBox(200, 70, Measure_Field&CIE_XYZ);
		TFT_DrawLine(10, 120, 262, 120, TFT_White);

		GUI_Text_CIE_xy(20, 145);
		GUI_CheckBox(200, 133, Measure_Field&CIE_xy);
		
		GUI_Text_CIE_xy_1931(35, 209);
		GUI_RadioBox(200, 198, Measure_Color_xy&CIE_xy_1931_1964, Measure_Field&CIE_xy);
		GUI_Text_CIE_xy_1964(35, 275);
		GUI_RadioBox(200, 263, !(Measure_Color_xy&CIE_xy_1931_1964), Measure_Field&CIE_xy);
		
		TFT_DrawLine(10, 313, 262, 313, TFT_White);
		
		GUI_Text_CIE_Luv(20, 337);
		GUI_CheckBox(200, 327, Measure_Field&CIE_Luv);
		TFT_DrawLine(10, 377, 262, 377, TFT_White);
	}
}

void GUI_DataSet4_Screen()
{
	if(preGUI_screen_state != GUI_screen_state){
		GUI_Panels();
		
		GUI_Text_CIE_Lab(20, 80);
		GUI_CheckBox(200, 65, Measure_Field&CIE_Lab);

		GUI_Text_A(40, 115);
		GUI_RadioBox(200, 108, Source_Type&Source_A, Measure_Field&CIE_Lab);
		
		GUI_Text_D65(40, 150);
		GUI_RadioBox(200, 143, Source_Type&Source_D65, Measure_Field&CIE_Lab);
		
		GUI_Text_C(40, 185);
		GUI_RadioBox(200, 178, Source_Type&Source_C, Measure_Field&CIE_Lab);
		
		GUI_Text_D50(40, 220);
		GUI_RadioBox(200, 213, Source_Type&Source_D50, Measure_Field&CIE_Lab);
		
		GUI_Text_D55(40, 255);
		GUI_RadioBox(200, 248, Source_Type&Source_D55, Measure_Field&CIE_Lab);
		
		GUI_Text_D75(40, 290);
		GUI_RadioBox(200, 283, Source_Type&Source_D75, Measure_Field&CIE_Lab);
		TFT_DrawLine(10, 330, 262, 330, TFT_White);
		
		Mode_EL ? GUI_Text_EbEr(20, 360) : GUI_Text_LbLr(20, 360);
		GUI_CheckBox(200, 345, Measure_Field&EbEr);
		TFT_DrawLine(10, 390, 262, 390, TFT_White);
	}
}

void GUI_DataSet5_Screen()
{
	if(preGUI_screen_state != GUI_screen_state){
		GUI_Panels();

		GUI_Text_lambda_d(35, 86);
		GUI_CheckBox(200, 70, Measure_Field&lambda_d);
		TFT_DrawLine(10, 120, 262, 120, TFT_White);

		GUI_Text_lambda_c(35, 145);
		GUI_CheckBox(200, 133, Measure_Field&lambda_c);
		TFT_DrawLine(10, 183, 262, 183, TFT_White);
		
		GUI_Text_SP(35, 209);
		GUI_CheckBox(200, 198, Measure_Field&SP_measure);
		TFT_DrawLine(10, 248, 262, 248, TFT_White);
	}
}

void GUI_GraphSet1_Screen()
{
	if(preGUI_screen_state != GUI_screen_state || Language_status_prev != Language_status){
		GUI_Panels();
		Language_status_prev = Language_status;
		Prev_Inf_Screen2 = GraphSet1_Screen;
		if(Language_status == Ru){
			GUI_OptionMenuRu();
			
			GUI_TextRu_PPF_bands(10, 337);
		}
		else if(Language_status == En){
			GUI_OptionMenuEn();
			
			GUI_TextEn_PARwavebands(10, 339);
		}
		
			GUI_CheckBox(200, 327, Graph_Field&PPF_Bands);
			TFT_DrawLine(10, 377, 262, 377, TFT_White);
	}
}

void GUI_GraphSet2_Screen()
{
	if(preGUI_screen_state != GUI_screen_state){
		GUI_Panels();
		
		GUI_Text_EbEr(18, 82);
		GUI_CheckBox(200, 70, Graph_Field&EbEr_graph);
		TFT_DrawLine(10, 122, 262, 122, TFT_White);

		GUI_Text_V_lambda(10, 145);
		GUI_CheckBox(200, 133, Graph_Field&V_lambda);
		TFT_DrawLine(10, 185, 262, 185, TFT_White);
	}
	
}

void GUI_ColorSet1_Screen()
{
	if(preGUI_screen_state != GUI_screen_state || Language_status_prev != Language_status){
		Language_status_prev = Language_status;
		GUI_Panels();
		Prev_Inf_Screen2 = ColorSet1_Screen;
		if(Language_status == Ru){
			GUI_OptionMenuRu();
		}
		else if(Language_status == En){
			GUI_OptionMenuEn();
		}
		
			GUI_Text_CIE_xy(10, 337);
			GUI_RadioBox(200, 327, Color_Field&Color_CIE_xy, 0x01);
			TFT_DrawLine(10, 377, 262, 377, TFT_White);
	}
}

void GUI_ColorSet2_Screen()
{
	if(preGUI_screen_state != GUI_screen_state){
		GUI_Panels();

		GUI_Text_CIE_Luv(20, 82);
		GUI_RadioBox(200, 70, Color_Field&Color_CIE_Luv, 0x01);
		TFT_DrawLine(10, 122, 262, 122, TFT_White);

		GUI_Text_CIE_Lab(20, 145);
		GUI_RadioBox(200, 133, Color_Field&Color_CIE_Lab, 0x01);
		TFT_DrawLine(10, 185, 262, 185, TFT_White);
	}
}

void GUI_ColorRendSet_Screen()
{
	old_meas_type_E = 2; old_meas_type_L = 2;
	if(preGUI_screen_state != GUI_screen_state || Language_status_prev != Language_status){
		GUI_Panels();
		Language_status_prev = Language_status;
		Prev_Inf_Screen2 = ColorRendSet_Screen;
		if(Language_status == Ru){
			GUI_OptionMenuRu();
		}
		if(Language_status == En){
			GUI_OptionMenuEn();
		}
			
			GUI_Text_CRI(30, 325);
			GUI_RadioBox(185, 318, Color_rend_Field&CRI_CQS, 0x01);
			TFT_DrawLine(10, 355, 262, 355, TFT_White);
			 
			GUI_Text_CQS(30, 369);
			GUI_RadioBox(185, 362, !(Color_rend_Field&CRI_CQS), 0x01);
			TFT_DrawLine(10, 401, 262, 401, TFT_White);
	}
}



uint8_t data[15] ={75, 82, 30, 99, 25, 70, 66, 31, 45, 92, 11, 37, 66, 78, 53};


void GUI_Measure_Screen(){
	
	
	if(preGUI_screen_state != GUI_screen_state){
		TFT_FillScreen_DMA(TFT_Black_Bkgr);
		
		screen_count = 0;
		Measure_Elements_Draw(0);
		GUI_Up_Panel();
		GUI_Down_Panel();
		

	} else
	{
			Measure_Elements_Draw(0);
	}
		Prev_Inf_Screen = Measure_Screen;
}

void Measure_Elements_Draw(uint8_t Measure_Number)
{	
	uint16_t Y = 50, limit = 410;
	
	for (uint8_t state_i = Measure_Number; state_i < 15; state_i++)
	{
		screen_count_old = screen_count;
		
		switch(state_i){
					case 0: if(Measure_Field&Illuminance){
					if(Y+35 <= limit){
						Y+=35;
					Mode_EL ?	 GUI_Text_E_Measure(20, Y, E_day, 0):GUI_Text_L_Measure(20, Y, E_day, 0); 
									Y+=35;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							} else {screen_count++;}} break;
				case 1: if(Measure_Field&Irradiance){
					if(Y+35 <= limit){
					Mode_EL ?	GUI_Text_E_Measure(20, Y, E_day_Wt, 1):GUI_Text_L_Measure(20, Y, E_day_Wt, 1); 
									Y+=35;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
					} else {screen_count++;}} break;
				case 2: if(Measure_Field&PPFD){
						if(Y+35 <= limit){
									GUI_Text_PPF_Measure(20, Y, PPFD_PPL_Measure);
									Y+=35;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				
				case 3: if(Measure_Field&PPFD_BGR){
						if(Y+95 <= limit){
									GUI_Text_PPFRGB_Measure(20, Y, PPFD_PPL_Red_Measure, PPFD_PPL_Green_Measure, PPFD_PPL_Blue_Measure, PPFD_PPL_Far_Red_Measure);
									Y+=95;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 4: if(Measure_Field&CCT){
						if(Y+35 <= limit){
							GUI_Text_CCT_Measure(20, Y,  Tc_Measure == 0xFFFF ? 0 : Tc_Measure); //
									Y+=35;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 5: if(Measure_Field&delta_E){
						if(Y+35 <= limit){
									GUI_Text_deltaE_Measure(20, Y, delta_Eab_Measure);
									Y+=35;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 6: if(Measure_Field&CIE_XYZ){
						if(Y+105 <= limit){
									GUI_Text_XYZ_Measure(20, Y, colorimetry_XYZ[0], colorimetry_XYZ[1], colorimetry_XYZ[2]);
									Y+=105;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 7: if(Measure_Field&CIE_xy){
					if(Y+70 <= limit){
									GUI_Text_xy_Measure(20, Y, colorimetry_xy[0], colorimetry_xy[1]);
									Y+=70;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 8: if(Measure_Field&CIE_Luv){
					if(Y+70 <= limit){
									GUI_Text_uv_Measure(20, Y, colorimetry_uv1976[0], colorimetry_uv1976[1]);
									Y+=70;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 9: if(Measure_Field&CIE_Lab){
					if(Y+105 <= limit){
									GUI_Text_LAB_Measure(20, Y, colorimetry_LAB[0],colorimetry_LAB[1], colorimetry_LAB[2]); 
									Y+=105;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 10: if(Measure_Field&lambda_d){
					if(Y+35 <= limit){
									GUI_Text_lambdaD_Measure(20, Y, lambda_d_Measure); 
									Y+=35;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 11: if(Measure_Field&lambda_c){
					if(Y+35 <= limit){
									GUI_Text_lambdaC_Measure(20, Y, lambda_c_Measure); 
									Y+=35;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 12: if(Measure_Field&EbEr){
					if(Y+70 <= limit){
						Mode_EL ?	 GUI_Text_EbEr_Measure(10, Y, ELb_Measure, ELr_Measure):GUI_Text_LbLr_Measure(20, Y, ELb_Measure, ELr_Measure); 
									Y+=70;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
				case 13: if(Measure_Field&SP_measure){
					if(Y+35 <= limit){
						GUI_Text_S_P_Measure(20, Y, SP_Measure); 
									Y+=35;
									TFT_DrawLine(10, Y, 262, Y, TFT_White);
									Y+=10;
							}else {screen_count++;}} break;
			default: break;
		}

		if (screen_count != screen_count_old)
			{
				state_Measure_Elements = state_i;
				screen_count_old = screen_count;
				break;
			}	
			
	}
	
}

void GUI_Measure2_Screen()
{
	old_meas_type_E = 2; old_meas_type_L = 2;
	if(preGUI_screen_state != Measure2_Screen){
		TFT_FillScreen_DMA(TFT_Black_Bkgr);
		current_state_Measure_Draw = state_Measure_Elements;
		screen_count = 1;
		Measure_Elements_Draw(current_state_Measure_Draw);
		GUI_Up_Panel();
		GUI_Down_Panel();
	} else
	{
			Measure_Elements_Draw(current_state_Measure_Draw);
	}
	Prev_Inf_Screen = Measure_Screen;
}

void GUI_Measure3_Screen()
{
	old_meas_type_E = 2; old_meas_type_L = 2;
	if(preGUI_screen_state != Measure3_Screen){
		TFT_FillScreen_DMA(TFT_Black_Bkgr);
		current_state_Measure_Draw= state_Measure_Elements;
		screen_count = 2;
		Measure_Elements_Draw(current_state_Measure_Draw);
		GUI_Up_Panel();
		GUI_Down_Panel();
	} else
	{
			Measure_Elements_Draw(current_state_Measure_Draw);
	}
	Prev_Inf_Screen = Measure_Screen;
}


void GUI_Graph_Screen(){
	float buf_pix;
	uint16_t  jj = 0, ii = 0;

	if((preGUI_screen_state != GUI_screen_state || Rotation_Screen_Spectral_Old != Rotation_Screen_Spectral)){
		TFT_FillScreen_DMA(TFT_Black_Bkgr);
		GUI_Panels();		
		Rotation_Screen_Spectral_Old = Rotation_Screen_Spectral;
		if(Graph_Field&PPF_Bands)
		{
			Spectral_PAR_Range(Rotation_Screen_Spectral);
		}
		
		if(Graph_Field&V_lambda)
		{
			if(Rotation_Screen_Spectral == 0)
				{
				for(uint16_t i = 0; i < 1024; i+=4)
				{
						buf_pix = (Spectral_day[i])*307;
						graph_spectral_day[jj] = (uint16_t)buf_pix;
						buf_pix = (Spectral_night[i])*307;
						graph_spectral_night[jj] = (uint16_t)buf_pix;
						jj++;
				} 

				} else
					{
						for(uint16_t i = 0; i < 1024; i+=3)
						{
								buf_pix = (Spectral_day[i])*209;
								graph_spectral_day[ii] = (uint16_t)buf_pix;
								buf_pix = (Spectral_night[i])*209;
								graph_spectral_night[ii] = (uint16_t)buf_pix;
								ii++;
						}
					}
			
			Spectral_DrawGraph_Const(20, 20, graph_spectral_day, TFT_Yellow, Rotation_Screen_Spectral);
			Spectral_DrawGraph_Const(20, 20, graph_spectral_night, TFT_Blue, Rotation_Screen_Spectral);
			}
			jj = 0; ii = 0;
	
			if(Graph_Field&EbEr_graph)
			{
				if(Rotation_Screen_Spectral == 0)
					{
					for(uint16_t i = 0; i < 1024; i+=4)
					{
							buf_pix = (Hazard_Blue[i])*307;
							graph_spectral_Blue[jj] = (uint16_t)buf_pix;
							buf_pix = (Hazard_Retina[i])/10.*307;
							graph_spectral_Retina[jj] = (uint16_t)buf_pix;
							jj++;
					} 

				} else
					{
						for(uint16_t i = 0; i < 1024; i+=3)
						{
								buf_pix = (Hazard_Blue[i])*209;
								graph_spectral_Blue[ii] = (uint16_t)buf_pix;
								buf_pix = (Hazard_Retina[i])/10.*209;
								graph_spectral_Retina[ii] = (uint16_t)buf_pix;
								ii++;
						}
					}
			
				Spectral_DrawGraph_Const(20, 20, graph_spectral_Blue, TFT_DarkCyan, Rotation_Screen_Spectral);
				
				Spectral_DrawGraph_Const(20, 20, graph_spectral_Retina, TFT_Red, Rotation_Screen_Spectral);
			}
			
		Spectral_Axes(Rotation_Screen_Spectral);
		Spectral_Axes_Text(Rotation_Screen_Spectral);

	}
	Prev_Inf_Screen = Graph_Screen;	

}


uint8_t flag = 0, scr_refresh = 0;
float colorimetry_xy_old[2] = {0}, colorimetry_uv1976_old[2] = {0};
int16_t colorimetry_LAB_old[3] = {0};
void GUI_Color_Screen(){

	if((preGUI_screen_state == Graph_Screen) ||  (preGUI_screen_state == ColorSet1_Screen)||(preGUI_screen_state == ColorSet2_Screen) || (preGUI_screen_state == SD_Write_Screen)){	
		GUI_Panels();	
		TFT_direction = Rotation_Screen_Color;
		TFT_DrawBitmap(Color_Field&Color_CIE_xy? 18:
		Color_Field&Color_CIE_Luv? 18 : 11, Color_Field&Color_CIE_Luv? 172 : 150, Locus); 
		flag = 0;	
		
		if(Color_Field&Color_CIE_xy){GUI_Axes_Locus_XY(18, 150+XY2_LOCUS_BMP_SIZEY, 0);}
		else if(Color_Field&Color_CIE_Luv){GUI_Axes_Locus_LUV(18, 172+LUV_LOCUS_BMP_SIZEY, 0);}
		else if(Color_Field&Color_CIE_Lab) {GUI_Axes_Locus_Lab(125+11, LAB_LOCUS_SIZEY-125+150, 0);}
	}
	preGUI_screen_state = Color_Screen;
	
	Prev_Inf_Screen = Color_Screen;
		
		
	if(Color_Field&Color_CIE_xy) {GUI_Text_xy_Measure(40, 50, colorimetry_xy[0], colorimetry_xy[1]); 
		 scr_refresh++;
		
   if(scr_refresh > 15 ){
		 if(colorimetry_xy[0] < 0.74 & colorimetry_xy[1] < 0.84 ){
		
			 if(flag){		TFT_DrawCutBMP(18-1+colorimetry_xy_old[0]*295-5, 150+XY2_LOCUS_BMP_SIZEY-1-colorimetry_xy_old[1]*300-5,
					 colorimetry_xy_old[0]*295-5, XY2_LOCUS_BMP_SIZEY-1-colorimetry_xy_old[1]*300-5, 10, Locus);}
		colorimetry_xy_old[0] = colorimetry_xy[0];
		colorimetry_xy_old[1] = colorimetry_xy[1];
		TFT_DrawFilledCircle( 18+colorimetry_xy[0]*295, 150+XY2_LOCUS_BMP_SIZEY-colorimetry_xy[1]*300, 2, TFT_Black);
		GUI_Axes_Locus_XY(18, 150+XY2_LOCUS_BMP_SIZEY, 0);
		flag = 1;
		scr_refresh = 0;}
	 }

	
	} else
	if(Color_Field&Color_CIE_Luv) {GUI_Text_uv_Measure(40, 50, colorimetry_uv1976[0], colorimetry_uv1976[1]);
		scr_refresh++;
		if(scr_refresh > 15 ){
		if(colorimetry_uv1976[0] < 0.63 & colorimetry_uv1976[1] < 0.59 & colorimetry_uv1976[0] > 0.0 & colorimetry_uv1976[1] > 0.0){
			
			if(flag){	TFT_DrawCutBMP(18-1+colorimetry_uv1976_old[0]*403-5, 172+LUV_LOCUS_BMP_SIZEY-1-colorimetry_uv1976_old[1]*396-5,
			colorimetry_uv1976_old[0]*403-5, LUV_LOCUS_BMP_SIZEY-1-colorimetry_uv1976_old[1]*396-5, 10, Locus);}
			
			colorimetry_uv1976_old[0] = colorimetry_uv1976[0];
			colorimetry_uv1976_old[1] = colorimetry_uv1976[1];

			TFT_DrawFilledCircle(18 + colorimetry_uv1976[0]*403, 172+LUV_LOCUS_BMP_SIZEY-colorimetry_uv1976[1]*396, 2, TFT_Black);
			GUI_Axes_Locus_LUV(18, 172+LUV_LOCUS_BMP_SIZEY, 0);
			flag = 1;
			scr_refresh = 0;
		 }
	}
	}
	else
	if(Color_Field&Color_CIE_Lab) {GUI_Text_LAB_Measure(40, 45, colorimetry_LAB[0], colorimetry_LAB[1], colorimetry_LAB[2]);
		if(colorimetry_LAB[1] < 128 & colorimetry_LAB[1] > -128 & colorimetry_LAB[2]<128 & colorimetry_LAB[2] > -128){
			if(flag){		TFT_DrawCutBMP(125+11-1+colorimetry_LAB_old[1]*0.976-5, 150+LAB_LOCUS_SIZEY-1-125-colorimetry_LAB_old[2]*0.976-5,
				125+colorimetry_LAB_old[1]*0.976-5, LAB_LOCUS_SIZEY-1-125-colorimetry_LAB_old[2]*0.976-5, 10, Locus);}
				colorimetry_LAB_old[1] = colorimetry_LAB[1];
				colorimetry_LAB_old[2] = colorimetry_LAB[2];
			
				TFT_DrawFilledCircle(125+11+(float)colorimetry_LAB[1]*0.976, LAB_LOCUS_SIZEY-125+150-(float)colorimetry_LAB[2]*0.976, 2, TFT_Black);
				GUI_Axes_Locus_Lab(125+11, LAB_LOCUS_SIZEY-125+150, 0);
				flag = 1;
				scr_refresh = 0;
		}
	}
	TFT_direction = 0x00;
}         


void GUI_ColorRend_Screen(){
	old_meas_type_E = 2; old_meas_type_L = 2;
	if(preGUI_screen_state != GUI_screen_state || Rotation_Screen_Rend_Old != Rotation_Screen_Rend){
		GUI_Panels();		

	Rotation_Screen_Rend_Old = Rotation_Screen_Rend;
		GUI_Bar_Measure(85, 13, Color_rend_Field? bar_CRI : bar_CQS);
	Prev_Inf_Screen = Color_Rendition_Screen;
	if (Color_rend_Field&CRI_CQS){
		CRI_Draw(Rotation_Screen_Rend, Ri, Ra, Rall, R9);
	}
	else{
		CQS_Draw(Rotation_Screen_Rend, Q_i, Qa, Qp, Qf);
	}
	}
	if(Calc_ColorRend != Calc_ColorRend_old){
		Calc_ColorRend_old = Calc_ColorRend;
		if (Color_rend_Field&CRI_CQS){
			CRI_Draw(Rotation_Screen_Rend, Ri, Ra, Rall, R9);
		}
		else{
			CQS_Draw(Rotation_Screen_Rend, Q_i, Qa, Qp, Qf);
		}
	}
}

void GUI_Error_Screen()
{
	TFT_FillScreen_DMA(TFT_Red);

}

void GUI_Information_Screen()
{
	if(preGUI_screen_state != GUI_screen_state){
		TFT_FillScreen_DMA(TFT_Black_Bkgr);
		if(Language_status == En){
			GUI_TextEn_Info_Callibration(0, 0, (uint8_t)(Calibration_date&0x00FF), (uint8_t)(Calibration_month&0x00FF), Calibration_year);
			GUI_TextEn_Info_Serial(0,0, Serial_part_device, Serial_number_device);
			GUI_TextEn_Info_Ver(0, 0, VERSION);
		}	
		else
		{	
			GUI_TextRu_Info_Callibration(0, 0,(uint8_t)(Calibration_date&0x00FF), (uint8_t)(Calibration_month&0x00FF), Calibration_year);
			GUI_TextRu_Info_Serial(0,0, Serial_part_device, Serial_number_device);
			GUI_TextRu_Info_Ver(0, 0, VERSION);
		}
	}
}

void GUI_SD_Write_Screen()
{
	
	if(preGUI_screen_state != GUI_screen_state){
		pause = 1;
		TFT_FillScreen_DMA(TFT_Black_Bkgr);
		if(Language_status == En){
			GUI_TextEn_WriteSD(80, 120);
		}
		else
		{	
				 GUI_TextRu_WriteSD(80, 120);
		}
		if (SD_Detect == 0) {
			Calculate_SD_Data(); 
			SD_Witer(sdfile_cnt, Language_status, Memory_Data_satus, Mode_EL, CRICQS_done);

		}
	}
	
	GUI_Bar_Measure(85, 280, SDWr_Status_bar);
	
	if(SDWr_Status_bar == 1){
			if(sdfile_cnt < 999){
					sdfile_cnt++;
				}else{
					sdfile_cnt = 0;
				} 
			WriteSDFLASH_t(sdfile_cnt);  
			pause = 0; 
			GUI_screen_state = Prev_Inf_Screen;
	}

}


void GUI_Up_Panel()
{
	GUI_Battery_Level(0, 0, percentage_charge);
	if (Bluetooth == ON){
		GUI_Bluetooth_Logo(240, 5);
	} else
	{
		TFT_FillRectangle(239, 4, 260, 35, TFT_Black_Bkgr);
	}
}

void GUI_Down_Panel()
{		
	GUI_Button_Settings(1, 426);
	GUI_Button_SD_Card(55, 426, !SD_Detect);
	GUI_Button_Measure_Start_Pause(109, 426);
	
	if(GUI_screen_state >= DataSet1_Screen)
	{
		GUI_Button_Down(163, 426);
		GUI_Button_TFT_On_Off(217, 426);
	}else if(GUI_screen_state <= Measure3_Screen)
	{
		GUI_Button_Down_Active(163, 426, (screen_count > 0));
		GUI_Button_Right(217, 426);
	} 
	else
	{
		GUI_Button_TFT_Rotate(163, 426);
		GUI_Button_Right(217, 426);
	}
}

void GUI_Panels()
{
	if((GUI_screen_state == Measure_Screen && (preGUI_screen_state !=Measure2_Screen 
			|| preGUI_screen_state !=Measure3_Screen)) || (GUI_screen_state == Graph_Screen) 
			|| (GUI_screen_state >= DataSet1_Screen && preGUI_screen_state < DataSet1_Screen)
			|| (preGUI_screen_state >= DataSet1_Screen && GUI_screen_state < DataSet1_Screen)
			|| (preGUI_screen_state == Information_Screen) || ((GUI_screen_state == Color_Rendition_Screen) && preGUI_screen_state < Color_Rendition_Screen))
	{
		TFT_FillScreen_DMA(TFT_Black_Bkgr);
		GUI_Up_Panel();
		GUI_Down_Panel();
	} 
	else 
	{
		TFT_FillRectangle(0, 40, 271, 425, TFT_Black_Bkgr);
	}
}
void GUI_LaserOnOff(void)
{
		if(Mode_EL == 0x00)
	{
		LaserOnOff = !LaserOnOff;
		if(LaserOnOff == 0){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		}else
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		}
	}
}

void GUI_TouchError()
{

}

void GUI_Display_Refresh()
{
	
	switch(GUI_screen_state){
		case Measure_Screen: GUI_Measure_Screen(); preGUI_screen_state = Measure_Screen; break;
		case Measure2_Screen: GUI_Measure2_Screen(); preGUI_screen_state = Measure2_Screen; break;
		case Measure3_Screen: GUI_Measure3_Screen(); preGUI_screen_state = Measure3_Screen; break;
		
		case Graph_Screen: GUI_Graph_Screen(); preGUI_screen_state = Graph_Screen; break;
		case Color_Screen: GUI_Color_Screen(); preGUI_screen_state = Color_Screen; break; 
		case Color_Rendition_Screen: GUI_ColorRend_Screen(); preGUI_screen_state = Color_Rendition_Screen; break;		
		
		case DataSet1_Screen: GUI_DataSet1_Screen();  preGUI_screen_state = DataSet1_Screen; break;
		case DataSet2_Screen: GUI_DataSet2_Screen();  preGUI_screen_state = DataSet2_Screen; break;
		case DataSet3_Screen: GUI_DataSet3_Screen();  preGUI_screen_state = DataSet3_Screen; break;
		case DataSet4_Screen: GUI_DataSet4_Screen();  preGUI_screen_state = DataSet4_Screen; break;
		case DataSet5_Screen: GUI_DataSet5_Screen();  preGUI_screen_state = DataSet5_Screen; break;
		case GraphSet1_Screen: GUI_GraphSet1_Screen(); preGUI_screen_state = GraphSet1_Screen; break;
		case GraphSet2_Screen: GUI_GraphSet2_Screen(); preGUI_screen_state = GraphSet2_Screen; break;
		case ColorSet1_Screen: GUI_ColorSet1_Screen(); preGUI_screen_state = ColorSet1_Screen; break;
		case ColorSet2_Screen: GUI_ColorSet2_Screen(); preGUI_screen_state = ColorSet2_Screen; break;
		case ColorRendSet_Screen:GUI_ColorRendSet_Screen();preGUI_screen_state = ColorRendSet_Screen; break;
					
		case Information_Screen : GUI_Information_Screen();preGUI_screen_state = Information_Screen; break;
		case SD_Write_Screen : GUI_SD_Write_Screen();preGUI_screen_state = SD_Write_Screen; break;
		default: break;
	}
}

void GUI_Touch_Processing()
{
	uint16_t Touch_x = 0, Touch_y = 0;
	TS_Get_XY1(TS_I2C_ADDRESS, &Touch_x, &Touch_y);
	switch(GUI_screen_state){
		
		case Measure_Screen:
			preGUI_screen_state = GUI_screen_state;
		
			if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Settings
				{	
					GUI_screen_state = DataSet1_Screen;
				} 
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //down
				{	
					GUI_screen_state = (screen_count > 0) ? Measure2_Screen : Measure_Screen; 
					WriteFLASH_Screen(GUI_screen_state);
				}
				else 
			if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Next
				{
					WriteFLASH_Screen(Graph_Screen);
					GUI_screen_state =  Graph_Screen;
				}else
			if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
					if(!SD_Detect){if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}}
				}		else
				if(Touch_x >= 109*TS_Callib & Touch_x <= (109+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Measure
				{
						pause = !pause;
						GUI_Bar_Measure(85, 13, 0.0);
				}		

		break;
				
	case Measure2_Screen:
			preGUI_screen_state = GUI_screen_state;
		
			if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Settings
				{	
					GUI_screen_state = DataSet1_Screen;
				} 
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Settings
				{	
					GUI_screen_state = (screen_count > 1) ? Measure3_Screen : Measure_Screen; 
					WriteFLASH_Screen(GUI_screen_state);
				}
				else 
			if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Next
				{
					WriteFLASH_Screen(Graph_Screen);
					GUI_screen_state = Graph_Screen;
				}else
			if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		else
				if(Touch_x >= 109*TS_Callib & Touch_x <= (109+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Measure
				{
						pause = !pause;
				}		

		break;

case Measure3_Screen:
			preGUI_screen_state = GUI_screen_state;
		
			if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Settings
				{	
					GUI_screen_state = DataSet1_Screen;
				} 
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Down
				{	
					GUI_screen_state = Measure_Screen;
					WriteFLASH_Screen(GUI_screen_state);
				}
				else 
			if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Next
				{
					WriteFLASH_Screen(Graph_Screen);
					GUI_screen_state = Graph_Screen;
				}else
			if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		else
				if(Touch_x >= 109*TS_Callib & Touch_x <= (109+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Measure
				{
						pause = !pause;
						GUI_Bar_Measure(85, 13, 0.0);
				}		
		break;
				
		case Graph_Screen:
			preGUI_screen_state = GUI_screen_state;
			if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Settings
				{	
					GUI_screen_state = GraphSet1_Screen;
				}  
			if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Rotation_Screen
				{
					if(Rotation_Screen_Spectral < 0x02) {Rotation_Screen_Spectral++;} else{Rotation_Screen_Spectral= 0x00;}
				}else 
			if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Next
				{
					WriteFLASH_Screen(Color_Screen);
					GUI_screen_state = Color_Screen;
				}else
			if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
						if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}	
				else 	 
				if(Touch_x >= 109*TS_Callib & Touch_x <= (109+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Measure
				{
					pause = !pause;
				}					
		break;
				
		case Color_Screen:
			preGUI_screen_state = GUI_screen_state;
		
			if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Settings
				{	
					preColor_Field = Color_Field;
					GUI_screen_state = ColorSet1_Screen;
				} else 
			if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Next
				{
					WriteFLASH_Screen(Color_Rendition_Screen);
					GUI_screen_state = Color_Rendition_Screen;
				}	else 
				if(Touch_x >= 109*TS_Callib & Touch_x <= (109+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Measure
				{
					pause = !pause;
				}else 			
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
					if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		else	if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Rotation_Screen
				{
//					if(Rotation_Screen_Color < 0x02) {Rotation_Screen_Color++;} else{Rotation_Screen_Color = 0x00;}
				}		 							
		break;
	
		case Color_Rendition_Screen:
			preGUI_screen_state = GUI_screen_state;
		
			if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Settings
				{	
					GUI_screen_state = ColorRendSet_Screen;
				} else 
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Next
				{
					WriteFLASH_Screen(Measure_Screen);
					GUI_screen_state = Measure_Screen;
				}	else 			
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Rotation_Screen
				{
					if(Rotation_Screen_Rend < 0x02) {Rotation_Screen_Rend++;} else{Rotation_Screen_Rend = 0x00;}
				}		else 
				if(Touch_x >= 109*TS_Callib & Touch_x <= (109+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Measure
				{

				//	calculate if CRI or CQS
					if (Color_rend_Field & CRI_CQS){
						CRICQS_done = 0x00;
						max_Rabs = Rabs_find_MAX_all(Line_Rabs_buff);
						Calculate_XYZ(Line_Rabs_buff, calibratre_x_1931, calibratre_y_1931, calibratre_z_1931);
						Calculate_xy(colorimetry_XYZ);
						Calculate_uv(colorimetry_xy);
						Tc_Measure = Calculate_Tc(Line_Rabs_buff, Measure_Color_xy);
						if(Tc_Measure == 0xFFFF ){Ra = 0; Rall = 0; R9 = 0; memset(Ri, 0, sizeof(Ri)); }
						else	{CRI_func(Tc_Measure, Line_Rabs_buff);}
						CRICQS_done = 0x01;
					}
					else{
						CRICQS_done = 0x00;
						pause = 1;
						Calculate_XYZ(Line_Rabs_buff, calibratre_x_1931, calibratre_y_1931, calibratre_z_1931);
						Calculate_xy(colorimetry_XYZ);
						Tc_Measure = Calculate_Tc(Line_Rabs_buff, Measure_Color_xy);
						max_Rabs = Rabs_find_MAX_all(Line_Rabs_buff);
						if(Tc_Measure == 0xFFFF ){Qa = 0; Qp = 0; Qf = 0; memset(Q_i, 0, sizeof(Q_i)); }
						else	{cqs_func(Tc_Measure, Line_Rabs_buff);}
						CRICQS_done = 0x01;
						pause = 0;
					}
					Calc_ColorRend = !Calc_ColorRend;
					GUI_Display_Refresh();
				}	else 			
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
						pause = 1;
						if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
						pause = 0;
				}								
		break;
		
		case DataSet1_Screen:
			preGUI_screen_state = GUI_screen_state;
		
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Down
				{	
					GUI_screen_state = DataSet2_Screen;
				} else
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=202*TS_Callib & Touch_y <=(202+54)*TS_Callib) //Mode_EL
				{
					Mode_EL = !Mode_EL;
					Calibration_Load_Pack(Mode_EL == 0x00 ? SPECTRAL_CORRECTION_L:SPECTRAL_CORRECTION_E, 0x400, Spectral_Corection_Buff);
					Factor2 = (Mode_EL == 0x00 ? Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_L) : Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_E));
					GUI_Switch_ButtonActive(182, 202, Mode_EL);
				}				
				else
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=268*TS_Callib & Touch_y <=(268+54)*TS_Callib) //Bluetooth
				{	
					Bluetooth = !Bluetooth;
					GUI_Switch_Button(182, 268, Bluetooth);
					GUI_Up_Panel();
				}
				else
				if(Touch_x >= 8*TS_Callib & Touch_x <= (250)*TS_Callib & Touch_y >=124*TS_Callib & Touch_y <=(174)*TS_Callib) // Information
				{
					GUI_screen_state = Information_Screen;
				}	else
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=327*TS_Callib & Touch_y <=(327+54)*TS_Callib) //Illuminance
				{	
					Measure_Field ^= Illuminance;
					GUI_CheckBox(200, 327, Measure_Field&Illuminance);
					
				}else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{	 
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					}
				} else
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(Touch_x >= 8*TS_Callib & Touch_x <= (250)*TS_Callib & Touch_y >=80*TS_Callib & Touch_y <=(120)*TS_Callib) // Language change
				{
					if (Language_status == Ru) Language_status=En;
					else if (Language_status == En) Language_status=Ru;
				}	else
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}	else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}
			break;
		case DataSet2_Screen:
				preGUI_screen_state = GUI_screen_state;
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib)////down
				{	
					GUI_screen_state = DataSet3_Screen;
				} else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=70*TS_Callib & Touch_y <=(70+54)*TS_Callib) //Irradiance
				{	
					Measure_Field ^= Irradiance;
					GUI_CheckBox(200, 70, Measure_Field&Irradiance);
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=133*TS_Callib & Touch_y <=(133+54)*TS_Callib) //PPFD
				{	
					Measure_Field ^= PPFD;
					GUI_CheckBox(200, 133, Measure_Field&PPFD);
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=198*TS_Callib & Touch_y <=(198+54)*TS_Callib) //PPFD_BGR
				{	
					Measure_Field ^= PPFD_BGR;
					GUI_CheckBox(200, 198, Measure_Field&PPFD_BGR);
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=263*TS_Callib & Touch_y <=(263+54)*TS_Callib) //CCT
				{	
					Measure_Field ^= CCT;
					GUI_CheckBox(200, 263, Measure_Field&CCT);
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=327*TS_Callib & Touch_y <=(327+54)*TS_Callib) //delta_E
				{	
					Measure_Field ^= delta_E;
					GUI_CheckBox(200, 327, Measure_Field&delta_E);
					GUI_Button_Measure_deltaE_Small(130, 327, Measure_Field&delta_E, 0);
				} 				
				else	if(Touch_x >= 130*TS_Callib & Touch_x <= (200+38)*TS_Callib & Touch_y >=327*TS_Callib & Touch_y <=(327+54)*TS_Callib) //delta_E_measure_small
				{	
					if(Measure_Field&delta_E)
					{
						Calculate_Lab(colorimetry_XYZ, Measure_Color_xy, Source_Type);
						colorimetry_LAB_mem[0] = colorimetry_LAB[0];
						colorimetry_LAB_mem[1] = colorimetry_LAB[1];
						colorimetry_LAB_mem[2] = colorimetry_LAB[2];
						GUI_Button_Measure_deltaE_Small(130, 327, Measure_Field&delta_E, 1);
					}
				} 		
				else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{	
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					}
				} 
				else	
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}	else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}				
			break;
		case DataSet3_Screen:
					preGUI_screen_state = GUI_screen_state;
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib)// down
				{	
					GUI_screen_state = DataSet4_Screen;
				} else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=70*TS_Callib & Touch_y <=(70+54)*TS_Callib) //CIE_XYZ
				{
					Measure_Field ^= CIE_XYZ;
					GUI_CheckBox(200, 70, Measure_Field&CIE_XYZ);
				} else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=133*TS_Callib & Touch_y <=(133+54)*TS_Callib) //CIE_xy
				{
					Measure_Field ^= CIE_xy;
					GUI_CheckBox(200, 133, Measure_Field&CIE_xy);
					GUI_RadioBox(200, 198, Measure_Color_xy&CIE_xy_1931_1964, Measure_Field&CIE_xy);
					GUI_RadioBox(200, 263, !(Measure_Color_xy&CIE_xy_1931_1964), Measure_Field&CIE_xy);
				}	else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=327*TS_Callib & Touch_y <=(327+54)*TS_Callib) //CIE_Luv
				{
					Measure_Field ^= CIE_Luv;
					GUI_CheckBox(200, 327, Measure_Field&CIE_Luv);
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=198*TS_Callib & Touch_y <=(198+54)*TS_Callib && (Measure_Field&CIE_xy)) //CIE_xy_1931
				{
					if(!(Measure_Color_xy&CIE_xy_1931_1964)){
						Measure_Color_xy ^= CIE_xy_1931_1964;
						GUI_RadioBox(200, 198, Measure_Color_xy&CIE_xy_1931_1964, 0x01);
						GUI_RadioBox(200, 263, !(Measure_Color_xy&CIE_xy_1931_1964), 0x01);
					}
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=263*TS_Callib & Touch_y <=(263+54)*TS_Callib && (Measure_Field&CIE_xy)) //CIE_xy_1964
				{
					if((Measure_Color_xy&CIE_xy_1931_1964)){
						Measure_Color_xy ^= CIE_xy_1931_1964;
						GUI_RadioBox(200, 198, Measure_Color_xy&CIE_xy_1931_1964, 0x01);
						GUI_RadioBox(200, 263, !(Measure_Color_xy&CIE_xy_1931_1964), 0x01);
					}
				}else	
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}		else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{	
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					}
				} else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		
			break;
				
		case DataSet4_Screen:
					preGUI_screen_state = GUI_screen_state;
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //down
				{	
					GUI_screen_state = DataSet5_Screen;
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=65*TS_Callib & Touch_y <=(65+54)*TS_Callib) //CIE_Lab
				{
					Measure_Field ^= CIE_Lab;
					GUI_CheckBox(200, 65, Measure_Field&CIE_Lab);
					GUI_RadioBox(200, 108, Source_Type&Source_A, Measure_Field&CIE_Lab);
					GUI_RadioBox(200, 143, Source_Type&Source_D65, Measure_Field&CIE_Lab);
					GUI_RadioBox(200, 178, Source_Type&Source_C, Measure_Field&CIE_Lab);
					GUI_RadioBox(200, 213, Source_Type&Source_D50, Measure_Field&CIE_Lab);
					GUI_RadioBox(200, 248, Source_Type&Source_D55, Measure_Field&CIE_Lab);
					GUI_RadioBox(200, 283, Source_Type&Source_D75, Measure_Field&CIE_Lab);
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=345*TS_Callib & Touch_y <=(345+54)*TS_Callib) //EbEr
				{
					Measure_Field ^= EbEr;
					GUI_CheckBox(200, 345, Measure_Field&EbEr);
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=108*TS_Callib & Touch_y <=(108+54)*TS_Callib && (Measure_Field&CIE_Lab)) //Source_A
				{
					if(!(Source_Type&Source_A))
					{
						Source_Type = 0;
						GUI_RadioBox(200, 108, Source_Type|=Source_A, 0x01);
						GUI_RadioBox(200, 143, Source_Type&Source_D65, 0x01);
						GUI_RadioBox(200, 178, Source_Type&Source_C, 0x01);
						GUI_RadioBox(200, 213, Source_Type&Source_D50, 0x01);
						GUI_RadioBox(200, 248, Source_Type&Source_D55, 0x01);
						GUI_RadioBox(200, 283, Source_Type&Source_D75, 0x01);
					}
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=143*TS_Callib & Touch_y <=(143+54)*TS_Callib && (Measure_Field&CIE_Lab)) //Source_D65
				{
					if(!(Source_Type&Source_D65))
					{
						Source_Type = 0;
						GUI_RadioBox(200, 108, Source_Type&Source_A, 0x01);
						GUI_RadioBox(200, 143, Source_Type|=Source_D65, 0x01);
						GUI_RadioBox(200, 178, Source_Type&Source_C, 0x01);
						GUI_RadioBox(200, 213, Source_Type&Source_D50, 0x01);
						GUI_RadioBox(200, 248, Source_Type&Source_D55, 0x01);
						GUI_RadioBox(200, 283, Source_Type&Source_D75, 0x01);
					}
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=178*TS_Callib & Touch_y <=(178+54)*TS_Callib && (Measure_Field&CIE_Lab)) //Source_C
				{
					if(!(Source_Type&Source_C))
					{
						Source_Type = 0;
						GUI_RadioBox(200, 108, Source_Type&Source_A, 0x01);
						GUI_RadioBox(200, 143, Source_Type&Source_D65, 0x01);
						GUI_RadioBox(200, 178, Source_Type|=Source_C, 0x01);
						GUI_RadioBox(200, 213, Source_Type&Source_D50, 0x01);
						GUI_RadioBox(200, 248, Source_Type&Source_D55, 0x01);
						GUI_RadioBox(200, 283, Source_Type&Source_D75, 0x01);
					}
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=213*TS_Callib & Touch_y <=(213+54)*TS_Callib && (Measure_Field&CIE_Lab)) //Source_D50
				{
					if(!(Source_Type&Source_D50))
					{
						Source_Type = 0;
						GUI_RadioBox(200, 108, Source_Type&Source_A, 0x01);
						GUI_RadioBox(200, 143, Source_Type&Source_D65, 0x01);
						GUI_RadioBox(200, 178, Source_Type&Source_C, 0x01);
						GUI_RadioBox(200, 213, Source_Type|=Source_D50, 0x01);
						GUI_RadioBox(200, 248, Source_Type&Source_D55, 0x01);
						GUI_RadioBox(200, 283, Source_Type&Source_D75, 0x01);
					}
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=248*TS_Callib & Touch_y <=(248+54)*TS_Callib && (Measure_Field&CIE_Lab)) //Source_D55
				{
					if(!(Source_Type&Source_D55))
					{
						Source_Type = 0;
						GUI_RadioBox(200, 108, Source_Type&Source_A, 0x01);
						GUI_RadioBox(200, 143, Source_Type&Source_D65, 0x01);
						GUI_RadioBox(200, 178, Source_Type&Source_C, 0x01);
						GUI_RadioBox(200, 213, Source_Type&Source_D50, 0x01);
						GUI_RadioBox(200, 248, Source_Type |= Source_D55, 0x01);
						GUI_RadioBox(200, 283, Source_Type&Source_D75, 0x01);
					}
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=283*TS_Callib & Touch_y <=(283+54)*TS_Callib && (Measure_Field&CIE_Lab)) //Source_D75
				{
					if(!(Source_Type&Source_D75))
					{
						Source_Type = 0;
						GUI_RadioBox(200, 108, Source_Type&Source_A, 0x01);
						GUI_RadioBox(200, 143, Source_Type&Source_D65, 0x01);
						GUI_RadioBox(200, 178, Source_Type&Source_C, 0x01);
						GUI_RadioBox(200, 213, Source_Type&Source_D50, 0x01);
						GUI_RadioBox(200, 248, Source_Type&Source_D55, 0x01);
						GUI_RadioBox(200, 283, Source_Type|=Source_D75, 0x01);
					}
				}else	
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}		else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					} 
				} else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		
				
			break;
		case DataSet5_Screen:
					preGUI_screen_state = GUI_screen_state;
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Next
				{	
					GUI_screen_state = DataSet1_Screen;
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=70*TS_Callib & Touch_y <=(70+54)*TS_Callib) //EbEr
				{
					Measure_Field ^= lambda_d;
					GUI_CheckBox(200, 70, Measure_Field&lambda_d);
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=133*TS_Callib & Touch_y <=(133+54)*TS_Callib) //EbEr
				{
					Measure_Field ^= lambda_c;
					GUI_CheckBox(200, 133, Measure_Field&lambda_c);
				}else 
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=198*TS_Callib & Touch_y <=(198+54)*TS_Callib) //EbEr
				{
					Measure_Field ^= SP_measure;
					GUI_CheckBox(200, 198, Measure_Field&SP_measure);
				}else	
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}		else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{	
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					}
				} else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		
			break;
				
		case GraphSet1_Screen:
					preGUI_screen_state = GUI_screen_state;
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //next
				{	
					GUI_screen_state = GraphSet2_Screen;
				}	else 
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=202*TS_Callib & Touch_y <=(202+54)*TS_Callib) //Mode_EL
				{
					Mode_EL = !Mode_EL;
					Calibration_Load_Pack(Mode_EL == 0x00 ? SPECTRAL_CORRECTION_L:SPECTRAL_CORRECTION_E, 0x400, Spectral_Corection_Buff);
					Factor2 = (Mode_EL == 0x00 ? Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_L) : Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_E));
					GUI_Switch_ButtonActive(182, 202, Mode_EL);
				}				
				else
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=268*TS_Callib & Touch_y <=(268+54)*TS_Callib) //Bluetooth
				{	
					Bluetooth = !Bluetooth;
					GUI_Switch_Button(182, 268, Bluetooth);
					GUI_Up_Panel();
				}
				else
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=327*TS_Callib & Touch_y <=(327+54)*TS_Callib) //PPF_Bands
				{	
					Graph_Field ^= PPF_Bands;
					GUI_CheckBox(200, 327, Graph_Field&PPF_Bands);
				}else	
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}		else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{	
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					}
				}else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		
				else
				if(Touch_x >= 8*TS_Callib & Touch_x <= (250)*TS_Callib & Touch_y >=80*TS_Callib & Touch_y <=(120)*TS_Callib) // Language change
				{
					if (Language_status == Ru) Language_status=En;
					else if (Language_status == En) Language_status=Ru;
				}	 else
				if(Touch_x >= 8*TS_Callib & Touch_x <= (250)*TS_Callib & Touch_y >=124*TS_Callib & Touch_y <=(174)*TS_Callib) // Information
				{
					GUI_screen_state = Information_Screen;
				}	
			break;

		case GraphSet2_Screen:
					preGUI_screen_state = GUI_screen_state;
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //next
				{	
					GUI_screen_state = GraphSet1_Screen;
				}	
				else
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=70*TS_Callib & Touch_y <=(70+54)*TS_Callib) //PPF_Bands
				{	
					Graph_Field ^= EbEr_graph;
					GUI_CheckBox(200, 70, Graph_Field&EbEr_graph);
				}	
				else
				if(Touch_x >= 200*TS_Callib & Touch_x <= (200+54)*TS_Callib & Touch_y >=133*TS_Callib & Touch_y <=(133+54)*TS_Callib) //PPF_Bands
				{	
					Graph_Field ^= V_lambda;
					GUI_CheckBox(200, 133, Graph_Field&V_lambda);
				}else	
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}		else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{	
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					}
				} else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		
			break;
				   
			case ColorSet1_Screen:
					preGUI_screen_state = GUI_screen_state;
					
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //next
				{	
					GUI_screen_state = ColorSet2_Screen;
				}
				else 
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=202*TS_Callib & Touch_y <=(202+54)*TS_Callib) //Mode_EL
				{
					Mode_EL = !Mode_EL;
					Calibration_Load_Pack(Mode_EL == 0x00 ? SPECTRAL_CORRECTION_L:SPECTRAL_CORRECTION_E, 0x400, Spectral_Corection_Buff);
					Factor2 = (Mode_EL == 0x00 ? Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_L) : Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_E));
					GUI_Switch_ButtonActive(182, 202, Mode_EL);
				}				
				else
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=268*TS_Callib & Touch_y <=(268+54)*TS_Callib) //Bluetooth
				{	
					Bluetooth = !Bluetooth;
					GUI_Switch_Button(182, 268, Bluetooth);
					GUI_Up_Panel();
				}
				else 
				if(Touch_x >= 8*TS_Callib & Touch_x <= (250)*TS_Callib & Touch_y >=124*TS_Callib & Touch_y <=(174)*TS_Callib) // Information
				{
					GUI_screen_state = Information_Screen;
				}	else
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=327*TS_Callib & Touch_y <=(327+54)*TS_Callib) //Color_CIE_xy
				{	
					if(!(Color_Field&Color_CIE_xy))
					{
						Color_Field = 0;
						GUI_RadioBox(200, 327, Color_Field|=Color_CIE_xy, 0x01);
					}
				}else	
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}		else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{	
					if(preColor_Field != Color_Field)
					{
						Image_load(Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP : XY10_LOCUS_BMP):
						Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP : LAB_LOCUS_BMP,
						Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEX*XY2_LOCUS_BMP_SIZEY : XY10_LOCUS_BMP_SIZEX*XY10_LOCUS_BMP_SIZEY):
						Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEX*LUV_LOCUS_BMP_SIZEY : LAB_LOCUS_SIZEX*LAB_LOCUS_SIZEY);		
						
						Locus.pData = (uint16_t *)bmp;
						Locus.Width = Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEX : XY10_LOCUS_BMP_SIZEX):
						Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEX : LAB_LOCUS_SIZEX;
						Locus.Height = Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEY : XY10_LOCUS_BMP_SIZEY):
						Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEY : LAB_LOCUS_SIZEY;
					}
					
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					}
				}	else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		else
				if(Touch_x >= 8*TS_Callib & Touch_x <= (250)*TS_Callib & Touch_y >=80*TS_Callib & Touch_y <=(120)*TS_Callib) // Language change
				{
					if (Language_status == Ru) Language_status=En;
					else if (Language_status == En) Language_status=Ru;
				}	 
				
			break;
			case ColorSet2_Screen:
					preGUI_screen_state = GUI_screen_state;
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //next
				{	
					GUI_screen_state = ColorSet1_Screen;
				}
				else 
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=70*TS_Callib & Touch_y <=(70+54)*TS_Callib) //Color_CIE_Luv
				{	
					if(!(Color_Field&Color_CIE_Luv))
					{
						Color_Field = 0;
						GUI_RadioBox(200, 70, Color_Field|=Color_CIE_Luv, 0x01);
						GUI_RadioBox(200, 133, Color_Field&Color_CIE_Lab, 0x01);
					}
				}
				else 
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=133*TS_Callib & Touch_y <=(133+54)*TS_Callib) //Color_CIE_Lab
				{	
					if(!(Color_Field&Color_CIE_Lab))
					{
						Color_Field = 0;
						GUI_RadioBox(200, 70, Color_Field&Color_CIE_Luv, 0x01);
						GUI_RadioBox(200, 133, Color_Field|=Color_CIE_Lab, 0x01);
					}
				}else	
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}		else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{	
					if(preColor_Field != Color_Field)
					{
								Image_load(Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP : XY10_LOCUS_BMP):
								Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP : LAB_LOCUS_BMP,
								Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEX*XY2_LOCUS_BMP_SIZEY : XY10_LOCUS_BMP_SIZEX*XY10_LOCUS_BMP_SIZEY):
								Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEX*LUV_LOCUS_BMP_SIZEY : LAB_LOCUS_SIZEX*LAB_LOCUS_SIZEY);		
								
								Locus.pData = (uint16_t *)bmp;
								Locus.Width = Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEX : XY10_LOCUS_BMP_SIZEX):
								Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEX : LAB_LOCUS_SIZEX;
								Locus.Height = Color_Field&Color_CIE_xy ? (Measure_Color_xy&CIE_xy_1931_1964 ? XY2_LOCUS_BMP_SIZEY : XY10_LOCUS_BMP_SIZEY):
								Color_Field&Color_CIE_Luv ? LUV_LOCUS_BMP_SIZEY : LAB_LOCUS_SIZEY;
					}
					
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					}
				} else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		
				
			break;
				
		case ColorRendSet_Screen:
					preGUI_screen_state = GUI_screen_state;
				if(Touch_x >= 163*TS_Callib & Touch_x <= (163+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib)//next
				{	
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Color_Rendition_Screen;
				}
				else 
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=202*TS_Callib & Touch_y <=(202+54)*TS_Callib) //Mode_EL
				{
					Mode_EL = !Mode_EL;
					Calibration_Load_Pack(Mode_EL == 0x00 ? SPECTRAL_CORRECTION_L:SPECTRAL_CORRECTION_E, 0x400, Spectral_Corection_Buff);
					Factor2 = (Mode_EL == 0x00 ? Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_L) : Rabs_calc_Factor2_Settings_change(Exposure_Factor, EnergyFactor_E));
					GUI_Switch_ButtonActive(182, 202, Mode_EL);
				}				
				else
				if(Touch_x >= 182*TS_Callib & Touch_x <= (182+54)*TS_Callib & Touch_y >=268*TS_Callib & Touch_y <=(268+54)*TS_Callib) //Bluetooth
				{	
					Bluetooth = !Bluetooth;
					GUI_Switch_Button(182, 268, Bluetooth);
					GUI_Up_Panel();
				}else 
				if(Touch_x >= 8*TS_Callib & Touch_x <= (250)*TS_Callib & Touch_y >=124*TS_Callib & Touch_y <=(174)*TS_Callib) // Information
				{
					GUI_screen_state = Information_Screen;
				}	else
				if(Touch_x >= 185*TS_Callib & Touch_x <= (185+54)*TS_Callib & Touch_y >=318*TS_Callib & Touch_y <=(318+54)*TS_Callib) //CRI
				{
					if(!(Color_rend_Field & CRI_CQS)){
						Color_rend_Field ^= CRI_CQS;
						GUI_RadioBox(185, 318, Color_rend_Field&CRI_CQS, 0x01);
						GUI_RadioBox(185, 362, !(Color_rend_Field&CRI_CQS), 0x01);
					}
				}else 
				if(Touch_x >= 185*TS_Callib & Touch_x <= (185+54)*TS_Callib & Touch_y >=362*TS_Callib & Touch_y <=(362+54)*TS_Callib) //CQS
				{
					if((Color_rend_Field&CRI_CQS)){
						Color_rend_Field ^= CRI_CQS;
						GUI_RadioBox(185, 318, Color_rend_Field&CRI_CQS, 0x01);
						GUI_RadioBox(185, 362, !(Color_rend_Field&CRI_CQS), 0x01);
					}
				}else	
				if(Touch_x >= 217*TS_Callib & Touch_x <= (217+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Display_Off
				{
					TFT_ON_OFF = 0x00;
					HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
				}	else
				if(Touch_x >= 1*TS_Callib & Touch_x <= (1+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //Back
				{	
					WriteSDFLASH_t(sdfile_cnt);
					GUI_screen_state = Prev_Inf_Screen;
					switch (Prev_Inf_Screen){
						case Measure_Screen: GUI_screen_state = Measure_Screen; 		break;
						case Graph_Screen:  GUI_screen_state = Graph_Screen; 		break;
						case Color_Rendition_Screen: GUI_screen_state = Color_Rendition_Screen; break;
						case Color_Screen: GUI_screen_state = Color_Screen; break;
					}
				}		else	
				if(Touch_x >= 55*TS_Callib & Touch_x <= (55+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib) //SD_Card
				{
							if(!SD_Detect){GUI_screen_state = SD_Write_Screen;}
				}		else
				if(Touch_x >= 8*TS_Callib & Touch_x <= (250)*TS_Callib & Touch_y >=80*TS_Callib & Touch_y <=(120)*TS_Callib) // Language change
				{
					if (Language_status == Ru) Language_status=En;
					else if (Language_status == En) Language_status=Ru;
				}	 
			break;
				
			case Information_Screen:
			
			if(Touch_x >= 8*TS_Callib & Touch_x <= (270)*TS_Callib & Touch_y >=8*TS_Callib & Touch_y <=(470)*TS_Callib) // Information
				{
					GUI_screen_state = preGUI_screen_state;
					preGUI_screen_state = Information_Screen;
						switch (Prev_Inf_Screen2){
						case DataSet1_Screen: GUI_screen_state = DataSet1_Screen; 	Prev_Inf_Screen = Measure_Screen;	break;
						case GraphSet1_Screen: GUI_screen_state = GraphSet1_Screen; Prev_Inf_Screen = Graph_Screen; 		break;
						case ColorSet1_Screen: GUI_screen_state = ColorSet1_Screen; Prev_Inf_Screen = Color_Screen; break;
						case ColorRendSet_Screen: GUI_screen_state = ColorRendSet_Screen; Prev_Inf_Screen = Color_Rendition_Screen; break;
					}
				}
			break;
						
			case SD_Write_Screen:

		break;
				
		default: preGUI_screen_state = Measure_Screen;
			}
}

