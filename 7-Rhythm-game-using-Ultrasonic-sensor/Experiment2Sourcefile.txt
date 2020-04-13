#include	<stdio.h> // standard input output 헤더파일
#include	<avr/io.h> // avr의 input output 헤더파일
#include	<util/delay.h> // delay 구문 사용하기 위함
#include 	<avr/interrupt.h>
#include	"lcd.h" // lcd.c의 함수들을 사용하기 위한 함수들이 정의된 헤더파일 선언
#define	RED PA4
#define WHITE PA5
#define GREEN PA6
#define YELLOW PA7
char lcd_string[2][MAX_LCD_STRING];

#define	boundary_dist10 10

unsigned int distance1;
unsigned int distance2;

unsigned int Q;
unsigned int QQ;
#define	Q1 1
#define Q2 2
#define Q3 3
#define Q4 4

void PORT_init()
{
	//PA4~7 : LED
	DDRA = 0xF0; 

	//PB0~1 : 초음파 1 ,  PB3~4 : 초음파 2
	DDRB = 0x09; //PORTB = 0x12;
}
void MODE_1_2()
{
   TCCR1A=0x00; TCCR1B=0x08;    // CTC mode
   TCCR3A=0x00; TCCR3B=0x08;    // CTC mode
}
void Trigger1() //초음파 트리거 신호
{
	//_delay_ms(1000);  //1초후 Trigger 신호 보냄`
    PORTB = 0x01;     //PB0 : 트리거 
    _delay_ms(10);    //0.01초후 신호 끝                              
    PORTB = 0x00;   
}
void Trigger2() //초음파 트리거 신호
{
	//_delay_ms(1000);  //1초후 Trigger 신호 보냄`
    PORTB = 0x08;     //PB0, PB3 : 트리거 
    _delay_ms(10);    //0.01초후 신호 끝                              
    PORTB = 0x00;   
}
void Echo1()//초음파센서 값 // PB1
{
	while(!(PINB&0x02));              // high가 될때까지 대기 //PULSE 시작  
	TCNT1=0x00; TCCR1B=0x02;    // 카운터 시작, 8분주 = 0.5us
	while(PINB&0x02);                // low가 될때까지 대기 //PULSE 종료
	TCCR1B=0x08;                // 카운터 정지
	distance1=TCNT1/116;            // cm로 변경
}
void Echo2()//초음파센서 값 // PB4
{
	while(!(PINB&0x10));              // high가 될때까지 대기 //PULSE 시작  
	TCNT3=0x00; TCCR3B=0x02;    // 카운터 시작, 8분주 = 0.5us
	while(PINB&0x10);                // low가 될때까지 대기 //PULSE 종료
	TCCR3B=0x08;                // 카운터 정지
	distance2=TCNT3/116;            // cm로 변경
}
void LED(int led1, int led2)
{
    //RED : PE3  ,  WHITE : PE4   ,  GREEN : PE5   ,   YELLOW : PE6
	if(led2==0){
	
	if(led1==1) {PORTA = ~((1<< WHITE)|(1<< GREEN)|(1<< YELLOW)); PORTA = 1<< RED; }
	else if(led1==2){PORTA &= ~((1<< RED)|(1<< GREEN)|(1<< YELLOW)); PORTA |= 1<< WHITE;  }
	else if(led1==3){PORTA &= ~((1<< RED)|(1<< WHITE)|(1<< YELLOW)); PORTA |= 1<< GREEN; }
    else if(led1==4){PORTA &= ~((1<< RED)|(1<< WHITE)|(1<< GREEN)); PORTA |= 1<< YELLOW; }
	else {  PORTA &= ~((1<< RED)|(1<< WHITE)|(1<< GREEN)|(1<< YELLOW));  }

	}
	else{
     if(led1==1 && led2==2) {PORTA = ~((1<< GREEN)|(1<< YELLOW)); PORTA = (1<< RED) | (1<< WHITE); }
	else if(led1==1 && led2==3){PORTA = ~((1<< WHITE)|(1<< YELLOW)); PORTA = (1<< RED) | (1<< GREEN);  }
	else if(led1==4 && led2==2){PORTA = ~((1<< GREEN)|(1<< RED)); PORTA = (1<< YELLOW) | (1<< WHITE); }
    else if(led1==4 && led2==3){PORTA = ~((1<< RED) | (1<< WHITE)); PORTA = (1<< GREEN)|(1<< YELLOW); }
	//else {  PORTA &= ~((1<< RED)|(1<< WHITE)|(1<< GREEN)|(1<< YELLOW));  }

	}
}
void START_SIGN(int level)
{   
    _delay_ms(3000);  LED(5,0); 
    LCD_command(0x01);

 	if(level == 1) sprintf(lcd_string[0], "  LEVEL1 START  "); 
    else       sprintf(lcd_string[0], "  LEVEL2 START  "); 
    
	LCD_str_write(0, 0, lcd_string[0]); _delay_ms(3000);
}
void Question(int position)
{
		sprintf(lcd_string[0], "********"); 

		if(position==1) LCD_str_write(0, 0, lcd_string[0]);
		else if(position==2) LCD_str_write(0, 8, lcd_string[0]); 
	    else if(position==3) LCD_str_write(1, 0, lcd_string[0]); 
		else if(position==4) LCD_str_write(1, 8, lcd_string[0]); 
}
void Rhythm(int Q, int QQ, int speed)
{
  	 LCD_command(0x01);

     if(QQ == 0){
      
	    Question(Q); _delay_ms(speed); 
 		Trigger1(); Echo1(); 
		Trigger2(); Echo2();

     	 if(Q==Q1)
	 	 { 
			if(distance1 > boundary_dist10) LED(4,0); 
				else{  for(int i=0;i<3;i++){ LED(1,0); _delay_ms(100);  LED(5,0);  _delay_ms(100); } }
       	 }

	  	 else if(Q==Q2)
	  	 {
			if(distance2 > boundary_dist10) LED(3,0); 
			else{  for(int i=0;i<3;i++){ LED(1,0); _delay_ms(100);  LED(5,0);  _delay_ms(100); } }
	  	 }
      
	 	 else if(Q==Q3)
	  	 { 
			if(distance1 < boundary_dist10) LED(1,0); 
		else{  for(int i=0;i<3;i++){ LED(1,0); _delay_ms(100);  LED(5,0);  _delay_ms(100); } }
	     }

	     else if(Q==Q4)
	     { 
			if(distance2 < boundary_dist10) LED(2,0); 
			else{  for(int i=0;i<3;i++){ LED(1,0); _delay_ms(100);  LED(5,0);  _delay_ms(100); } }
	     }
	 }
	 else{
     
	    Question(Q); Question(QQ); _delay_ms(speed); 
 		Trigger1(); Echo1(); 
		Trigger2(); Echo2();

     	 if(Q==Q1 && QQ==Q2)
	 	 { 
			if(distance1 > boundary_dist10 && distance2 > boundary_dist10){ LED(4,3);  }
				else{  for(int i=0;i<3;i++){ LED(1,0); _delay_ms(100);  LED(5,0);  _delay_ms(100); } }
       	 }

	  	 else if(Q==Q1 && QQ==Q4)
	  	 {
			if(distance1 > boundary_dist10 && distance2 < boundary_dist10){ LED(4,2); }
			else{  for(int i=0;i<3;i++){ LED(1,0); _delay_ms(100);  LED(5,0);  _delay_ms(100); } }
	  	 }
      
	 	  else if(Q==Q3 && QQ==Q2)
	  	 {
			if(distance1 < boundary_dist10 && distance2 > boundary_dist10){ LED(1,3); }
		else{  for(int i=0;i<3;i++){ LED(1,0); _delay_ms(100);  LED(5,0);  _delay_ms(100); } }
	  	 }

	     else if(Q==Q3 && QQ==Q4)
	  	 {
			if(distance1 < boundary_dist10 && distance2 < boundary_dist10){ LED(1,2); } 
			else{  for(int i=0;i<3;i++){ LED(1,0); _delay_ms(100);  LED(5,0);  _delay_ms(100); } }
	  	 }
	 }

}

int	main(void) 
{
	LCD_init(); // LCD 초기화 함수 선언
	PORT_init();
	MODE_1_2();
   

	while(1){ 
  
	  int speed = 1000;

	  START_SIGN(1);

	  Rhythm(1, 0, speed);
	  Rhythm(2, 0, speed);
	  Rhythm(3, 0, speed);
	  Rhythm(4, 0, speed);



      START_SIGN(2);
	 
   	  Rhythm(1, 2, speed);
	  Rhythm(1, 4, speed);
	  Rhythm(3, 2, speed);
	  Rhythm(3, 4, speed);
		
	}
	return 0; // 종료하며 마침
}
