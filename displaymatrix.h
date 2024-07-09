/** @file   displaymatrix.h
    @author Lucas, Mason
    @date   18 October 2023
    @brief  function declarations for the display matrix
*/

#ifndef DISPLAYMATRIX_H
#define DISPLAYMATRIX_H

#include "system.h"
#include "tinygl.h"

//updates the bitmap to display onto the LED matrix
void Display_Update(uint8_t* bitmap, uint8_t x, uint8_t y);

//turns on all required LEDs
void Display_Draw(void);

//clears the LED matrix
void Display_Clear(void);

#endif