#ifndef __LTDC_H
#define __LTDC_H

#include "stm32l4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include "DRAWIMAGE.h"
#include "fonts.h"


#define swap(a,b) {int16_t t=a;a=b;b=t;}

//Color
#define TFT_Black           0x0000      /*   0,   0,   0 */
#define TFT_Navy            0x000F      /*   0,   0, 128 */
#define TFT_DarkGreen       0x03E0      /*   0, 128,   0 */
#define TFT_DarkCyan        0x03EF      /*   0, 128, 128 */
#define TFT_RuBlue     		  0x01D4			/*   0, 57, 165*/
#define TFT_RuRed     		  0xC943			/*   212, 43, 30*/
#define TFT_Maroon          0x7800      /* 128,   0,   0 */
#define TFT_Purple          0x780F      /* 128,   0, 128 */
#define TFT_Olive           0x7BE0      /* 128, 128,   0 */
#define TFT_LightGrey       0xC618      /* 192, 192, 192 */
#define TFT_DarkGrey        0x7BEF      /* 128, 128, 128 */
#define TFT_Blue            0x001F      /*   0,   0, 255 */
#define TFT_Green           0x07E0      /*   0, 255,   0 */
#define TFT_Cyan            0x07FF      /*   0, 255, 255 */
#define TFT_Red             0xF800      /* 255,   0,   0 */
#define TFT_Magenta         0xF81F      /* 255,   0, 255 */
#define TFT_Yellow          0xFFE0      /* 255, 255,   0 */
#define TFT_White           0xFFFF      /* 255, 255, 255 */
#define TFT_Orange          0xFD20      /* 255, 165,   0 */
#define TFT_GreenYellow     0xAFE5      /* 173, 255,  47 */
#define TFT_PINK            0xF81F
#define	TFT_PETERRIVER			0x34BA			
#define	TFT_GreyMain				0xDF1C			/*223, 227, 238*/
#define TFT_Grey 						0x94D2			/*156, 156, 156*/
#define	TFT_GreenBattery		0x8CB1			/*144, 153, 141*/
#define	TFT_Blue_On					0x249B			/*33, 149, 224*/
#define	TFT_Blue_Off				0x1376			/*21, 113, 188*/
#define TFT_Black_Bkgr      0x0063      /*  3,  15,  29 */
#define TFT_Blue_action			0x1376//// del
#define TFT_PAR_Blue				0x22B2
#define TFT_PAR_Green				0xCF38
#define TFT_PAR_Red					0xF5B9
#define TFT_PAR_IRed				0x1B46

////CQS chart color///
#define CQS_COLOR_Q1		0x7A2F
#define CQS_COLOR_Q2		0x5A92
#define CQS_COLOR_Q3		0x22B2
#define CQS_COLOR_Q4		0x03D4
#define CQS_COLOR_Q5		0x04D4
#define CQS_COLOR_Q6		0x04D0
#define CQS_COLOR_Q7		0x04EB
#define CQS_COLOR_Q8		0x7569
#define CQS_COLOR_Q9		0xB607
#define CQS_COLOR_Q10		0xEE25
#define CQS_COLOR_Q11		0xD4A3
#define CQS_COLOR_Q12		0xEC47
#define CQS_COLOR_Q13		0xDB48
#define CQS_COLOR_Q14		0xA947
#define CQS_COLOR_Q15		0x99AB

////CRI chart color///
#define CRI_COLOR_R1		0xC4F0
#define CRI_COLOR_R2		0xC3E7
#define CRI_COLOR_R3		0xAD88
#define CRI_COLOR_R4		0x140F
#define CRI_COLOR_R5		0x14D8
#define CRI_COLOR_R6		0x3DF6
#define CRI_COLOR_R7		0x8457
#define CRI_COLOR_R8		0xA477
#define CRI_COLOR_R9		0xE165
#define CRI_COLOR_R10		0xE723
#define CRI_COLOR_R11		0x1427
#define CRI_COLOR_R12		0x218D
#define CRI_COLOR_R13		0xF75D
#define CRI_COLOR_R14		0x1B46
#define CRI_COLOR_R15		0xF611

#define TKA_LOGO_BMP		0x0000
#define TKA_LOGO_BMP_SIZEX	270
#define TKA_LOGO_BMP_SIZEY	181

