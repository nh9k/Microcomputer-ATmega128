#include	<avr/io.h>
#include	"lcd.h"

#define	RS	PD5	// LCD ���ڵ��÷��̿� ����� ��ƮD �� �ɹ�ȣ 
#define	RW	PD6
#define	E	PD7

void	gen_E_strobe(void)
{	volatile	int	i;

	PORTD |= 1<<E;		// E ��ȣ�� High��
	for(i=0; i<10; i++);		// E ��Ʈ�κ� ��ȣ�� �����Ⱓ High�� ����
	PORTD &= ~(1<<E);		// E ��ȣ�� Low��
}	

void	wait_BusyFlag(void)
{	volatile int 		i;
	unsigned char		bf;

	DDRC = 0x0;			// ��ƮC�� �Է������� ����
	PORTD = (PORTD & ~(1<<RS)) | 1<<RW; // RS <- Low, RW <- High
	do{
		PORTD |= 1<<E;		// E ��ȣ�� High��
		for(i=0; i<10; i++);	// E ��Ʈ�κ� ��ȣ�� �����Ⱓ High�� ����
		bf = PINC & 1<<PC7;	// busy flag �о� ��
		PORTD &= ~(1<<E);	// E ��ȣ�� Low��
	}while( bf );			// bf ���� 0�� �ƴϸ� busy, 0 �� ������ �ݺ�
}

void	LCD_command(unsigned char data)
{	wait_BusyFlag();		// busy flag�� 0�� ������ ���
	DDRC = 0xFF;			// ��ƮC�� ��������� ����
	PORTC = data;			// data ���
	PORTD &= ~(1<<RS | 1<<RW);	// RS <- 0, RW <-0
	gen_E_strobe();		// E ��Ʈ�κ� ��ȣ �����
}

void	LCD_data_write(unsigned char data)
{	wait_BusyFlag();
	DDRC = 0xFF;
	PORTC = data;
	PORTD = (PORTD | 1<<RS) & ~(1<<RW); // RS <- 1, RW <-0
	gen_E_strobe();
}

void	LCD_init(void)
{
	DDRD |= 1<<RS | 1<<RW | 1<<E;	// RS, RW, E ���� ��������� ����
	
	PORTD &= ~(1<<RS | 1<<E | 1<<RW); 	// �ʱ⿡ RS, E, RW <- 0

	LCD_command(0x3C);
	LCD_command(0x02);
	LCD_command(0x01);
	LCD_command(0x06);
	LCD_command(0x0F);
}

void	set_cursor(unsigned int row, unsigned int col)
{
	LCD_command(0x80 + (row % 2) * 0x40 + (col % 0x40));
}

// �Լ� ���� : row, col ��ġ���� ���ڿ� str �� LCD�� ��½�Ų��.
void	LCD_str_write(unsigned int row, unsigned int col, char *str)
{
	int	i;
	
	set_cursor(row, col);
	for(i=0; (i+col < MAX_LCD_STRING) && (str[i] != '\0'); i++)
		LCD_data_write(str[i]);
}
