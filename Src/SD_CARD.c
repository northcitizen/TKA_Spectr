#include "SD_CARD.h"
#include <stdio.h>
#include <string.h>
#include "stm32l4xx_hal_flash.h"
volatile uint8_t SD_CARD_FLAG;
volatile uint8_t	preGUI_screen_state;
volatile uint8_t GUI_screen_state;
FLASH_EraseInitTypeDef EraseInitStruct_SDNum;

uint8_t SD_Text_SP_en[] = "S/P Twilight/Daytime ratio\r\n";
uint8_t SD_Text_SP_ru[] = "S/P Сумеречное/дневное отношение\r\n";

uint8_t SD_Text_ColorXYZ_1931_ru[] = "\r\nКоординаты цвета МКО-1931(X,Y,Z)\r\n";
uint8_t SD_Text_ColorXYZ_1964_ru[] = "\r\nКоординаты цвета МКО-1964(X,Y,Z)\r\n";
uint8_t SD_Text_ColorXYZ_1931_en[] = "\r\nTristimulus values CIE-1931(X,Y,Z)\r\n";
uint8_t SD_Text_ColorXYZ_1964_en[] = "\r\nTristimulus values CIE-1964(X,Y,Z)\r\n";

uint8_t SD_Text_Colorxy_1931_ru[] = "\r\nКоординаты цветности МКО-1931(x,y)\r\n";
uint8_t SD_Text_Colorxy_1964_ru[] = "\r\nКоординаты цветности МКО-1964(x,y)\r\n";
uint8_t SD_Text_Colorxy_1931_en[] = "\r\nChromaticity Coordinates CIE-1931(x,y)\r\n";
uint8_t SD_Text_Colorxy_1964_en[] = "\r\nChromaticity Coordinates CIE-1964(x,y)\r\n";

uint8_t SD_Text_Coloruv_ru[] = "\r\nКоординаты цветности МКО-1976 (u',v')\r\n";
uint8_t SD_Text_Coloruv_en[] = "\r\nChromaticity Coordinates CIE-1976 (u',v')\r\n";

uint8_t SD_Text_CCT_ru[] = "\r\nКЦТ, К\r\n";
uint8_t SD_Text_CCT_en[] = "\r\nCCT, K\r\n";

uint8_t SD_Text_LAB_ru[] = "\r\nКоординаты МКО-1976(Lab)\r\n";
uint8_t SD_Text_RefSource_ru[] = "\r\nРеференсный источник\r\n";
uint8_t SD_Text_LAB_en[] = "\r\nCIELAB-1976 coordinates\r\n";
uint8_t SD_Text_RefSource_en[] = "\r\nReference White\r\n";

uint8_t SD_Text_lambdaD_ru[] = "\r\nДоминантная длина волны, нм\r\n";
uint8_t SD_Text_lambdaD_en[] = "\r\nDominant wavelenght, nm\r\n";
uint8_t SD_Text_lambdaC_ru[] = "\r\nДополнительная длина волны, нм\r\n";
uint8_t SD_Text_lambdaC_en[] = "\r\nComplementary wavelenght, nm\r\n";

uint8_t SD_Text_deltaE_ru[] = "\r\nЦветовое различие dEab\r\n";
uint8_t SD_Text_deltaE_en[] = "\r\nCIELAB dEab\r\n";

uint8_t SD_Text_Elambda_ru[] = "\r\nДлина волны, нм\tСПЭО, Вт/(м2*нм)\r\n";
uint8_t SD_Text_Elambda_en[] = "\r\nWavelength, nm\tSpectral Irradiance W/(m2*nm)\r\n";

uint8_t SD_Text_Llambda_ru[] = "\r\nДлина волны, нм\tСПЭЯ, Вт/(м2*ср*нм)\r\n";
uint8_t SD_Text_Llambda_en[] = "\r\nWavelength, nm\tSpectral Radiance, W/(m2*sr*nm)\r\n";

uint8_t SD_Text_Le_ru[] = "\r\nЯркость, кд/м2\r\n";
uint8_t SD_Text_Le_en[] = "\r\nRadiance, W/(m2*sr)\r\n";

uint8_t SD_Text_Lu_ru[] = "\r\nЭнергетическая яркость, Вт/(м2*ср)\r\n";
uint8_t SD_Text_Lu_en[] = "\r\nLuminance, cd/m2\r\n";

