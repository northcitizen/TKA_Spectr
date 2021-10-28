#include "CQS_graph.h"
extern uint8_t TFT_direction;


void CQS_Axes(uint8_t direction){
	if (direction == 0x00)
	{
		TFT_FillRectangle(16, 95, 18, 412, TFT_White); //Yline
		TFT_FillRectangle(16, 412, 270, 414, TFT_White);//XLine
		
		TFT_DrawLine(16, 334, 268, 334, TFT_White); //25
		TFT_DrawLine(16, 257, 268, 257, TFT_White); //50
		TFT_DrawLine(16, 181, 268, 181, TFT_White); //75
		TFT_DrawLine(16, 105, 268, 105, TFT_White); //100
	} else if (direction == 0x01)
	{
		TFT_FillRectangle(253, 70, 255, 406, TFT_White); //XLine
		TFT_FillRectangle(40, 404, 255, 406, TFT_White); //Yline
		
		TFT_DrawLine(204, 70, 204, 406, TFT_White); //25
		TFT_DrawLine(151, 70, 151, 406, TFT_White); //50
		TFT_DrawLine(98, 70, 98, 406, TFT_White); //75
		TFT_DrawLine(45, 70, 45, 406, TFT_White); //100
	}else if (direction == 0x02)
	{
		TFT_FillRectangle(18, 74, 16, 406, TFT_White); //XLine
		TFT_FillRectangle(17, 74, 232, 76, TFT_White); //Yline
		
		TFT_DrawLine(68, 70, 68, 406, TFT_White); //25
		TFT_DrawLine(121, 70, 121, 406, TFT_White); //50
		TFT_DrawLine(174, 70, 174, 406, TFT_White); //75
		TFT_DrawLine(227, 70, 227, 406, TFT_White); //100
		}
}

void CQS_Axes_Measure(uint8_t direction, uint8_t Qa, uint8_t Qp, uint8_t Qf){

	char buffer[2] = {0};
	
	
if (direction == 0x00)
	{
		
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black);
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(20, 70, 'a');
		TFT_SetFont(&Font16EN_arch_big);
		TFT_DrawChar(5, 70-2, 'Q');
		
		sprintf (buffer, "%d", Qa);
		TFT_DisplayString(39, 70-2, (uint8_t *)buffer, LEFT_MODE);
		
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(112, 70, 'p');

		TFT_SetFont(&Font16EN_arch_big);
		TFT_DrawChar(93, 70-2, 'Q');
		
		sprintf (buffer, "%d", Qp);
		TFT_DisplayString(130, 70-2, (uint8_t *)buffer, LEFT_MODE);
		
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(206, 70, 'f');
		TFT_SetFont(&Font16EN_arch_big);
		TFT_DrawChar(191, 70-2, 'Q');

		sprintf (buffer, "%d", Qf);
		TFT_DisplayString(230, 70-2, (uint8_t *)buffer, LEFT_MODE);
	} else if(direction != 0x00)
	{
		if(direction == 0x01){TFT_direction = 0x01;} 
		else {TFT_direction = 0x02;}

		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black);
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(100, 16, 'a');
		TFT_SetFont(&Font16EN_arch_big);
		TFT_DrawChar(85, 16-2, 'Q');
		
		sprintf (buffer, "%d", Qa);
		TFT_DisplayString(125, 16-2, (uint8_t *)buffer, LEFT_MODE);
		
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(216, 16, 'p');
		
		TFT_SetFont(&Font16EN_arch_big);
		TFT_DrawChar(199, 16-2, 'Q');
		
		sprintf (buffer, "%d", Qp);
		TFT_DisplayString(252, 16-2, (uint8_t *)buffer, LEFT_MODE);
		
		TFT_SetFont(&Font16EN_arch_small);
		TFT_DrawChar(340, 16-2, 'f');
		TFT_SetFont(&Font16EN_arch_big);
		TFT_DrawChar(325, 16-2, 'Q');
		
		sprintf (buffer, "%d", Qf);
		TFT_DisplayString(365, 16-2, (uint8_t *)buffer, LEFT_MODE);
		TFT_direction = 0x00;
	}
}

