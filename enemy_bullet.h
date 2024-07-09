/** @file   enemy_bullet.h
    @author Lucas, Mason
    @date   18 October 2023
    @brief  function declarations for the enemy bullet
*/

#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "system.h"

#define COLUMN_NUM 5

//bitmap declaration
uint8_t Enemy_bullet_bitmap[COLUMN_NUM];

//initialises the enemy bullet
void Enemy_bullet_init(void);

//fires the bullet and sets position
void Enemy_bullet_fire(uint8_t x_pos, uint8_t y_pos);

//moves the bullet +1 in x direction every call
void Enemy_bullet_move(void);

//displays the bullet at its position
void Enemy_bullet_update(uint16_t PACER_RATE);

//gets bullet x position
uint8_t Enemy_bullet_xpos(void);

//gets bullet y position
uint8_t Enemy_bullet_ypos(void);

#endif
