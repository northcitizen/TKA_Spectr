#ifndef __SD_CARD_H
#define __SD_CARD_H

#include "fatfs.h"
#include "stm32l4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include "GUI.h"
#include "main.h"
#include "CQS_Calculate.h"
#include "CRI_Calculate.h"
#include <stm32l4xx_hal_def.h>
#include "Calculate_Measure.h"
#include "Calibration_Address.h"
void SD_Witer(uint16_t file_cnt, uint8_t Language_status, uint8_t Memory_Data_satus, uint8_t Mode_EL, uint8_t CRICQS_done);
void Calculate_SD_Data();
void WriteSDFLASH_t(uint64_t filenum);
void WriteFLASH_Screen(uint8_t Screen);
#endif /* __SD_CARD_H */

