#include "ltdc.h"
#include "Qspi_func.h"

extern uint16_t coordX[1500], coordY[1500], i_coord;
extern uint32_t graph_data_old[1500];
extern uint8_t flag_spectral;

extern volatile uint16_t RGB565_480x272[130560];
extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;
extern volatile uint8_t TFT_direction;
LCD_DrawPropTypeDef lcdprop;
uint16_t X_SIZE = 480;
uint16_t Y_SIZE = 272;
uint32_t Pixels = 130560;
const uint8_t *ch;
float Unit_nm[7]= {0};
const float Unit_Relative[5]= {0, 0.25, 0.5, 0.75, 1};

void TFT_FillRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color)
{
	for (; y0 <= y1; y0++) {
		TFT_DrawLine(x0, y0, x1, y0, color);
	}
}
void TFT_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color)
{
	TFT_DrawLine(x0, y0, x1, y0, color); /* Top */
	TFT_DrawLine(x0, y0, x0, y1, color);	/* Left */
	TFT_DrawLine(x1, y0, x1, y1, color);	/* Right */
	TFT_DrawLine(x0, y1, x1, y1, color);	/* Bottom */
}
void TFT_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) 
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    TFT_DrawPixel(x0, y0 + r, color);
    TFT_DrawPixel(x0, y0 - r, color);
    TFT_DrawPixel(x0 + r, y0, color);
    TFT_DrawPixel(x0 - r, y0, color);
    TFT_DrawLine(x0 - r, y0, x0 + r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        TFT_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        TFT_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);

        TFT_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, color);
        TFT_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, color);
    }
}

void TFT_DrawFilledRoundedRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t r, uint32_t color) 
{
	uint16_t temp;
	
	/* Check input parameters */
	if (x1 == x0 || y1 == y0) {
		return;
	}
	
	/* No radius */
	if (r == 0) {
		TFT_FillRectangle(x0, y0, x1, y1, color);
	}
	
	/* Swap X coordinates */
	if (x0 > x1) {
		temp = x1;
		x1 = x0;
		x0 = temp;
	}
	
	/* Swap Y coordinates */
	if (y0 > y1) {
		temp = y1;
		y1 = y0;
		y0 = temp;
	}
	
	/* Check max radius */
	if (r > ((x1 - x0) / 2)) {
		r = (x1 - x0) / 2;
	}
	if (r > ((y1 - y0) / 2)) {
		r = (y1 - y0) / 2;
	}
	
	/* Draw rectangles */
	TFT_FillRectangle(x0 + r, y0, x1 - r, y1, color);
	TFT_FillRectangle(x0, y0 + r, x0 + r, y1 - r, color);
	TFT_FillRectangle(x1 - r, y0 + r, x1, y1 - r, color);
	
	/* Draw corners */
	TFT_DrawFilledCircleCorner(x0 + r, y0 + r, r, 0x01, color);
	TFT_DrawFilledCircleCorner(x1 - r, y0 + r, r, 0x02, color);
	TFT_DrawFilledCircleCorner(x1 - r, y1 - r - 1, r, 0x04, color);
	TFT_DrawFilledCircleCorner(x0 + r, y1 - r - 1, r, 0x08, color);
}

void TFT_DrawCircleCorner(int16_t x0, int16_t y0, int16_t r, uint8_t corner, uint32_t color) 
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (corner & 0x01) {	
			TFT_DrawPixel(x0 - y, y0 - x, color);
			TFT_DrawPixel(x0 - x, y0 - y, color);
		}
		
        if (corner & 0x02) {	
			TFT_DrawPixel(x0 + x, y0 - y, color);
			TFT_DrawPixel(x0 + y, y0 - x, color);
		}
		
		if (corner & 0x04) {	
			TFT_DrawPixel(x0 + x, y0 + y, color);
			TFT_DrawPixel(x0 + y, y0 + x, color);
		}
		
        if (corner & 0x08) {	
			TFT_DrawPixel(x0 - x, y0 + y, color);
			TFT_DrawPixel(x0 - y, y0 + x, color);
		}
    }
}

