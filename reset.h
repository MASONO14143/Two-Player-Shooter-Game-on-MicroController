/** @file   reset.h
    @author Lucas, Mason
    @date   18 October 2023
    @brief  function declarations for the reset game state
*/

#ifndef RESET_H
#define RESET_H

#include "system.h"
#include "gamestates.h"

//resets the game after every death
GameStates reset(GameStates current_state, uint8_t wins, uint8_t losses);

#endif