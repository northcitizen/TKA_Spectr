/**
  ******************************************************************************
  * @file    font16.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file provides text font16 for STM32xx-EVAL's LCD driver. 
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


const uint8_t Font16RU_arch_small_Table[] = 
{

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

/* @544 'р' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x3F, 0xE0, //   #########   
	0x3F, 0xF0, //   ##########  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x3F, 0xF0, //   ##########  
	0x3F, 0xC0, //   ########    
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          

	/* @578 'с' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x1F, 0xE0, //    ########   
	0x3F, 0xE0, //   #########   
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x3F, 0xE0, //   #########   
	0x1F, 0xE0, //    ########   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @612 'т' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x1F, 0xE0, //    ########   
	0x1F, 0xE0, //    ########   
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @646 'у' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x38, 0x1C, //   ###      ###
	0x18, 0x38, //    ##     ### 
	0x1C, 0x30, //    ###    ##  
	0x0C, 0x70, //     ##   ###  
	0x0E, 0x60, //     ###  ##   
	0x06, 0xE0, //      ## ###   
	0x07, 0xC0, //      #####    
	0x03, 0xC0, //       ####    
	0x03, 0x80, //       ###     
	0x03, 0x00, //       ##      
	0x07, 0x00, //      ###      
	0x1E, 0x00, //    ####       
	0x1C, 0x00, //    ###        
	0x00, 0x00, //               

	/* @680 'ф' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x7F, 0xF8, //  ############ 
	0xFF, 0xFC, // ##############
	0xC3, 0x0C, // ##    ##    ##
	0xC3, 0x0C, // ##    ##    ##
	0xC3, 0x0C, // ##    ##    ##
	0xC3, 0x0C, // ##    ##    ##
	0xC3, 0x0C, // ##    ##    ##
	0xFF, 0xFC, // ##############
	0x7F, 0xF8, //  ############ 
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      

	/* @714 'х' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x38, 0xE0, //   ###   ###   
	0x1D, 0xC0, //    ### ###    
	0x0F, 0x80, //     #####     
	0x07, 0x80, //      ####     
	0x07, 0x00, //      ###      
	0x07, 0x80, //      ####     
	0x0F, 0x80, //     #####     
	0x1D, 0xC0, //    ### ###    
	0x38, 0xE0, //   ###   ###   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @748 'ц' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x30, 0x60, //   ##     ##   
	0x30, 0x60, //   ##     ##   
	0x30, 0x60, //   ##     ##   
	0x30, 0x60, //   ##     ##   
	0x30, 0x60, //   ##     ##   
	0x30, 0x60, //   ##     ##   
	0x30, 0x60, //   ##     ##   
	0x3F, 0xF0, //   ##########  
	0x1F, 0xF0, //    #########  
	0x00, 0x30, //           ##  
	0x00, 0x30, //           ##  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @782 'ч' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x3F, 0xF0, //   ##########  
	0x1F, 0xF0, //    #########  
	0x00, 0x30, //           ##  
	0x00, 0x30, //           ##  
	0x00, 0x30, //           ##  
	0x00, 0x30, //           ##  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @816 'ш' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x63, 0x18, //  ##   ##   ## 
	0x63, 0x18, //  ##   ##   ## 
	0x63, 0x18, //  ##   ##   ## 
	0x63, 0x18, //  ##   ##   ## 
	0x63, 0x18, //  ##   ##   ## 
	0x63, 0x18, //  ##   ##   ## 
	0x63, 0x18, //  ##   ##   ## 
	0x7F, 0xF8, //  ############ 
	0x3F, 0xF8, //   ########### 
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @850 'щ' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x63, 0x30, //  ##   ##  ##  
	0x63, 0x30, //  ##   ##  ##  
	0x63, 0x30, //  ##   ##  ##  
	0x63, 0x30, //  ##   ##  ##  
	0x63, 0x30, //  ##   ##  ##  
	0x63, 0x30, //  ##   ##  ##  
	0x63, 0x30, //  ##   ##  ##  
	0x7F, 0xF8, //  ############ 
	0x3D, 0xF8, //   #### ###### 
	0x00, 0x18, //            ## 
	0x00, 0x18, //            ## 
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @884 'ъ' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x78, 0x00, //  ####         
	0x78, 0x00, //  ####         
	0x1F, 0xE0, //    ########   
	0x1F, 0xF8, //    ########## 
	0x18, 0x18, //    ##      ## 
	0x18, 0x18, //    ##      ## 
	0x18, 0x18, //    ##      ## 
	0x1F, 0xF8, //    ########## 
	0x1F, 0xF0, //    #########  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @918 'ы' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0xC0, 0x18, // ##         ## 
	0xC0, 0x18, // ##         ## 
	0xFE, 0x18, // #######    ## 
	0xFF, 0x18, // ########   ## 
	0xFF, 0x98, // #########  ## 
	0xC1, 0x98, // ##     ##  ## 
	0xC1, 0x98, // ##     ##  ## 
	0xFF, 0x98, // #########  ## 
	0xFF, 0x18, // ########   ## 
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @952 'ь' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x3F, 0xC0, //   ########    
	0x3F, 0xF0, //   ##########  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x3F, 0xF0, //   ##########  
	0x3F, 0xE0, //   #########   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @986 'э' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x1F, 0xE0, //    ########   
	0x1F, 0xF0, //    #########  
	0x00, 0x30, //           ##  
	0x07, 0xF0, //      #######  
	0x07, 0xF0, //      #######  
	0x00, 0x30, //           ##  
	0x00, 0x30, //           ##  
	0x1F, 0xF0, //    #########  
	0x1F, 0xE0, //    ########   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @1020 'ю' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0xC3, 0xF8, // ##    ####### 
	0xC7, 0xFC, // ##   #########
	0xC6, 0x0C, // ##   ##     ##
	0xFE, 0x0C, // #######     ##
	0xFE, 0x0C, // #######     ##
	0xC6, 0x0C, // ##   ##     ##
	0xC6, 0x0C, // ##   ##     ##
	0xC7, 0xFC, // ##   #########
	0x03, 0xF8, //       ####### 
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @1054 'я' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x0F, 0xF0, //     ########  
	0x1F, 0xF0, //    #########  
	0x18, 0x30, //    ##     ##  
	0x1F, 0xF0, //    #########  
	0x0F, 0xF0, //     ########  
	0x03, 0xB0, //       ### ##  
	0x07, 0x30, //      ###  ##  
	0x0E, 0x30, //     ###   ##  
	0x1C, 0x30, //    ###    ##  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //   
	
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //

		0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //

		0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //

		0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //

		0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //  

	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //    
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //    

	/* @0 'а' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x1F, 0xE0, //    ########   
	0x1F, 0xF0, //    #########  
	0x00, 0x30, //           ##  
	0x0F, 0xF0, //     ########  
	0x1F, 0xF0, //    #########  
	0x18, 0x30, //    ##     ##  
	0x18, 0x30, //    ##     ##  
	0x1F, 0xF0, //    #########  
	0x0F, 0xF0, //     ########  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @34 'б' (14 pixels wide) */
	0x1F, 0xC0, //    #######    
	0x3F, 0xC0, //   ########    
	0x30, 0x00, //   ##          
	0x3F, 0xC0, //   ########    
	0x3F, 0xF0, //   ##########  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x3F, 0xF0, //   ##########  
	0x1F, 0xE0, //    ########   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @68 'в' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x3F, 0xE0, //   #########   
	0x3F, 0xF0, //   ##########  
	0x30, 0x30, //   ##      ##  
	0x3F, 0xF0, //   ##########  
	0x3F, 0xE0, //   #########   
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x3F, 0xF0, //   ##########  
	0x3F, 0xE0, //   #########   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @102 'г' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x1F, 0xC0, //    #######    
	0x1F, 0xE0, //    ########   
	0x00, 0x60, //          ##   
	0x1F, 0xE0, //    ########   
	0x3F, 0xC0, //   ########    
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x3F, 0xE0, //   #########   
	0x1F, 0xE0, //    ########   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @136 'д' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x1F, 0xF0, //    #########  
	0x3F, 0xF0, //   ##########  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x3F, 0xF0, //   ##########  
	0x0F, 0xF0, //     ########  
	0x00, 0x30, //           ##  
	0x00, 0x30, //           ##  
	0x0F, 0xF0, //     ########  
	0x0F, 0xE0, //     #######   
	0x00, 0x00, //               

	/* @170 'е' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x1F, 0xC0, //    #######    
	0x3F, 0xE0, //   #########   
	0x30, 0x60, //   ##     ##   
	0x3F, 0xE0, //   #########   
	0x3F, 0xE0, //   #########   
	0x30, 0x00, //   ##          
	0x30, 0x00, //   ##          
	0x3F, 0xE0, //   #########   
	0x1F, 0xE0, //    ########   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @204 'ж' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0xE3, 0x1C, // ###   ##   ###
	0x73, 0x38, //  ###  ##  ### 
	0x3B, 0x70, //   ### ## ###  
	0x1F, 0xE0, //    ########   
	0x1F, 0xE0, //    ########   
	0x1F, 0xE0, //    ########   
	0x3B, 0x70, //   ### ## ###  
	0x73, 0x38, //  ###  ##  ### 
	0xE3, 0x1C, // ###   ##   ###
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @238 'з' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x1F, 0xE0, //    ########   
	0x1F, 0xF0, //    #########  
	0x00, 0x30, //           ##  
	0x03, 0xF0, //       ######  
	0x03, 0xE0, //       #####   
	0x00, 0x30, //           ##  
	0x00, 0x30, //           ##  
	0x1F, 0xF0, //    #########  
	0x1F, 0xE0, //    ########   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @272 'и' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x70, //   ##     ###  
	0x30, 0xF0, //   ##    ####  
	0x3F, 0xF0, //   ##########  
	0x1F, 0xB0, //    ###### ##  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @306 'й' (14 pixels wide) */
	0x03, 0x00, //       ##      
	0x03, 0x00, //       ##      
	0x00, 0x00, //               
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x70, //   ##     ###  
	0x39, 0xF0, //   ###  #####  
	0x3F, 0xF0, //   ##########  
	0x0F, 0xB0, //     ##### ##  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @340 'к' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x30, 0xF0, //   ##    ####  
	0x31, 0xE0, //   ##   ####   
	0x33, 0x80, //   ##  ###     
	0x3F, 0x00, //   ######      
	0x3E, 0x00, //   #####       
	0x3F, 0x00, //   ######      
	0x33, 0x80, //   ##  ###     
	0x31, 0xE0, //   ##   ####   
	0x30, 0xF0, //   ##    ####  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @374 'л' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x03, 0xF0, //       ######  
	0x07, 0xF0, //      #######  
	0x0E, 0x30, //     ###   ##  
	0x0C, 0x30, //     ##    ##  
	0x0C, 0x30, //     ##    ##  
	0x0C, 0x30, //     ##    ##  
	0x0C, 0x30, //     ##    ##  
	0x1C, 0x30, //    ###    ##  
	0x18, 0x30, //    ##     ##  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @408 'м' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x60, 0x18, //  ##        ## 
	0x70, 0x38, //  ###      ### 
	0x78, 0x78, //  ####    #### 
	0x7C, 0xF8, //  #####  ##### 
	0x7F, 0xF8, //  ############ 
	0x6F, 0xD8, //  ## ###### ## 
	0x67, 0x98, //  ##  ####  ## 
	0x63, 0x18, //  ##   ##   ## 
	0x62, 0x18, //  ##   #    ## 
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @442 'н' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x3F, 0xF0, //   ##########  
	0x3F, 0xF0, //   ##########  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @476 'о' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x1F, 0xE0, //    ########   
	0x3F, 0xF0, //   ##########  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x3F, 0xF0, //   ##########  
	0x1F, 0xE0, //    ########   
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	/* @510 'п' (14 pixels wide) */
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x3F, 0xE0, //   #########   
	0x3F, 0xF0, //   ##########  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x30, 0x30, //   ##      ##  
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               
	0x00, 0x00, //               

	            
                                
};

sFONT Font16RU_arch_small = {
  Font16RU_arch_small_Table,
  14, /* Width */
  17, /* Height */
};
