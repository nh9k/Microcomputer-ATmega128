#include	<avr/io.h>
#include	<avr/interrupt.h>
#include	<stdio.h>
#include	"usart.h"

volatile unsigned char rx1_buffer[LENGTH_RX_BUFFER], tx1_buffer[LENGTH_TX_BUFFER];
volatile unsigned char rx1_head=0, rx1_tail=0, tx1_head=0, tx1_tail=0;

// 인터럽트 USART 초기화
void USART_init(unsigned char ch, unsigned int ubrr_baud)
{
	if( ch == USART0){
		UCSR0B |= 1<<RXEN0 | 1<<TXEN0 | 1<<RXC0;
		UBRR0H = ubrr_baud >> 8;
		UBRR0L = ubrr_baud;
	}else if(ch == USART1){
		UCSR1B |= 1<<RXEN1 | 1<<TXEN1| 1<<RXC1;
		UBRR1H = ubrr_baud >> 8;
		UBRR1L = ubrr_baud;
	}		
}

// 인터럽트에 의한 문자 전송 호출
int USART1_send(char data, FILE *stream)
{
	// txbuffer[] full, 한 개라도 빌 때까지 기다림
	while( (tx1_head+1==tx1_tail) || ((tx1_head==LENGTH_TX_BUFFER-1) && (tx1_tail==0)) );
	
	tx1_buffer[tx1_head] = data;
	tx1_head = (tx1_head==LENGTH_TX_BUFFER-1) ? 0 : tx1_head+1;
	UCSR1B = UCSR1B | 1<<UDRIE1;	// 보낼 문자가 있으므로 UDRE1 빔 인터럽트 활성화

	return data;
}

// USART1 UDR empty interrupt service
ISR(USART1_UDRE_vect)
{
	UDR1 = tx1_buffer[tx1_tail];
	tx1_tail = (tx1_tail==LENGTH_TX_BUFFER-1) ? 0 : tx1_tail+1;
	
	if( tx1_tail==tx1_head)		// 보낼 문자가 없으면 UDRE1 빔 인터럽트 비활성화
		UCSR1B = UCSR1B & ~(1<<UDRIE1);
}

// 인터럽트에 의한 문자 수신 호출
int USART1_receive(FILE *stream)
{	unsigned char data;
	
	while( rx1_head==rx1_tail );	// 수신 문자가 없음

	data = rx1_buffer[rx1_tail];
	rx1_tail = (rx1_tail==LENGTH_RX_BUFFER-1) ? 0 : rx1_tail + 1;
	
	return data;
}

// USART1 RXC interrupt service
ISR(USART1_RX_vect)
{	volatile unsigned char data;
	
	// rx_buffer[] full, 마지막 수신 문자 버림
	if( (rx1_head+1==rx1_tail) || ((rx1_head==LENGTH_RX_BUFFER-1) && (rx1_tail==0)) ){
		data = UDR1;
	}else{
		rx1_buffer[rx1_head] = UDR1;
		rx1_head = (rx1_head==LENGTH_RX_BUFFER-1) ? 0 : rx1_head+1;
	}
}

// USART1 receive char check
int	USART1_rx_check(void)	{	return (rx1_head != rx1_tail) ? 1 : 0;	}
