#ifndef __DRAWIMAGE_H
#define __DRAWIMAGE_H

#include <stdint.h>

typedef struct {
  uint16_t Width;
  uint16_t Height;
  const uint16_t *pData;
	
} sImage;


typedef struct {
  uint16_t Width;
  uint16_t Height;
  uint16_t Address;

} sImageFlash;
#endif
