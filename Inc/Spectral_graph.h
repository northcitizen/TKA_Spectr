#ifndef __SPECTRAL_GRAPH_H
#define __SPECTRAL_GRAPH_H

#include <string.h>
#include <stdlib.h>
#include "fonts.h"
#include "ltdc.h"
#include "GUI.h"

extern uint16_t Vertical_color_dara[];
extern uint16_t Horizontal_color_dara[];

void Spectral_Axes(uint8_t direction);
void Spectral_Axes_Text(uint8_t direction);
void Spectral_DrawGraph(uint16_t ZeroX, uint16_t ZeroY, float *GraphData, uint16_t color, uint8_t direction);
void Spectral_PAR_Range(uint8_t direction);
void Spectral_DrawGraph_Const(uint16_t ZeroX, uint16_t ZeroY, uint16_t *GraphData, uint16_t color, uint8_t direction);
void Spectral_RefreshGraph(uint8_t direction);

void Spectral_DrawGraph_Line(uint16_t ZeroX, uint16_t ZeroY, uint16_t GraphData[], uint16_t color, uint8_t direction);
void Spectral_DrawGraph_Line2(uint16_t ZeroX, uint16_t ZeroY, uint16_t GraphData[], uint16_t color, uint8_t direction);
void Rabs_graph_to_display(uint8_t direction, float Line_Rabs_buff[]);
void Refresh_screen_Graph(uint16_t ZeroX, uint16_t ZeroY, uint16_t GraphData[], uint8_t direction);
#endif 