#define LAB_LOCUS_BMP		0x18100
#define LAB_LOCUS_SIZEX		250
#define LAB_LOCUS_SIZEY		250

#define XY2_LOCUS_BMP		0x37000 
#define XY2_LOCUS_BMP_SIZEX		216
#define XY2_LOCUS_BMP_SIZEY		250

#define XY10_LOCUS_BMP	0x51D00
#define XY10_LOCUS_BMP_SIZEX	216 
#define XY10_LOCUS_BMP_SIZEY	250 

#define LUV_LOCUS_BMP		0x6CA00 
#define LUV_LOCUS_BMP_SIZEX		250 
#define LUV_LOCUS_BMP_SIZEY	234 

typedef struct
{
  uint32_t TextColor;
  uint32_t BackColor;
  sFONT *pFont;
}LCD_DrawPropTypeDef;

//------------------------------------------

typedef enum
{
  CENTER_MODE = 0x01, /* Center mode */
  RIGHT_MODE = 0x02, /* Right mode */
  LEFT_MODE = 0x03 /* Left mode */
}Text_AlignModeTypdef;

//------------------------------------------

void TFT_FillScreen(uint16_t color);
void TFT_FillRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color);
void TFT_FillRectangle_DMA(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void TFT_DrawPixel(uint16_t x1, uint16_t y1, uint16_t color);
void TFT_DrawLine(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1, uint16_t color);
void TFT_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color);
void TFT_DrawBitmap(uint16_t X1, uint16_t Y1, sImage pbmp);
void TFT_DrawGridAxes(uint16_t ZeroX, uint16_t ZeroY, uint16_t MaxX, uint16_t MaxY, uint16_t StepX, uint16_t StepY, uint16_t grid_color);
void TFT_DrawGraphAxes(uint16_t ZeroX, uint16_t ZeroY, uint16_t MaxX, uint16_t MaxY, uint16_t StepX, uint16_t StepY, uint16_t color, uint8_t grid_on, uint16_t grid_color);
void TFT_DrawGraphData(uint16_t ZeroX, uint16_t ZeroY, uint16_t *GraphData, uint16_t color);
uint16_t TFT_GetPixelValue(uint16_t Xpos, uint16_t Ypos);
void TFT_GetPixelsLineValue(uint16_t x0, uint16_t y0,	uint16_t x1, uint16_t y1, uint16_t Pixels_data[]);
void TFT_FillScreen_DMA(uint16_t color);
void TFT_DrawPixel_DMA(uint16_t Xpos, uint16_t Ypos, uint16_t color);
void TFT_DrawBitmap_DMA(uint16_t Xpos, uint16_t Ypos, sImage pbmp);
void TFT_FontsIni(void);
void TFT_SetFont(sFONT *fonts);
void TFT_SetTextColor(uint32_t color);
void TFT_SetBackColor(uint32_t color);
void TFT_DrawCharRus(uint16_t x, uint16_t y, const uint8_t c);
void TFT_DrawChar(uint16_t x, uint16_t y, const uint8_t c);
void TFT_DisplayString(uint16_t Xpos, uint16_t Ypos, const uint8_t *Text, Text_AlignModeTypdef Mode);
void TFT_DisplayStringRus(uint16_t Xpos, uint16_t Ypos, const uint16_t *Text, Text_AlignModeTypdef Mode);
void TFT_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);
void TFT_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);
void TFT_DrawCircleCorner(int16_t x0, int16_t y0, int16_t r, uint8_t corner, uint32_t color);
void TFT_DrawFilledCircleCorner(int16_t x0, int16_t y0, int16_t r, uint8_t corner, uint32_t color);
void TFT_DrawFilledRoundedRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t r, uint32_t color);
void TFT_DrawLineGraph(uint16_t x0, uint16_t y0,	uint16_t x1, uint16_t y1, uint16_t color);
void TFT_DrawBitmap_Flash(uint16_t X1, uint16_t Y1, sImageFlash pbmp);
void TFT_DrawBitmap_DMA_FLASH(uint16_t Xpos, uint16_t Ypos, sImageFlash bmp);

void TFT_DrawCutBMP(uint16_t x_pos, uint16_t y_pos, uint16_t xs, uint16_t ys, uint16_t size, sImage pbmp);

void DrawLineX(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void GetLineX(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
#endif /* __LTDC_H */
