/*********************************************
Project : Test software
**********************************************
Chip type: ATmega164A
Clock frequency: 20 MHz
Compilers:  CVAVR 2.x
*********************************************/

#include <mega164a.h>
#include <stdio.h>
#include <delay.h>  
#include <string.h> 
#include <stdlib.h>
#include <lcd8bit.h>
#include "defs.h"    

//*************************************************************************************************
//*********** BEGIN SERIAL STUFF (interrupt-driven, generated by Code Wizard) *********************
//*************************************************************************************************

#ifndef RXB8
#define RXB8 1
#endif

#ifndef TXB8
#define TXB8 0
#endif

#ifndef UPE
#define UPE 2
#endif

#ifndef DOR
#define DOR 3
#endif

#ifndef FE
#define FE 4
#endif

#ifndef UDRE
#define UDRE 5
#endif

#ifndef RXC
#define RXC 7
#endif

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// USART0 Receiver buffer
#define RX_BUFFER_SIZE0 8
char rx_buffer0[RX_BUFFER_SIZE0];

#if RX_BUFFER_SIZE0 <= 256
unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
#else
unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
#endif

// This flag is set on USART0 Receiver buffer overflow
bit rx_buffer_overflow0;

// USART0 Receiver interrupt service routine
interrupt [USART0_RXC] void usart0_rx_isr(void)
{
char status,data;
status=UCSR0A;
data=UDR0;
if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {
   rx_buffer0[rx_wr_index0++]=data;
#if RX_BUFFER_SIZE0 == 256
   // special case for receiver buffer size=256
   if (++rx_counter0 == 0) rx_buffer_overflow0=1;
#else
   if (rx_wr_index0 == RX_BUFFER_SIZE0) rx_wr_index0=0;
   if (++rx_counter0 == RX_BUFFER_SIZE0)
      {
      rx_counter0=0;
      rx_buffer_overflow0=1;
      }
#endif
   }
}

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART0 Receiver buffer
#define _ALTERNATE_GETCHAR_
#pragma used+
char getchar(void)
{
char data;
while (rx_counter0==0);
data=rx_buffer0[rx_rd_index0++];
#if RX_BUFFER_SIZE0 != 256
if (rx_rd_index0 == RX_BUFFER_SIZE0) rx_rd_index0=0;
#endif
#asm("cli")
--rx_counter0;
#asm("sei")
return data;
}
#pragma used-
#endif

// USART0 Transmitter buffer
#define TX_BUFFER_SIZE0 8
char tx_buffer0[TX_BUFFER_SIZE0];

#if TX_BUFFER_SIZE0 <= 256
unsigned char tx_wr_index0,tx_rd_index0,tx_counter0;
#else
unsigned int tx_wr_index0,tx_rd_index0,tx_counter0;
#endif

// USART0 Transmitter interrupt service routine
interrupt [USART0_TXC] void usart0_tx_isr(void)
{
if (tx_counter0)
   {
   --tx_counter0;
   UDR0=tx_buffer0[tx_rd_index0++];
#if TX_BUFFER_SIZE0 != 256
   if (tx_rd_index0 == TX_BUFFER_SIZE0) tx_rd_index0=0;
#endif
   }
}

#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART0 Transmitter buffer
#define _ALTERNATE_PUTCHAR_
#pragma used+
void putchar(char c)
{
while (tx_counter0 == TX_BUFFER_SIZE0);
#asm("cli")
if (tx_counter0 || ((UCSR0A & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer0[tx_wr_index0++]=c;
#if TX_BUFFER_SIZE0 != 256
   if (tx_wr_index0 == TX_BUFFER_SIZE0) tx_wr_index0=0;
#endif
   ++tx_counter0;
   }
else
   UDR0=c;
#asm("sei")
}
#pragma used-
#endif
//*************************************************************************************************
//********************END SERIAL STUFF (USART0)  **************************************************
//*************************************************************************************************
//*******   if you need USART1, enable it in Code Wizard and copy coresponding code here  *********
//*************************************************************************************************

/*
 * Timer 1 Output Compare A interrupt is used to blink LED
 */
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
LED1 = ~LED1; // invert LED    
}                                  
    void blink(int n){ 
    LED1=1;  
    delay_ms(n);
    LED1=0;
   delay_ms(n);    
 }      
 void aprindere(int n)
 {            
    n-=48;
    while(n){      
    blink(500);
    n--;
    }
    
 }
/*
 * main function of program
 */
 
// unsigned int ADC_read()
//
//{
//
//
//ADMUX = 0x40;        //channel A0 selected
//
//ADCSRA|=0xC0;   // start conversion
//
//while(ADCSRA==0xC0);   // wait for ADIF conversion complete return
////
//ADCSRA =ADCSRA & 0x10;   // clear ADIF when conversion complete by writing 1
////
//return (ADCH); //return calculated ADC value
//
//}






// functie pentru citirea valorii de pe pinul AD0
void ADC_read()
{
  
  ADMUX = 0x60; // referinta este AVCC cu capacitor extern la AREF pin
  ADCSRA = 0x87; // activare ADC, setare divizor prescaler la 128
  ADCSRA |= 0x40; // incepere conversie
  while (ADCSRA == 0xC0); // asteptare finalizare conversie
  printf("%d ",ADCH);
}

int* random_generator(int lower, int upper, int count)
{
    int i=0;
    int *v;
    v=(int*) malloc(count * sizeof(int));
    for(i=0; i<count; i++){
        int num = (rand() %(upper - lower + 1)) + lower;
        v[i]=num;
    }
    
    return v;      
}

char *inttochar(int n){

return (char*) n;
}
void main (void)
{  
      
int i=0;
int cnt=3;
int j=0;
int* random;
srand(3); 

	Init_initController();  // this must be the first "init" action/call!
	#asm("sei")             // enable interrupts
	//LED1 = 0;           	// initial state, will be changed by timer 1
    CNTRL_DDR = 0xFF;
	CNTRL_PORT = 0x00;
	DATA_DDR = 0xFF;
	DATA_PORT = 0x00; 

    LCD_init();
	LCD_clear();
   
//	LCD_goto(1,2);

    delay_ms(1000);               
      while(1){
       // random=(int*)malloc(cnt * sizeof(int));   
        random = random_generator(0,4, cnt);  
    for(i=0; i<cnt; i++){
    switch (random[i])
           {
           case 1:
              LCD_print("Rosu");  
              delay_ms(1000);
           break;

           case 2:
              LCD_print("Albastru");  
              delay_ms(1000);
           break;   
           case 3:
              LCD_print("Verde");  
              delay_ms(1000);
           break; 
           case 4:
              LCD_print("Galben");  
              delay_ms(1000);
           break;
            
           case 0:
              LCD_print("Mov");  
              delay_ms(1000);
           break; 
            default:
                 LCD_print(inttochar(random[i]));  
              delay_ms(1000);
            break;
           } 
           LCD_clear();
    }   
    delay_ms(5000);
    cnt++; 
    free(random);   
    }



}
    
    
     
    

            
// end main loop 


