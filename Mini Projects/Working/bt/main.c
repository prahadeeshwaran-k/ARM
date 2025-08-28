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
#include"LCD4Bit.h"

#define IN1 1<<4
#define IN2 1<<5
#define IN3 1<<6
#define IN4 1<<7

#define LED1 1<<10
#define LED2 1<<11
#define LED3 1<<12
#define LED4 1<<13

#define STOP     0
#define FORWARD  1
#define BACKWARD 2

void State(unsigned char direction,int Terminal1,int Terminal2){
	switch(direction){
		//Stop Condition
		case STOP:
			IOCLR0 = Terminal1|Terminal2;
			break;
		//Forward Condition
		case FORWARD:
			IOSET0 = Terminal1;
			IOCLR0 = Terminal2;
			break;
		//Backward Condition
		case BACKWARD:
			IOSET0 = Terminal2;
			IOCLR0 = Terminal1;
			break;
	}
}

int main()
{
	unsigned char op;
	unsigned char str1[] = "Forward Moving";
	unsigned char str2[] = "Backward Moving";
	unsigned char str3[] = "Stop";
	unsigned char str4[] = "Left Moving";
	unsigned char str5[] = "Right Moving";

	State(STOP,IN1,IN2); //Motor 1 -> Stop
	State(STOP,IN3,IN4); //Motor 2 -> Stop
	IODIR0 |= (IN1 | IN2 | IN3 | IN4 | LED1 | LED2 | LED3 | LED4 ); // set motor pins as output And lED
	LCD_INIT();
	UART0_CONFIG();

	IOSET0 =  LED1 | LED2 | LED3 | LED4;

	LCD_COMMAND(0x80);
	LCDPrintString("Bluetooth car");
	LCD_COMMAND(0xC0);
	
	
	while(1)
	{	
		op = UART0_RX();
    switch(op){

				case 'F'://Forward
					State(FORWARD, IN1, IN2); //Motor 1 -> Forward
					State(FORWARD, IN3, IN4); //Motor 2 -> Forward
					IOSET0 =   LED2 | LED4;
					IOCLR0 =   LED1 | LED3 ;
					UART0_STR(str1);
					LCD_COMMAND(0x80);
					LCDPrintString(str1);
					break;
				
				case 'B'://Backward
					State(BACKWARD, IN1, IN2); //Motor 1 -> Backward
					State(BACKWARD, IN3, IN4); //Motor 2 -> Backward
					IOSET0 =   LED1 | LED3;
					IOCLR0 =   LED2 | LED4 ;
					UART0_STR(str2);
					LCD_COMMAND(0x80);
					LCDPrintString(str2);
					break;
				
				case 'S'://Stop
					State(STOP, IN1, IN2); //Motor 1 -> Stop
					State(STOP, IN3, IN4); //Motor 2 -> Stop
					IOSET0 =  LED1 | LED2 | LED3 | LED4;
					UART0_STR(str3);
					LCD_COMMAND(0x80);
					LCDPrintString(str3);
					break;
				
				case 'L'://Left
					State(STOP, IN1, IN2); //Motor 1 -> Stop
					State(FORWARD, IN3, IN4); //Motor 2 -> Forward
					UART0_STR(str4);
					IOSET0 =  LED1 | LED2 | LED4;
					IOCLR0 = LED3 ;
					LCD_COMMAND(0x80);
					LCDPrintString(str4);
					break;
				
				case 'R'://Right
					State(FORWARD, IN1, IN2); //Motor 1 -> Forward
					State(STOP, IN3, IN4); //Motor 2 -> Stop
					IOSET0 =  LED3 | LED2 | LED4;
					IOCLR0 = LED1 ;
					UART0_STR(str5);
					LCD_COMMAND(0x80);
					LCDPrintString(str5);
					break;
				
				default: //Stop
					State(STOP, IN1, IN2); //Motor 1 -> Stop
					State(STOP, IN3, IN4); //Motor 2 -> Stop
					IOSET0 =  LED1 | LED2 | LED3 | LED4;
					UART0_STR(str3);
					LCD_COMMAND(0x80);
					LCDPrintString(str3);
					break;
				
		}//Switch End

		UART0_TX('\n');

	}//SuperLoop

}

