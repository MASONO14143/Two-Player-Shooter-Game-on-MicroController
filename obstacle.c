/** @file   obstacle.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  Obstacles
*/

#include "system.h"
#include "displaymatrix.h"
#include "stdlib.h"
#include "obstacle.h"

#define OBSTACLE_RATE 2

// sets the initial bitmap for the obstacle
uint8_t Obstacle_bitmap[] = {
	0b00000001,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

// defines obstacle class, defining position
typedef struct {
	uint8_t x;
	uint8_t y;
} Obstacle_t;

//creates the obstacle
Obstacle_t obstacle;

//initialises the obstacle
void Obstacle_init(void)
{
	obstacle.x = 0;
	obstacle.y = 0;
}

/*moves obstacle across the LED matrix, if it moves off the screen
moves it to the first position of a randomly generated row*/
void Obstacle_move()
{
	if(obstacle.y >= 6) {
		obstacle.y = 0;
		obstacle.x = rand() % 5;
	} else {
		obstacle.y += 1;
	}
}

//updates the obstacles position
void Obstacle_update(uint16_t PACER_RATE)
{
	static uint16_t count = 0;
	
	Display_Update(Obstacle_bitmap, obstacle.x, obstacle.y);
	++count;
	if(count > PACER_RATE/OBSTACLE_RATE) {
		Obstacle_move();
		count = 0;
	}
}

//returns the x position of the obstacle
uint8_t Obstacle_xpos(void)
{
	return obstacle.x;
}

//returns the y position of the obstacle
uint8_t Obstacle_ypos(void)
{
	return obstacle.y;
}