void TFT_DrawFilledCircleCorner(int16_t x0, int16_t y0, int16_t r, uint8_t corner, uint32_t color) 
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (corner & 0x01) {
			TFT_DrawLine(x0, y0 - y, x0 - x, y0 - y, color);
			TFT_DrawLine(x0, y0 - x, x0 - y, y0 - x, color);
		}
		
        if (corner & 0x02) {	
			TFT_DrawLine(x0 + x, y0 - y, x0, y0 - y, color);
			TFT_DrawLine(x0 + y, y0 - x, x0, y0 - x, color);
		}
		
		if (corner & 0x04) {
			TFT_DrawLine(x0, y0 + y, x0 + x, y0 + y, color);
			TFT_DrawLine(x0 + y, y0 + x, x0, y0 + x, color);
		}
		
        if (corner & 0x08) {
			TFT_DrawLine(x0 - x, y0 + y, x0, y0 + y, color);
			TFT_DrawLine(x0, y0 + x, x0 - y, y0 + x, color);
		}
    }
}

void TFT_FillRectangle_DMA(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
  if(x1>x2) swap(x1,x2);
  if(y1>y2) swap(y1,y2);

  uint32_t addr = 0;
  addr = (hltdc.LayerCfg[0].FBStartAdress) + 2*(y1*hltdc.LayerCfg[0].ImageWidth + x1);
  hdma2d.Init.Mode = DMA2D_R2M;

  hdma2d.Init.OutputOffset = hltdc.LayerCfg[0].ImageWidth-(x2-x1);

  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
  {
    if (HAL_DMA2D_Start(&hdma2d, color, addr, x2-x1, y2-y1) == HAL_OK)
    {
      HAL_DMA2D_PollForTransfer(&hdma2d, 10);
    }
  }
}


void TFT_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    TFT_DrawPixel(x0, y0 + r, color);
    TFT_DrawPixel(x0, y0 - r, color);
    TFT_DrawPixel(x0 + r, y0, color);
    TFT_DrawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        TFT_DrawPixel(x0 + x, y0 + y, color);
        TFT_DrawPixel(x0 - x, y0 + y, color);
        TFT_DrawPixel(x0 + x, y0 - y, color);
        TFT_DrawPixel(x0 - x, y0 - y, color);

        TFT_DrawPixel(x0 + y, y0 + x, color);
        TFT_DrawPixel(x0 - y, y0 + x, color);
        TFT_DrawPixel(x0 + y, y0 - x, color);
        TFT_DrawPixel(x0 - y, y0 - x, color);
    }
}

void TFT_FillScreen(uint16_t color)
{
	uint32_t i;
	uint32_t n = hltdc.LayerCfg[0].ImageHeight*hltdc.LayerCfg[0].ImageWidth;
	for(i=0;i<n;i++)
	{
		*(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(i*2))=(uint16_t) color;
	}
}

void TFT_FillScreen_DMA(uint16_t color)
{
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.OutputOffset = 0;
	hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;
	
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
  {
    if (HAL_DMA2D_Start(&hdma2d, color, hltdc.LayerCfg[0].FBStartAdress,
    hltdc.LayerCfg[0].ImageWidth, hltdc.LayerCfg[0].ImageHeight) == HAL_OK)
    {
      HAL_DMA2D_PollForTransfer(&hdma2d, 2);
    }
  }
}


//----------------------------------------
void TFT_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t color)
{
	uint16_t tmp;
	
//	tmp = Xpos;
//	Xpos = Ypos;
//	Ypos = X_SIZE - 1 - tmp;
////////////////////////////////////////////rotate -90
	if(TFT_direction == 0x00){

	tmp = Xpos;
	Xpos = Ypos;
	Ypos = Y_SIZE - 1 - tmp;
	*(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(Pixels - Xpos - Ypos*hltdc.LayerCfg[0].ImageWidth))) = (uint16_t) color;}
	else	if (TFT_direction == 0x01){
//////////////////////////////////////////// 0 - no rotate
	*(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(Ypos*hltdc.LayerCfg[0].ImageWidth+Xpos)))=(uint16_t) color;
	}else	if (TFT_direction == 0x02){
////////////////////////////////////////////rotate -180
	*(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(Pixels - Xpos - Ypos*hltdc.LayerCfg[0].ImageWidth))) = (uint16_t) color;
	}
//  |-------------------|
//	|										|
//	|					0					|
//	|										|
//	|-------------------|
//		|Cable|		|Cable|
}			

