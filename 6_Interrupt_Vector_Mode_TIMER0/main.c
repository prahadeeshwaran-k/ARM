#include<LPC21XX.H>

#define LED1 1<<0	// Define LED1 as P0.0 bit mask
char Flag = 0;	// Flag variable to toggle LED state

void Timer0_ISR(void) __irq
{
	T0IR = 0x01;	// Clear interrupt flag for MR0 by writing 1 to bit 0 of T0IR
	if(Flag == 0){
		IOSET0 = LED1;	// Turn ON LED1 (set P0.0 high)
	}else{
		IOCLR0 = LED1;	// Turn OFF LED1 (clear P0.0)
	}
	Flag = !Flag;	// Toggle flag for next interrupt
	VICVectAddr = 0;// Signal end of interrupt to the VIC
}

unsigned int count;

int main(){
	IODIR0 = LED1; //P0.0 as output pin
	/*
	15.6.8 Match Control Register (T0MCR)
    Controls the behavior of the timer when it reaches a match value.
    Bit 0 (MR0I) - Interrupt on MR0: Timer generates interrupt when TC == MR0.
    Bit 1 (MR0R) - Reset on MR0: Timer Counter resets to 0 when TC == MR0.
    Bit 2 (MR0S) - Stop on MR0: Timer stops when TC == MR0 (not used here).
	*/
	T0MCR = 0X03;  //Enable MR0I(interrupt) and MR0R(reset).
	//Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
	//Reset on MR0: the TC will be reset if MR0 matches it.
	T0MR0=7500000-1;
	// Match value for 0.5 second delay:
    // Assuming PCLK = 15 MHz, timer counts at PCLK frequency,
    // so 15,000,000 counts = 1 second,
    // MR0 = 7,500,000 - 1 counts = 0.5 second interval.
	
	VICIntSelect = 0;	// Select IRQ (not FIQ) for all interrupts
	VICVectCntl0 = (1<<5) | 4;	// Enable IRQ slot 0 and select Timer0 interrupt (slot 4)
	VICVectAddr0 = (int)Timer0_ISR;	// Set address of Timer0 ISR
	VICIntEnable = 1<<4;	// Enable Timer0 interrupt in VIC
	T0TCR = 0x01;	// Start Timer0 (enable counter)
	
	while(1){
		count++; // Main loop activity (optional)
	}
}
