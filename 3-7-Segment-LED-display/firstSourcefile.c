
#include	<avr/io.h>
#include	<avr/interrupt.h>

volatile	 unsigned  long	timer0;	  // �����÷θ��� 1�� ������ ����

volatile unsigned  int	number=0;	  // �����Ǿ� 7-���׸�Ʈ LED�� ���÷��̵� ����
unsigned char led[] = {0x88, 0xBE, 0xC4, 0xA4, 0xB2, 0xA1, 0x83, 0xBC, 0x80, 0xB0};


ISR(TIMER0_OVF_vect) // Ÿ�̸�/ī����0 ���ͷ�Ʈ ���� ��ƾ
{
	timer0++;		  // �����÷θ��� 1�� ����

    if(timer0 % 8 == 0){ // �����÷� Ƚ���� 16�� ����� �� 10�ڸ� Ȥ�� �� 8����� �� 1�ڸ� ���÷���
		PORTC = (timer0%16 == 0) ? led[(number%100) / 10] : led[number%10];
		PORTD = (PORTD |0xC0) & ~(1<<((timer0 % 16 == 0) ? PD7 : PD6));
		}
	
	if(timer0 >= 62500){ //256/16M *62500 = 1 => timer0�� 62500�� �Ǵ� ������ 1�ʰ� �Ǵ� ����
	number++;	//1�ʸ��� number ����
	timer0 = 0;  //1���� �ٽ� ��Ƹ��� ���� ����
	if(number==61) number=1; //60�ʰ� �� ���� 1�ʺ��� ���� 
	}
}

	
int	main(void)
{	
	DDRC = 0xFF;
	DDRD |= 1<<PD7 | 1<<PD6;    // �����ư��� 7-���׸�Ʈ LED�� �ѱ����� ���
	
	TCCR0 |=  1<<CS00;	 // NO ���������� ����(���ֺ� 1)
	TIMSK |= 1<<TOIE0;	 // Ÿ�̸�/ī����0 ���ͷ�Ʈ Ȱ��ȭ
	
	timer0 = 0; //Ÿ�̸� �����÷θ��� ���ŵǴ� ���� //���� ���� 0���� �ʱ�ȭ 
	sei(); // �۷ι� ���ͷ�Ʈ ��� 

	while(1);
	
	return 0;
}


