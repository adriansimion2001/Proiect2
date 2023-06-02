#include <mega164a.h>
#include "defs.h"
                                          
void Init_initController(void)
{
// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Port A initialization
PORTA=0x00; 
DDRA=0x00;  //set PORTA as input for colored buttons

// Port B initialization
PORTB=0x00; //initial values for PORTB
DDRB=0xFF; //set PORTB as output for DATA

// Port C initialization
PORTC=0x00;
DDRC=0x01; //C.0 RS Pin

// Port D initialization
PORTD=0b00100000; // D.5 needs pull-up resistor
DDRD= 0b01001100; // D.2 RW, D.3 Enable Pin, D.6 is LED



}


int verif(int v1[], int v2[], int dim1, int dim2){
int i;
     if(dim1!=dim2){ 
     return 0;
     }
    
     for(i=0; i<dim1; i++){
        if (v1[i] != v2[i]){
        return 0;
        }
     } 
     
     return 1;
}

#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif
