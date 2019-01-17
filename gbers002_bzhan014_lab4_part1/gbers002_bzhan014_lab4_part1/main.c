/*
 * gbers002_bzhan014_lab4_part1.c
 *
 * Created: 1/17/2019 3:00:03 PM
 * Author : Glenn
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x01;
	unsigned char button = 0x00;
	   
    while (1) 
    {
		if ((PINA & 0x01) == 0x01) {
			button = 0x01;	
		}
		else if ((PINA & 0x01) == 0x00) {
			button = 0x00;	
		}
		
		if (button == 0x00) {
			PORTB = 0x01;
		}
		else if (button == 0x01) {
			PORTB = 0x02;	
		}
    } 
}