uint8_t SD_Text_Ee_ru[] = "\r\nЭнергетическая освещенность, Вт/м2\r\n";
uint8_t SD_Text_Ee_en[] = "\r\nIrradiance, W/m2\n";

uint8_t SD_Text_Eu_ru[] = "\r\nОсвещенность, лк\r\n";
uint8_t SD_Text_Eu_en[] = "\r\nIlluminance, lx\r\n";

uint8_t SD_Text_PPFD_ru[] = "\r\nФАР яркость, мкмоль/(с*м2)\r\n";
uint8_t SD_Text_PPFD_en[] = "\r\nPPFD, umol/(s*m2)\r\n";

uint8_t SD_Text_PPFDRGB_ru[] = "\r\nФАР-Cин\tФАР-Зел\tФАР-Кр\tФАР-FR, мкмоль/(с*м2)\r\n";
uint8_t SD_Text_PPFDRGB_en[] = "\r\nPFD-B, PFD-G, PFD-R, PFD-FR, umol/(s*m2)\r\n";

uint8_t SD_Text_PPL_ru[] = "\r\nФАР облученность, мкмоль/(с*м2*ср)\r\n";
uint8_t SD_Text_PPL_en[] = "\r\nPPL, umol/(s*m2*sr)\r\n";

uint8_t SD_Text_PPLRGB_ru[] = "\r\nФАР-Cин\tФАР-Зел\tФАР-Кр\tФАР-FR, мкмоль/(с*м2*ср)\r\n";
uint8_t SD_Text_PPLRGB_en[] = "\r\nPAR-B, PAR-G, PAR-R, PAR-FR, umol/(s*m2*sr)\r\n";

uint8_t SD_Text_Eb_Er_ru[] = "\r\nEb, Er(@390-760нм), Вт/м2\r\n";
uint8_t SD_Text_Eb_Er_en[] = "\r\nEb, Er(@390-760nm), W/m2\r\n";

uint8_t SD_Text_Lb_Lr_ru[] = "\r\nLb, Lr(@390-760нм), Вт/(м2*ср)\r\n";
uint8_t SD_Text_Lb_Lr_en[] = "\r\nLb, Lr(@390-760nm), W/(m2*sr)\r\n";

uint8_t SD_Text_CRI_ru[] = "\r\nИндекс цветопередачи (CRI): Ra, Rall, %\r\nR1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15\r\n";
uint8_t SD_Text_CRI_en[] = "\r\nColour rendering index (CRI): Ra, Rall, %\r\nR1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15\r\n";

uint8_t SD_Text_CQS_ru[] = "\r\nИндекс цветопередачи (CQS): Qa, Qp, Qf, \r\nQ1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12, Q13, Q14, Q15\r\n";
uint8_t SD_Text_CQS_en[] = "\r\nColor Quality Scale (CQS): Qa, Qp, Qf, \r\nQ1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12, Q13, Q14, Q15\r\n";

extern float E_day, E_day_Wt, E_Night, SP_Measure, PPFD_PPL_Measure, PPFD_PPL_Blue_Measure, PPFD_PPL_Green_Measure, PPFD_PPL_Red_Measure, PPFD_PPL_Far_Red_Measure,
	ELr_Measure, ELb_Measure, CCT_Measure;
extern uint16_t	Tc_Measure, lambda_d_Measure, lambda_c_Measure;
extern uint16_t colorimetry_XYZ1931[3];
extern int16_t colorimetry_LAB[3], delta_Eab_Measure;
extern float colorimetry_xy1931[2], colorimetry_xy1964[2], colorimetry_uv1976[2], Line_Rabs_buff[1024];
extern uint8_t Q_i[15], Qf, Qa, Qp, Source_Type;
extern int8_t Ra, Rall, R9, Ri[15];
extern float WaveLenght[1024], calibratre_x_1931[1024], calibratre_z_1931[1024];
extern float colorimetry_xy1931[2], colorimetry_XYZ1964[3], colorimetry_uv1976[2], Spectral_day[1024], Spectral_night[1024], Hazard_Retina[1024], Hazard_Blue[1024];
extern uint8_t Measure_Color_xy;
double SDWr_Status_bar = 0;
volatile uint8_t LAMBDA_TYPE;
extern uint16_t	Measure_Field;
extern uint8_t	Graph_Field, Color_Field, Color_rend_Field, Language_status, Source_Type, Mode_EL, Bluetooth;


