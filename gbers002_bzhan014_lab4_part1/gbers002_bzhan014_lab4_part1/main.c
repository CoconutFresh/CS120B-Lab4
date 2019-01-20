/*	Glenn Bersabe Email: Gbers002@ucr.edu
 *  Bohan Zhang Email: Bzhan014@ucr.edu
 *	Lab Section: 023
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: Simulates a button where pressing it transitions the state.
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

enum States {start, B_1, B_2} state;
	unsigned char hold = 0x00;

	void tick() {
		switch(state) { //transition
			case start: 
				state = B_1;
				break;
			case B_1:
				if (PINA == 0x01 && hold == 0x00) { //Hold state where A0 is still 1
					state = B_1;
				}
				else if (PINA == 0x00) { //State where button is released
					state = B_1;
					hold = 0x01;
				}
				else if (PINA == 0x01 && hold == 0x01) { //Transition state
					state = B_2;
					hold = 0x00;
				}
				break;
			case B_2:
				if (PINA == 0x01 && hold == 0x00) { //Hold state where A0 is still 1
					state = B_2;
				}
				else if (PINA == 0x00) { //State where button is released
					state = B_2;
					hold = 0x01;
				}
				else if (PINA == 0x01 && hold == 0x01) { //Transition state
					state = B_1;
					hold = 0x00;
				}
					break;
			default: 
				printf("Error");
				exit(1);
				
		}
		switch(state) { //states
			case B_1: 
				PORTB = 0x01;
				break;
			case B_2:
				PORTB = 0x02;
				break;
		}
	}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = start;
	   
    while (1) 
    {
			tick();
    } 
}

