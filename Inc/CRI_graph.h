#ifndef __CRI_GRAPH_H
#define __CRI_GRAPH_H

#include <string.h>
#include <stdlib.h>
#include "fonts.h"
#include "ltdc.h"


void CRI_Axes(uint8_t direction);
void CRI_Axes_Text(uint8_t direction);
void CRI_chart(uint8_t direction, int8_t *GraphData);
void CRI_Axes_Measure(uint8_t direction, int8_t Ra, int8_t Rall, int8_t R9);
void CRI_Draw(uint8_t direction, int8_t *GraphData, int8_t Ra, int8_t Rall, int8_t R9);
#endif /* __LTDC_H */