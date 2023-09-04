#include <LPC214x.H> 
void delay_led(unsigned long int); // Delay Time Function
int main(void)
{

IO1DIR = 0xC0000000;
IO0DIR = 0x00200000; 
while(1) // Loop Continue
{
IO0SET = 0x00200000;
delay_led(15000);
IO1SET = 0x80000000;
IO1CLR = 0x40000000; // Clear Pin P0.7,6,5,4 (ON LED)
delay_led(1500000); // Display LED Delay
IO1SET = 0x40000000;
IO1CLR = 0x80000000; // Set Pin P0.7,6,5,4 (OFF LED)
delay_led(1500000); // Display LED Delay
}
}
/***********************/
/* Delay Time Function */
/***********************/
void delay_led(unsigned long int count1)
{
while(count1 > 0) {count1--;} // Loop Decrease Counter
}
