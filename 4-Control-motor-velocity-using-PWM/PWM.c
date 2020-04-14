#include		<avr/io.h>
#include		<avr/interrupt.h>

#define	DISP_INTERVAL	2
#define	OC0		PB4

volatile	unsigned	long	timer0;		// �����÷θ��� 1�� ������ ����
volatile	unsigned	int	number;
unsigned 	char led[] = {0x88, 0xBE, 0xC4, 0xA4, 0xB2, 0xA1, 0x83, 0xBC, 0x80, 0xB0};

// Ÿ�̸�/ī����0 ���ͷ�Ʈ ���� ��ƾ
ISR(TIMER0_OVF_vect)
{
	timer0++; // �����÷θ��� 1�� ����
	
	// �� �ڸ�7-���׸�Ʈ LED ���÷���
	if( timer0 % DISP_INTERVAL == 0){
		PORTC = (timer0 % (DISP_INTERVAL<<1) == 0) ? led[(number % 100) / 10] : led[number%10];
		PORTD = (PORTD |0xC0) & ~(1<<((timer0 % (DISP_INTERVAL<<1) == 0) ? PD7 : PD6));
	}
}

int	main(void)
{	
	DDRC = 0xFF;
	DDRD |= 1<<PD7 | 1<<PD6;	// �� �ڸ� 7-���׸�Ʈ LED�� �ѱ����� ���
	DDRB |= 1<<OC0;				// OC0 = PB4 ���
	
	TCCR0 = 1<<WGM01 | 1<<WGM00;			// ��� PWM ���� �߻����
	TCCR0 |= 1<<CS02 | 1<<CS01| 0<<CS00;	// ���������Ϸ� CS02:00 = (1,1,0) 256 ����
	TCCR0 |= 1<<COM01;						// TCNT0 0xFF���� 1, ��� ���� OCR0�� ��ġ�ϸ� 0
	
	TIMSK |= 1<<TOIE0;		// Ÿ�̸�/ī����0 ���ͷ�Ʈ Ȱ��ȭ
	
	timer0 = 0;
	sei();

	OCR0 = 100;
	number = OCR0*101/256;	// OCR0 ���� number ���� ��ġ 
	while(1);				// ���� loop
	
	return 0;
}

