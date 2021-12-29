/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter (ST) for emWin V5.32.                      *
*        Compiled Oct  8 2015, 11:58:22                              *
*                                                                    *
*        (c) 1998 - 2015 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: Buttons                                               *
* Dimensions:  50 * 50                                               *
* NumColors:   16bpp: 65536                                          *
*                                                                    *
**********************************************************************
*/


#include <stdint.h>
#include "Buttons.h"



static const uint16_t image_data_Buttons[] = {
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xF79E, 0xEF9D, 0xEF9D, 0xF79E, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 
        0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xE75C, 0xD6BA, 0xCE59, 0xC618, 0xC618, 0xC638, 0xC638, 0xC618, 0xC618, 0xBDF7, 0xBDF7, 0xC638, 0xD69A, 
        0xE73C, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xEF7D, 0xCE99, 0xC638, 0xCE79, 0xD6BA, 0xD6BA, 0xD6BA, 0xD6BA, 0xD69A, 0xD69A, 0xCE99, 0xCE79, 0xCE79, 0xCE79, 0xCE59, 0xCE59, 
        0xC618, 0xBDD7, 0xCE59, 0xE73C, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE75C, 0xCE59, 0xCE79, 0xDEDB, 0xDEDB, 0xDEDB, 0xDEDB, 0xDEDB, 0xDEFB, 0xDF1B, 0xDF1B, 0xE71C, 0xDF1B, 0xDEFB, 0xDEFB, 0xD6DA, 0xD69A, 0xCE59, 
        0xC638, 0xC638, 0xC638, 0xBDD7, 0xBDF7, 0xE71C, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xCE79, 0xCE79, 0xDEFB, 0xDEDB, 0xDEDB, 0xDEFB, 0xE71C, 0xE71C, 0xD6BA, 0xC638, 0xBDD7, 0xB5B6, 0xAD75, 0xAD75, 0xB596, 0xBDD7, 0xC638, 0xD69A, 0xDEFB, 
        0xDEFB, 0xD69A, 0xC638, 0xC618, 0xBE17, 0xB5D6, 0xC618, 0xEF9D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE71C, 0xC638, 0xDEFB, 0xDEFB, 0xDEFB, 0xE71C, 0xE71C, 0xCE79, 0xB596, 0x8C72, 0x5B2E, 0x3A4B, 0x29A9, 0x1948, 0x1128, 0x1128, 0x1949, 0x21CA, 0x3A4C, 0x5B2E, 0x8452, 
        0xAD75, 0xCE59, 0xDEFB, 0xD6BA, 0xC618, 0xBDF7, 0xBDD7, 0xB596, 0xDEDB, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xD6BA, 0xCE99, 0xDEFB, 0xDEFB, 0xE71C, 0xE71C, 0xC658, 0x9CF3, 0x5AED, 0x2168, 0x00A6, 0x08E7, 0x1949, 0x21AA, 0x29CA, 0x29EB, 0x29EB, 0x21CB, 0x19AB, 0x116A, 0x0929, 0x0109, 
        0x198B, 0x4AEE, 0x94B3, 0xC618, 0xDEFB, 0xCE79, 0xBDD7, 0xB5D6, 0xB596, 0xC658, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE79, 0xD6BA, 0xDEFB, 0xDEFB, 0xE73C, 0xD6BA, 0xA514, 0x4AAC, 0x08E6, 0x08E7, 0x2189, 0x322B, 0x3A6C, 0x3A6C, 0x3A6D, 0x3A6D, 0x3A4D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x2A0D, 
        0x19AC, 0x092A, 0x094B, 0x42AE, 0x9CF3, 0xCE79, 0xD6DA, 0xBDF7, 0xB5B6, 0xB596, 0xBDF7, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE79, 0xD6DA, 0xDEFB, 0xDEFB, 0xE73C, 0xBDF7, 0x73AF, 0x1127, 0x08C6, 0x29CA, 0x426C, 0x426C, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x2A2D, 0x2A2D, 
        0x2A2D, 0x2A0D, 0x19CD, 0x014B, 0x118C, 0x6390, 0xB5D6, 0xDEDB, 0xBE17, 0xB596, 0xB596, 0xBDF7, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xD6BA, 0xD6BA, 0xDEFB, 0xDF1B, 0xE71C, 0xB596, 0x4AAC, 0x00A6, 0x2169, 0x426C, 0x426C, 0x426D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x2A2D, 0x2A2D, 0x2A2D, 
        0x2A2D, 0x220E, 0x220E, 0x220E, 0x118D, 0x014C, 0x3AAF, 0xA555, 0xDEDB, 0xBE17, 0xAD75, 0xAD75, 0xC638, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE71C, 0xD69A, 0xDEFB, 0xDEFB, 0xE71C, 0xAD55, 0x3A2A, 0x08A6, 0x31EA, 0x428C, 0x426C, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x2A2D, 0x2A2D, 0x2A2D, 0x2A2E, 
        0x222E, 0x220E, 0x220E, 0x220E, 0x220E, 0x11CE, 0x014D, 0x2A4E, 0x9D14, 0xD6DA, 0xBDD7, 0xAD75, 0xAD55, 0xD6BA, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF79E, 0xC658, 0xDEFB, 0xDEFB, 0xE73C, 0xAD75, 0x3A2A, 0x08C6, 0x322B, 0x428C, 0x428D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x2A2D, 0x2A2D, 0x2A2E, 0x2A2E, 0x222E, 
        0x220E, 0x220E, 0x220E, 0x220E, 0x1A0E, 0x1A0E, 0x11CE, 0x016D, 0x2A4F, 0xA535, 0xDEDB, 0xB596, 0xAD55, 0xA554, 0xEF5D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE59, 0xDEFB, 0xDEFB, 0xE73C, 0xBDF7, 0x4AAC, 0x00A6, 0x322B, 0x428D, 0x428D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A4D, 0x324D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x2A2D, 0x2A2D, 0x2A2E, 0x2A2E, 0x220E, 0x220E, 
        0x220E, 0x220E, 0x220E, 0x1A0E, 0x1A0F, 0x19EF, 0x19EF, 0x11CF, 0x016E, 0x3AB0, 0xB596, 0xD69A, 0xAD55, 0xA554, 0xB596, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xE73C, 0xCE99, 0xDEDB, 0xDF1B, 0xD69A, 0x6B8F, 0x00A6, 0x29EA, 0x428D, 0x428D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A4D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A4D, 0x2A2D, 0x2A2D, 0x2A2E, 0x2A2E, 0x220D, 0x21ED, 0x19ED, 0x19EE, 
        0x19EE, 0x19EE, 0x1A0E, 0x1A0F, 0x19EF, 0x19EF, 0x11EF, 0x11EF, 0x09CF, 0x018F, 0x5B71, 0xC638, 0xC618, 0xA534, 0xA514, 0xD6DA, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xCE59, 0xDEDB, 0xDEFB, 0xE71C, 0x9CF3, 0x1107, 0x1969, 0x428D, 0x428D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A4D, 0x2A2D, 0x220D, 0x19AC, 0x096C, 0x014B, 0x012B, 0x012C, 0x014C, 0x014C, 
        0x014C, 0x014D, 0x016D, 0x098E, 0x09AE, 0x11CF, 0x11EF, 0x11EF, 0x11F0, 0x09AF, 0x09CF, 0x8C93, 0xD6BA, 0xAD75, 0xA514, 0xAD55, 0xFFDF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xE75C, 0xCE79, 0xDEDB, 0xE71C, 0xC638, 0x4A8C, 0x08C7, 0x3A6C, 0x428D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x21CC, 0x094B, 0x012B, 0x012B, 0x012B, 0x012B, 0x012C, 0x014C, 0x014C, 0x014D, 
        0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x016E, 0x018F, 0x09CF, 0x09F0, 0x09D0, 0x01B0, 0x32B1, 0xBDD7, 0xC638, 0xA514, 0x9D13, 0xDEDB, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xCE79, 0xDEDB, 0xDEDB, 0xE71C, 0x94B3, 0x08E7, 0x21AA, 0x428D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x324D, 0x21ED, 0x094B, 0x010A, 0x012B, 0x012B, 0x012B, 0x012B, 0x012C, 0x014C, 0x014C, 0x014D, 0x014D, 
        0x016D, 0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01AF, 0x01D0, 0x01D0, 0x01D0, 0x8453, 0xD6BA, 0xA534, 0x9CF3, 0xB596, 0xFFFF, 0xFFFF,
  0xFFFF, 0xF7DE, 0xC638, 0xD6DA, 0xDEFB, 0xCE59, 0x4AAD, 0x08C7, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x118C, 0x010A, 0x010A, 0x012B, 0x012B, 0x012B, 0x012C, 0x014C, 0x014C, 0x014C, 0x014D, 0x016D, 0x016D, 
        0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B0, 0x01D1, 0x3AD2, 0xBDF7, 0xBDD7, 0x9CF3, 0x9CF3, 0xEF9D, 0xFFFF,
  0xFFFF, 0xDF1B, 0xCE99, 0xD6BA, 0xE73C, 0xAD55, 0x1949, 0x198A, 0x3A6D, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x094B, 0x010A, 0x010B, 0x012B, 0x012B, 0x012B, 0x012C, 0x014C, 0x014C, 0x014D, 0x014D, 0x016D, 0x016D, 0x016E, 
        0x016E, 0x018E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x09F2, 0x9D14, 0xCE79, 0x9CF3, 0x9CD3, 0xD69A, 0xFFFF,
  0xFFFF, 0xCE79, 0xD6BA, 0xD6DA, 0xDEFB, 0x7C11, 0x00C7, 0x2A0C, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x094B, 0x010A, 0x012B, 0x012B, 0x012B, 0x012C, 0x012C, 0x014C, 0x014C, 0x014D, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 
        0x018E, 0x018F, 0x018F, 0x018F, 0x01AF, 0x01B0, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x01D2, 0x01D2, 0x6BD3, 0xD69A, 0xA514, 0x9CD3, 0xB5D6, 0xFFFF,
  0xFFFF, 0xC638, 0xD6BA, 0xDEDB, 0xCE99, 0x52ED, 0x00E8, 0x3A6D, 0x3A6D, 0x3A6D, 0x324D, 0x324D, 0x324D, 0x324D, 0x2A2D, 0x094B, 0x010A, 0x012B, 0x012B, 0x012B, 0x012C, 0x014C, 0x014C, 0x014D, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x016E, 0x018E, 
        0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B0, 0x01D1, 0x01D1, 0x01D1, 0x01D2, 0x01D2, 0x01F2, 0x3B12, 0xC638, 0xAD75, 0x9CD3, 0xA514, 0xFFFF,
  0xFFFF, 0xC618, 0xD69A, 0xDEFB, 0xBE17, 0x320B, 0x1149, 0x3A6D, 0x326D, 0x324D, 0x324D, 0x324D, 0x324E, 0x2A2E, 0x096B, 0x010B, 0x012B, 0x012B, 0x012B, 0x012C, 0x014C, 0x014C, 0x014D, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 
        0x018F, 0x01AF, 0x01B0, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x01D1, 0x01D2, 0x01F2, 0x01F2, 0x01F2, 0x1A73, 0xB5B6, 0xBDD7, 0x9CD3, 0x9CD3, 0xF79E,
  0xF79E, 0xC618, 0xD69A, 0xDF1B, 0xB5B6, 0x198A, 0x198A, 0x326D, 0x326D, 0x324D, 0x324E, 0x324E, 0x2A4E, 0x19AC, 0x012B, 0x012B, 0x012B, 0x012C, 0x014C, 0x014C, 0x014C, 0x014D, 0x016D, 0x016D, 0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 
        0x01B0, 0x01B0, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x01D2, 0x01D2, 0x01F2, 0x01F2, 0x01F3, 0x01F3, 0x0A33, 0xA555, 0xC638, 0x9CD3, 0x9CD3, 0xE75C,
  0xEF7D, 0xC638, 0xD69A, 0xE71C, 0xAD55, 0x0929, 0x19AB, 0x326D, 0x324E, 0x324E, 0x324E, 0x2A4E, 0x220D, 0x012B, 0x012B, 0x012B, 0x012C, 0x014C, 0x014C, 0x014D, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 
        0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x01D1, 0x01D2, 0x01F2, 0x01F2, 0x01F2, 0x01F3, 0x0213, 0x0213, 0x0214, 0x94D4, 0xCE59, 0x9CD3, 0x9CD3, 0xDEFB,
  0xE73C, 0xC638, 0xCE99, 0xE71C, 0xA534, 0x0909, 0x19AC, 0x324E, 0x324E, 0x324E, 0x2A4E, 0x2A4E, 0x096C, 0x012B, 0x012B, 0x012C, 0x014C, 0x014C, 0x014D, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01AF, 0x01B0, 0x01B0, 
        0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x01F2, 0x09F2, 0x0A12, 0x0A13, 0x0A33, 0x0A33, 0x0A33, 0x0A34, 0x0234, 0x0234, 0x8CB4, 0xCE79, 0x9CD3, 0x9CD3, 0xDEFB,
  0xE73C, 0xC638, 0xCE79, 0xE71C, 0xA514, 0x090A, 0x19AC, 0x324E, 0x2A4E, 0x2A4E, 0x2A4E, 0x21ED, 0x012B, 0x012C, 0x014C, 0x014C, 0x014C, 0x014D, 0x016D, 0x016D, 0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B0, 
        0x01D1, 0x01F1, 0x09F2, 0x0A12, 0x0A12, 0x0A33, 0x0A33, 0x1253, 0x1254, 0x1254, 0x0A54, 0x0A54, 0x0A55, 0x0A35, 0x8CB4, 0xCE79, 0x9CD3, 0x9CD3, 0xDEFB,
  0xEF7D, 0xC618, 0xCE79, 0xDF1B, 0xA555, 0x092A, 0x19AC, 0x2A4E, 0x2A4E, 0x2A4E, 0x2A2E, 0x098C, 0x012C, 0x014C, 0x014C, 0x014D, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x018E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01D1, 0x01D1, 
        0x09F2, 0x0A12, 0x0A32, 0x1233, 0x1253, 0x1253, 0x1274, 0x1274, 0x1274, 0x1274, 0x1295, 0x1275, 0x1275, 0x0A75, 0x94D4, 0xCE59, 0x9CD3, 0x9CD3, 0xDEDB,
  0xEF9D, 0xBDF7, 0xCE59, 0xDEFB, 0xB596, 0x118B, 0x118C, 0x2A4E, 0x2A4E, 0x2A2E, 0x220E, 0x014C, 0x014C, 0x014C, 0x014D, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01AF, 0x01B0, 0x01B0, 0x01B0, 0x01D1, 0x09F1, 0x0A12, 
        0x1232, 0x1233, 0x1253, 0x1273, 0x1A74, 0x1A94, 0x1A94, 0x1A95, 0x1AB5, 0x1AB5, 0x1AB5, 0x1AB6, 0x12B6, 0x1275, 0x9D35, 0xC638, 0x9CD3, 0x9CD3, 0xE73C,
  0xF7DE, 0xBDD7, 0xCE59, 0xDEDB, 0xBDD7, 0x2A0D, 0x094B, 0x2A4E, 0x2A2E, 0x2A2E, 0x19CD, 0x014C, 0x014C, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01D1, 0x01D1, 0x09F2, 0x0A12, 0x1232, 
        0x1253, 0x1A73, 0x1A94, 0x1A94, 0x1AB4, 0x22B5, 0x22B5, 0x22D5, 0x22D5, 0x22D6, 0x22D6, 0x1AD6, 0x1AD6, 0x1AD6, 0xB596, 0xBDF7, 0x9CD3, 0x9CD3, 0xEF9D,
  0xFFFF, 0xBDF7, 0xC638, 0xD69A, 0xCE59, 0x42CE, 0x012B, 0x222E, 0x2A2F, 0x222F, 0x098D, 0x014D, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01AF, 0x01B0, 0x01B0, 0x01B0, 0x01D1, 0x09F1, 0x0A12, 0x1232, 0x1253, 0x1A73, 
        0x1A73, 0x1A94, 0x22B4, 0x22B5, 0x22D5, 0x22D5, 0x2AF6, 0x2AF6, 0x2AF6, 0x22F6, 0x22F6, 0x22F7, 0x22F7, 0x3B35, 0xBDF7, 0xAD75, 0x9CD3, 0x9CF3, 0xFFDF,
  0xFFFF, 0xC658, 0xC638, 0xCE59, 0xDEDB, 0x6BD1, 0x012C, 0x19EE, 0x222F, 0x222F, 0x016D, 0x014D, 0x016D, 0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B0, 0x01D1, 0x09F1, 0x0A12, 0x1232, 0x1253, 0x1A73, 0x1A94, 
        0x22B4, 0x22B5, 0x22D5, 0x2AF5, 0x2AF6, 0x2B16, 0x2B16, 0x2B16, 0x2B17, 0x2B17, 0x2B17, 0x2B17, 0x2317, 0x5BD4, 0xCE59, 0xA514, 0x9CD3, 0xAD75, 0xFFFF,
  0xFFFF, 0xD6DA, 0xC618, 0xC638, 0xDEFB, 0x9D14, 0x096C, 0x098D, 0x222F, 0x1A0F, 0x016D, 0x016D, 0x016E, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B0, 0x01D1, 0x01F1, 0x0A12, 0x1232, 0x1253, 0x1A73, 0x1A94, 0x22B4, 
        0x22D5, 0x2AF5, 0x2AF5, 0x2B16, 0x3336, 0x3336, 0x3357, 0x3357, 0x3357, 0x3357, 0x2B57, 0x2B38, 0x2317, 0x8CB4, 0xCE79, 0x9CD3, 0x9CD3, 0xC658, 0xFFFF,
  0xFFFF, 0xEF9D, 0xB5D6, 0xC618, 0xD6BA, 0xBE17, 0x3A8F, 0x014D, 0x1A0F, 0x11EF, 0x016D, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01AF, 0x01B0, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x0A12, 0x1232, 0x1253, 0x1A73, 0x1A94, 0x22B4, 0x22D5, 
        0x2AF5, 0x2B16, 0x3336, 0x3336, 0x3357, 0x3B77, 0x3B77, 0x3B77, 0x3B78, 0x3378, 0x3378, 0x3378, 0x3B56, 0xB5B6, 0xBDD7, 0x9CD3, 0x9CD3, 0xE73C, 0xFFFF,
  0xFFFF, 0xFFFF, 0xBDF7, 0xBE17, 0xC638, 0xDEDB, 0x7C32, 0x016D, 0x09AE, 0x11CF, 0x016E, 0x016E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x09F2, 0x0A32, 0x1253, 0x1A73, 0x1A94, 0x22B4, 0x2AD5, 0x2AF5, 
        0x3316, 0x3336, 0x3357, 0x3B77, 0x3B77, 0x3B97, 0x3B98, 0x3B98, 0x3B98, 0x3B98, 0x3B98, 0x3378, 0x6C15, 0xCE79, 0xA514, 0x9CD3, 0xA534, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xDEDB, 0xBDD7, 0xBDF7, 0xD6DA, 0xB5B6, 0x2A6F, 0x016E, 0x09AE, 0x018E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x01D1, 0x09F2, 0x0A32, 0x1253, 0x1A74, 0x1A94, 0x22B5, 0x2AD5, 0x2B16, 0x3336, 
        0x3356, 0x3B77, 0x3B77, 0x3B97, 0x43B8, 0x43B8, 0x43D8, 0x43D8, 0x43D9, 0x43B9, 0x3BB9, 0x3B97, 0xAD55, 0xC638, 0x9CD3, 0x9CD3, 0xCE59, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFDF, 0xB5B6, 0xBDD7, 0xC638, 0xD6DA, 0x8452, 0x018E, 0x018E, 0x018F, 0x018F, 0x018F, 0x01AF, 0x01B0, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x01D2, 0x01F2, 0x0A12, 0x1233, 0x1273, 0x1A94, 0x22B5, 0x22D5, 0x2AF6, 0x3336, 0x3356, 
        0x3B77, 0x3B97, 0x43B8, 0x43B8, 0x4BD8, 0x4BF8, 0x4BF9, 0x4BF9, 0x43F9, 0x43D9, 0x3BB9, 0x7455, 0xCE59, 0xA534, 0x9CD3, 0x9CF3, 0xF79E, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xD6BA, 0xB5B6, 0xBDD7, 0xD69A, 0xC618, 0x4B10, 0x018F, 0x018F, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B0, 0x01D1, 0x01D1, 0x01D1, 0x01D2, 0x01F2, 0x0A12, 0x0A33, 0x1253, 0x1A94, 0x1AB5, 0x22D5, 0x2AF6, 0x2B16, 0x3356, 0x3B77, 
        0x3B97, 0x43B8, 0x43D8, 0x4BF8, 0x4BF9, 0x4C19, 0x4C19, 0x4C19, 0x4C1A, 0x4BFA, 0x53F7, 0xB5B6, 0xBDF7, 0x9CD3, 0x9CD3, 0xC638, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xB5B6, 0xB5B6, 0xBDD7, 0xDEDB, 0xAD55, 0x2250, 0x018F, 0x01B0, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x01D1, 0x01D2, 0x01F2, 0x01F2, 0x0A13, 0x1253, 0x1274, 0x1A95, 0x22B5, 0x22F6, 0x2B16, 0x3336, 0x3B77, 0x3B97, 
        0x43B8, 0x43D8, 0x4BF9, 0x4C19, 0x5439, 0x5439, 0x543A, 0x543A, 0x543A, 0x4BF9, 0x9D15, 0xCE79, 0x9CF3, 0x9CD3, 0xA514, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE73C, 0xB596, 0xB5B6, 0xBE17, 0xD6DA, 0x94D4, 0x1A10, 0x01B0, 0x01B0, 0x01B1, 0x01D1, 0x01D1, 0x01D2, 0x01D2, 0x01F2, 0x01F2, 0x0213, 0x0A33, 0x1254, 0x1A94, 0x1AB5, 0x22D6, 0x2AF6, 0x2B36, 0x3357, 0x3B77, 0x43B8, 
        0x43D8, 0x4BF9, 0x5419, 0x5439, 0x5C5A, 0x5C5A, 0x5C7A, 0x5C5A, 0x543A, 0x8CB4, 0xCE79, 0xA534, 0x9CD3, 0x9CD3, 0xD6BA, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE59, 0xB596, 0xB596, 0xC638, 0xD69A, 0x8C93, 0x1A31, 0x01D1, 0x01D1, 0x01D1, 0x01D2, 0x01F2, 0x01F2, 0x01F2, 0x01F3, 0x0A13, 0x0A54, 0x1274, 0x1AB5, 0x22D5, 0x22F6, 0x2B16, 0x3337, 0x3377, 0x3B98, 0x43B8, 
        0x4BD9, 0x4C19, 0x5439, 0x5C5A, 0x5C7A, 0x649A, 0x5C9B, 0x5C5A, 0x8CB5, 0xCE59, 0xB596, 0x9CD3, 0x9CD3, 0xBDD7, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xBDD7, 0xAD75, 0xAD75, 0xC638, 0xD69A, 0x94B3, 0x2271, 0x01D2, 0x01D2, 0x01F2, 0x01F2, 0x01F2, 0x01F3, 0x0213, 0x0A34, 0x0A54, 0x1295, 0x1AB5, 0x22D6, 0x22F6, 0x2B37, 0x3357, 0x3B78, 0x3B98, 0x43D9, 
        0x4BF9, 0x5419, 0x543A, 0x5C7A, 0x649A, 0x64BB, 0x647A, 0x8CD5, 0xCE59, 0xB5B6, 0x9CD3, 0x9CD3, 0xAD55, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xB596, 0xAD75, 0xAD75, 0xC618, 0xD6BA, 0xA535, 0x4312, 0x01F2, 0x01F2, 0x01F3, 0x01F3, 0x0213, 0x0214, 0x0A34, 0x1275, 0x1295, 0x1AB6, 0x22F6, 0x2B17, 0x2B37, 0x3358, 0x3B98, 0x43B8, 0x43D9, 
        0x4BF9, 0x543A, 0x545A, 0x5C7A, 0x649B, 0x6C98, 0x9D15, 0xCE79, 0xB596, 0x9CD3, 0x9CD3, 0xA514, 0xEF9D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xB596, 0xAD55, 0xAD55, 0xB5B6, 0xD6BA, 0xBDD7, 0x7433, 0x2273, 0x01F3, 0x0213, 0x0214, 0x0234, 0x0A55, 0x1275, 0x12B6, 0x1AD6, 0x22F6, 0x2B17, 0x2B57, 0x3378, 0x3B98, 0x43B9, 0x43D9, 
        0x4C1A, 0x543A, 0x545A, 0x5C59, 0x8495, 0xB5B6, 0xCE79, 0xAD55, 0x9CD3, 0x9CD3, 0xA514, 0xEF7D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xB5B6, 0xA534, 0xA534, 0xAD55, 0xCE59, 0xD69A, 0xAD75, 0x63F3, 0x22B3, 0x0234, 0x0234, 0x0A55, 0x1295, 0x1AB6, 0x1AD6, 0x22F7, 0x2B17, 0x2B58, 0x3378, 0x3B99, 0x3BB9, 0x43D9, 
        0x4BFA, 0x5419, 0x7476, 0xA555, 0xCE59, 0xBE17, 0x9CF3, 0x9CD3, 0x9CD3, 0xAD55, 0xEF7D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7DE, 0xC618, 0xA534, 0xA514, 0xA514, 0xAD75, 0xCE79, 0xCE99, 0xB5B6, 0x8494, 0x5394, 0x2AF4, 0x1295, 0x12B6, 0x1AD7, 0x22F7, 0x2318, 0x2B58, 0x3378, 0x3378, 0x4BD7, 0x6436, 
        0x84B5, 0xAD76, 0xCE59, 0xC638, 0xA554, 0x9CD3, 0x9CD3, 0x9CD3, 0xB5B6, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xDEFB, 0xA554, 0x9D13, 0x9CF3, 0x9CF3, 0xAD55, 0xC618, 0xD69A, 0xCE79, 0xBDD7, 0xAD55, 0x94D4, 0x8474, 0x7454, 0x7C54, 0x8474, 0x94D4, 0xA555, 0xB5D6, 0xC658, 
        0xCE79, 0xBDF7, 0xA534, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CF3, 0xD6BA, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xC638, 0xA514, 0x9CF3, 0x9CD3, 0x9CD3, 0x9CF3, 0xA534, 0xB5B6, 0xC638, 0xCE79, 0xCE79, 0xCE99, 0xCE99, 0xCE79, 0xCE59, 0xC618, 0xB5B6, 0xA534, 
        0x9CF3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CF3, 0xBE17, 0xF79E, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xCE59, 0xA534, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 
        0x9CD3, 0x9CD3, 0xA514, 0xC638, 0xEF9D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xE71C, 0xC638, 0xAD55, 0x9CF3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0x9CD3, 0xA554, 
        0xBE17, 0xDEFB, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xE75C, 0xDEFB, 0xD69A, 0xCE79, 0xCE79, 0xD69A, 0xDEDB, 0xE73C, 0xF7BE, 0xFFFF, 
        0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};



const sImage bmButtons_W = {
  50, // xSize
  50, // ySize
  (uint16_t *)image_data_Buttons,  // Pointer to picture data
};


/*************************** End of file ****************************/