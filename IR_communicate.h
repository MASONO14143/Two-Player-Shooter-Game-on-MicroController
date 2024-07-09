/** @file   IR_communicate.h
    @author Lucas, Mason
    @date   18 October 2023
    @brief  function declarations for and macro defintions for the IR communication
*/

#ifndef IR_SEND_H
#define IR_SEND_H

#include "system.h"

//all data vars sent and received over IR
typedef struct {
    uint8_t game_state;
	uint8_t bullet_pos;
	uint8_t isFired;
	uint8_t death;//sent if you die?
	uint8_t win;//send if your score is enough to win?
	uint8_t data_received;
} Received_data_t;

//intialises IR
void IR_init(Received_data_t* incoming);

//sends data through IR with a max size of 8 bits
void Send_Data(uint8_t* data, uint8_t* bit_size, uint8_t num);

//checks IR and returns data when ready
Received_data_t Receive_Data(void);

#endif