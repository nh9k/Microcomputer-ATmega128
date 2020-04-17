#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#define S0 PD0

#define D0 PB0
#define D1 PB1
#define D2 PB2
#define D3 PB3
#define D4 PB4

volatile int state = 0;

ISR(INT0_vect)
{	
	state++;
	if(state>3) state=1;
}

void INIT_PORT(void)
{
 DDRB = 1<<D0 | 1<<D1 | 1<<D2 | 1<<D3 | 1<<D4;

 DDRD = 0<<S0;
 PORTD = 1<<S0;
}	

void INIT_INT0(void)
{
	EIMSK |= (1<<INT0);
	EICRA |= (1<<ISC01);
	sei();
}

int main(void)
{
	INIT_PORT();
	INIT_INT0();

	while(1){

	 	if(state==1)	{
	    	PORTB &=~(1<<D3 | 1<<D4);	
		 	PORTB |= 1<<D0 | 1<<D1;
}
		else if(state==2){
		    PORTB &=~(1<<D0 | 1<<D1);	
			PORTB |= 1<<D2;
}
		else {
	    	PORTB &=~(1<<D2);	
			PORTB |= 1<<D3 | 1<<D4;
		}
	}			 
	return 0;
}
