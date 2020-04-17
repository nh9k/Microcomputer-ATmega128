
#include   <avr/io.h>
#include   <avr/interrupt.h>

volatile unsigned long timer0;     // 오버플로마다 1씩 증가될 변수
volatile unsigned  int   number;     // 증가되어 7-세그먼트 LED에 디스플레이될 숫자

unsigned char led[] = {0x88, 0xBE, 0xC4, 0xA4, 0xB2, 0xA1, 0x83, 0xBC, 0x80, 0xB0};


ISR(TIMER0_OVF_vect)// 타이머/카운터0 인터럽트 서비스 루틴
{
   timer0++;        // 오버플로마다 1씩 증가
   
   // 오버플로 횟수가 4의 배수일 때 10자리 혹은 2의 배수일 때 1자리 디스플레이
   if(timer0 % 2 == 0){   
      PORTC = (timer0%4 == 0) ? led[(number%100) / 10] : led[number%10];
      PORTD = (PORTD |0xC0) & ~(1<<((timer0 % 4 == 0) ? PD7 : PD6));
   }
}
   
int main(void)
{   
   DDRC = 0xFF;
   DDRD |= 1<<PD7 | 1<<PD6;      // 번갈아가며 7-세그먼트 LED를 켜기위한 출력
   
   TCCR0 |= 1<<CS02 | 1<<CS01;   // 256 프리스케일 설정

   TIMSK |= 1<<TOIE0;      // 타이머/카운터0 인터럽트 활성화
   
   timer0 = 0; //타이머 오버플로마다 갱신되는 변수
   sei(); 

   number = 12; // 디스플레이할 숫자
   while(1);
   
   return 0;
}


