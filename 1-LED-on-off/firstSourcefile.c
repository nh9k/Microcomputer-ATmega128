#include <avr/io.h>

#define S0 PB5
#define S1 PB6
#define S2 PB7

#define D0 PB0
#define D1 PB1
#define D2 PB2
#define D3 PB3
#define D4 PB4

int main(void)
{
	DDRB = 1<<D0 | 1<<D1 | 1<<D2 | 1<<D3 | 1<<D4;

	while(1){
	 	if(!(PINB & (1<<S0)) )
		 	PORTB |= 1<<D0 | 1<<D1;
		else
			PORTB &= ~(1<<D0 | 1<<D1);

		if(! (PINB &(1<<S1)))
			PORTB |= 1<<D2;
		else
			PORTB &= ~(1<<D2);

		if(! (PINB &(1<<S2)))
			PORTB |= 1<<D3 | 1<<D4;
		else
			PORTB &=~(1<<D3 | 1<<D4);
	}
			 
	return 0;
}