FATFS SDFatFs;  /* File system object for SD card logical drive */
FIL MyFile;     /* File object */
extern char SDPath[4];  /* SD logical drive path */
FRESULT res;                                          /* FatFs function common result code */
uint32_t byteswritten, bytesread;                     /* File write/read counts */
char buffer_sd[11];

FLASH_EraseInitTypeDef EraseInitStruct3;

void WriteSDFLASH_t(uint64_t filenum)
{
	
uint32_t PAGEError = 0;
HAL_StatusTypeDef	flash_ok = HAL_ERROR;

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
		HAL_FLASH_Unlock();
		HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
		HAL_Delay(100);
		EraseInitStruct3.TypeErase = FLASH_TYPEERASE_PAGES;
		EraseInitStruct3.Banks = FLASH_BANK_2; 
		EraseInitStruct3.Page = (uint32_t)48;
		EraseInitStruct3.NbPages = (uint32_t)0x1; 

	 HAL_FLASHEx_Erase(&EraseInitStruct3, &PAGEError);

	HAL_Delay(50);

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
		HAL_FLASH_Lock();
			flash_ok = HAL_ERROR;
						HAL_FLASH_Unlock();
						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)FILENUMBER, filenum);
					}

				flash_ok = HAL_ERROR;
						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)SET_MODEEL, Mode_EL);
					}
						
						flash_ok = HAL_ERROR;
						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)SET_MEASUREFIELD, Measure_Field);
							}
						flash_ok = HAL_ERROR;
						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)SET_GRAPHFIELD, Graph_Field);
							}
						flash_ok = HAL_ERROR;
						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)SET_COLORFIELD, Color_Field);
							}
						flash_ok = HAL_ERROR;
						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)SET_COLORRENDFIELD, Color_rend_Field);
						}
						flash_ok = HAL_ERROR;
					__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)SET_LANGUAGE, Language_status);
					}
					flash_ok = HAL_ERROR;
					__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)SET_SOURCETYPE, Source_Type);
					}
					flash_ok = HAL_ERROR;
					__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)SET_BLUETOOTH, Bluetooth);
					}
						HAL_FLASH_Lock();
}


void WriteFLASH_Screen(uint8_t Screen)
{
	
uint32_t PAGEError = 0;
HAL_StatusTypeDef	flash_ok = HAL_ERROR;

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
		HAL_FLASH_Unlock();
		HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
		HAL_Delay(100);
		EraseInitStruct3.TypeErase = FLASH_TYPEERASE_PAGES;
		EraseInitStruct3.Banks = FLASH_BANK_2;
		EraseInitStruct3.Page = (uint32_t)49;
		EraseInitStruct3.NbPages = (uint32_t)0x1;

	 HAL_FLASHEx_Erase(&EraseInitStruct3, &PAGEError);

	HAL_Delay(50);

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
		HAL_FLASH_Lock();
			flash_ok = HAL_ERROR;
						HAL_FLASH_Unlock();
						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
						while(flash_ok != HAL_OK){
							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, (uint32_t)SCREENADDR, Screen);
					}
		HAL_FLASH_Lock();
}


