#ifndef __CRI_CALCULATE_H
#define __CRI_CALCULATE_H


#include "stm32l4xx_hal.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Calibration_Address.h"


float calcSref_CRI(int idx, uint16_t CCT_measure);
void CRI_func(uint16_t CCT_measure, float *Rabs);

	
#endif