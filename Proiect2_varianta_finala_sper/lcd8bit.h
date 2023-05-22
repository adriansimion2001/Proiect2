#ifndef lcd8bit
# define lcd8bit


#include <stdio.h>
#include <delay.h>  
#include <string.h> 
#include <stdlib.h>

#define F_CPU 20000000UL      // FCPU Definition for util/delay
#define _delay_ms delay_ms
#define _delay_us delay_us

#define RS_PIN		4
#define RW_PIN		2
#define ENABLE_PIN	3



void LCD_send_command(unsigned char cmnd)      //send comands to display
{
	PORTB = cmnd;
	PORTD &= ~(1<< RW_PIN);    //initializare write
	PORTD &= ~(1<< RS_PIN);    //initializare Rs pentru comenzi

	PORTD |= (1<< ENABLE_PIN);
	_delay_us(2);
	PORTD &= ~(1<< ENABLE_PIN);
	_delay_us(100);
}


void LCD_send_data(unsigned char data)     //send ascii characters to display
{
	PORTB = data;
	PORTD &= ~(1<< RW_PIN);
	PORTD |= (1<< RS_PIN);

	PORTD |= (1<< ENABLE_PIN);
	_delay_us(2);
	PORTD &= ~(1<< ENABLE_PIN);
	_delay_us(100);
}

void LCD_init()                 // initiate the screen
{
	_delay_ms(10);
	LCD_send_command(0x38);
	LCD_send_command(0x0E);
	LCD_send_command(0x01);
	_delay_ms(10);
	LCD_send_command(0x06);
}


void LCD_goto(unsigned char y, unsigned char x)     //LCD_goto(y,x) =>row x, column y
{
	unsigned char firstAddress[] = {0x80,0xC0,0x94,0xD4};

	LCD_send_command(firstAddress[y-1] + x-1);
	_delay_ms(10);
}

void LCD_print(char *string) //Print string on screen
{

	while(*string > 0)
	{
		LCD_send_data(*string++);

	}
}


void LCD_clear(void)        //clear the screen
{
LCD_send_command(0x01);
_delay_ms(100);

}

# endif
