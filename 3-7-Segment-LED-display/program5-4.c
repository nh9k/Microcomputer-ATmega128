#include		<avr/io.h>

#define	PRESSED		1
#define	RELEASED		0

unsigned char digit[] = {0x88, 0xBE, 0xC4, 0xA4, 0xB2, 0xA1, 0x83, 0xBC, 0x80, 0xB0};

void	display_7segled(unsigned char led[], unsigned int number)
{	PORTC = led[number];	}

int	main(void)
{
	int	number;
	int	before;
	
	DDRC = 0xFF;
	DDRD = DDRD & ~(1<<PD0);	  // PD0를 입력핀으로 설정
	PORTD = PORTD | 1<<PD0;	  // 입력핀 PD0를 내부 풀업저항으로 연결

	number = 0;
	before = RELEASED;
	
	while(1){
		display_7segled(digit, number % 10);
		
		if( before==RELEASED && !(PIND & 1<<PD0) ){    // 전에 눌리지 않은 상태에서 처음으로 눌림
			number++;
			before = PRESSED;
		}else if( before==PRESSED && (PIND & 1<<PD0) ){	// 전에 눌린 상태에서 처음으로 떨어짐
			before = RELEASED;
		}
	}
	return 0;
}
