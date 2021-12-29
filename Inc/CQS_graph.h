#ifndef __CQS_GRAPH_H
#define __CQS_GRAPH_H

#include <string.h>
#include <stdlib.h>
#include "fonts.h"
#include "ltdc.h"


void CQS_Axes(uint8_t direction);
void CQS_Axes_Text(uint8_t direction);
void CQS_chart(uint8_t direction, uint8_t *GraphData);
void CQS_Axes_Measure(uint8_t direction, uint8_t Qa, uint8_t Qp, uint8_t Qf);
void CQS_Draw(uint8_t direction, uint8_t *GraphData, uint8_t Qa, uint8_t Qp, uint8_t Qf);
#endif /* __LTDC_H */