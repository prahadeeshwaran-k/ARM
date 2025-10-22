#include <LPC21xx.h>  // note the name: LPC21xx.h
#include "UART.h"



void delay(unsigned int sec){
	T0PR = 15000000 - 1; //Assign The Prescaler Value
	T0TCR = 0x01;				 //Enable The Counter Register T0TC & TOPC
	while(T0TC < sec); 	 //Wait for the T0TV meet the condition
	T0TCR = 0X03;				 //Reset the T0TC Counter
	T0TCR = 0X00;				 //Disable the Counter Register T0TC & TOPC
}

void clock_setup(void) {
    // Step 1: Disconnect the PLL before changing settings
    PLLCON = 0x00; // Disconnect and disable PLL
    PLLFEED = 0xAA; // Feed sequence
    PLLFEED = 0x55;

    // Step 2: Configure the PLL
    // For 10MHz crystal to 60MHz CCLK (M=6, P=2)
    // PLLCFG = (P-1 << 5) | (M-1)
    // PLLCFG = (1 << 5) | (5) = 0x25
    PLLCFG = 0x25;
    PLLFEED = 0xAA; // Feed sequence
    PLLFEED = 0x55;

    // Step 3: Enable the PLL and wait for lock
    PLLCON = 0x01; // Enable PLL
    PLLFEED = 0xAA; // Feed sequence
    PLLFEED = 0x55;

    while (!(PLLSTAT & 0x04)); // Wait for PLL to lock

    // Step 4: Connect the PLL as the new clock source
    PLLCON = 0x03; // Connect PLL
    PLLFEED = 0xAA; // Feed sequence
    PLLFEED = 0x55;

    // Step 5: Configure the VPB divider for PCLK
    // VPBDIV = 0x01 sets PCLK = CCLK (60 MHz)
    VPBDIV = 0x01;
}


int main(void)
{
    clock_setup();
	UART0_CONFIG();
    while (1) {
		UART0_STR("1sec\r\n");
		delay(1);
	}
	
}



