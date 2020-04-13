#include	<stdio.h>
#include	<avr/io.h>
#include <avr/interrupt.h> // 인터럽트 관련 헤더파일

#define	F_CPU	8000000
#include	<util/delay.h>
#include	"lcd.h"

#define S0 PD0 // S는 Switch, PD0 핀을 풀업 저항이 달린 스위치로 사용 
#define D0 PB0 // D는 Diode, PB0 핀을 330옴 저항이 달린 LED로 사용
#define string_num 4
volatile int state = 0; // 인터럽트 사용을 위한 Volatile 변수 

ISR(INT0_vect) //Interrupt Service Routine: 인터럽트가 호출되었을 시 실행되는 루틴
{	
	state++; //state로 어떤 LED를 켤지 결정 
}

void INIT_PORT(void) //PORT 초기화 함수
{
 DDRB = 1<<D0; //PORT B의 0번 PIN을 다이오드로 사용하기 위한 출력으로 설정
 DDRD = 0<<S0; //PORT D를 인터럽트를 사용한 스위치로, PD0 PIN을 입력으로 설정
 PORTD = 1<<S0; // PD0 PIN의 풀업 저항 사용
}	

void INIT_INT0(void) //인터럽트 초기화 함수
{
	EIMSK |= (1<<INT0); //INT0 사용, 인터럽트 마스크 레지스터 : 인터럽트 활성화
	EICRA |= (1<<ISC01); //인터럽트 컨트롤 레지스터 : 하강 엣지에서 인터럽트 발생
	sei(); // 전역적으로 인터럽트 허용, SREG |= 0x80;
}

int	main(void)
{	
	INIT_PORT(); //포트 설정
	INIT_INT0(); //INT0 인터럽트 설정

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
