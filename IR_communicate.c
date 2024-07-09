/** @file   IR_communicate.c
    @author Lucas, Mason
    @date   18 October 2023
    @brief  Sends and receives data in a certain format
	@note Bit arrangement in game state send
          Bit 0  Bit 1  Bit 2  Bit 3  Bit 4  Bit 5  Bit 6  Bit 7
          |game state|  | bullet position | |isfired| |death| |win|
*/

#include "IR_communicate.h"

#include "system.h"
#include "ir_uart.h"

#define BIT(X) (1 << (X))

/* initalises the IR communication
 by setting all data to 0 */
void IR_init(Received_data_t* incoming)
{
	incoming->game_state = 0;
	incoming->bullet_pos = 0;
	incoming->isFired = 0;
	incoming->death = 0;
	incoming->win = 0;
	incoming->data_received = 0;
}

//sends data to other ucfk
void Send_Data(uint8_t* data, uint8_t* bit_size, uint8_t num)
{
	//inits variable
	char output = 0x0;
	
	uint8_t bit_shift = 0;
	for(uint8_t i = 0; i < num; ++i) {
		//bit shifts data into output
		output |= data[i] << bit_shift;
		bit_shift += bit_size[i];
	}
	//sends data
	ir_uart_putc (output);
}

//receives data from other ucfk
Received_data_t Receive_Data(void)
{
	// calling and initialising a received data variable
    uint8_t ch = 0;
	Received_data_t temp;
	IR_init(&temp);
	
	//assigns each variables data given its bit size
	if (ir_uart_read_ready_p ()) {
        ch = ir_uart_getc ();
		temp.game_state |= (ch & 0b00000011);
		temp.bullet_pos |= ((ch >> 2) & 0b00000111);
		temp.bullet_pos = 4 - temp.bullet_pos;
		temp.isFired |= ((ch >> 5) & 1);
		temp.death |= ((ch >> 6) & 1);
		temp.win |= ((ch >> 7) & 1);
		temp.data_received = 1;
    } else {
		temp.data_received = 0;
	}
	return temp;
	//if data_received is 0, no data received
}
