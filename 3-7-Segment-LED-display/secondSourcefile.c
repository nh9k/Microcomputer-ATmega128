
#include   <avr/io.h>
#include   <avr/interrupt.h>

volatile unsigned long timer0;     // �����÷θ��� 1�� ������ ����
volatile unsigned  int   number;     // �����Ǿ� 7-���׸�Ʈ LED�� ���÷��̵� ����

unsigned char led[] = {0x88, 0xBE, 0xC4, 0xA4, 0xB2, 0xA1, 0x83, 0xBC, 0x80, 0xB0};


ISR(TIMER0_OVF_vect)// Ÿ�̸�/ī����0 ���ͷ�Ʈ ���� ��ƾ
{
   timer0++;        // �����÷θ��� 1�� ����
   
   // �����÷� Ƚ���� 4�� ����� �� 10�ڸ� Ȥ�� 2�� ����� �� 1�ڸ� ���÷���
   if(timer0 % 2 == 0){   
      PORTC = (timer0%4 == 0) ? led[(number%100) / 10] : led[number%10];
      PORTD = (PORTD |0xC0) & ~(1<<((timer0 % 4 == 0) ? PD7 : PD6));
   }
}
   
int main(void)
{   
   DDRC = 0xFF;
   DDRD |= 1<<PD7 | 1<<PD6;      // �����ư��� 7-���׸�Ʈ LED�� �ѱ����� ���
   
   TCCR0 |= 1<<CS02 | 1<<CS01;   // 256 ���������� ����

   TIMSK |= 1<<TOIE0;      // Ÿ�̸�/ī����0 ���ͷ�Ʈ Ȱ��ȭ
   
   timer0 = 0; //Ÿ�̸� �����÷θ��� ���ŵǴ� ����
   sei(); 

   number = 12; // ���÷����� ����
   while(1);
   
   return 0;
}


