#ifndef __RABS_MATH_H
#define __RABS_MATH_H

#include "stm32l4xx_hal.h"
#include <math.h>

float Rabs_calc_Factor2_Settings_change(float Kt, float P);
float Rabs_calc_Factor1(uint16_t Rdark, float Lt, uint16_t R_data[]);
void Rabs_calc_main(uint16_t R_data[], uint16_t Rdark, float Factor1, float Factor2, float Sn[], float Rabs[]);
float Rabs_calc_MAX(uint16_t Rdark, float Factor1, float Factor2);
float Rabs_find_MAX(float Rabs[], uint8_t direction);
float Rabs_find_MAX_all(float Rabs[]);
#endif /* __RABS_MATH_H */
