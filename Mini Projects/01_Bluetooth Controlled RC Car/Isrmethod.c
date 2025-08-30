/* ================== Motor Input Control Table ==================
| IN1 | IN2 | IN3 | IN4 | Spinning Direction | Char |
|-----|-----|-----|-----|---------------------|------|
|  0  |  0  |  0  |  0  | Motor OFF           |  0   |
|  1  |  0  |  1  |  0  | Forward             |  1   |
|  0  |  1  |  0  |  1  | Backward            |  2   |
|  1  |  1  |  1  |  1  | Motor OFF           |  -   |
================================================================ */

/* ================== Motor Direction Operation ==================
| Direction | Operation | Motor1      | Motor2      | IN1 | IN2 | IN3 | IN4 |
|-----------|------------|-------------|-------------|-----|-----|-----|-----|
| Forward   | F          | Forward(1)  | Forward(1)  |  1  |  0  |  1  |  0 |
| Backward  | B          | Backward(2) | Backward(2) |  0  |  1  |  0  |  1 |
| Stop      | S          | Stop(0)     | Stop(0)     |  0  |  0  |  0  |  0 |
| Left      | L          | Stop(0)     | Forward(1)  |  0  |  0  |  1  |  0 |
| Right     | R          | Forward(1)  | Stop(0)     |  1  |  0  |  0  |  0 |
================================================================ */

#include<LPC21XX.H>
#include<stdio.h>
#include"Delay.h"
#include"UART.h"
#include"LCD8Bit.h"

//Macros
#define IN1 1<<27
#define IN2 1<<28
#define IN3 1<<29
#define IN4 1<<30

#define STOP     0
#define FORWARD  1
#define BACKWARD 2

//Function Prototypes
void UART0_ISR(void) __irq;
void UART0_Interrupt_config(void);
void State(unsigned char direction,int Terminal1,int Terminal2);

//GlobalVariables
unsigned char op = 'S';
unsigned char flag;

int main()
{
	unsigned char str1[] = "Forward Moving ";
	unsigned char str2[] = "Backward Moving";
	unsigned char str3[] = "Stop           ";
	unsigned char str4[] = "Left Moving    ";
	unsigned char str5[] = "Right Moving   ";

	State(STOP,IN1,IN2); //Motor 1 -> Stop
	State(STOP,IN3,IN4); //Motor 2 -> Stop
	IODIR0 |= (IN1 | IN2 | IN3 | IN4); // set motor pins as output

	LCD_INIT();
	UART0_CONFIG();
	UART0_Interrupt_config();
	VICIntEnable = 1<<6;//Enable UART0 interrupt

	UART0_STR("Connected with LPC2129");
	UART0_STR("\r\n");
	LCD_COMMAND(0x80);
	LCDPrintString("Bluetooth car  ");

	while(1) {

		if(flag) {
			
			switch(op) {

			case 'F'://Forward
				State(FORWARD, IN1, IN2); //Motor 1 -> Forward
				State(FORWARD, IN3, IN4); //Motor 2 -> Forward

				UART0_STR(str1);
				UART0_STR("\r\n");
				LCD_COMMAND(0xC0);
				LCDPrintString(str1);
				break;

			case 'B'://Backward
				State(BACKWARD, IN1, IN2); //Motor 1 -> Backward
				State(BACKWARD, IN3, IN4); //Motor 2 -> Backward

				UART0_STR(str2);
				UART0_STR("\r\n");
				LCD_COMMAND(0xC0);
				LCDPrintString(str2);
				break;

			case 'S'://Stop
				State(STOP, IN1, IN2); //Motor 1 -> Stop
				State(STOP, IN3, IN4); //Motor 2 -> Stop

				UART0_STR(str3);
				UART0_STR("\r\n");
				LCD_COMMAND(0xC0);
				LCDPrintString(str3);
				break;

			case 'L'://Left
				State(STOP, IN1, IN2);    //Motor 1 -> Stop
				State(FORWARD, IN3, IN4); //Motor 2 -> Forward

				UART0_STR(str4);
				UART0_STR("\r\n");
				LCD_COMMAND(0xC0);
				LCDPrintString(str4);

				break;

			case 'R'://Right
				State(FORWARD, IN1, IN2); //Motor 1 -> Forward
				State(STOP, IN3, IN4);    //Motor 2 -> Stop

				UART0_STR(str5);
				UART0_STR("\r\n");
				LCD_COMMAND(0xC0);
				LCDPrintString(str5);
				break;

			}//Switch End
			UART0_TX('\n');
			flag = 0;

		}//if(flag)

	}//SuperLoop

}//mainloop

void UART0_Interrupt_config(void)
{
	VICIntSelect = 0;
	VICVectCntl0 = (0x20)|6;
	VICVectAddr0 = (int)UART0_ISR;
	U0IER	= (1<<1)|(1<<0);//Enable THRE & RDA  interupt
}

void UART0_ISR(void) __irq
{
	int temp;
	temp=U0IIR;
	if(temp==0x04)//if RDA interrupt occured
	{
		op = U0RBR;
		flag = 1;
	}

	VICVectAddr = 0;
}

void State(unsigned char direction,int Terminal1,int Terminal2) {
	switch(direction) {
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
