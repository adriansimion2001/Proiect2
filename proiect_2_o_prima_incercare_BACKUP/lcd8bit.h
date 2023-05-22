
#ifndef lcd8bit
# define lcd8bit


#include <stdio.h>
#include <delay.h>  
#include <string.h> 
#include <stdlib.h>

#define F_CPU 20000000UL      // FCPU Definition for util/delay
#define _delay_ms delay_ms
#define _delay_us delay_us
/*LCD function declarations */
void LCD_send_command(unsigned char cmnd);
void LCD_send_data(unsigned char data);
void LCD_init(void);
void LCD_goto(unsigned char y, unsigned char x);
void LCD_print(char *string);
void LCD_blink(void);
void LCD_clear(void);

#define DATA_PORT	PORTB
#define DATA_DDR	DDRB

#define CNTRL_PORT	PORTD
#define CNTRL_DDR	DDRD


#define RS_PIN		4
#define RW_PIN		2
#define ENABLE_PIN	3



void LCD_send_command(unsigned char cmnd)   
{
	DATA_PORT = cmnd;
	CNTRL_PORT &= ~(1<< RW_PIN);    //initializare write
	CNTRL_PORT &= ~(1<< RS_PIN);    //initializare Rs pentru comenzi

	CNTRL_PORT |= (1<< ENABLE_PIN);
	_delay_us(2);
	CNTRL_PORT &= ~(1<< ENABLE_PIN);
	_delay_us(100);
}

/* This function sends the data 'data' to the LCD module*/
void LCD_send_data(unsigned char data)
{
	DATA_PORT = data;
	CNTRL_PORT &= ~(1<< RW_PIN);
	CNTRL_PORT |= (1<< RS_PIN);

	CNTRL_PORT |= (1<< ENABLE_PIN);
	_delay_us(2);
	CNTRL_PORT &= ~(1<< ENABLE_PIN);
	_delay_us(100);
}

void LCD_init()
{


	_delay_ms(10);
	LCD_send_command(0x38);
	LCD_send_command(0x0E);
	LCD_send_command(0x01);
	_delay_ms(10);
	LCD_send_command(0x06);
}

/* This function moves the cursor the line y column x on the LCD module*/

void LCD_goto(unsigned char y, unsigned char x)     //se duce la o pozitie dorita LCD_goto(2,3) =>linia 2, coloana 3
{
	unsigned char firstAddress[] = {0x80,0xC0,0x94,0xD4};

	LCD_send_command(firstAddress[y-1] + x-1);
	_delay_ms(10);
}

void LCD_print(char *string) //LCD_print("foame");
{

	while(*string > 0)
	{
		LCD_send_data(*string++);

	}
}

void LCD_blink()
{
	LCD_send_command(0x08);
	_delay_ms(250);
	LCD_send_command(0x0C);
	_delay_ms(250);
}



void LCD_clear(void)
{
LCD_send_command(0x01);
_delay_ms(100);

}

# endif