void CQS_Axes_Text(uint8_t direction){
	if (direction == 0x00)
	{
		
		//max Y = 105    min Y = 410
		TFT_SetFont(&Font6EN_arch_big);
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black);
		
		TFT_DrawChar(24, 415, 'Q');
		TFT_DrawChar(30, 415, '1');

		TFT_DrawChar(40, 415, 'Q');
		TFT_DrawChar(46, 415, '2');

		TFT_DrawChar(56, 415, 'Q');
		TFT_DrawChar(62, 415, '3');

		TFT_DrawChar(72, 415, 'Q');
		TFT_DrawChar(78, 415, '4');
		
		TFT_DrawChar(88, 415, 'Q');
		TFT_DrawChar(94, 415, '5');


		TFT_DrawChar(104, 415, 'Q');
		TFT_DrawChar(110, 415, '6');
		
		TFT_DrawChar(120, 415, 'Q');
		TFT_DrawChar(126, 415, '7');
		
		TFT_DrawChar(136, 415, 'Q');
		TFT_DrawChar(142, 415, '8');
		
		TFT_DrawChar(152, 415, 'Q');
		TFT_DrawChar(158, 415, '9');
		
		TFT_DrawChar(173, 415, '1');
		TFT_DrawChar(168, 415, 'Q');
		TFT_DrawChar(177, 415, '0');


		TFT_DrawChar(189, 415, '1');
		TFT_DrawChar(184, 415, 'Q');
		TFT_DrawChar(194, 415, '1');
		
		TFT_DrawChar(205, 415, '1');
		TFT_DrawChar(200, 415, 'Q');
		TFT_DrawChar(209, 415, '2');
		
		TFT_DrawChar(221, 415, '1');
		TFT_DrawChar(216, 415, 'Q');
		TFT_DrawChar(225, 415, '3');
		
		TFT_DrawChar(237, 415, '1');
		TFT_DrawChar(232, 415, 'Q');
		TFT_DrawChar(241, 415, '4');
		
		TFT_DrawChar(253, 415, '1');		
		TFT_DrawChar(248, 415, 'Q');
		TFT_DrawChar(257, 415, '5');

		TFT_DrawChar(5, 410, '0');
		
		TFT_DrawChar(1, 334, '2');
		TFT_DrawChar(7, 334, '5');
		
		TFT_DrawChar(1, 257, '5');
		TFT_DrawChar(7, 257, '0');
		
		TFT_DrawChar(1, 181, '7');
		TFT_DrawChar(7, 181, '5');
		
		TFT_DrawChar(0, 105, '1');
		TFT_DrawChar(4, 105, '0');
		TFT_DrawChar(9, 105, '0');
	} else if(direction != 0x00)
	{
		if(direction == 0x01){TFT_direction = 0x01;} 
		else {TFT_direction = 0x02;}

		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black);
		TFT_SetFont(&Font6EN_arch_big);
		
		TFT_DrawChar(87, 258, 'Q');
		TFT_DrawChar(93, 258, '1');

		TFT_DrawChar(109, 258, 'Q');
		TFT_DrawChar(115, 258, '2');

		TFT_DrawChar(131, 258, 'Q');
		TFT_DrawChar(137, 258, '3');

		TFT_DrawChar(153, 258, 'Q');
		TFT_DrawChar(159, 258, '4');
		
		TFT_DrawChar(175, 258, 'Q');
		TFT_DrawChar(181, 258, '5');


		TFT_DrawChar(197, 258, 'Q');
		TFT_DrawChar(203, 258, '6');
		
		TFT_DrawChar(219, 258, 'Q');
		TFT_DrawChar(225, 258, '7');
		
		TFT_DrawChar(241, 258, 'Q');
		TFT_DrawChar(247, 258, '8');
		
		TFT_DrawChar(263, 258, 'Q');
		TFT_DrawChar(269, 258, '9');
		
		TFT_DrawChar(290, 258, '1');
		TFT_DrawChar(285, 258, 'Q');
		TFT_DrawChar(294, 258, '0');


		TFT_DrawChar(312, 258, '1');
		TFT_DrawChar(307, 258, 'Q');
		TFT_DrawChar(317, 258, '1');
		
		TFT_DrawChar(334, 258, '1');
		TFT_DrawChar(329, 258, 'Q');
		TFT_DrawChar(338, 258, '2');
		
		TFT_DrawChar(356, 258, '1');
		TFT_DrawChar(351, 258, 'Q');
		TFT_DrawChar(360, 258, '3');
		
		TFT_DrawChar(378, 258, '1');
		TFT_DrawChar(373, 258, 'Q');
		TFT_DrawChar(382, 258, '4');
		
		TFT_DrawChar(400, 258, '1');		
		TFT_DrawChar(395, 258, 'Q');
		TFT_DrawChar(404, 258, '5');

		TFT_DrawChar(65, 250, '0');
		
		TFT_DrawChar(58, 202, '2');
		TFT_DrawChar(65, 202, '5');
		
		TFT_DrawChar(58, 149, '5');
		TFT_DrawChar(65, 149, '0');
		
		TFT_DrawChar(58, 96, '7');
		TFT_DrawChar(65, 96, '5');
			
		TFT_DrawChar(57, 43, '1');
		TFT_DrawChar(62, 43, '0');
		TFT_DrawChar(67, 43, '0');
		

		TFT_direction = 0x00;
	}
}

