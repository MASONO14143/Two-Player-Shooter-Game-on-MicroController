/** @file   displaymatrix.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  Shifts bitmaps by amount and displays
*/

#include "displaymatrix.h"
#include "system.h"
#include "tinygl.h"
#include "shift_bitmap.h"

#define ROW_NUM 7
#define COLUMN_NUM 5

// draws the bitmap onto the LED matrix
void Display_Columns(uint8_t row_pattern, uint8_t current_column)
{
	for(uint8_t i = 0; i < 7; ++i) {
		//if bit is 1, turn LED on, otherwise off
		if(row_pattern & (1<<i)) {
			tinygl_draw_point(tinygl_point(current_column, i), 1);
		}
	}
}

// updates the display
void Display_Update(uint8_t* bitmap, uint8_t x, uint8_t y)
{
	uint8_t newbitmap[COLUMN_NUM];
	
	Shift_Bitmap(newbitmap, bitmap, x, y);
	//display columns by sending each row first
	for(uint8_t i = 0; i < 5; ++i) {
		Display_Columns(newbitmap[i], i);
	}
}

// updates the LED matrix
void Display_Draw(void)
{
	tinygl_update();
}

// clears the LED matrix
void Display_Clear(void)
{
	tinygl_clear();
}
