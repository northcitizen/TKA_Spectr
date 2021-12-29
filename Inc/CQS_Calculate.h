#ifndef __CQS_CALCULATE_H
#define __CQS_CALCULATE_H

#include "stm32l4xx_hal.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Calibration_Address.h"


void calcNorm560(uint16_t CCT_measure);
double calcSref(int idx, uint16_t CCT_measure);
void cqs_func(uint16_t CCT_measure, float *Rabs);


#endif