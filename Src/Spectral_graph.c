#include "Spectral_graph.h"
extern uint8_t TFT_direction;
extern uint16_t WaveLenght_Graph[4];
extern uint16_t PARGraph_B, PARGraph_G, PARGraph_R, PARGraph_IR;
extern uint8_t Graph_Field;

void Spectral_Axes(uint8_t direction){
	if (direction == 0x00)
	{
		TFT_FillRectangle(18, 95, 20, 412, TFT_White); //Yline
		TFT_FillRectangle(18, 412, 270, 414, TFT_White);//XLine
		
		TFT_DrawLine(18, 334, 268, 334, TFT_White); //25
		TFT_DrawLine(18, 257, 268, 257, TFT_White); //50
		TFT_DrawLine(18, 181, 268, 181, TFT_White); //75
		TFT_DrawLine(18, 105, 268, 105, TFT_White); //100
		
		for(uint16_t i = 0; i < 210; i+=40){
			TFT_FillRectangle(56+i, 95, 56+i, 412, TFT_White); 
		}
	} else if (direction == 0x01)
	{
		TFT_FillRectangle(253, 70, 255, 406, TFT_White); //XLine
		TFT_FillRectangle(40, 404, 255, 406, TFT_White); //Yline
		
		TFT_DrawLine(204, 70, 204, 406, TFT_White); //25
		TFT_DrawLine(151, 70, 151, 406, TFT_White); //50
		TFT_DrawLine(98, 70, 98, 406, TFT_White); //75
		TFT_DrawLine(45, 70, 45, 406, TFT_White); //100
		
		for(uint16_t i = 0; i < 260; i+=50){
			TFT_FillRectangle(40, 354-i, 255, 354-i, TFT_White);
		}

	} else if (direction == 0x02)
	{
		TFT_FillRectangle(18, 74, 16, 406, TFT_White); //XLine
		TFT_FillRectangle(17, 74, 232, 76, TFT_White); //Yline
		
		TFT_DrawLine(68, 70, 68, 406, TFT_White); //25
		TFT_DrawLine(121, 70, 121, 406, TFT_White); //50
		TFT_DrawLine(174, 70, 174, 406, TFT_White); //75
		TFT_DrawLine(227, 70, 227, 406, TFT_White); //100
		
		for(uint16_t i = 0; i < 260; i+=50){
			TFT_FillRectangle(17, 374-i, 232, 374-i, TFT_White);
		}
	}
}

void Spectral_PAR_Range(uint8_t direction){
	if (direction == 0x00)
	{
		TFT_FillRectangle(19, 105, 19+PARGraph_B/4, 411, TFT_Black_Bkgr);
		TFT_FillRectangle(19+PARGraph_B/4, 105, 19+PARGraph_G/4, 411, TFT_PAR_Blue);
		TFT_FillRectangle(19+PARGraph_G/4, 105, 19+PARGraph_R/4, 411, TFT_PAR_Green);
		TFT_FillRectangle(19+PARGraph_R/4, 105, 19+PARGraph_IR/4, 411, TFT_PAR_Red);
		TFT_FillRectangle(19+PARGraph_IR/4, 105, 19+1000/4, 411, TFT_PAR_IRed);
	} else if(direction == 0x01)
	{
		TFT_FillRectangle( 45, 403-PARGraph_G/3, 253, 403-PARGraph_B/3, TFT_PAR_Blue);
		TFT_FillRectangle( 45, 403-PARGraph_R/3, 253, 403-PARGraph_G/3, TFT_PAR_Green);
		TFT_FillRectangle( 45, 403-PARGraph_IR/3, 253, 403-PARGraph_R/3, TFT_PAR_Red);
		TFT_FillRectangle( 45, 403-1000/3, 253, 403-PARGraph_IR/3, TFT_PAR_IRed);
	}else
	{
		TFT_FillRectangle( 19, 74+PARGraph_B/3, 227, 74+PARGraph_G/3, TFT_PAR_Blue);
		TFT_FillRectangle( 19, 74+PARGraph_G/3, 227, 74+PARGraph_R/3, TFT_PAR_Green);
		TFT_FillRectangle( 19, 74+PARGraph_R/3, 227, 74+PARGraph_IR/3, TFT_PAR_Red);
		TFT_FillRectangle( 19, 74+PARGraph_IR/3, 227, 74+1000/3, TFT_PAR_IRed);
	}
}


