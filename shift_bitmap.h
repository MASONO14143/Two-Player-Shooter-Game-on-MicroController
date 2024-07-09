/** @file   shift_bitmap.h
    @author Lucas, Mason
    @date   18 October 2023
    @brief  file declaration for shift bitmap
*/

#ifndef SHIFT_BITMAP
#define SHIFT_BITMAP

#include "system.h"

//shifts the bitmap a given x position and y position
void Shift_Bitmap(uint8_t* newbitmap, uint8_t* bitmap, uint8_t x, uint8_t y);

#endif