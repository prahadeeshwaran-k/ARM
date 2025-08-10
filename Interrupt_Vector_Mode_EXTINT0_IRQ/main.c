#include<LPC21XX.H>

#define LED1 1<<2				// Using P0.2 for LED
#define IRQ_Slot_En 0x20//IRQ Slot Enable in 5th bit possion of the VICVectCntl0to15
#define EXT_INT0 14			// External interrupt 0 vector number

void config_interrupt(void);

void EXTINT0_Function_ISR(void)__irq{
	EXTINT = 0x01; 		// Clear EINT0 interrupt flag by writing 1 to bit0
	IOSET0 = LED1;		//Logic 1 to the 
	IOCLR0 = LED1;		//Logic 2 to the
	VICVectAddr = 0;    //Dummy Write to indicate end the Isr+
}
unsigned int count = 0 ;
			  
int main(){
	PINSEL1 = 0x01;	
	IODIR0 = LED1;
	config_interrupt();
	//Select the triggering mode for external interrupt
	EXTMODE = 0x01; 	// Edge sensitive for EINT0
	EXTPOLAR = 0x00;	// Falling edge trigger
	//Now Enable the Interrupt in VICbolck
	VICIntEnable = 1<<EXT_INT0;
	
	//Main Block Code 
	while(1){
		count++;
	}	
}

void config_interrupt(void){
	
	VICIntSelect=0; //Select all Interrupt as IRQs(5.6 Interrupt sources) Table in Datasheet
	VICVectCntl0 = IRQ_Slot_En | EXT_INT0; //Enable The 5th position the register and set the number 14 in right most the 5 bit Enable slot 0 for external interrupt 0 
	VICVectAddr0 = (int)EXTINT0_Function_ISR;// Function Pointer type casted to integer address.
}