void Spectral_Axes_Text(uint8_t direction){
	char buffer[4] = {0};
	
	if (direction == 0x00)
	{
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black_Bkgr);
		TFT_SetFont(&Font6EN_arch_big);

		TFT_DrawChar(5, 410, '0');
		
		TFT_DrawChar(7, 257, '.');
		TFT_DrawChar(3, 257, '0');
		TFT_DrawChar(11, 257, '5');
		
		TFT_DrawChar(0, 105, '1');
		TFT_DrawChar(4, 105, '.');
		TFT_DrawChar(9, 105, '0');
		
		
		sprintf (buffer, "%.0u", WaveLenght_Graph[0]);
		TFT_DisplayString(11, 416, (uint8_t *)buffer, LEFT_MODE);
		sprintf (buffer, "%.0u", WaveLenght_Graph[1]);
		TFT_DisplayString(85, 416, (uint8_t *)buffer, LEFT_MODE);
		sprintf (buffer, "%.0u", WaveLenght_Graph[2]);
		TFT_DisplayString(165, 416, (uint8_t *)buffer, LEFT_MODE);
		sprintf (buffer, "%.0u", WaveLenght_Graph[3]);
		TFT_DisplayString(245, 416, (uint8_t *)buffer, LEFT_MODE);
		
	} else if (direction != 0x00)
	{
		if(direction == 0x01){TFT_direction = 0x01;} 
		else {TFT_direction = 0x02;}


		
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black_Bkgr);
		TFT_SetFont(&Font6EN_arch_big);

		sprintf (buffer, "%.0u", WaveLenght_Graph[0]);
		TFT_DisplayString(65, 258, (uint8_t *)buffer, LEFT_MODE);
		sprintf (buffer, "%.0u", WaveLenght_Graph[1]);
		TFT_DisplayString(165, 258, (uint8_t *)buffer, LEFT_MODE);
		sprintf (buffer, "%.0u", WaveLenght_Graph[2]);
		TFT_DisplayString(265, 258, (uint8_t *)buffer, LEFT_MODE);
		sprintf (buffer, "%.0u", WaveLenght_Graph[3]);
		TFT_DisplayString(365, 258, (uint8_t *)buffer, LEFT_MODE);
		
		TFT_DrawChar(65, 250, '0');

		TFT_DrawChar(57, 149, '0');
		TFT_DrawChar(62, 149, '.');
		TFT_DrawChar(67, 149, '5');

			
		TFT_DrawChar(57, 43, '1');
		TFT_DrawChar(62, 43, '.');
		TFT_DrawChar(67, 43, '0');

		TFT_direction = 0x00;
	}
}

uint32_t graph_data_old[1500] = {0};
uint16_t coordX[1500] = {0}, coordY[1500] = {0};
uint16_t i_coord = 0;
uint8_t flag_spectral = 0, flag_refresh = 0;
uint16_t screen_cnt = 0;
uint8_t Rotation_Screen_Spectral_Old2;
extern float max_Rabs_graph;
extern uint16_t graph_spectral_day[355], graph_spectral_night[355], graph_spectral_Retina[355], graph_spectral_Blue[355];
    