void Calculate_SD_Data()
{

	SDWr_Status_bar = 0;
	GUI_Bar_Measure(85, 280, SDWr_Status_bar);
	Calculate_XYZ1931(Line_Rabs_buff, calibratre_x_1931, Spectral_day, calibratre_z_1931);
	Calculate_xy1931(colorimetry_XYZ1931);
	Calculate_uv1976(colorimetry_xy1931);
	Calculate_Lab(colorimetry_XYZ1931, Measure_Color_xy, Source_Type);
	Tc_Measure = Calculate_Tc(Line_Rabs_buff, 1);
	
	SDWr_Status_bar = 0.1;
	GUI_Bar_Measure(85, 280, SDWr_Status_bar);
	delta_Eab_Measure = Calculate_deltaEab();
	
	E_day = Calculate_EL_Day(Line_Rabs_buff, Spectral_day);
	E_day_Wt = Calculate_EL_Day_Wt(Line_Rabs_buff);
	PPFD_PPL_Measure = (Calculate_PPFD_PPL(Line_Rabs_buff, WaveLenght));
	PPFD_PPL_Blue_Measure = (Calculate_PPFD_PPL_Range(Line_Rabs_buff, WaveLenght, BLUE_RANGE));
	PPFD_PPL_Green_Measure = (Calculate_PPFD_PPL_Range(Line_Rabs_buff, WaveLenght, GREEN_RANGE));
	PPFD_PPL_Red_Measure = (Calculate_PPFD_PPL_Range(Line_Rabs_buff, WaveLenght, RED_RANGE));
	PPFD_PPL_Far_Red_Measure = (Calculate_PPFD_PPL_Range(Line_Rabs_buff, WaveLenght, FAR_RED_RANGE));
	
	SDWr_Status_bar = 0.3;
	GUI_Bar_Measure(85, 280, SDWr_Status_bar);
	E_Night = Calculate_EL_Night(Line_Rabs_buff, Spectral_night);
	SP_Measure = (Calculate_SP(E_day, E_Night));
	
	ELr_Measure = Calculate_ELr(Line_Rabs_buff,Hazard_Retina);
	ELb_Measure = Calculate_ELb(Line_Rabs_buff, Hazard_Blue);
	
	SDWr_Status_bar = 0.4;
	GUI_Bar_Measure(85, 280, SDWr_Status_bar);
}



