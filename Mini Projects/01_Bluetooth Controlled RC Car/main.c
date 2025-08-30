//Normal and simple method
/* ================== Motor Input Control Table ==================
| IN1 | IN2 | IN3 | IN4 | Spinning Direction  | Char |
|-----|-----|-----|-----|---------------------|------|
|  0  |  0  |  0  |  0  | Motor OFF           |  0   |
|  1  |  0  |  1  |  0  | Forward             |  1   |
|  0  |  1  |  0  |  1  | Backward            |  2   |
|  1  |  1  |  1  |  1  | Motor OFF           |  -   |
================================================================ */

/* ================== Motor Direction Operation ==================
| Direction | Operation  | Motor1      | Motor2      | IN1 | IN2 | IN3 | IN4 |
|-----------|------------|-------------|-------------|-----|-----|-----|-----|
| Forward   | F          | Forward(1)  | Forward(1)  |  1  |  0  |  1  |  0  |
| Backward  | B          | Backward(2) | Backward(2) |  0  |  1  |  0  |  1  |
| Stop      | S          | Stop(0)     | Stop(0)     |  0  |  0  |  0  |  0  |
| Left      | L          | Stop(0)     | Forward(1)  |  0  |  0  |  1  |  0  |
| Right     | R          | Forward(1)  | Stop(0)     |  1  |  0  |  0  |  0  |
================================================================ */

#include<LPC21XX.H>
#include<stdio.h>
#include"Delay.h"
#include"UART.h"
#include"LCD8Bit.h"

#define IN1 1<<27
#define IN2 1<<28
#define IN3 1<<29
#define IN4 1<<30
#define BTSTATE 1<<2

int main()
{
	unsigned char op;
	unsigned char str1[] = "Forward Moving ";
	unsigned char str2[] = "Backward Moving";
	unsigned char str3[] = "Stop           ";
	unsigned char str4[] = "Left Moving    ";
	unsigned char str5[] = "Right Moving   ";

	
	IODIR1 |= IN1 | IN2 | IN3 | IN4 ; // set motor pins as output And lED
	IOCLR1 = IN1 | IN3 | IN2 | IN4;

	LCD_INIT();
	UART0_CONFIG();

	UART0_STR("Connected with LPC2129");
				UART0_STR("\r\n");
				LCD_COMMAND(0x80);
				LCDPrintString("Bluetooth car  ");

	while(1)
	{	
		
		op = UART0_RX();
    	switch(op){

				case 'F'://Forward
	
					IOCLR1 = IN2 |IN4;
					IOSET1 = IN1 |IN3;

					UART0_STR(str1);
					UART0_STR("\r\n");
					LCD_COMMAND(0xC0);
					LCDPrintString(str1);
					break;	
				
				case 'B'://Backward
					
					IOCLR1 = IN1 | IN3;
					IOSET1 = IN2 | IN4;

					UART0_STR(str2);
					UART0_STR("\r\n");
					LCD_COMMAND(0xC0);
					LCDPrintString(str2);
					break;
				
				case 'S'://Stop
					
					IOCLR1 = IN1 | IN3 | IN2 | IN4;
					UART0_STR(str3);
					UART0_STR("\r\n");
					LCD_COMMAND(0xC0);
					LCDPrintString(str3);
					break;
				
				case 'L'://Left
					
					IOCLR1 = IN1 |IN2 | IN4;
					IOSET1 = IN3;
					UART0_STR(str4);
					UART0_STR("\r\n");
					LCD_COMMAND(0xC0);
					LCDPrintString(str4);
					break;
				
				case 'R'://Right

					IOCLR1 = IN3 |IN2 | IN4;
					IOSET1 = IN1;
					UART0_STR(str5);
					UART0_STR("\r\n");
					LCD_COMMAND(0xC0);
					LCDPrintString(str5);
					break;
				
		}//Switch End

		UART0_TX('\n');

	}//SuperLoop

}

