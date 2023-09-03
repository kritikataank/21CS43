#include "LPC214X.h"

unsigned int  result=0x00000040,val;

int main()
{

 PINSEL1|=0x00080000; 
 

 while(1)
 {
    while(1)
    {
       
       val =0xFFFFFFFF; 
       DACR=val;
       
       {
         break;
       }
    }
    while(1)
    {
       
       val =0x00000000; 
       DACR=val;
       
       {
        break;
       }
    }
 }

}
