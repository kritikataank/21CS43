#include "LPC214X.h"

unsigned int  value;

int main()
{

 PINSEL1|=0x00080000; 
 

 while(1)
 {
    value = 0;
				while ( value != 1023 )
				{
					DACR = ( (1<<16) | (value<<6) );
					value++;
				}	
				while ( value != 0 )
				{
					DACR = ( (1<<16) | (value<<6) );
					value--;
				}
 }

}