void Spectral_DrawGraph(uint16_t ZeroX, uint16_t ZeroY, float GraphData[], uint16_t color, uint8_t direction)
{
    float buf_pix;
    uint16_t i, j = 0;
    uint16_t graph_data[335];
    uint16_t graph_lenht = (direction == 0x00)? 240 : 330;
    uint16_t scale = (direction == 0x00)? 307 : 209; //307+200 : 209+200;
    uint8_t    step = (direction == 0x00)? 4 :3;
    uint16_t  jj = 0, ii = 0;

    screen_cnt++;
    if(screen_cnt > 200 || direction != Rotation_Screen_Spectral_Old2){
			Rotation_Screen_Spectral_Old2 = direction;
        if(Graph_Field&PPF_Bands)
        {
            Spectral_PAR_Range(direction);
        }else{TFT_FillRectangle(5, 55, 270, 421, TFT_Black_Bkgr);
        }
        
        if(Graph_Field&V_lambda)
        {
            Spectral_DrawGraph_Const(20, 20, graph_spectral_day, TFT_Yellow, direction);
            Spectral_DrawGraph_Const(20, 20, graph_spectral_night, TFT_Blue, direction);
            }
        
        if(Graph_Field&EbEr_graph)
            {
                Spectral_DrawGraph_Const(20, 20, graph_spectral_Blue, TFT_DarkCyan, direction);
                Spectral_DrawGraph_Const(20, 20, graph_spectral_Retina, TFT_Red, direction);
            }
    Spectral_Axes(direction);
    Spectral_Axes_Text(direction);
						
    screen_cnt = 0;
    }
    flag_refresh = 1;
    
    for(uint16_t graph_i = 1023; graph_i >= step; graph_i-=step)
            {
                buf_pix = (((float)GraphData[1023-graph_i])/max_Rabs_graph)*scale;//(65535.0  data/max(data))*graph scale
                if(buf_pix < ((direction == 0x00)? 307 : 209))
								{graph_data[j] = (uint16_t)buf_pix;} else{graph_data[j] = ((direction == 0x00)? 307 : 209);}  
                j++;
            }        
    i_coord = 0;
            
    for(i = 0; i < graph_lenht; i++)
    {
        if(direction == 0x00){
            flag_spectral = 1;
           TFT_DrawLineGraph(ZeroX+i, 412-graph_data[i], ZeroX+i+1, 412-graph_data[i+1], color);
            flag_spectral = 0;
        }
        else if(direction == 0x01)
        {
            flag_spectral = 1;
           TFT_DrawLineGraph(253 - graph_data[graph_lenht-i], 72+i+1, 253 - graph_data[graph_lenht-i+1], 72+i, color);
            flag_spectral = 0;
        } else if(direction == 0x02)
				{flag_spectral = 1; 
						TFT_DrawLineGraph(graph_data[i]+18, 76+i, graph_data[i+1]+18, 76+i+1, color);
				flag_spectral = 0;}
					}
}
void Spectral_RefreshGraph(uint8_t direction)
{
    uint16_t i = 0;
    for(i = 0; i < i_coord; i++){
            TFT_DrawPixel(coordX[i], coordY[i], graph_data_old[i]);
        }
		memset(coordX, 0, sizeof(coordX));
		memset(coordY, 0, sizeof(coordY));
		memset(graph_data_old, 0, sizeof(graph_data_old));	
}


void Spectral_DrawGraph_Const(uint16_t ZeroX, uint16_t ZeroY, uint16_t *GraphData, uint16_t color, uint8_t direction)
{
		uint16_t i, j = 0;
		uint16_t graph_data[335];
		uint16_t graph_lenht = (direction == 0x00)? 240 : 330;
		uint16_t scale = (direction == 0x00)? 307 : 209;
		uint8_t	step = (direction == 0x00)? 4 :3;
	
		for(i = 0; i < graph_lenht; i++)
	{
		if(direction == 0x00){
			TFT_DrawLine(ZeroX+i, 412-GraphData[i], ZeroX+i+1, 412-GraphData[i+1], color);} 
		else if(direction == 0x01)
		{
			TFT_DrawLine(253 - GraphData[graph_lenht-i], 72+1+i, 253 - GraphData[graph_lenht-i+1], 72+i, color);
		} else {TFT_DrawLine(GraphData[i]+18, 76+i, GraphData[i+1]+18, 76+i+1, color);}
	}
}