uint16_t TFT_GetPixelValue(uint16_t Xpos, uint16_t Ypos)
{
	uint16_t tmp;
	
//	tmp = Xpos;
//	Xpos = Ypos;
//	Ypos = X_SIZE - 1 - tmp;
////////////////////////////////////////////rotate -90
	if(TFT_direction == 0x00){
	tmp = Xpos;
	Xpos = Ypos;
	Ypos = Y_SIZE - 1 - tmp;
	return *(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(Pixels - Xpos - Ypos*hltdc.LayerCfg[0].ImageWidth)));}
	else	if (TFT_direction == 0x01){
//////////////////////////////////////////// 0 - no rotate
	return *(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(Ypos*hltdc.LayerCfg[0].ImageWidth+Xpos)));
	}else	if (TFT_direction == 0x02){
////////////////////////////////////////////rotate -180
	return *(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(Pixels - Xpos - Ypos*hltdc.LayerCfg[0].ImageWidth)));
	}
}		


int16_t prev_x=0, prev_y=0; 
//----------------------------------------
void TFT_DrawLine(uint16_t x0, uint16_t y0,	uint16_t x1, uint16_t y1, uint16_t color)
{
	int16_t dx, dy, sx, sy, err, e2;
	
	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1); 
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1); 
	sx = (x0 < x1) ? 1 : -1; 
	sy = (y0 < y1) ? 1 : -1; 
	err = ((dx > dy) ? dx : -dy) / 2; 

	while (1) {
		
		TFT_DrawPixel(x0, y0, color); 

		if (x0 == x1 && y0 == y1) {
			break;
		}
		e2 = err; 
		if (e2 > -dx) {
			err -= dy;
			x0 += sx;
		} 
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		} 
	}
}

void TFT_DrawLineGraph(uint16_t x0, uint16_t y0,	uint16_t x1, uint16_t y1, uint16_t color)
{
	int16_t dx, dy, sx, sy, err, e2;
	
	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1); 
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1); 
	sx = (x0 < x1) ? 1 : -1; 
	sy = (y0 < y1) ? 1 : -1; 
	err = ((dx > dy) ? dx : -dy) / 2; 

	while (1) {
		
		if(flag_spectral && !(coordX[i_coord] == x0 && coordY[i_coord]== y0) && i_coord == 0){
				coordX[i_coord] = x0; 
				coordY[i_coord] = y0;
				graph_data_old[i_coord] = TFT_GetPixelValue(x0, y0);
				i_coord++;
			}
		if(i_coord > 0){
			if(flag_spectral && !(coordX[i_coord-1] == x0 && coordY[i_coord-1]== y0)){
				coordX[i_coord] = x0; 
				coordY[i_coord] = y0;
				graph_data_old[i_coord] = TFT_GetPixelValue(x0, y0);
				i_coord++;

			}
		}
		TFT_DrawPixel(x0, y0, color); 

		if (x0 == x1 && y0 == y1) {
			break;
		}
		e2 = err; 
		if (e2 > -dx) {
			err -= dy;
			x0 += sx;
		} 
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		} 
	}
}


void TFT_DrawBitmap(uint16_t X1, uint16_t Y1, sImage pbmp)
{
	uint16_t Xpos, Ypos;
	uint32_t i = 0;
	for(Ypos = Y1; Ypos < pbmp.Height+Y1; Ypos++){
		for(Xpos=X1; Xpos < pbmp.Width+X1; Xpos++){
			TFT_DrawPixel(Xpos, Ypos, (uint16_t)pbmp.pData[i]);
			i++;
		}
	}
}

void TFT_DrawBitmap_Flash(uint16_t X1, uint16_t Y1, sImageFlash pbmp)
{
	uint16_t Xpos, Ypos, buff_data[1];
	uint32_t i = 0;
	for(Ypos = Y1; Ypos < pbmp.Height+Y1; Ypos++){
//		QSPI_Recieve_IO_16(buff_data, Ypos*2+pbmp.Address, 100);
		for(Xpos=X1; Xpos < pbmp.Width+X1; Xpos++){
			QSPI_Recieve_IO_16(buff_data, i*2, 1);
			TFT_DrawPixel(Xpos, Ypos, (uint16_t)buff_data[0]);
			i++;
		}
	}
}


