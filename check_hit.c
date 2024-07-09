/** @file   check_hit.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  Checks whether a bitmap overlaps with another bitmap
*/

#include "system.h"
#include "shift_bitmap.h"
#include "check_hit.h"

#define COLUMN_NUM 5
#define ROW_NUM 7

uint8_t Check_hit(uint8_t* bitmap1, uint8_t x1, uint8_t y1, uint8_t* bitmap2, uint8_t x2, uint8_t y2)
{	
	//where shifted bitmaps are stored
	uint8_t newbitmap1[COLUMN_NUM];
	uint8_t newbitmap2[COLUMN_NUM];
	
	//shifts the bitmaps by the given amount
	Shift_Bitmap(newbitmap1, bitmap1, x1, y1);
	Shift_Bitmap(newbitmap2, bitmap2, x2, y2);
	
	//checks each value of the bitmap
	//if any 1s overlap, return true otherwise false
	for(uint8_t column = 0; column < COLUMN_NUM; ++column) {
		for(uint8_t row = 0; row < ROW_NUM; ++row) {
			if(((newbitmap1[column] >> row) & 1) & ((newbitmap2[column] >> row) & 1)) {
				return 1;
			}
		}
	}
	return 0;
}