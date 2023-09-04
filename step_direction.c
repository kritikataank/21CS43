#include <lpc214x.h>
void  delay();


void delay()
{
  int i,j;
  for(i=0;i<0xff;i++)
     for(j=0;j<0x25;j++);
}


void main()
{
  int num=0x08,val=0x00;
  char rotate=0;
  IO0DIR=0x000F0000;
  while(1)
  {
   if(rotate==1)
   {
    IO0CLR=val;
    val=(num<<16);
    num=num*2;
    IO0SET=val;
    if(num>8)
      num=1;
    delay();
   }
   else
   {
    IO0CLR=val;
    val=(num<<16);
    num=num/2;
    IO0SET=val;
    if(num<1)
      num=0x08;
    delay();
   }
 
   if(!(IO0PIN & 0x00008000))
   {
     while(!(IO0PIN & 0x00008000));
     
     rotate=1;
   }
   else if(!(IO0PIN & 0x00100000)) 
   {
     while(!(IO0PIN & 0x00100000));
     
     rotate=0;
   }
  }
}