void TFT_DrawBitmap_DMA(uint16_t Xpos, uint16_t Ypos, sImage bmp)
{
	uint32_t i = 0;
	uint32_t address, index, index2;
	address = hltdc.LayerCfg[0].FBStartAdress+(((X_SIZE*Ypos) + Xpos)*2);
	
	for(index=0; index < bmp.Height; index++){
		for(index2 = 0; index2 < bmp.Width; index2++){
			hdma2d.Init.Mode = DMA2D_R2M;
			hdma2d.Init.ColorMode = DMA2D_RGB565;
			hdma2d.Init.OutputOffset = 0;
			hdma2d.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
			hdma2d.LayerCfg[0].InputAlpha = 0xFF;
			hdma2d.LayerCfg[0].InputColorMode = DMA2D_INPUT_RGB565;
			hdma2d.LayerCfg[0].InputOffset = 0;
			if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
			{
				if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK)
				{
					if(HAL_DMA2D_Start(&hdma2d, bmp.pData[i], address, 1, 1) == HAL_OK)
					{
						HAL_DMA2D_PollForTransfer(&hdma2d, 10);
						i++;
						address = hltdc.LayerCfg[0].FBStartAdress+(((X_SIZE*(Ypos+index) + (Xpos+index2))*2));
					}
				}
			}
		}
	}
}


void TFT_DrawBitmap_DMA_FLASH(uint16_t Xpos, uint16_t Ypos, sImageFlash bmp)
{
	
	uint32_t i = 0;
	uint32_t address, index, index2;
	address = hltdc.LayerCfg[0].FBStartAdress+(((X_SIZE*Ypos) + Xpos)*2);
	uint16_t buff[1400] = {0};
		uint16_t q = 0;

//	for (i = 0; i < 0xBEE6; i=i+0x578){
//			memcpy(buff, &TKA_Logo[i], sizeof(buff));
//			QSPI_Recieve_IO_16(buff, 0x0000+q*0x0B00, (sizeof(test16)/2));
//			q = q+1;
//	}
	
	
	for(index=0; index < bmp.Height; index++){
		for(index2 = 0; index2 < bmp.Width; index2++){
			hdma2d.Init.Mode = DMA2D_R2M;
			hdma2d.Init.ColorMode = DMA2D_RGB565;
			hdma2d.Init.OutputOffset = 0;
			hdma2d.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
			hdma2d.LayerCfg[0].InputAlpha = 0xFF;
			hdma2d.LayerCfg[0].InputColorMode = DMA2D_INPUT_RGB565;
			hdma2d.LayerCfg[0].InputOffset = 0;
			if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
			{
				if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK)
				{
//					if(HAL_DMA2D_Start(&hdma2d, bmp.pData[i], address, 1, 1) == HAL_OK)
//					{
//						HAL_DMA2D_PollForTransfer(&hdma2d, 10);
//						i++;
//						address = hltdc.LayerCfg[0].FBStartAdress+(((X_SIZE*(Ypos+index) + (Xpos+index2))*2));
//					}
				}
			}
		}
	}
}


void TFT_DrawGridAxes(uint16_t ZeroX, uint16_t ZeroY, uint16_t MaxX, uint16_t MaxY, uint16_t StepX, uint16_t StepY, uint16_t grid_color)
{	
	int16_t i;
				for (i = 0; i < MaxX-StepX; i+= StepX)
			{
				TFT_DrawLine(ZeroX+i, ZeroY,	ZeroX+i, MaxY, grid_color); //Ver. grid line
			}
			for (i = 0; i < Y_SIZE - MaxY; i+= StepY)
			{
				TFT_DrawLine(ZeroX, ZeroY-i,	MaxX, ZeroY-i, grid_color);//Hor. grid line
			}
}
	
