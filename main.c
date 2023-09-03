
#include <LPC21xx.H>            /* LPC21xx definitions */
#include "Serial.h"	
void delay_ms(int count)
{
  int j=0,i=0;

  for(j=0;j<count;j++)
  {
    for(i=0;i<35;i++);
  }
}
int main (void)  
{          
  uart0_init();					  // Initialize UART0
  delay_ms(100000);

  while (1)
   {                    
  uart0_puts ("\n\rHello World\n\r");	  
  delay_ms(1000000);
  }                               
}
