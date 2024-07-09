/** @file   game.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  main game file
    
    @defgroup shooty shooty game
*/

#include "system.h"
#include "button.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pio.h"
#include "../../../ence260-ucfk4/fonts/font5x5_1.h"

//modules
#include "spaceship.h"
#include "bullet.h"
#include "IR_communicate.h"
#include "enemy_bullet.h"
#include "obstacle.h"
#include "check_hit.h"
#include "reset.h"
#include "start.h"
#include "gamestates.h"

//defines the rate at which things update
#define PACER_RATE 500
#define TEXT_SPEED 7
#define WIN_NEEDED 3

//flags for IR data
#define GAME_STATE 0
#define BULLET_POS 1
#define IS_FIRED 2
#define DEATH 3
#define WIN 4

//where data from IR is stored
static Received_data_t incoming;

//various game states of the program

static GameStates current_state;
static uint8_t wins = 0, losses = 0;

//initialising the text for the start screen
void text_display(char* disp_message)
{
    tinygl_font_set(&font5x5_1);
    tinygl_text_speed_set(TEXT_SPEED);
	tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(disp_message);
}

//resets the game to prepare for the next round 
void game_reset(uint8_t* data) {
	//displays the numberof wins
	char temp[] = {' ', (char)(wins+48), '\0'};
	tinygl_clear();
	text_display(temp);
	
	//resets all data vars
	data[GAME_STATE] = GAME;
	data[BULLET_POS] = 0;
	data[IS_FIRED] = 0;
	data[DEATH] = 0;
	data[WIN] = 0;
	
	//reinits everything
	current_state = RESET;
	Enemy_bullet_init();
	Obstacle_init();
	Spaceship_init();
	Bullet_init();
}

/*checks if any input from the navswitch has occurred
and moves the spaceship, or fires a bullet accordingly*/
void nav_check(void)
{	
	if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
		Spaceship_Up();
	} else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
		Spaceship_Down();
	}
	if (navswitch_push_event_p (NAVSWITCH_EAST)) {
		Spaceship_Right();
	} else if (navswitch_push_event_p (NAVSWITCH_WEST)) {
		Spaceship_Left();
	}
	if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
		Bullet_fire(Spaceship_xpos(), Spaceship_ypos());
	}
}

//The main game function
void game(void)
{
	//where data to send is stored along with its bitsize
	static uint8_t bit_size[] = {2, 3, 1, 1, 1};
	static uint8_t data[] = {GAME, 0, 0, 0, 0};
	
	//clears screen
	tinygl_clear();
	//checks navswitch state whether pushed in any direction
	nav_check();
	
	//checks whether data from IR is received and stores values if so
	incoming = Receive_Data();
	if(incoming.data_received) {
		//data received
		
		//if the opponent dies, death flag is sent
		if(incoming.death) {
			//get a win and send to opponent
			wins += 1;
			Send_Data(data, bit_size, 5);
			//resets game
			game_reset(data);
			return;
		}
		
		//if enemy_bullet is fired, fire the bullet at the position given from IR
		if(incoming.isFired) {
			Enemy_bullet_fire(0, incoming.bullet_pos);	
		}
	}
	
	//updates enemy bullet, obstacle, and spaceship
	Enemy_bullet_update(PACER_RATE);
	Obstacle_update(PACER_RATE);
	Spaceship_update();
	
	//returns true if your bullet reaches the border
	//sends data to opponent for bullet to appear there
	uint8_t posy = Bullet_ypos();
	if(Bullet_update(PACER_RATE)) {
		//updating data byte
		//maybe need separate module, looks messy
		data[GAME_STATE] = current_state;
		data[BULLET_POS] = posy;
		data[IS_FIRED] = 1;
		
		Send_Data(data, bit_size, 5);
	}
	
	//checks whether the obstacle is overlapping with the player ship
	//if so, death flag is sent and a loss is incremented
	//the game will be reset
	if(Check_hit(Spaceship_bitmap, Spaceship_xpos(), Spaceship_ypos(), Obstacle_bitmap, Obstacle_xpos(), Obstacle_ypos())) {
		data[DEATH] = 1;
		Send_Data(data, bit_size, 5);
		game_reset(data);
		losses += 1;
		return;
	//checks whether the enemy bullet is overlapping with the player ship
	//if so, death flag is sent and a loss is incremented
	//the game will be reset
	} else if(Check_hit(Spaceship_bitmap, Spaceship_xpos(), Spaceship_ypos(), Enemy_bullet_bitmap, Enemy_bullet_xpos(), Enemy_bullet_ypos())) {
		data[DEATH] = 1;
		Send_Data(data, bit_size, 5);
		game_reset(data);
		losses += 1;
		return;
	}
	
	//updates the display
	tinygl_update();
}

//displays the game result after a player has reach the necessary wins
void game_over(void)
{
	//if 3 wins then display win screen
	if(wins >= WIN_NEEDED) {
		char message[] = "YOU WIN :)";
		tinygl_text(message);
	} else {//if not display the lose screen
		char message[] = "YOU LOSE :(";
		tinygl_text(message);
	}
	//permanent loop
	while(1) {
		pacer_wait();
		tinygl_update();
	}
}

int main (void)
{
	/*INITIALISING*/
	IR_init(&incoming);
	
    system_init ();
    tinygl_init(PACER_RATE);
	pacer_init(PACER_RATE);
    navswitch_init();
    ir_uart_init();
    Spaceship_init();
	Bullet_init();
	Enemy_bullet_init();
	Obstacle_init();
    
	text_display(" START$_$");
	current_state = START;
	/*INITIALISING END*/
	
    while (1)
    {
		//sets framerate
		pacer_wait();
		//checks navswitch
        navswitch_update();
		
		//switches which state is run depending on the current state
		switch (current_state) {
			case START:
				current_state = start(current_state);
				break;
			case GAME:
				game();
				break;
			case RESET:
				current_state = reset(current_state, wins, losses);
				break;
			case GAME_OVER:
				game_over();
		}
		//updates the display
		tinygl_update();

    }
}
