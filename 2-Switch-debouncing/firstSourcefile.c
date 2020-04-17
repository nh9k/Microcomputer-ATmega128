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
	DDRD = DDRD & ~(1<<PD0);	  // PD0�� �Է������� ����
	PORTD = PORTD | 1<<PD0;	  // �Է��� PD0�� ���� Ǯ���������� ����

	number = 0;
	before = RELEASED;
	
	while(1){
		display_7segled(digit, number % 10);
		
		if( before==RELEASED && !(PIND & 1<<PD0) ){    // ���� ������ ���� ���¿��� ó������ ����
			number++;
			before = PRESSED;
		}else if( before==PRESSED && (PIND & 1<<PD0) ){	// ���� ���� ���¿��� ó������ ������
			before = RELEASED;
		}
	}
	return 0;
}
