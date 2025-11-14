#include <LPC21XX.h>
#include "Delay.h"
//#include"HC_SR04.h"
#include "UART.h"
#define TRIG (1<<2) //P0.2
#define ECHO (1<<3) //P0.3
void startTimer0(void)
{
	T0TCR = 0x02; //Reset Timer
	T0TCR = 0x01; //Enable timer
}

unsigned int stopTimer0(void)
{
	T0TCR = 0x00; //Disable timer
	return T0TC;
}

int main()
{
	int echoTime=0;
	float distance=0;
//    VPBDIV=0x01; // PCLK = 60MHz
	UART0_CONFIG();
	UART0_STR("HC-SR04\r\n");
	IO0DIR |= TRIG;    //Set P0.2(TRIG) as output
	IO0DIR &= ~(ECHO); //Set P0.3(ECHO) as input (explicitly)
	IO0CLR |= TRIG;    //Set P0.2 LOW initially
		

	
    while(1) {
		UART0_STR("1");
		IO0SET |= TRIG;
		delay_micro(10);
		IO0CLR |= TRIG;
		UART0_STR("2");
		while(!(IO0PIN & ECHO)); //Wait for a HIGH on ECHO pin
		UART0_STR("3");
		startTimer0(); //Start counting
		while(IO0PIN & ECHO); //Wait for a LOW on ECHO pin
		UART0_STR("4");
		echoTime = stopTimer0(); //Stop counting and save value(us) in echoTime

		distance = (0.0343 * echoTime)/2; //Find the distance

		UART0_STR("Distance = ");
		UART0_Integer(distance);
		
		delay_ms(1000); //wait 1 second for next update
	}
}