uint8_t mount = 0;
void SD_Witer(uint16_t file_cnt, uint8_t Language_status, uint8_t Memory_Data_satus, uint8_t Mode_EL, uint8_t CRICQS_done)
{
	HAL_StatusTypeDef flash_ok = HAL_ERROR;
	uint32_t PAGEError = 0;
	
	char digit_buff[3];
	char source_type[4];
	char measure_buff[12];
	float deltaWave = 0.0;
	float E_Day_delata = 0.0;
	strcpy(source_type, Source_Type == Source_A ? "A" : Source_Type == Source_D65 ? "D65" : Source_Type == Source_C ? "C" : Source_Type == Source_D50 ? "D50" : Source_Type == Source_D55 ? "D55" : Source_Type == Source_D75 ? "D75" : "NAN");
	
	memset(measure_buff, 0, 12);
	
		sprintf(digit_buff, "%.3d", file_cnt );
		strcat(buffer_sd, digit_buff);
		strcat(buffer_sd, ".txt");

		HAL_Delay(1);

		HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
		HAL_NVIC_DisableIRQ(TIM2_IRQn);
		HAL_NVIC_DisableIRQ(USART2_IRQn);
		HAL_NVIC_DisableIRQ(USART3_IRQn);
		HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
		res = f_mount(&SDFatFs,(TCHAR const*) SDPath, 1);
		HAL_Delay(1);
       if (res != FR_OK)
        {
                //printf("Ошибка монтирования диска %d\r\n", result);
        }
			else
				{
				res = f_open(&MyFile, buffer_sd, FA_CREATE_ALWAYS | FA_WRITE);
				if (res == FR_OK)
					{

							SDWr_Status_bar = 0.5;
							/////////////////////////////
							if (Measure_Field & delta_E) {
											delta_Eab_Measure = Calculate_deltaEab();
										}
										if (Measure_Field & Illuminance) {
											E_day = Calculate_EL_Day(Line_Rabs_buff, Spectral_day);
										}
										if (Measure_Field & Irradiance) {
											E_day_Wt = Calculate_EL_Day_Wt(Line_Rabs_buff);
										}

										if (Measure_Field & SP_measure) {
											E_Night = Calculate_EL_Night(Line_Rabs_buff, Spectral_night);
											E_day = (Measure_Field & Illuminance) ?
													E_day : Calculate_EL_Day(Line_Rabs_buff, Spectral_day);
											SP_Measure = (Calculate_SP(E_day, E_Night));
										}
										if (Measure_Field & PPFD) {
											PPFD_PPL_Measure = (Calculate_PPFD_PPL(Line_Rabs_buff,
													WaveLenght)); //*100000
										}
										if (Measure_Field & PPFD_BGR) {
											PPFD_PPL_Blue_Measure = (Calculate_PPFD_PPL_Range(
													Line_Rabs_buff, WaveLenght, BLUE_RANGE)); //*100000
											PPFD_PPL_Green_Measure = (Calculate_PPFD_PPL_Range(
													Line_Rabs_buff, WaveLenght, GREEN_RANGE)); //*100000
											PPFD_PPL_Red_Measure = (Calculate_PPFD_PPL_Range(Line_Rabs_buff,
													WaveLenght, RED_RANGE)); //*100000
											PPFD_PPL_Far_Red_Measure = (Calculate_PPFD_PPL_Range(
													Line_Rabs_buff, WaveLenght, FAR_RED_RANGE)); //*100000
										}

										if (Measure_Field & CIE_Luv) {
											Calculate_uv1976(
													(Measure_Color_xy == 0x00) ?
															colorimetry_xy1964 : colorimetry_xy1931);
											Calculate_uv(
													(Measure_Color_xy == 0x00) ?
															colorimetry_xy1964 : colorimetry_xy1931);
										}
										if (Measure_Field & CIE_Lab) {
											Calculate_Lab(
													(Measure_Color_xy == 0x00) ?
															colorimetry_XYZ1964 : colorimetry_XYZ1931,
													Measure_Color_xy, Source_Type);
										}
										if (Measure_Field & lambda_d) {
											Calculate_Lambda_Dominant(Line_Rabs_buff, Measure_Color_xy);
										}
										if (Measure_Field & lambda_c) {
											Calculate_Lambda_Dominant(Line_Rabs_buff, Measure_Color_xy);
										}
										if (Measure_Field & EbEr) {
											ELr_Measure = Calculate_ELr(Line_Rabs_buff, Hazard_Retina);
											ELb_Measure = Calculate_ELb(Line_Rabs_buff, Hazard_Blue);
										}

										delta_Eab_Measure = Calculate_deltaEab();
							////////////////////////////
							GUI_Bar_Measure(85, 280, SDWr_Status_bar);
						(Language_status==Ru)? (f_write(&MyFile, &SD_Text_SP_ru, sizeof(SD_Text_SP_ru), &byteswritten)) : (f_write(&MyFile, &SD_Text_SP_en, sizeof(SD_Text_SP_en), &byteswritten)); //S/P
							sprintf(measure_buff, "%.4f", SP_Measure);
							f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
							memset(measure_buff, 0, 12);
						
							if(Measure_Color_xy)
							{
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_ColorXYZ_1931_ru, sizeof(SD_Text_ColorXYZ_1931_ru), &byteswritten)) :(f_write(&MyFile, &SD_Text_ColorXYZ_1931_en, sizeof(SD_Text_ColorXYZ_1931_en), &byteswritten)); //XYZ
								sprintf(measure_buff, "%d\t", colorimetry_XYZ1931[0]);//X
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);

								sprintf(measure_buff, "%d\t", colorimetry_XYZ1931[1]);//Y
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);

								sprintf(measure_buff, "%d\t", colorimetry_XYZ1931[2]);//Z
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
							}else{
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_ColorXYZ_1964_ru, sizeof(SD_Text_ColorXYZ_1964_ru), &byteswritten)) :(f_write(&MyFile, &SD_Text_ColorXYZ_1964_en, sizeof(SD_Text_ColorXYZ_1964_en), &byteswritten)); //XYZ
								sprintf(measure_buff, "%d\t", colorimetry_XYZ1964[0]);//X
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);

								sprintf(measure_buff, "%d\t", colorimetry_XYZ1964[1]);//Y
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);

								sprintf(measure_buff, "%d\t", colorimetry_XYZ1964[2]);//Z
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
							}
						
							if(Measure_Color_xy)
							{
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Colorxy_1931_ru, sizeof(SD_Text_Colorxy_1931_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Colorxy_1931_en, sizeof(SD_Text_Colorxy_1931_en), &byteswritten));//xy
								sprintf(measure_buff, "%.4f\t", colorimetry_xy1931[0]); //x
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
						
								sprintf(measure_buff, "%.4f", colorimetry_xy1931[1]);//y
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
							}else
							{
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Colorxy_1964_ru, sizeof(SD_Text_Colorxy_1964_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Colorxy_1964_en, sizeof(SD_Text_Colorxy_1964_en), &byteswritten));//xy
								sprintf(measure_buff, "%.4f\t", colorimetry_xy1964[0]); //x
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);

								sprintf(measure_buff, "%.4f", colorimetry_xy1964[1]);//y
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
							}
							(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Coloruv_ru, sizeof(SD_Text_Coloruv_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Coloruv_en, sizeof(SD_Text_Coloruv_en), &byteswritten));//u'v'
							sprintf(measure_buff, "%.4f\t", colorimetry_uv1976[0]);//u'
							f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
							memset(measure_buff, 0, 12);
						
							sprintf(measure_buff, "%.4f", colorimetry_uv1976[1]);//v'
							f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
							memset(measure_buff, 0, 12);
							
							(Language_status==Ru)?(f_write(&MyFile, &SD_Text_CCT_ru, sizeof(SD_Text_CCT_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_CCT_en, sizeof(SD_Text_CCT_en), &byteswritten));//CCT
							if(Tc_Measure == 0xFFFF){f_write(&MyFile, "NAN", 3, &byteswritten);}
							else{
										sprintf(measure_buff, "%.d", Tc_Measure);
										f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
										memset(measure_buff, 0, 12);
								}
						
								SDWr_Status_bar = 0.7;
								GUI_Bar_Measure(85, 280, SDWr_Status_bar);
							(Language_status==Ru)?(f_write(&MyFile, &SD_Text_LAB_ru, sizeof(SD_Text_LAB_ru), &byteswritten)):f_write(&MyFile, &SD_Text_LAB_en, sizeof(SD_Text_LAB_en), &byteswritten); //L*a*b*
							sprintf(measure_buff, "%i\t", colorimetry_LAB[0]);//L
							f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
							memset(measure_buff, 0, 12);
						
							sprintf(measure_buff, "%i\t", colorimetry_LAB[1]);//a
							f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
							memset(measure_buff, 0, 12);
						
							sprintf(measure_buff, "%i\t", colorimetry_LAB[2]);//b
							f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
							memset(measure_buff, 0, 12);
						
							(Language_status==Ru)?(f_write(&MyFile, &SD_Text_RefSource_ru, sizeof(SD_Text_RefSource_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_RefSource_en, sizeof(SD_Text_RefSource_en), &byteswritten)); //RefSource
							f_write(&MyFile, &source_type, sizeof(source_type), &byteswritten);//SourceType
						
							if(LAMBDA_TYPE)
							{
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_lambdaD_ru, sizeof(SD_Text_lambdaD_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_lambdaD_en, sizeof(SD_Text_lambdaD_en), &byteswritten));//Lambda D
								sprintf(measure_buff, "%d\t", lambda_d_Measure); //Lambda D
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
							}else{
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_lambdaC_ru, sizeof(SD_Text_lambdaC_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_lambdaC_en, sizeof(SD_Text_lambdaC_en), &byteswritten));//Lambda C
								sprintf(measure_buff, "%d\t", lambda_d_Measure); //Lambda C
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
							}
						
							if(Memory_Data_satus == 0x01)
							{
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_deltaE_ru, sizeof(SD_Text_deltaE_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_deltaE_en, sizeof(SD_Text_deltaE_en), &byteswritten));//Delta E
								sprintf(measure_buff, "%d\t", delta_Eab_Measure); //Delta E
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
							} else
							{
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_deltaE_ru, sizeof(SD_Text_deltaE_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_deltaE_en, sizeof(SD_Text_deltaE_en), &byteswritten));//Delta E
								f_write(&MyFile, "NAN", 3, &byteswritten);
							}
							

	SDWr_Status_bar = 0.8;
	GUI_Bar_Measure(85, 280, SDWr_Status_bar);

	if(Mode_EL == 0x01) //E mode
	{


	(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Ee_ru, sizeof(SD_Text_Ee_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Ee_en, sizeof(SD_Text_Ee_en), &byteswritten));//Ee
	sprintf(measure_buff, "%.2f",  E_day); //Ee
	f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
	memset(measure_buff, 0, 12);

	(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Eu_ru, sizeof(SD_Text_Eu_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Eu_en, sizeof(SD_Text_Eu_en), &byteswritten));//Eu
	sprintf(measure_buff, "%.1f",  E_day_Wt); //Eu
	f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
	memset(measure_buff, 0, 12);

	(Language_status==Ru)?(f_write(&MyFile, &SD_Text_PPFD_ru, sizeof(SD_Text_PPFD_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_PPFD_en, sizeof(SD_Text_PPFD_en), &byteswritten));//PPFD
	sprintf(measure_buff, "%.2f", PPFD_PPL_Measure); //PPFD
	f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
	memset(measure_buff, 0, 12);

	(Language_status==Ru)?(f_write(&MyFile, &SD_Text_PPFDRGB_ru, sizeof(SD_Text_PPFDRGB_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_PPFDRGB_en, sizeof(SD_Text_PPFDRGB_en), &byteswritten));//PPFDRGB
	sprintf(measure_buff, "%.2f\t", PPFD_PPL_Blue_Measure); //PPFD B
	f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
	memset(measure_buff, 0, 12);

	sprintf(measure_buff, "%.2f\t", PPFD_PPL_Green_Measure); //PPFD G
	f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
	memset(measure_buff, 0, 12);

	sprintf(measure_buff, "%.2f\t", PPFD_PPL_Red_Measure); //PPFD R
	f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
	memset(measure_buff, 0, 12);

	sprintf(measure_buff, "%.2f\t", PPFD_PPL_Far_Red_Measure); //PPFD FR
	f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
	memset(measure_buff, 0, 12);

	(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Eb_Er_ru, sizeof(SD_Text_Eb_Er_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Eb_Er_en, sizeof(SD_Text_Eb_Er_en), &byteswritten));//Eb/Er
	sprintf(measure_buff, "%.2f\t", ELb_Measure); //Eb
	f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
	memset(measure_buff, 0, 12);

	sprintf(measure_buff, "%.2f", ELr_Measure); //Er
	f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
	memset(measure_buff, 0, 12);

	SDWr_Status_bar = 0.9;
	 GUI_Bar_Measure(85, 280, SDWr_Status_bar);
	}
	else //Lmode
	{
			for (uint16_t iq = 0; iq < 1024; iq++)
			{
				E_Day_delata = E_Day_delata + (Line_Rabs_buff[iq]*deltaWave);
			}

		(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Le_ru, sizeof(SD_Text_Le_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Le_en, sizeof(SD_Text_Le_en), &byteswritten));//Le
		sprintf(measure_buff, "%.2f", E_day); //Le
		f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
		memset(measure_buff, 0, 12);
		(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Lu_ru, sizeof(SD_Text_Lu_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Lu_en, sizeof(SD_Text_Lu_en), &byteswritten));//Lu
		sprintf(measure_buff, "%.5f", E_day_Wt); //Lu E_Day_delata изменено на E_Day_Wt 14_10_2021
		f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
		memset(measure_buff, 0, 12);

		(Language_status==Ru)?(f_write(&MyFile, &SD_Text_PPL_ru, sizeof(SD_Text_PPL_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_PPL_en, sizeof(SD_Text_PPL_en), &byteswritten));//PPL
		sprintf(measure_buff, "%.2f", PPFD_PPL_Measure); //PPL
		f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
		memset(measure_buff, 0, 12);

		(Language_status==Ru)?(f_write(&MyFile, &SD_Text_PPLRGB_ru, sizeof(SD_Text_PPLRGB_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_PPLRGB_en, sizeof(SD_Text_PPLRGB_en), &byteswritten));//PPFDRGB
		sprintf(measure_buff, "%.2f\t", PPFD_PPL_Blue_Measure); //PPL B
		f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
		memset(measure_buff, 0, 12);

		sprintf(measure_buff, "%.2f\t", PPFD_PPL_Green_Measure); //PPL G
		f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
		memset(measure_buff, 0, 12);

		sprintf(measure_buff, "%.2f\t", PPFD_PPL_Red_Measure); //PPL R
		f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
		memset(measure_buff, 0, 12);

		sprintf(measure_buff, "%.2f\t", PPFD_PPL_Far_Red_Measure); //PPL FR
		f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
		memset(measure_buff, 0, 12);

		(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Lb_Lr_ru, sizeof(SD_Text_Lb_Lr_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Lb_Lr_en, sizeof(SD_Text_Lb_Lr_en), &byteswritten));//Lb/Lr
		sprintf(measure_buff, "%.2f\t", ELb_Measure); //Lb
		f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
		memset(measure_buff, 0, 12);

		sprintf(measure_buff, "%.2f", ELr_Measure); //Lr
		f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
		memset(measure_buff, 0, 12);


		SDWr_Status_bar = 0.9;
		GUI_Bar_Measure(85, 280, SDWr_Status_bar);
	}

							if(CRICQS_done == 0x01)
							{
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_CRI_ru, sizeof(SD_Text_CRI_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_CRI_en, sizeof(SD_Text_CRI_en), &byteswritten));
								sprintf(measure_buff, "%d\t", Ra); //Ra
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								
								sprintf(measure_buff, "%d", Rall); //Rall
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								
								sprintf(measure_buff, "\n%d\t", Ri[0]); //R1
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[1]); //R2
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[2]); //R3
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[3]); //R4
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[4]); //R5
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[5]); //R6
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t",Ri[6]); //R7
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t",Ri[7]); //R8
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t",Ri[8]); //R9
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[9]); //R10
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[10]); //R11
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[11]); //R12
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[12]); //R13
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[13]); //R14
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Ri[14]); //R15
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								
								(Language_status==Ru)?(f_write(&MyFile, &SD_Text_CQS_ru, sizeof(SD_Text_CQS_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_CQS_en, sizeof(SD_Text_CQS_en), &byteswritten));
								sprintf(measure_buff, "%d\t", Qa); //Qa
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								
								sprintf(measure_buff, "%d\t", Qp); //Qp
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								
								sprintf(measure_buff, "%d", Qf); //Qf
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								
								sprintf(measure_buff, "\n%d\t", Q_i[0]); //Q1
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[1]); //Q2
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[2]); //Q3
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[3]); //Q4
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[4]); //Q5
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[5]); //Q6
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t",Q_i[6]); //Q7
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t",Q_i[7]); //Q8
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t",Q_i[8]); //Q9
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[9]); //Q10
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[10]); //Q11
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[11]); //Q12
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[12]); //Q13
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[13]); //Q14
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
								sprintf(measure_buff, "%d\t", Q_i[14]); //Q15
								f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
								memset(measure_buff, 0, 12);
							}


				if(Mode_EL == 0x01) //E mode
				{
					(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Elambda_ru, sizeof(SD_Text_Elambda_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Elambda_en, sizeof(SD_Text_Elambda_en), &byteswritten));//Delta E
					for(uint16_t i=0; i < 1024; i++)
					{
						sprintf(measure_buff, "%.2f", WaveLenght[i]); //lambda
						f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
						memset(measure_buff, 0, 12);

						sprintf(measure_buff, "\t%.7f\r\n", Line_Rabs_buff[i]); //E(lambda)
						f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
						memset(measure_buff, 0, 12);
					}
					SDWr_Status_bar = 0.9;
					GUI_Bar_Measure(85, 280, SDWr_Status_bar);
				}
				else //Lmode
				{
					deltaWave = WaveLenght[1023]-WaveLenght[1022];
					(Language_status==Ru)?(f_write(&MyFile, &SD_Text_Llambda_ru, sizeof(SD_Text_Llambda_ru), &byteswritten)):(f_write(&MyFile, &SD_Text_Llambda_en, sizeof(SD_Text_Llambda_en), &byteswritten));//Delta E

					for(uint16_t i=0; i < 1024; i++)
					{
						sprintf(measure_buff, "%.2f", WaveLenght[i]); //lambda
						f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
						memset(measure_buff, 0, 12);

						sprintf(measure_buff, "\t%.7f\r\n", Line_Rabs_buff[i]*deltaWave); //L(lambda)
						f_write(&MyFile, &measure_buff, sizeof(measure_buff), &byteswritten);
						memset(measure_buff, 0, 12);

					}
					SDWr_Status_bar = 0.9;
					GUI_Bar_Measure(85, 280, SDWr_Status_bar);

				}
					}
				}
				
       HAL_Delay(1);
				f_close(&MyFile);
				HAL_Delay(1);
				memset(buffer_sd, 0, 11);
				HAL_Delay(1);
				res = f_mount(&SDFatFs,(TCHAR const*)SDPath, 0);
				HAL_Delay(1);
				SDWr_Status_bar = 1.0;
				GUI_Bar_Measure(85, 280, SDWr_Status_bar);
				HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
				HAL_NVIC_EnableIRQ(TIM2_IRQn);
				HAL_NVIC_EnableIRQ(USART2_IRQn);
				HAL_NVIC_EnableIRQ(USART3_IRQn);
				HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
				SD_CARD_FLAG = 1;
	}
