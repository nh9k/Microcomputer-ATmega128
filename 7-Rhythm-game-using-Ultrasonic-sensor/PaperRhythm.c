#include	<stdio.h> // standard input output �������
#include	<avr/io.h> // avr�� input output �������
#include	<util/delay.h> // delay ���� ����ϱ� ����
#include 	<avr/interrupt.h>
#include	"lcd.h" // lcd.c�� �Լ����� ����ϱ� ���� �Լ����� ���ǵ� ������� ����
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

	//PB0~1 : ������ 1 ,  PB3~4 : ������ 2
	DDRB = 0x09; //PORTB = 0x12;
}
void MODE_1_2()
{
   TCCR1A=0x00; TCCR1B=0x08;    // CTC mode
   TCCR3A=0x00; TCCR3B=0x08;    // CTC mode
}
void Trigger1() //������ Ʈ���� ��ȣ
{
	//_delay_ms(1000);  //1���� Trigger ��ȣ ����`
    PORTB = 0x01;     //PB0 : Ʈ���� 
    _delay_ms(10);    //0.01���� ��ȣ ��                              
    PORTB = 0x00;   
}
void Trigger2() //������ Ʈ���� ��ȣ
{
	//_delay_ms(1000);  //1���� Trigger ��ȣ ����`
    PORTB = 0x08;     //PB0, PB3 : Ʈ���� 
    _delay_ms(10);    //0.01���� ��ȣ ��                              
    PORTB = 0x00;   
}
void Echo1()//�����ļ��� �� // PB1
{
	while(!(PINB&0x02));              // high�� �ɶ����� ��� //PULSE ����  
	TCNT1=0x00; TCCR1B=0x02;    // ī���� ����, 8���� = 0.5us
	while(PINB&0x02);                // low�� �ɶ����� ��� //PULSE ����
	TCCR1B=0x08;                // ī���� ����
	distance1=TCNT1/116;            // cm�� ����
}
void Echo2()//�����ļ��� �� // PB4
{
	while(!(PINB&0x10));              // high�� �ɶ����� ��� //PULSE ����  
	TCNT3=0x00; TCCR3B=0x02;    // ī���� ����, 8���� = 0.5us
	while(PINB&0x10);                // low�� �ɶ����� ��� //PULSE ����
	TCCR3B=0x08;                // ī���� ����
	distance2=TCNT3/116;            // cm�� ����
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
	LCD_init(); // LCD �ʱ�ȭ �Լ� ����
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
	return 0; // �����ϸ� ��ħ
}