void TFT_DrawGraphAxes(uint16_t ZeroX, uint16_t ZeroY, uint16_t MaxX, uint16_t MaxY, uint16_t StepX, uint16_t StepY, uint16_t color, uint8_t grid_on, uint16_t grid_color)
{
	int16_t i;
	uint8_t num = 0;
	char buffer[5] = {0};
	
	TFT_DrawLine(ZeroX-2, ZeroY,	MaxX, ZeroY, color);//Axe X
	TFT_DrawLine(ZeroX, ZeroY+2,	ZeroX, MaxY, color);//Axe Y
	
//Pick
	for (i = 0; i < MaxX-StepX; i+= StepX)
		{
			TFT_DrawLine(ZeroX+i, ZeroY-2,	ZeroX+i, ZeroY+2, color); 
		}
		
	for (i = 0; i < Y_SIZE - MaxY; i+= StepY)
		{
			TFT_DrawLine(ZeroX-2, ZeroY-i,	ZeroX+2, ZeroY-i, color);
		}
//Grid		
	if(grid_on)
		{

			for (i = 0; i < MaxX-StepX; i+= StepX)
			{
				TFT_SetTextColor(TFT_Black);
				TFT_SetBackColor(TFT_White);
				TFT_SetFont(&Font8);
				TFT_DrawLine(ZeroX+i, ZeroY,	ZeroX+i, MaxY, grid_color); //Ver. grid line
				sprintf (buffer, "%.1f", Unit_nm[num]);
				TFT_DisplayString(ZeroX+i-10, ZeroY+3, (uint8_t *)buffer, LEFT_MODE);
				num++;
			}
			num = 0;
			for (i = 0; i < Y_SIZE - MaxY; i+= StepY)
			{
				TFT_SetTextColor(TFT_Black);
				TFT_SetBackColor(TFT_White);
				TFT_SetFont(&Font8);
				TFT_DrawLine(ZeroX, ZeroY-i,	MaxX, ZeroY-i, grid_color);//Hor. grid line
				sprintf (buffer, "%.1f", Unit_Relative[num]);
				TFT_DisplayString(ZeroX-20, ZeroY-i-5, (uint8_t *)buffer, LEFT_MODE);
				num++;
			}
		}
	}

void TFT_DrawGraphData(uint16_t ZeroX, uint16_t ZeroY, uint16_t *GraphData, uint16_t color)
{
	uint16_t i;
	for(i = 0; i < 240; i++)
	{
		TFT_DrawLine(ZeroX+i, 412-GraphData[i], ZeroX+i+1, 412-GraphData[i+1], color);
	}
}

void TFT_FontsIni(void)
{
  lcdprop.BackColor = TFT_Black;
  lcdprop.TextColor = TFT_Green;
  lcdprop.pFont=&Font16;
}

//----------------------------------------

void TFT_SetFont(sFONT *fonts)
{
  lcdprop.pFont=fonts;
}

//----------------------------------------

void TFT_SetTextColor(uint32_t color)
{
  lcdprop.TextColor=color;
}

//----------------------------------------

void TFT_SetBackColor(uint32_t color)
{
  lcdprop.BackColor=color;
}

//----------------------------------------
	//--------------------------------------------------------------

void TFT_DrawCharRus(uint16_t x, uint16_t y, const uint8_t c)
{
  uint32_t i = 0, j = 0;
  uint16_t height, width;
  uint8_t offset;
  uint8_t *pchar;
  uint32_t line;
	if(c == 0x01)
	{
		ch = &lcdprop.pFont->table[0];
	}
	else
	{
		ch = &lcdprop.pFont->table[(c-0x7F) * lcdprop.pFont->Height * ((lcdprop.pFont->Width + 7) / 8)];
	}
	
	height = lcdprop.pFont->Height;
	width = lcdprop.pFont->Width;
	offset = 8 *((width + 7)/8) - width ;
	for(i = 0; i < height; i++)
	{
		pchar = ((uint8_t *)ch + (width + 7)/8 * i);
		switch((width + 7)/8)
		{
			case 1:
				line = pchar[0];
			break;
			
			case 2:
				line = (pchar[0]<< 8) | pchar[1];
			break;
			
			case 3:
			default:
				line = (pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2];
			break;
		}
		for (j = 0; j < width; j++)
		{
				if(line & (1 << (width- j + offset- 1)))
			{
				TFT_DrawPixel((x + j), y, lcdprop.TextColor);
			}
			else
			{
				TFT_DrawPixel((x + j), y, lcdprop.BackColor);
			}
		}
		y++;
	}
}


	uint16_t Xpos, Ypos;
	uint32_t ip = 0;
void TFT_DrawCutBMP(uint16_t x_pos, uint16_t y_pos, uint16_t xs, uint16_t ys, uint16_t size, sImage pbmp)
{
	uint16_t q = 1;
	ip = pbmp.Width*ys+xs-1;
	
	for(Ypos = y_pos; Ypos < y_pos+size; Ypos++){
		for(Xpos=x_pos; Xpos < x_pos+size; Xpos++){
			TFT_DrawPixel(Xpos, Ypos, (uint16_t)pbmp.pData[ip]);
			if(ip < ys*(pbmp.Width)+xs+size-2+(q-1)*pbmp.Width)
				{	ip++;} 
				else
				{ip = ip + pbmp.Width-size+1; 
					q++;}
		}
	}
	
}


