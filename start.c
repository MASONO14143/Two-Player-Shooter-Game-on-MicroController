/** @file   reset.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  Start game state
*/

#include "tinygl.h"
#include "navswitch.h"
#include "start.h"
#include "IR_communicate.h"
#include "gamestates.h"

//flags for IR data
#define GAME_STATE 0
#define BULLET_POS 1
#define IS_FIRED 2
#define DEATH 3
#define WIN 4

static Received_data_t incoming;

//THe start function, first state when booting on ucfk
GameStates start(GameStates current_state)
{
	//stores data for sending IR and its bitsize
	static uint8_t bit_size[] = {2, 3, 1, 1, 1};
	static uint8_t data[] = {START, 0, 0, 0, 0};
	static GameStates buffer_state = START;
	
	//update display
	tinygl_update();
	
	//checks whether player is ready if the navswitch is pushed in
	if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
		//if so, set buffer_state the GAME, send game to show its ready
		buffer_state = GAME;
		data[GAME_STATE] = buffer_state;
		Send_Data(data, bit_size, 5);
	}
	//wait for other player to be ready
	if(buffer_state == GAME) {
		//receiving data from IR if ready
		incoming = Receive_Data();
		//if has received data and shows other p;ayer is ready, start game
		if(incoming.data_received && incoming.game_state == GAME) {
			//clear display and reset buffer_state
			tinygl_clear();
			current_state = GAME;
			buffer_state = START;
			//returns current_state as GAME
			return current_state;
		}
	}
    return current_state;
}
