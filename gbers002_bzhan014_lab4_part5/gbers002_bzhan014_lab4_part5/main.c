/*	Glenn Bersabe Email: Gbers002@ucr.edu
 *  Bohan Zhang Email: Bzhan014@ucr.edu
 *	Lab Section: 023
 *	Assignment: Lab 4  Exercise 5
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
enum States{start, input, unlock, lock}state;
unsigned char count = 0x00;
unsigned char code = 0x00;
unsigned char sequence[4];
unsigned char correctSequence[] = {2,0,1,0};
void tick() {
	switch(state) {
		case start:
			state = input;
			break;
		case input:
			if (code == 0x00) {
				state = input;
			}
			else if (code == 0x01 && PORTB == 0x00) {
				state = unlock;
			}
			else if (code == 0x01 && PORTB == 0x01) {
				state = lock;
			}
			break;
		case unlock:
			state = input;
			break;
		case lock:
			state = input;
			break;
	}	
	switch(state) {
		case input:
			if (count < 4) {
				sequence[count] = PINA;
				count++;
			}
			else if (count == 4) {
				for (unsigned char i = 0; i < 4; i++) {
					if (sequence[i] != correctSequence[i]) {
						count = 0x00;
						break;
					}
					else {
						code = 0x01;
						count = 0x00;
						break;
					}
				}
			}
			break;
		case unlock:
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
	state = start;
    while (1) 
    {
		tick();
    }
}

