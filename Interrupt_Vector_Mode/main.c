#include<LPC21XX.H>

#define LED1 1<<2
#define IRQ_Slot_En 0x20//IRQ Slot Enable in 5th bit possion of the VICVectCntl0to15
#define EXT_INT0 14

void config_interrupt(void);

void EXTINT0_Function_ISR(void)__irq{
	EXTINT = 0x01; 		//TO CLEAR EINT0 flag
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
	EXTMODE = 0x01;
	EXTPOLAR = 0x00;
	//Now Enable the Interrupt in VICbolck
	VICIntEnable = 1<<EXT_INT0;
	
	//Main Block Code 
	while(1){
		count++;
	}	
}

void config_interrupt(void){
	VICIntSelect=0;						  //Select all Interrupt as IRQs
	VICVectCntl0 = IRQ_Slot_En | EXT_INT0; //Enable The 5th position the register and set the number 14 in right most the 5 bit 
	VICVectAddr0 = (int)EXTINT0_Function_ISR;// Function Pointer type casted to integer address.
}
