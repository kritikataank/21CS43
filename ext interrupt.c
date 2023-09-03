#include <LPC214x.H> 
int i; 
void init_ext_interrupt(void);
__irq void Ext_ISR(void);
int main (void) 
{ 	init_ext_interrupt();   // initialize the external interrupt 	
  while (1)  
  {
  	}
} 
void init_ext_interrupt()  // Initialize Interrupt
{
  EXTMODE = 0x4; 		//Edge sensitive mode on EINT2  
  EXTPOLAR &= ~(0x4); 	//Falling Edge Sensitive
  PINSEL0 = 0x80000000; //Select Pin function P0.15 as EINT2   
  /* initialize the interrupt vector */
  VICIntSelect &= ~ (1<<16);        	// EINT2 selected as IRQ 16
  VICVectAddr5 = (unsigned int)Ext_ISR; // address of the ISR
  VICVectCntl5 = (1<<5) | 16;			// 
  VICIntEnable = (1<<16);           	// EINT2 interrupt enabled
  EXTINT &= (0x4);	
}
__irq void Ext_ISR(void) // Interrupt Service Routine-ISR 
{
	IO1DIR |= (1<<16);
	IO1SET |= (1<<16); 	 // Turn OFF Buzzer
	for(i=0; i<2000000;i++);
	IO1CLR |= (1<<16); 	 // Turn ON Buzzer   
	EXTINT |= 0x4; 		 //clear interrupt
	VICVectAddr = 0; 	 // End of interrupt execution
}

