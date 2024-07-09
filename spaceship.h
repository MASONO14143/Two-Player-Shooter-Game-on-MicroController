/** @file   spaceship.h
    @author Lucas, Mason
    @date   18 October 2023
    @brief  file declarations for spaceship
*/

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "system.h"

#define COLUMN_NUM 5

//bitmap declaration
uint8_t Spaceship_bitmap[COLUMN_NUM];

//initialises the spaceship
void Spaceship_init(void);

//displays the spaceship at its given position
void Spaceship_update(void);

//moves spaceship down
void Spaceship_Down(void);

//moves spaceship left
void Spaceship_Left(void);

//moves spaceship right
void Spaceship_Right(void);

//moves spaceship up
void Spaceship_Up(void);

//gets spaceship y position
uint8_t Spaceship_ypos(void);

//gets spaceship x position
uint8_t Spaceship_xpos(void);

#endif