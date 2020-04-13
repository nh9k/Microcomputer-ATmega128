#include	<avr/io.h>
#include	"usart.h"

// ���� USART �ʱ�ȭ
void USART_init(unsigned char ch, unsigned int ubrr_baud)
{
	if( ch == USART0){
		UCSR0B |= 1<<RXEN0 | 1<<TXEN0;
		UBRR0H = ubrr_baud >> 8;
		UBRR0L = ubrr_baud;
	}else if(ch == USART1){
		UCSR1B |= 1<<RXEN1 | 1<<TXEN1;
		UBRR1H = ubrr_baud >> 8;
		UBRR1L = ubrr_baud;
	}		
}

// ������ ���� ���� ����
int USART1_send(char data, FILE *stream)
{	
	while ( !( UCSR1A & (1<<UDRE1)) );	// UDR �������Ͱ� �� ������ �����Ѵ�.
	UDR1 = data;			// UDR �������Ϳ� ���� ����Ѵ�.
	return data;
}

// ������ ���� ���� ����
int USART1_receive(FILE *stream)
{
	while ( !(UCSR1A & (1<<RXC1)) );	// UDR �������Ϳ� ���� ���� �˻�
	return UDR1;
}
