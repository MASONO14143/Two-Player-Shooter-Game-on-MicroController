/** @file   spaceship.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  Spaceship
*/

#include "spaceship.h"
#include "displaymatrix.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

// sets the initial bitmap for the spaceship
uint8_t Spaceship_bitmap[] = {
	0b00000010,
	0b00000111,
	0b00000000,
	0b00000000,
	0b00000000
};

//spaceship class, defining postion and if its alive
typedef struct {
	uint8_t x;
	uint8_t y;
	bool alive;
} Spaceship_t;

// makes spaceship
static Spaceship_t ship;

//initialises spaceship
void Spaceship_init(void)
{
	ship.x = 3;
	ship.y = 2;
	ship.alive = true;
}

//updates and draws the spaceship
//should separate to allow for different refresh rates
void Spaceship_update(void)
{
	Display_Update(Spaceship_bitmap, ship.x, ship.y);
}

//movement functions
// moves spaceship up
void Spaceship_Up(void)
{
	ship.y = max(ship.y - 1, 0);
}

// moves spaceship down
void Spaceship_Down(void)
{
	ship.y = min(ship.y + 1, 4);
}

// moves spaceship left
void Spaceship_Left(void)
{
	ship.x = max(ship.x - 1, 0);
}

// moves spaceship right
void Spaceship_Right(void)
{
	ship.x = min(ship.x + 1, 3);
}
//movement functions end

// returns the x position of the spaceship
uint8_t Spaceship_xpos(void)
{
	return ship.x;
}

// returns the y position of the spaceship
uint8_t Spaceship_ypos(void)
{
	return ship.y;
}