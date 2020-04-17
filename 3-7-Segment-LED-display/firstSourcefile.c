
#include	<avr/io.h>
#include	<avr/interrupt.h>

volatile	 unsigned  long	timer0;	  // 오버플로마다 1씩 증가될 변수

volatile unsigned  int	number=0;	  // 증가되어 7-세그먼트 LED에 디스플레이될 숫자
unsigned char led[] = {0x88, 0xBE, 0xC4, 0xA4, 0xB2, 0xA1, 0x83, 0xBC, 0x80, 0xB0};


ISR(TIMER0_OVF_vect) // 타이머/카운터0 인터럽트 서비스 루틴
{
	timer0++;		  // 오버플로마다 1씩 증가

    if(timer0 % 8 == 0){ // 오버플로 횟수가 16의 배수일 때 10자리 혹은 의 8배수일 때 1자리 디스플레이
		PORTC = (timer0%16 == 0) ? led[(number%100) / 10] : led[number%10];
		PORTD = (PORTD |0xC0) & ~(1<<((timer0 % 16 == 0) ? PD7 : PD6));
		}
	
	if(timer0 >= 62500){ //256/16M *62500 = 1 => timer0가 62500이 되는 시점은 1초가 되는 시점
	number++;	//1초마다 number 증가
	timer0 = 0;  //1초후 다시 헤아리기 위해 갱신
	if(number==61) number=1; //60초가 된 이후 1초부터 시작 
	}
}

	
int	main(void)
{	
	DDRC = 0xFF;
	DDRD |= 1<<PD7 | 1<<PD6;    // 번갈아가며 7-세그먼트 LED를 켜기위한 출력
	
	TCCR0 |=  1<<CS00;	 // NO 프리스케일 설정(분주비 1)
	TIMSK |= 1<<TOIE0;	 // 타이머/카운터0 인터럽트 활성화
	
	timer0 = 0; //타이머 오버플로마다 갱신되는 변수 //시작 전에 0으로 초기화 
	sei(); // 글로벌 인터럽트 허용 

	while(1);
	
	return 0;
}


