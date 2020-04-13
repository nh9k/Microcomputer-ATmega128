#include<avr/io.h>
#include<stdio.h>
#include <util/delay.h> 

#include"lcd.h"
#include"usart.h"

#define D0 PB0 
#define D1 PB2
#define D2 PB4 

int main(void) // main �Լ�
{
 	DDRB |= (1<<D0)|(1<<D1)|(1<<D2);
 	char lcd_string[2][MAX_LCD_STRING];

 	LCD_init();
 	USART_init(USART1, 12);// USART1 ��������Ʈ : 38400(UBRR=12), 8MHz

	sprintf(lcd_string[0], "   Flag Game   ");// LCD�� ���
	LCD_str_write(0, 0, lcd_string[0]);

	int question[5] = {0,1,0,0,1};

	for(int i=0;i<5;i++)
	{
		sprintf(lcd_string[0], " Send : %d",question[i]);// LCD�� ���
		LCD_str_write(1, 0, lcd_string[0]);
 
		if(question[i]==0){ PORTB |= (1<<D0); PORTB &= ~(1<<D1);}
		else { PORTB &= ~(1<<D0); PORTB |= (1<<D1);}
    	
		_delay_ms(1000); // �ٷ� �۽ŵǴ� ���� �����ϱ� ���� 5�� delay
    	USART1_send(question[i],0); // �����̿��� �۽�
		PORTB &= ~((1<<D0)|(1<<D1)); 
 		_delay_ms(50);
    }
        sprintf(lcd_string[0], "Complete : %d%d%d%d%d",question[0],question[1],question[2],question[3],question[4]);// LCD�� ���
		LCD_str_write(1, 0, lcd_string[0]);
		PORTB |= (1<<D2); PORTB &= ~((1<<D0)|(1<<D1)); 
 

	return 0;
}
