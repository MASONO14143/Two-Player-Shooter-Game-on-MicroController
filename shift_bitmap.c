/** @file   shift_bitmap.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  shifts bitmap
*/

#include "system.h"
#include "shift_bitmap.h"

#define ROW_NUM 7
#define COLUMN_NUM 5

void Shift_Bitmap(uint8_t* newbitmap, uint8_t* bitmap, uint8_t x, uint8_t y)
{
	
	for(uint8_t column = 0; column < COLUMN_NUM; ++column) {
		//shifts column leds by x amount
		if(column >= x) {
			//bitshifts rows by y amount
			newbitmap[column] = bitmap[column - x] << y;
		} else {
			//fills empty columns due to column shift with 0s
			newbitmap[column] = 0;
		}
	}
}