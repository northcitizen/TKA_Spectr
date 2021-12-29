#ifndef TMP144
#define TMP144

#include "main.h"
#include "stm32l4xx_hal.h"
#include "stdint.h"
#include <stdlib.h>
#include <stdbool.h>

extern float temperature_C;
extern volatile uint16_t temperature_measure;
extern volatile bool usart2_wait;
extern float temperature_degree;
void Temperature_Measure_Func(void);

#endif
