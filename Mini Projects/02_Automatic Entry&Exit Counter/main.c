#include<LPC21XX.H>
#include"Delay.h"
#include"UART.h"

#define EXT_INT0 14
#define EXT_INT1 15
#define EXT_INT2 16
#define EXT_INT3 17

//Led Pins
#define LED1 (1 << 2)
#define LED2 (1 << 3)
#define LED3 (1 << 4)
#define LED4 (1 << 5)

volatile unsigned char sensorFlag1[2] = {0,0};
volatile unsigned char sensorFlag2[2] = {0,0};
volatile unsigned char directionFlag1;
volatile unsigned char directionFlag2;
volatile unsigned char CountFlag1[2]= {0,0};
volatile unsigned char CountFlag2[2]= {0,0};

volatile unsigned char Humans = 0;

void Config_Interrupt(void);

void Non_Vectored_Isr(void)__irq {

	unsigned int irqStatus = VICIRQStatus;  // snapshot of pending IRQs

	switch (irqStatus) {
	// For Door 1 Logic
	// For Out -> In
	case (1 << EXT_INT0):
		EXTINT = 0x01;      // clear EINT0
		if(directionFlag1== 0) { //when directionFlag1 = 0 means it occurs 1st
			sensorFlag1[0] = 1;
			directionFlag1 = 1;
		} else {
			sensorFlag1[0] = 0;
		}
		CountFlag1[0] = 1;
		break;
	// For In -> Out
	case (1 << EXT_INT3):
		EXTINT = 0x08;      // clear EINT3
		if(directionFlag1 == 0) { //when directionFlag1 = 0 means it occurs 1st
			sensorFlag1[1] = 1;
			directionFlag1 = 1;
		} else {
			sensorFlag1[1] = 0;
		}
		CountFlag1[1] = 1;
		break;

	// For Door 2 Logic
	case (1 << EXT_INT1):
		EXTINT = 0x02;      // clear EINT1
		if(directionFlag2== 0) { //when directionFlag1 = 0 means it occurs 1st
			sensorFlag2[0] = 1;
			directionFlag2 = 1;
		} else {
			sensorFlag2[0] = 0;
		}
		CountFlag2[0] = 1;
		break;

	case (1 << EXT_INT2):
		EXTINT = 0x04;      // clear EINT2
		if(directionFlag2 == 0) { //when directionFlag1 = 0 means it occurs 1st
			sensorFlag2[1] = 1;
			directionFlag2 = 1;
		} else {
			sensorFlag2[1] = 0;
		}
		CountFlag2[1] = 1;
		break;
	}

	VICVectAddr = 0;   // Acknowledge ISR
}


int main() {
	IODIR0  |= (LED1 | LED2 | LED3 | LED4);
	PINSEL0 |= 0xA0000000;   // P0.14 -> EINT1, P0.15 -> EINT2
	PINSEL1 |= 0x00000301;		// P0.16 -> EINT0, P0.20 -> EINT3

	Config_Interrupt();
	UART0_CONFIG();
	UART0_STR("Automatic Person Counter");
	UART0_STR("\r\n");

	EXTMODE = 0x0f;
	EXTPOLAR = 0x0f;

	VICIntEnable = (1<<EXT_INT0) | (1<<EXT_INT1) | (1<<EXT_INT2) | (1<<EXT_INT3) ;
	while(1) {
		
		if(CountFlag1[0] && CountFlag1[1]) {
			if(sensorFlag1[0]){
				Humans++;
				UART0_STR("in door 1 +One Person Entered: TotalPersons ");
				UART0_TX(Humans);
				UART0_STR("\r\n");
			}

			if(sensorFlag1[1]){
				if(humans>0){Humans--}
				UART0_STR("in door 1 -One Person Exited: TotalPersons ");
				UART0_TX(Humans);
				UART0_STR("\r\n");
			}

			//Reset All The Flags
			CountFlag1[0] = 0;
			CountFlag1[1] = 0;
			directionFlag1 = 0;
			sensorFlag1[0] = 0;
			sensorFlag1[1] = 0;
		}//1st if Ends
		
		if(CountFlag2[0] && CountFlag2[1]) {
			if(sensorFlag2[0]){
				Humans++;
				UART0_STR("+One Person Entered: TotalPersons ");
				UART0_TX(Humans);
				UART0_STR("\r\n");
				}
			
			if(sensorFlag2[1]){
				if(humans>0){Humans--}
				UART0_STR("- One Person Exited: TotalPersons ");
				UART0_TX(Humans);
				UART0_STR("\r\n");
				}

			//Reset All The Flags
			CountFlag2[0] = 0;
			CountFlag2[1] = 0;
			directionFlag2 = 0;
			sensorFlag2[0] = 0;
			sensorFlag2[1] = 0;
		}//2st if Ends
		
	}//SuperLoop
}//Main Function

void Config_Interrupt(void) {
	VICIntSelect = 0;
	VICDefVectAddr = (int)Non_Vectored_Isr;
}


