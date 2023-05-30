#ifndef lcd8bit
# define lcd8bit


#include <stdio.h>
#include <delay.h>  
#include <string.h> 
#include <stdlib.h>

#define F_CPU 20000000UL      // FCPU Definition for util/delay
#define _delay_ms delay_ms
#define _delay_us delay_us

#define RS_PIN		0   //Register select 0: commands/ 1: data 
#define RW_PIN		2   //0: Read / 1: Write
#define ENABLE_PIN	3   //0: Disable / 1: Enable
						//PORTD (0:7) reserved for DATA



void LCD_send_command(unsigned char cmnd)      //Send comands to display
{
	PORTB = cmnd;
	PORTD &= ~(1<< RW_PIN);    //LCD set for write
	PORTC &= ~(1<< RS_PIN);    //LCD set for send commands

	PORTD |= (1<< ENABLE_PIN); //LCD ENABLE_PIN = 1;
	_delay_us(2);
	PORTD &= ~(1<< ENABLE_PIN);//LCD ENABLE_PIN = 0;
	_delay_us(100);
}


void LCD_send_data(unsigned char data)     //Send ascii characters to display
{
	PORTB = data;
	PORTD &= ~(1<< RW_PIN);		//LCD set for writre 
	PORTC |= (1<< RS_PIN);		//LCD set for send data

	PORTD |= (1<< ENABLE_PIN);	//LCD ENABLE_PIN = 1;
	_delay_us(2);
	PORTD &= ~(1<< ENABLE_PIN); //LCD ENABLE_PIN = 0;
	_delay_us(100);
}

void LCD_init()                 //Initiate the screen
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


void LCD_clear(void)        //Clear the LCD screen
{
LCD_send_command(0x01);
_delay_ms(100);

}

# endif
