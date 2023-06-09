/* definitions / defines file */
#define DEFS_H

#define SW_VERSION		13   /* i.e. major.minor software version nbr. */

#ifndef NULL
#define NULL  0
#endif

#define LED1 PORTD.6        // PORTx is used for output
#define SW1 PIND.5          // PINx is used for input
#include "funct.h"

#define BUTON_ROSU PINA.0 
#define BUTON_ALBASTRU PINA.1 
#define BUTON_PORTOCALIU PINA.2 
#define BUTON_VERDE PINA.3 