void Spectral_DrawGraph_Line(uint16_t ZeroX, uint16_t ZeroY, uint16_t GraphData[], uint16_t color, uint8_t direction)
{
    float buf_pix;
    uint16_t i, j = 0;
    uint16_t graph_data[335];
    uint16_t graph_lenht = (direction == 0x00)? 240 : 330;
    uint16_t scale = (direction == 0x00)? 307 : 209; //307+200 : 209+200;
    uint8_t    step = (direction == 0x00)? 4 :3;
    uint16_t  jj = 0, ii = 0;

    screen_cnt++;
    if(screen_cnt > 200 || direction != Rotation_Screen_Spectral_Old2){
			Rotation_Screen_Spectral_Old2 = direction;
        if(Graph_Field&PPF_Bands)
        {
            Spectral_PAR_Range(direction);
        }else{TFT_FillRectangle(5, 55, 270, 421, TFT_Black_Bkgr);
        }
        
        if(Graph_Field&V_lambda)
        {
            Spectral_DrawGraph_Const(20, 20, graph_spectral_day, TFT_Yellow, direction);
            Spectral_DrawGraph_Const(20, 20, graph_spectral_night, TFT_Blue, direction);
            }
        
        if(Graph_Field&EbEr_graph)
            {
                Spectral_DrawGraph_Const(20, 20, graph_spectral_Blue, TFT_DarkCyan, direction);
                Spectral_DrawGraph_Const(20, 20, graph_spectral_Retina, TFT_Red, direction);
            }
    Spectral_Axes(direction);
    Spectral_Axes_Text(direction);
						
    screen_cnt = 0;
    }
    flag_refresh = 1;
    
    for(uint16_t graph_i = 1023; graph_i >= step; graph_i-=step)
            {
                buf_pix = (((float)GraphData[graph_i])/65535.0)*scale;//(65535.0  data/max(data))*graph scale
                if(buf_pix < ((direction == 0x00)? 307 : 209))
								{graph_data[j] = (uint16_t)buf_pix;} else{graph_data[j] = ((direction == 0x00)? 307 : 209);}  
                j++;
            }        
    i_coord = 0;
            
    for(i = 0; i < graph_lenht; i++)
    {
        if(direction == 0x00){
            flag_spectral = 1;
           TFT_DrawLineGraph(ZeroX+i, 412-graph_data[i], ZeroX+i+1, 412-graph_data[i+1], color);
            flag_spectral = 0;
        }
        else if(direction == 0x01)
        {
            flag_spectral = 1;
           TFT_DrawLineGraph(253 - graph_data[graph_lenht-i], 72+i+1, 253 - graph_data[graph_lenht-i+1], 72+i, color);
            flag_spectral = 0;
        } else if(direction == 0x02)
				{flag_spectral = 1; 
						TFT_DrawLineGraph(graph_data[i]+18, 76+i, graph_data[i+1]+18, 76+i+1, color);
				flag_spectral = 0;}
					}
}

void Spectral_DrawGraph_Line2(uint16_t ZeroX, uint16_t ZeroY, uint16_t GraphData[], uint16_t color, uint8_t direction)
{
    float buf_pix;
    uint16_t i, j = 0;
    uint16_t graph_data[335];
    uint16_t graph_lenht = (direction == 0x00)? 240 : 330;
    uint16_t scale = (direction == 0x00)? 307 : 209; //307+200 : 209+200;
    uint8_t    step = (direction == 0x00)? 4 :3;
    uint16_t  jj = 0, ii = 0;

//    screen_cnt++;
//	screen_cnt > 200 ||
    if( direction != Rotation_Screen_Spectral_Old2){
			Rotation_Screen_Spectral_Old2 = direction;
			TFT_FillRectangle(1, 55, 271, 421, TFT_Black_Bkgr);
        if(Graph_Field&PPF_Bands)
        {
            Spectral_PAR_Range(direction);
        }else{TFT_FillRectangle(5, 55, 270, 421, TFT_Black_Bkgr);
        }

    Spectral_Axes(direction);
    Spectral_Axes_Text(direction);
						
    screen_cnt = 0;
    }
    flag_refresh = 1;
    
    
    i_coord = 0;
            
    for(i = 0; i < graph_lenht; i++)
    {
        if(direction == 0x00){
            flag_spectral = 1;
						DrawLineX(ZeroX+i, 412-GraphData[i], ZeroX+i+1, 412-GraphData[i+1], color);
            flag_spectral = 0;
        }
        else if(direction == 0x01)
        {
            flag_spectral = 1;
           DrawLineX(253 - GraphData[graph_lenht-i], 72+i+1, 253 - GraphData[graph_lenht-i+1], 72+i, color);
            flag_spectral = 0;
        } else if(direction == 0x02)
				{flag_spectral = 1; 
						DrawLineX(GraphData[i]+18, 76+i, GraphData[i+1]+18, 76+i+1, color);
				flag_spectral = 0;}
					}
}



uint16_t Line_Rabs_buff_graph2[355] = {0};
void Rabs_graph_to_display(uint8_t direction, float Line_Rabs_buff[])
{    
	uint8_t    step = (direction == 0x00)? 4 :3;
	uint16_t  q = 0, res;
	float scale = (direction == 0x00)? 307 : 209; 
	memset(Line_Rabs_buff_graph2, 0, sizeof(Line_Rabs_buff_graph2));

	for(uint16_t ic = 0; ic <= 1023; ic+=step){
		res = (uint16_t)((Line_Rabs_buff[ic]/max_Rabs_graph)*scale);
		Line_Rabs_buff_graph2[q] = (res > scale) ? scale : res;
		q++;
	}
}

