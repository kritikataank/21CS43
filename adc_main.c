	#include<LPC214X.H>
	/*--------------------------------------------------------
	MACRO FOR ADC
	-------------------------------------------------------- */
    #define ch (1 << 3)
	#define clk_div (3 << 8)
	#define bst_on (1 << 16)
//#define bst_off (0 << 16)
	#define clk_res (0 << 17)
	#define operational (1 << 21)
	#define start (0 << 24)
	#define adc_init_macro ch | clk_div | bst_on | clk_res | operational | start
	/*-------------------------------------------------------------
	MACRO FOR LCD
	---------------------------------------------------------------*/
	#define EN (1 << 28)
	#define RW (1 << 29)
	#define RS (1 << 22)
	#define DATA  (0Xff << 6)
	#define port  EN | RW | RS | DATA
	
/*----------------------------------------------------------------------
FUNCTION DECLARATIONS
-----------------------------------------------------------------------*/
		void adc_init(void);
		void delay(int count);
		void cmd(int c);
		void data(char d);
		void lcd_string(char *str);
		void display(unsigned int n);
		
/*----------------------------------------------------------------------------
		GLOBAL VARIABLES
-----------------------------------------------------------------------------*/
		unsigned int result;
	    float voltage;
		char volt[18];
/*-------------------------------------------------------------------------------
		FUNCTION DEFINITIONS
---------------------------------------------------------------------------------*/
		void adc_init(void)
		{
			AD0CR = adc_init_macro;
		} 
		void cmd(int c)
		{
			IOPIN0 = c << 6;
			IOCLR0 = RW;
			IOCLR0 = RS;
			IOSET0 = EN;
			delay(100); 
			IOCLR0 = EN;
		}
		void data(char d)
		{
			IOPIN0 = d << 6;
			IOCLR0 = RW;
			IOSET0 = RS;
			IOSET0 = EN;
			delay(100); 
			IOCLR0 = EN;
		}

		void lcd_string(char *str)
		{
			while(*str)
			{
				data(*str);
				str++;
				delay(20);
			}
		}
		void display(unsigned int n)
		{ 
			if(n == 0)
				data(n+0x30);
			if(n)
			{
				display(n / 10);
				data((n % 10) + 0x30);
			}
		} 

		void delay(int count)
		{
			int i,j;
			for(i = 0;i < count;i++)
				for(j = 0;j < 5000;j++);
		} 
/*-------------------------------------------------------------------
MAIN
---------------------------------------------------------------------*/
			int main()
			{
				int c = 0;
				IODIR0 |= port ;			
				PINSEL1|=0x10000000; 				
				cmd(0x38);
				cmd(0x0E);
				cmd(0X80);
				cmd(0X01);
				adc_init();
				lcd_string("ADC PROGRAM");
				cmd(0X01); 
				while(1)
				{
					cmd(0x01);
					while((AD0DR3 & (0x80000000)==0));
				 	result = (AD0DR3 & (0X3FF << 6));
					result = result >> 6;
					lcd_string("ADC:");
					cmd(0x86);
					display(result);  
					voltage = ( (result/1023.0) * 3.3 );
					cmd(0xc0);
					sprintf(volt, "Voltage=%.2f V  ", voltage);
					lcd_string(volt);
					//delay(1000);
				}	 	
			
			}







