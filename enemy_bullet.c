/** @file   enemy_bullet.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief 	Enemy bullet
*/

#include "system.h"
#include "displaymatrix.h"
#include "enemy_bullet.h"

#define ENEMY_BULLET_RATE 3

// sets the initial bitmap for the enemy bullet
uint8_t Enemy_bullet_bitmap[] = {
	0b00000010,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

// bullet class, defines position and whether the bullet is fired
typedef struct {
	uint8_t isFired;
	uint8_t x;
	uint8_t y;
} Bullet_t;

// makes enemy bullet
Bullet_t enemy_bullet;

// initialises the enemy bullet
void Enemy_bullet_init(void)
{
    enemy_bullet.x = 15;
	enemy_bullet.y = 15;
	enemy_bullet.isFired = 0;
}

// spawns the enemy's bullet at the correct position
void Enemy_bullet_fire(uint8_t x_pos, uint8_t y_pos)
{
	enemy_bullet.y = y_pos+1;
	enemy_bullet.x = x_pos;
	enemy_bullet.isFired = 1;
}

// moves the enemy bullet down the screen
void Enemy_bullet_move(void)
{
	// resets bullet if off screen
	if(enemy_bullet.isFired) {
		if(enemy_bullet.x >= 5) {
			enemy_bullet.isFired = 0;
			enemy_bullet.x = 15;
			enemy_bullet.y = 15;
		// else moves bullet
		} else {
			enemy_bullet.x += 1;
		}
	}
}

/* updates the bullet position of the enemy's bullet */
void Enemy_bullet_update(uint16_t PACER_RATE)
{
	static uint16_t count = 0;
	++count;
	if(count > PACER_RATE/ENEMY_BULLET_RATE) {
		Enemy_bullet_move();
		count = 0;
	}
	Display_Update(Enemy_bullet_bitmap, enemy_bullet.x, enemy_bullet.y);
}

// returns the x position of the enemy's bullet
uint8_t Enemy_bullet_xpos(void)
{
	return enemy_bullet.x;
}

// returns the y position of the enemy's bullet
uint8_t Enemy_bullet_ypos(void)
{
	return enemy_bullet.y;
}