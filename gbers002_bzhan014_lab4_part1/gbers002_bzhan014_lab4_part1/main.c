/*
 * gbers002_bzhan014_lab4_part1.c
 *
 * Created: 1/17/2019 3:00:03 PM
 * Author : Glenn
 */ 

#include <avr/io.h>
enum States {start, OFF, ON} state;
	unsigned char button = 0x00;

	void tick() {
		switch(state) {
			case start: 
			state = OFF;
			break;
			case OFF:
				if (PINA == 0x00) { state = OFF;}
				else if (PINA == 0x01) { state = ON;}
				break;
			case ON:
				if (PINA == 0x00) {state = ON;}
				else if (PINA == 0x01) {state = OFF;}
					break;
		}
		switch(state) {
			case OFF: 
			PORTB = 0x01;
			break;
			case ON:
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