void Refresh_screen_Graph(uint16_t ZeroX, uint16_t ZeroY, uint16_t GraphData[], uint8_t direction)
{   
	uint16_t i = 0;
	uint16_t graph_lenht = (direction == 0x00)? 240 : 330;
	
	 for(i = 0; i < graph_lenht; i++)
    {
        if(direction == 0x00){
					if((Graph_Field&PPF_Bands)){TFT_FillRectangle_DMA(68, 18+PARGraph_G/4, 375, 20+PARGraph_G/4, TFT_PAR_Green);
																			TFT_FillRectangle_DMA(68, 18+PARGraph_R/4, 375, 20+PARGraph_R/4, TFT_PAR_Red);
																			TFT_FillRectangle_DMA(68, 18+PARGraph_IR/4, 375, 20+PARGraph_IR/4, TFT_PAR_IRed);}
					DrawLineX(ZeroX+i, 412-GraphData[i], ZeroX+i+1, 412-GraphData[i+1], (Graph_Field&PPF_Bands) ? ((ZeroX+i < 19+PARGraph_B/4) ? TFT_Black_Bkgr : (ZeroX+i < 19+PARGraph_G/4 ) ? TFT_PAR_Blue :
																																							(ZeroX+i < 19+PARGraph_R/4) ? TFT_PAR_Green :
																																							(ZeroX+i < 19+PARGraph_IR/4) ? TFT_PAR_Red : TFT_PAR_IRed) : TFT_Black_Bkgr);
        }
        else if(direction == 0x01)
        {
				if((Graph_Field&PPF_Bands)){TFT_FillRectangle_DMA(76+PARGraph_G/3, 45, 79+PARGraph_G/3,253, TFT_PAR_Green);
																			TFT_FillRectangle_DMA(76+PARGraph_R/3, 45, 79+PARGraph_R/3,253, TFT_PAR_Red);
																			TFT_FillRectangle_DMA(76+PARGraph_IR/3,45, 79+PARGraph_IR/3,253, TFT_PAR_IRed);}
				
				DrawLineX(253 - GraphData[graph_lenht-i], 72+i+1, 253 - GraphData[graph_lenht-i+1], 72+i, 
					(Graph_Field&PPF_Bands) ? (72+i+1 < 403-1000/3 ? TFT_Black_Bkgr :
											   72+i+1 < 403-PARGraph_IR/3 ? TFT_PAR_IRed:
											   72+i+1 < 403-PARGraph_R/3 ? TFT_PAR_Red:
											   72+i+1 < 403-PARGraph_G/3 ? TFT_PAR_Green:TFT_PAR_Blue) : TFT_Black_Bkgr);

        } else if(direction == 0x02)
				{
					if((Graph_Field&PPF_Bands)){TFT_FillRectangle_DMA(408-PARGraph_G/3, 19, 405-PARGraph_G/3,227, TFT_PAR_Green);//TFT_PAR_Green
															TFT_FillRectangle_DMA(408-PARGraph_R/3, 19, 405-PARGraph_R/3,227, TFT_PAR_Red);
															TFT_FillRectangle_DMA(408-PARGraph_IR/3,19, 405-PARGraph_IR/3,227, TFT_PAR_IRed);}
					
					DrawLineX(GraphData[i]+18, 76+i, GraphData[i+1]+18, 76+i+1, (Graph_Field&PPF_Bands) ? ((76+i < PARGraph_B/3) ? TFT_Black_Bkgr :
           	(76+i < 74+PARGraph_G/3) ? TFT_PAR_Blue : 
           	(76+i < 74+PARGraph_R/3) ? TFT_PAR_Green : 
						(76+i < 74+PARGraph_IR/3) ? TFT_PAR_Red : TFT_PAR_IRed)
           	:TFT_Black_Bkgr);
				}
			}
		Spectral_Axes(direction);
		 if(Graph_Field&V_lambda)
			{
					Spectral_DrawGraph_Const(20, 20, graph_spectral_day, TFT_Yellow, direction);
					Spectral_DrawGraph_Const(20, 20, graph_spectral_night, TFT_Blue, direction);
					}
			
			if(Graph_Field&EbEr_graph)
					{
							Spectral_DrawGraph_Const(20, 20, graph_spectral_Blue, TFT_DarkCyan, direction);
							Spectral_DrawGraph_Const(20, 20, graph_spectral_Retina, TFT_Red, direction);
					}
}