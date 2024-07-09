/** @file   reset.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  Reset game state
*/

#include "tinygl.h"
#include "navswitch.h"
#include "gamestates.h"
#include "reset.h"
#include "IR_communicate.h"

#define WIN_NEEDED 3

//flags for IR data
#define GAME_STATE 0
#define BULLET_POS 1
#define IS_FIRED 2
#define DEATH 3
#define WIN 4

static Received_data_t incoming;

GameStates reset(GameStates current_state, uint8_t wins, uint8_t losses)
{
	static uint8_t bit_size[] = {2, 3, 1, 1, 1};
	static uint8_t data[] = {RESET, 0, 0, 1, 0};
	static GameStates buffer_state = RESET;
	
	tinygl_update();
	if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
		//need a way to confirm whether the other ucfk is ready
		buffer_state = START;
		data[GAME_STATE] = buffer_state;
		Send_Data(data, bit_size, 5);
	}
	// changes game state to start when both funkit are ready
	if(buffer_state == START) {
		incoming = Receive_Data();
		if(incoming.data_received && incoming.game_state == START) {
			current_state = START;
			data[GAME_STATE] = RESET;
			buffer_state = RESET;
			tinygl_clear();
			// if player has won or lose, change game state to GAME OVER
			if(wins >= WIN_NEEDED || losses >= WIN_NEEDED) {
				current_state = GAME_OVER;
			}				
			
			return current_state;
		}
	}
    return current_state;
}