void TFT_DisplayStringRus(uint16_t Xpos, uint16_t Ypos, const uint16_t *Text,	Text_AlignModeTypdef Mode)
{
	uint16_t ref_column = 1, i = 0;
	uint32_t size = 0, xsize = 0;
	const uint16_t *ptr = Text;
	uint8_t character = 0;
	
	while(*ptr++) size++ ;
	xsize = (X_SIZE/lcdprop.pFont->Width);
	switch (Mode)
	{
		case CENTER_MODE:
		{
			ref_column = Xpos + ((xsize-size) * lcdprop.pFont->Width) / 2;
			break;
		}
		case LEFT_MODE:
		{
			ref_column = Xpos;
			break;
		}
		case RIGHT_MODE:
		{
			ref_column = Xpos + ((xsize-size) * lcdprop.pFont->Width);
			break;
		}
		default:
		{
			ref_column = Xpos;
			break;
		}
	}
	if((ref_column < 1) || (ref_column >= 0x8000))
	{
		ref_column = 1;
	}
	while ((*Text != 0) & (((X_SIZE - (i*lcdprop.pFont->Width)) & 0xFFFF) >=
			lcdprop.pFont->Width))
	{
		if(*Text != 0x81D0)
		{character = (uint8_t)(((*Text)>>8)&0x00FF);}
			else
		{character = (uint8_t)(0x01);}
		
		TFT_DrawCharRus(ref_column, Ypos, character);
		ref_column += lcdprop.pFont->Width;
		Text++;
		i++;
	}
}

void TFT_DrawChar(uint16_t x, uint16_t y, const uint8_t c)
{

	uint32_t i=0, j=0;
	uint16_t height, width;
	uint8_t offset;
	uint8_t *pchar;
	uint32_t line;
	ch = &lcdprop.pFont->table[(c-' ') * lcdprop.pFont->Height *
		((lcdprop.pFont->Width +7) / 8)];
	height = lcdprop.pFont->Height;
	width = lcdprop.pFont->Width;
	offset = 8 * ((width + 7)/8) - width;
	for(i = 0;i < height; i++)
	{
		pchar = ((uint8_t *)ch + (width + 7)/8 * i);
		switch((width + 7)/8)
		{
		case 1:
			line = pchar[0];
			break;
		case 2:
			line = (pchar[0]<<8) | pchar[1];
			break;
		case 3:
		default:
			line = (pchar[0]<<16) | (pchar[1]<<8) | pchar[2];
			break;
		}
		for(j = 0;j < width; j++)
		{
			if(line & (1 << (width - j + offset -1)))
			{
				TFT_DrawPixel((x+j), y, lcdprop.TextColor);
			}
			else
			{
				TFT_DrawPixel((x+j), y, lcdprop.BackColor);
			}
		}
		y++;
	}
}
//----------------------------------------
void TFT_DisplayString(uint16_t Xpos, uint16_t Ypos, const uint8_t *Text,	Text_AlignModeTypdef Mode)
{
	uint16_t ref_column = 1, i = 0;
	uint32_t size = 0, xsize = 0;
	const uint8_t *ptr = Text;
	
	while(*ptr++) size++ ;
	xsize = (X_SIZE/lcdprop.pFont->Width);
	switch (Mode)
	{
		case CENTER_MODE:
		{
			ref_column = Xpos + ((xsize-size) * lcdprop.pFont->Width) / 2;
			break;
		}
		case LEFT_MODE:
		{
			ref_column = Xpos;
			break;
		}
		case RIGHT_MODE:
		{
			ref_column = Xpos + ((xsize-size) * lcdprop.pFont->Width);
			break;
		}
		default:
		{
			ref_column = Xpos;
			break;
		}
	}
	if((ref_column < 1) || (ref_column >= 0x8000))
	{
		ref_column = 1;
	}
	
	while ((*Text != 0) & (((X_SIZE - (i*lcdprop.pFont->Width)) & 0xFFFF) >=
			lcdprop.pFont->Width))
	{
		TFT_DrawChar(ref_column, Ypos, *Text);
		ref_column += lcdprop.pFont->Width;
		Text++;
		i++;
	}
}

