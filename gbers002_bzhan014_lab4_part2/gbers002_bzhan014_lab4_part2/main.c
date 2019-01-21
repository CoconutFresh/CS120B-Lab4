/*
 * gbers002_bzhan014_lab4_part2.c
 *
 * Created: 1/17/2019 3:14:31 PM
 * Author : Glenn
 */ 

#include <avr/io.h>

enum States{start, increase, decrease} state;
void tick() {
	switch(state) {
		case start:
			PORTC = 7;
			if(PINA == 0x01) {
				state = increase;
			}
			else if (PINA == 0x02) {
				state = decrease;
			}
			break;
		case increase:
			if(PINA == 0x01) {
				state = increase;
			}
			else if (PINA = 0x02) {
				state = decrease;
			}
			break;
		case decrease:
			if(PINA == 0x01) {
				state = increase;
			}
			else if (PINA = 0x02) {
				state = decrease;
			}
			break;
	}
	switch (state) {
		case increase:
			if (PORTC < 9) {
				PORTC = PORTC + 1; 
				break;
			}
			else {
				break;
			}
		case decrease:
			if (PORTC > 0) {
				PORTC = PORTC - 1;
				break;
			}
			else {
				break;
			}
	}
}
	
int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	state = start;
    while (1) 
    {
		tick();
    }
}

