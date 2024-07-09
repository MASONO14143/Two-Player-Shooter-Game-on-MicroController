/** @file   obstacle.h
    @author Lucas, Mason
    @date   18 October 2023
    @brief  function declarations for obstacles
*/

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "system.h"

#define COLUMN_NUM 5

//bitmap declaration
uint8_t Obstacle_bitmap[COLUMN_NUM];

//initialises obstacle
void Obstacle_init(void);

//moves the obstacle +1 in y direction every call
void Obstacle_move(void);

//displays obstacle at its position
void Obstacle_update(uint16_t PACER_RATE);

//gets obstacle y position
uint8_t Obstacle_ypos(void);

//gets obstacle x position
uint8_t Obstacle_xpos(void);

#endif