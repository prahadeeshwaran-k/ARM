#include <LPC21xx.h>
#include "Delay.h"

#define LED1 (1 << 0)

volatile int Flag = 0;
unsigned int count= 0 ;

void FIQ_Handler() __irq {
    T0IR = 0x01;     // Clear interrupt flag for MR0
    Flag = 1;        // Set flag for main loop
		VICVectAddr = 0;
}

int main(void) {
    IODIR0 = LED1;       // Set P0.0 as output

    // Timer0 setup
    T0MR0 = 15000000 - 1; // Match value
    T0MCR = 0x03;         // Interrupt + Reset on match

    VICIntSelect = (1 << 4); // Timer0 as FIQ
    VICIntEnable = (1 << 4); // Enable Timer0 interrupt

    T0TCR = 0x01;          // Start Timer0

    while (1) {
        if (Flag) {
            IOSET0 = LED1;
            delay_ms(500);
            IOCLR0 = LED1;
            Flag = 0;
        }else
					count++;
    }
}