void CQS_chart(uint8_t direction, uint8_t *GraphData)
{
	char buffer[2] = {0};
	uint16_t X = 0;
	
	if(direction == 0x00){
		TFT_FillRectangle(24, 410-(float)GraphData[0]/100*305, 34, 410, CQS_COLOR_Q1);
		TFT_FillRectangle(40, 410-(float)GraphData[1]/100*305, 50, 410, CQS_COLOR_Q2);
		TFT_FillRectangle(56, 410-(float)GraphData[2]/100*305, 66, 410, CQS_COLOR_Q3);
		TFT_FillRectangle(72, 410-(float)GraphData[3]/100*305, 82, 410, CQS_COLOR_Q4);
		TFT_FillRectangle(88, 410-(float)GraphData[4]/100*305, 98, 410, CQS_COLOR_Q5);
		TFT_FillRectangle(104, 410-(float)GraphData[5]/100*305, 114, 410, CQS_COLOR_Q6);
		TFT_FillRectangle(120, 410-(float)GraphData[6]/100*305, 130, 410, CQS_COLOR_Q7);
		TFT_FillRectangle(136, 410-(float)GraphData[7]/100*305, 146, 410, CQS_COLOR_Q8);
		TFT_FillRectangle(152, 410-(float)GraphData[8]/100*305, 162, 410, CQS_COLOR_Q9);
		TFT_FillRectangle(168, 410-(float)GraphData[9]/100*305, 178, 410, CQS_COLOR_Q10);
		TFT_FillRectangle(184, 410-(float)GraphData[10]/100*305, 194, 410, CQS_COLOR_Q11);
		TFT_FillRectangle(200, 410-(float)GraphData[11]/100*305, 210, 410, CQS_COLOR_Q12);
		TFT_FillRectangle(216, 410-(float)GraphData[12]/100*305, 226, 410, CQS_COLOR_Q13);
		TFT_FillRectangle(232, 410-(float)GraphData[13]/100*305, 242, 410, CQS_COLOR_Q14);
		TFT_FillRectangle(248, 410-(float)GraphData[14]/100*305, 258, 410, CQS_COLOR_Q15);
		
		TFT_SetFont(&Font6EN_arch_big);
		TFT_SetTextColor(TFT_White);
		TFT_SetBackColor(TFT_Black);
		
		for(uint8_t i = 0; i<=14; i++)
		{
			sprintf (buffer, "%d", GraphData[i]);
			TFT_DisplayString(24+X, 400-(float)GraphData[i]/100*305, (uint8_t *)buffer, LEFT_MODE);
			X += 16;
		}
	} 
	else if(direction != 0x00)
	{
		if(direction == 0x01){TFT_direction = 0x01;} 
		else {TFT_direction = 0x02;}
		
		TFT_FillRectangle(87, 252-(float)GraphData[0]/100*210, 98, 	 252, CQS_COLOR_Q1);
		TFT_FillRectangle(109, 252-(float)GraphData[1]/100*210, 120, 252, CQS_COLOR_Q2);
		TFT_FillRectangle(131, 252-(float)GraphData[2]/100*210, 142, 252, CQS_COLOR_Q3);
		TFT_FillRectangle(153, 252-(float)GraphData[3]/100*210, 164, 252, CQS_COLOR_Q4);
		TFT_FillRectangle(175, 252-(float)GraphData[4]/100*210, 186, 252, CQS_COLOR_Q5);
		TFT_FillRectangle(197, 252-(float)GraphData[5]/100*210, 208, 252, CQS_COLOR_Q6);
		TFT_FillRectangle(219, 252-(float)GraphData[6]/100*210, 230, 252, CQS_COLOR_Q7);
		TFT_FillRectangle(241, 252-(float)GraphData[7]/100*210, 252, 252, CQS_COLOR_Q8);
		TFT_FillRectangle(263, 252-(float)GraphData[8]/100*210, 274, 252, CQS_COLOR_Q9);
		TFT_FillRectangle(285, 252-(float)GraphData[9]/100*210, 296, 252, CQS_COLOR_Q10);
		TFT_FillRectangle(307, 252-(float)GraphData[10]/100*210,318, 252, CQS_COLOR_Q11);
		TFT_FillRectangle(329, 252-(float)GraphData[11]/100*210,340, 252, CQS_COLOR_Q12);
		TFT_FillRectangle(351, 252-(float)GraphData[12]/100*210,362, 252, CQS_COLOR_Q13);
		TFT_FillRectangle(373, 252-(float)GraphData[13]/100*210,384, 252, CQS_COLOR_Q14);
		TFT_FillRectangle(395, 252-(float)GraphData[14]/100*210,406, 252, CQS_COLOR_Q15);
			
		for(uint8_t i = 0; i<=14; i++)
		{
			sprintf (buffer, "%d", GraphData[i]);
			TFT_DisplayString(87+X, (GraphData[i]< 10) ? 243-(float)GraphData[i]/100*215 : 250-(float)GraphData[i]/100*215, (uint8_t *)buffer, LEFT_MODE);
			X += 22;
		}
		
		TFT_direction = 0x00;
	}
}

void CQS_Draw(uint8_t direction, uint8_t *GraphData, uint8_t Qa, uint8_t Qp, uint8_t Qf){
	TFT_FillRectangle(5, 58, 270, 410, TFT_Black);
	CQS_Axes(direction);
	CQS_Axes_Text(direction);
	CQS_chart(direction, GraphData);
	CQS_Axes_Measure(direction, Qa, Qp, Qf);
}
