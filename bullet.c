/** @file   bullet.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  Player Bullet
*/

#include "system.h"
#include "displaymatrix.h"
#include "bullet.h"

#define BULLET_RATE 3

// sets the initial bitmap for the player bullet
static uint8_t bitmap[] = {
	0b00000001,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

//toggles whether we wait for the delay before shooting
//delay should be how long till bullet reach end of opponent screen
static uint8_t wait = 0;

// bullet class, defines position and whether the bullet is fired
typedef struct {
	uint8_t isFired;
	uint8_t x;
	uint8_t y;
} Bullet_t;

// makes bullet
Bullet_t player_bullet;

//initialises the player bullet
void Bullet_init(void)
{
	player_bullet.x = 15;
	player_bullet.y = 15;
	player_bullet.isFired = 0;
}

//fires a bullet
void Bullet_fire(uint8_t x_pos, uint8_t y_pos)
{
	if(player_bullet.isFired == 0 && wait == 0) {
		player_bullet.y = y_pos+1;
		player_bullet.x = x_pos;
		player_bullet.isFired = 1;
	}
}

/* Moves the players bullet up towards the enemy */
uint8_t Bullet_move(void)
{
	// resets bullet if off screen
	if(player_bullet.x <= 0) {
		player_bullet.isFired = 0;
		player_bullet.x = 15;
		player_bullet.y = 15;
		return 1;
	// else moves bullet
	} else {
		player_bullet.x -= 1;
		return 0;
	}
}

/* updates the bullet position */
uint8_t Bullet_update(uint16_t PACER_RATE)
{
	static uint16_t count = 0;
	static uint8_t timer = 0;
	uint8_t border = 0;
	
	++count;
	if(count > PACER_RATE/BULLET_RATE) {
		//only moves if fired
		if(player_bullet.isFired) {
			border = Bullet_move();
		}
		//if reached player's border, trigger wait
		if(border) {
			wait = 1;
		}
		//resets wait after 5 blocks moved
		if(timer >= 5) {
			wait = 0;
			timer = 0;
		} else if(wait) {
			timer += 1;
		}
		count = 0;
	}
	Display_Update(bitmap, player_bullet.x, player_bullet.y);
	
	return border;
}

// returns the y position of the players bullet 
uint8_t Bullet_ypos(void) {
	return player_bullet.y;
}