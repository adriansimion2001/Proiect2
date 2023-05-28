/*********************************************
Project : Test software
**********************************************
Chip type: ATmega164A
Clock frequency: 20 MHz
Compilers:  CVAVR 2.x
*********************************************/

#include <mega164a.h>

#include <delay.h>  
#include <string.h> 
#include <stdlib.h>
#include <lcd8bit.h>
#include "defs.h"    

void main (void)
{          
    int timp=0;
    int max=0;
    int v_inreg[30];  
    int i=0;
    int cnt=1;
    int j=0;
    int contor_v=0;
    int random[30];
    srand(3); 
    Init_initController();  
    LED1 = 1;               //The high value of led indicate indicate if the game is powered on
    LCD_init();
    LCD_clear();
 
while(1){                          //Level select

        LCD_print("Apasa orice buton");
         while(1){
            delay_ms(100);   
            if(!BUTON_VERDE){      
            LCD_clear();
            break;}   
            if(!BUTON_PORTOCALIU){      
            LCD_clear();
            break;}
            if(!BUTON_ALBASTRU){      
            LCD_clear();
            break;}
            if(!BUTON_ROSU){      
            LCD_clear();
            break;}
            
         }   
        
        LCD_print("Selecteaza"); 
        LCD_goto(2,1);
        LCD_print("dificultatea");
        delay_ms(2000);
        LCD_clear();
        LCD_print("Verde -> Usor");  
        LCD_goto(2,1);     
        LCD_print("Portocaliu -> Mediu");  
        LCD_goto(3,1);  
        LCD_print("Albastru -> Greu");  
        LCD_goto(4,1);  
        LCD_print("Rosu -> Foarte Greu");  
      
            while(1){
            delay_ms(100);   
            if(!BUTON_VERDE){
             delay_ms(500);
             LCD_clear();  
             timp=1000;
             max=5;
             cnt=3;
            break;
         } 
             
        if(!BUTON_PORTOCALIU){
             delay_ms(500);
             LCD_clear();  
             timp=900;
             max=6;
             cnt=4;
            break;
         } 
             
             
          if(!BUTON_ALBASTRU){
             delay_ms(500);
             LCD_clear();  
             timp=800;
             max=9;
             cnt=5;
            break;
         }
             
           if(!BUTON_ROSU){
             delay_ms(500);
             LCD_clear();  
             timp=800;
             max=10;
             cnt=6;
            break;  
        }
            
        }
    while(1){                   //Display the color sequence 
    if(cnt>max) break;
    for(i=0;i<cnt;i++){  
       random[i] = rand() % 4;
    }        
        for(i=0; i<cnt; i++){
            switch (random[i])
                {
           case 0:
              LCD_print("Verde");  
              delay_ms(timp);
           break;

           case 1:
              LCD_print("Portocaliu");  
              delay_ms(timp);
           break;   
           case 2:
              LCD_print("Albastru");  
              delay_ms(timp);
           break; 
           case 3:
              LCD_print("Rosu");  
              delay_ms(timp);
           break;
            
            default:
                 LCD_print("Eroare");  
              delay_ms(1000);
            break;
           } 
           LCD_clear();
    }   
        contor_v=0;
        LCD_print("Introdu secventa:"); //Wait for user to introduce the sequence in order
        delay_ms(1000);
        LCD_clear();
        for(i=0; i<cnt*10;i++ ){
             delay_ms(100);
             if(!BUTON_VERDE){v_inreg[contor_v]=0; contor_v++; LCD_print("Verde"); delay_ms(300); LCD_clear();}
             else if(!BUTON_PORTOCALIU){v_inreg[contor_v]=1; contor_v++; LCD_print("Portocaliu"); delay_ms(300); LCD_clear();}   
             else if(!BUTON_ALBASTRU){v_inreg[contor_v]=2;contor_v++; LCD_print("Albastru"); delay_ms(300); LCD_clear();   }
             else if(!BUTON_ROSU){v_inreg[contor_v]=3;contor_v++; LCD_print("Rosu"); delay_ms(300); LCD_clear();      
             }
        }
        LCD_clear();
          if(!verif(random, v_inreg, cnt, contor_v)){  //Verify if the user entered the sequence wrong
            LCD_print("Ai esuat!"); 
            delay_ms(1000);   
            LCD_clear();
            break;     //If the sequence was wrong, the player jump to the select level menu
          }
          else  {LCD_print("Felicitari!");  delay_ms(1000); LCD_clear();   //If the sequence was right, the player pass to the next level
          }
        cnt++; 
        }      
    }           
}


