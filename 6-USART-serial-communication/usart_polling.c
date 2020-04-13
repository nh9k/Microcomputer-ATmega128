#include	<avr/io.h>
#include	"usart.h"

// 폴링 USART 초기화
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

// 폴링에 의한 문자 전송
int USART1_send(char data, FILE *stream)
{	
	while ( !( UCSR1A & (1<<UDRE1)) );	// UDR 레지스터가 빌 때까지 폴링한다.
	UDR1 = data;			// UDR 레지스터에 값을 기록한다.
	return data;
}

// 폴링에 의한 문자 수신
int USART1_receive(FILE *stream)
{
	while ( !(UCSR1A & (1<<RXC1)) );	// UDR 레지스터에 문자 수신 검사
	return UDR1;
}
