# File:   Makefile
# Author: Lucas, Mason
# Date:   19 October 2023
# Descr:  Makefile for pew pew game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/system.h spaceship.h bullet.h IR_communicate.h enemy_bullet.h obstacle.h reset.h start.h gamestates.h
	$(CC) -c $(CFLAGS) $< -o $@

# prerequisites for driver headers

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@
	
tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@
	
ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/delay.h ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

	
#end
	
displaymatrix.o: displaymatrix.c ../../drivers/avr/system.h ../../utils/tinygl.h shift_bitmap.h displaymatrix.h
	$(CC) -c $(CFLAGS) $< -o $@
	
spaceship.o: spaceship.c ../../drivers/avr/system.h spaceship.h
	$(CC) -c $(CFLAGS) $< -o $@
	
bullet.o: bullet.c ../../drivers/avr/system.h bullet.h
	$(CC) -c $(CFLAGS) $< -o $@

enemy_bullet.o: enemy_bullet.c ../../drivers/avr/system.h enemy_bullet.h
	$(CC) -c $(CFLAGS) $< -o $@

IR_communicate.o: IR_communicate.c ../../drivers/avr/system.h IR_communicate.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@
	
obstacle.o: obstacle.c ../../drivers/avr/system.h obstacle.h
	$(CC) -c $(CFLAGS) $< -o $@

check_hit.o: check_hit.c ../../drivers/avr/system.h shift_bitmap.h check_hit.h
	$(CC) -c $(CFLAGS) $< -o $@

shift_bitmap.o: shift_bitmap.c ../../drivers/avr/system.h shift_bitmap.h
	$(CC) -c $(CFLAGS) $< -o $@

reset.o: reset.c ../../drivers/avr/system.h reset.h gamestates.h
	$(CC) -c $(CFLAGS) $< -o $@

start.o: start.c ../../drivers/avr/system.h start.h gamestates.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
game.out: game.o displaymatrix.o spaceship.o bullet.o IR_communicate.o enemy_bullet.o obstacle.o check_hit.o shift_bitmap.o ir_uart.o pio.o prescale.o system.o timer.o timer0.o usart1.o display.o ledmat.o navswitch.o font.o pacer.o tinygl.o reset.o start.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start


