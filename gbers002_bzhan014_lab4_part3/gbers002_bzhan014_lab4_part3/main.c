/*	Glenn Bersabe Email: Gbers002@ucr.edu
 *  Bohan Zhang Email: Bzhan014@ucr.edu
 *	Lab Section: 023
 *	Assignment: Lab 4  Exercise 3
 *	Exercise Description: Simulates a button where pressing it transitions the state.
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
enum States{start, input, pound, r_pound, unlock, lock} state;
unsigned char hold = 0x00;
void tick() {
	switch(state) {
		case start:
			state = input;
			break;
		case input:
			if(PINA == 0x04) {
				state = pound;
				hold = 0x01;
			}
			else {
				state = input;
			}
			break;
		case pound: 
			if(PINA == 0x04 && hold == 0x01) {
				state = pound;
			}
			else if (PINA == 0x00) {
				state = pound;
				hold = 0x00;
			}
			else if (PINA == 0x02 && hold == 0x00) {
				state = r_pound;
			}
			else {
				state = input;
			}
			break;
		case r_pound:
			state = unlock;
			break;
		case unlock: 
			if (PINA == 0x80) {
				state = lock;
			}
			break;
		case lock: 
			state = input;
			break;
	}
	switch(state) {
		case input:
			PORTC = 0x01;
			break;
		case pound:
			PORTC = 0x02;
			break;
		case r_pound:
			PORTC = 0x04;
			break;
		case unlock:
			PORTC = 0x08;
			PORTB = 0x01;
			break;
		case lock:
			PORTB = 0x00;
			break;
	}
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	state = start;
    while (1) 
    {
		tick();
    }
}

