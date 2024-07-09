/** @file   gamestates.h
    @author Lucas, Mason
    @date   17 October 2023
    @brief  defines the gamestates
*/

#ifndef GAMESTATES_H
#define GAMESTATES_H

//All possible states of the program are stored
typedef enum {
    START,
    GAME,
    RESET,
    GAME_OVER
} GameStates;

#endif