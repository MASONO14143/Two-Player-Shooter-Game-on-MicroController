/** @file   check_hit.h
    @author Lucas, Mason
    @date   18 October 2023
    @brief  function declaration for Check_hit function
*/

#ifndef CHECK_HIT_H
#define CHECK_HIT_H

#include "system.h"

//Check whether 2 bitmaps or overlapping
uint8_t Check_hit(uint8_t* bitmap1, uint8_t x1, uint8_t y1, uint8_t* bitmap2, uint8_t x2, uint8_t y2);

#endif