void DrawLineX(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
    uint8_t steep = abs(y2-y1)>abs(x2-x1);
    if (steep){
        swap(x1, y1);
        swap(x2, y2);
    }
    if(x1>x2){
        swap(x1, x2);
        swap(y1, y2);
    }
    int dx,dy;
    dx=x2-x1;
    dy=abs(y2-y1);
    int err=dx/2;
    int ystep;
    if(y1<y2) ystep = 1;
    else  ystep = -1;
    for ( ; x1<=x2; x1++){
			
        if (steep) {TFT_DrawPixel(y1, x1, color);
//					if(flag_spectral && !(coordX[i_coord] == y1 && coordY[i_coord]== x1) && i_coord == 0){
//                coordX[i_coord] = y1; 
//                coordY[i_coord] = x1;
//                graph_data_old[i_coord] = TFT_GetPixelValue(y1, x1);
//                i_coord++;
//            }
//					if(i_coord > 0){
//							if(flag_spectral && !(coordX[i_coord-1] == y1 && coordY[i_coord-1]== x1)){
//									coordX[i_coord] = y1; 
//									coordY[i_coord] = x1;
//									graph_data_old[i_coord] = TFT_GetPixelValue(y1, x1);
//									i_coord++;
//							}
//					}
				}
        else {TFT_DrawPixel(x1, y1, color);
//					if(flag_spectral && !(coordX[i_coord] == x1 && coordY[i_coord]== y1) && i_coord == 0){
//									coordX[i_coord] = x1; 
//									coordY[i_coord] = y1;
//									graph_data_old[i_coord] = TFT_GetPixelValue(x1, y1);
//									i_coord++;
//							}
//					if(i_coord > 0){
//							if(flag_spectral && !(coordX[i_coord-1] == x1 && coordY[i_coord-1]== y1)){
//									coordX[i_coord] = x1; 
//									coordY[i_coord] = y1;
//									graph_data_old[i_coord] = TFT_GetPixelValue(x1, y1);
//									i_coord++;
//							}
//						}
					}
        err-=dy;
        if (err<0){
            y1 += ystep;
            err+=dx;
        }
    }
}


void GetLineX(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
    uint8_t steep = abs(y2-y1)>abs(x2-x1);
    if (steep){
        swap(x1, y1);
        swap(x2, y2);
    }
    if(x1>x2){
        swap(x1, x2);
        swap(y1, y2);
    }
    int dx,dy;
    dx=x2-x1;
    dy=abs(y2-y1);
    int err=dx/2;
    int ystep;
    if(y1<y2) ystep = 1;
    else  ystep = -1;
    for ( ; x1<=x2; x1++){
			
        if (steep) {
					if(flag_spectral && !(coordX[i_coord] == y1 && coordY[i_coord]== x1) && i_coord == 0){
                coordX[i_coord] = y1; 
                coordY[i_coord] = x1;
                graph_data_old[i_coord] = TFT_GetPixelValue(y1, x1);
                i_coord++;
            }
					if(i_coord > 0){
							if(flag_spectral && !(coordX[i_coord-1] == y1 && coordY[i_coord-1]== x1)){
									coordX[i_coord] = y1; 
									coordY[i_coord] = x1;
									graph_data_old[i_coord] = TFT_GetPixelValue(y1, x1);
									i_coord++;
							}
					}
				}
        else {
					if(flag_spectral && !(coordX[i_coord] == x1 && coordY[i_coord]== y1) && i_coord == 0){
									coordX[i_coord] = x1; 
									coordY[i_coord] = y1;
									graph_data_old[i_coord] = TFT_GetPixelValue(x1, y1);
									i_coord++;
							}
					if(i_coord > 0){
							if(flag_spectral && !(coordX[i_coord-1] == x1 && coordY[i_coord-1]== y1)){
									coordX[i_coord] = x1; 
									coordY[i_coord] = y1;
									graph_data_old[i_coord] = TFT_GetPixelValue(x1, y1);
									i_coord++;
							}
						}
					}
        err-=dy;
        if (err<0){
            y1 += ystep;
            err+=dx;
        }
    }
}
//----------------------------------------
