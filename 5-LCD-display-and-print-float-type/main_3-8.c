#include	<stdio.h>
#include	<avr/io.h>
#include <avr/interrupt.h> // ���ͷ�Ʈ ���� �������

#define	F_CPU	8000000
#include	<util/delay.h>
#include	"lcd.h"

#define S0 PD0 // S�� Switch, PD0 ���� Ǯ�� ������ �޸� ����ġ�� ��� 
#define D0 PB0 // D�� Diode, PB0 ���� 330�� ������ �޸� LED�� ���
#define string_num 4
volatile int state = 0; // ���ͷ�Ʈ ����� ���� Volatile ���� 

ISR(INT0_vect) //Interrupt Service Routine: ���ͷ�Ʈ�� ȣ��Ǿ��� �� ����Ǵ� ��ƾ
{	
	state++; //state�� � LED�� ���� ���� 
}

void INIT_PORT(void) //PORT �ʱ�ȭ �Լ�
{
 DDRB = 1<<D0; //PORT B�� 0�� PIN�� ���̿���� ����ϱ� ���� ������� ����
 DDRD = 0<<S0; //PORT D�� ���ͷ�Ʈ�� ����� ����ġ��, PD0 PIN�� �Է����� ����
 PORTD = 1<<S0; // PD0 PIN�� Ǯ�� ���� ���
}	

void INIT_INT0(void) //���ͷ�Ʈ �ʱ�ȭ �Լ�
{
	EIMSK |= (1<<INT0); //INT0 ���, ���ͷ�Ʈ ����ũ �������� : ���ͷ�Ʈ Ȱ��ȭ
	EICRA |= (1<<ISC01); //���ͷ�Ʈ ��Ʈ�� �������� : �ϰ� �������� ���ͷ�Ʈ �߻�
	sei(); // ���������� ���ͷ�Ʈ ���, SREG |= 0x80;
}

int	main(void)
{	
	INIT_PORT(); //��Ʈ ����
	INIT_INT0(); //INT0 ���ͷ�Ʈ ����

	LCD_init();

    char *string[] = {"line 1","line 2","hello!","nice!"};
    int r=0, c=0, save=0;

	while(1){
		if(state!=save){
			PORTB |= (1<<D0);
 			while(r<string_num){
				while(c<16){
					if(string[r][c]=='\0'){
						if(r%2==0) {LCD_command(0xc0);}
						else {LCD_command(0x01); LCD_command(0x80);}
						r++; c=0; 
					 break;
					}
					else  { 
					     LCD_data_write(string[r][c]); _delay_ms(1000);	 
						 c++; save=state; 
					 break;
					}
				}
		
	   		 break;
	  	    }
	    }
		else PORTB &= ~(1<<D0);
	}
	return 0;
}
