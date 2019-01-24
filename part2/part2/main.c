
#include <avr/io.h>
enum States {Start, Init, Inc, Dec, Hold, Reset}state;

void tick(){
	//Transitions
	switch(state){
		case Start:
		{
			state = Init;
			break;
		}
		
		case Init:
		if(PINA == 0x01)
		{
			state = Inc;
			break;
		}
		else if(PINA == 0x02)
		{
			state = Dec;
			break;
		}
		else if(PINA == 0x03)
		{
			state = Reset;
			break;
		}
		else
		{
			state = Init;
			break;
		}
		
		case Inc:
		state = Hold;
		break;
		
		case Dec:
		state = Hold;
		break;
		
		case Hold:
		if((PINA == 0x01) || (PINA == 0x02))
		{
			state = Hold;
			break;
		}
		else if(PINA == 0x03)
		{
			state = Reset;
			break;
		}
		else
		{
			state = Init;
			break;
		}
		
		case Reset:
		if((PINA == 0x01) || (PINA == 0x02))
		{
			state = Reset;
			break;
		}
		else if (PINA == 0x03)
		{
			state = Init;
			break;
		}
		
		default:
		break;
	}
	switch(state){ //State actions
		case Start:
		PORTC = 0x07;
		break;
		
		case Init:
		break;
		
		case Inc:
		if(PORTC < 0x09)
		{
			PORTC += 0x01;
			break;
		}
		break;
		
		case Dec:
		if(PORTC > 0x00)
		{
			PORTC -= 0x01;
			break;
		}
		break;
		
		case Hold:
		break;
		
		case Reset:
		PORTC = 0x00;
		break;
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x07;
	state = Start;
	while(1)
	{
		tick();
	}
}
