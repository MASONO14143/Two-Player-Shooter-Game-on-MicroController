/** @file   bullet.h
    @author Lucas, Mason
    @date   18 October 2023
    @brief  function declarations for the player bullet
*/

#ifndef BULLET_H
#define BULLET_H

#include "system.h"

//initialises the bullet
void Bullet_init(void);

//fires the bullet and sets position
void Bullet_fire(uint8_t x_pos, uint8_t y_pos);

//Moves the bullet -1 in x direction every call
uint8_t Bullet_move(void);

//displays the bullet at its position
uint8_t Bullet_update(uint16_t PACER_RATE);

//gets the bullet y position.
uint8_t Bullet_ypos(void);

#endif