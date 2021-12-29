/**
  ******************************************************************************
  * @file    Font12.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file provides text Font12 for STM32xx-EVAL's LCD driver. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fonts.h"


const uint8_t Font12RU_arch_small_Table[] = 
{

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

/* @170 'р' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x7C, //  #####  
	0x40, //  #      
	0x40, //  #      
	0x40, //  #      

	/* @180 'с' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x40, //  #      
	0x40, //  #      
	0x40, //  #      
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @190 'т' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x10, //    #    
	0x10, //    #    
	0x10, //    #    
	0x10, //    #    
	0x00, //         
	0x00, //         
	0x00, //         

	/* @200 'у' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0xC6, // ##   ## 
	0x4C, //  #  ##  
	0x68, //  ## #   
	0x38, //   ###   
	0x30, //   ##    
	0x20, //   #     
	0x60, //  ##     
	0x00, //         

	/* @210 'ф' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0xFE, // ####### 
	0x92, // #  #  # 
	0x92, // #  #  # 
	0x92, // #  #  # 
	0xFE, // ####### 
	0x10, //    #    
	0x10, //    #    
	0x10, //    #    

	/* @220 'х' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x6C, //  ## ##  
	0x38, //   ###   
	0x10, //    #    
	0x38, //   ###   
	0x6C, //  ## ##  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @230 'ц' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x3E, //   ##### 
	0x02, //       # 
	0x00, //         
	0x00, //         

	/* @240 'ч' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x44, //  #   #  
	0x44, //  #   #  
	0x7C, //  #####  
	0x04, //      #  
	0x04, //      #  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @250 'ш' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x92, // #  #  # 
	0x92, // #  #  # 
	0x92, // #  #  # 
	0x92, // #  #  # 
	0xFE, // ####### 
	0x00, //         
	0x00, //         
	0x00, //         

	/* @260 'щ' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x94, // #  # #  
	0x94, // #  # #  
	0x94, // #  # #  
	0x94, // #  # #  
	0xFE, // ####### 
	0x02, //       # 
	0x00, //         
	0x00, //         

	/* @270 'ъ' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x60, //  ##     
	0x3C, //   ####  
	0x22, //   #   # 
	0x22, //   #   # 
	0x3E, //   ##### 
	0x00, //         
	0x00, //         
	0x00, //         

	/* @280 'ы' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x82, // #     # 
	0xF2, // ####  # 
	0xFA, // ##### # 
	0x8A, // #   # # 
	0xFA, // ##### # 
	0x00, //         
	0x00, //         
	0x00, //         

	/* @290 'ь' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x40, //  #      
	0x78, //  ####   
	0x44, //  #   #  
	0x44, //  #   #  
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @300 'э' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x04, //      #  
	0x3C, //   ####  
	0x04, //      #  
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @310 'ю' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x9F, // #  #####
	0x91, // #  #   #
	0xF1, // ####   #
	0x91, // #  #   #
	0x9F, // #  #####
	0x00, //         
	0x00, //         
	0x00, //         

	/* @320 'я' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x44, //  #   #  
	0x7C, //  #####  
	0x34, //   ## #  
	0x64, //  ##  #  
	0x00, //         
	0x00, //         
	0x00, //         

	
	/* @0 'μ' (8 pixels wide) */
	0x00, //         
	0x22, //   #   # 
	0x22, //   #   # 
	0x22, //   #   # 
	0x22, //   #   # 
	0x22, //   #   # 
	0x3D, //   #### #
	0x20, //   #     
	0x20, //   #     
	0x00, //    

	/* @0 '2' (5 pixels wide) */
	0xF0, // #### 
	0x08, //     #
	0x78, //  ####
	0x80, // #    
	0xF8, // #####
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

	
		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

			0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //  

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

			0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //  

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

			0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //  

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

			0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //

		0x00, //         
	0x00, //         
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //
	0x00, //         
	0x00, //         
	0x00, //  

	/* @10 'а' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x04, //      #  
	0x7C, //  #####  
	0x44, //  #   #  
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @20 'б' (8 pixels wide) */
	0x7C, //  #####  
	0x40, //  #      
	0x7C, //  #####  
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @30 'в' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x44, //  #   #  
	0x7C, //  #####  
	0x44, //  #   #  
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @40 'г' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x04, //      #  
	0x7C, //  #####  
	0x40, //  #      
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @50 'д' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x7C, //  #####  
	0x04, //      #  
	0x3C, //   ####  
	0x00, //         

	/* @60 'е' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x44, //  #   #  
	0x7C, //  #####  
	0x40, //  #      
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @70 'ж' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0xD6, // ## # ## 
	0x54, //  # # #  
	0x38, //   ###   
	0x54, //  # # #  
	0xD6, // ## # ## 
	0x00, //         
	0x00, //         
	0x00, //         

	/* @80 'з' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x04, //      #  
	0x1C, //    ###  
	0x04, //      #  
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @90 'и' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x4C, //  #  ##  
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @100 'й' (8 pixels wide) */
	0x10, //    #    
	0x00, //         
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x4C, //  #  ##  
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @110 'к' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x4E, //  #  ### 
	0x58, //  # ##   
	0x70, //  ###    
	0x58, //  # ##   
	0x4E, //  #  ### 
	0x00, //         
	0x00, //         
	0x00, //         

	/* @120 'л' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x3C, //   ####  
	0x24, //   #  #  
	0x24, //   #  #  
	0x64, //  ##  #  
	0x44, //  #   #  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @130 'м' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x42, //  #    # 
	0x66, //  ##  ## 
	0x7E, //  ###### 
	0x5A, //  # ## # 
	0x52, //  # #  # 
	0x00, //         
	0x00, //         
	0x00, //         

	/* @140 'н' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x44, //  #   #  
	0x44, //  #   #  
	0x7C, //  #####  
	0x44, //  #   #  
	0x44, //  #   #  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @150 'о' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x7C, //  #####  
	0x00, //         
	0x00, //         
	0x00, //         

	/* @160 'п' (8 pixels wide) */
	0x00, //         
	0x00, //         
	0x7C, //  #####  
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x44, //  #   #  
	0x00, //         
	0x00, //         
	0x00, //   
                                
};

sFONT Font12RU_arch_small = {
  Font12RU_arch_small_Table,
  8, /* Width */
  10, /* Height */
};

