#include<LPC21XX.H>

#define LED1 1<<0
#define LED2 1<<1

#define IRQ_Slot_En 1<<5

// Table 51. Connection of interrupt sources to the Vectored Interrupt Controller to Find the Number
// Note: Typically, EXT_INT0 is interrupt 14, EXT_INT1 is 15 on LPC21xx (check datasheet)
#define EXT_INT0 14
#define EXT_INT1 15

void Config_Interrupt(void);

//External Interrupt 0 Function
void EXT_INT0_ISR(void) __irq{
	EXTINT = 0x1;	// Clear EINT0 interrupt flag
	IOSET0 = LED1;// Turn LED1 ON
	IOCLR0 = LED1;// Turn LED1 OFF immediately
	VICVectAddr = 0;// Signal end of ISR
}

//External Interrupt 0 Function
void EXT_INT1_ISR(void) __irq{
	EXTINT = 0x2;	// Clear EINT1 interrupt flag
	IOSET0 = LED2;// Turn LED2 ON
	IOCLR0 = LED2;// Turn LED2 OFF immediately
	VICVectAddr = 0;// Signal end of ISR
}

unsigned int count = 0;

//Main Function
int main(){
	PINSEL0 = 0x20000000; //Config P0.14 pin as EINT1(10)  29:28
	PINSEL1 = 0x01; //Config P0.16 pin as EINT1(01)  1:0
	IODIR0 = LED1 | LED2 ; //Config the P0.0 and  P0.1 as output
	Config_Interrupt();
	
	EXTMODE = 0x03;  // Set both EINT0 and EINT1 as edge sensitive (bits 0 and 1)
	EXTPOLAR = 0x00; // Set interrupts to trigger on falling edge (active low)
	
	VICIntEnable = (1<<EXT_INT0) | (1<<EXT_INT1);
	while(1){
		count++;
	}
}

void Config_Interrupt(void){
	VICIntSelect = 0; // Select IRQ (not FIQ) for all interrupts
	
	// Setup vectored interrupt slot 0 for EXT_INT0
	VICVectCntl0 = IRQ_Slot_En | EXT_INT0;
	VICVectAddr0 = (unsigned int)EXT_INT0_ISR;
	
	// Setup vectored interrupt slot 1 for EXT_INT1
	VICVectCntl1 = IRQ_Slot_En | EXT_INT1;
	VICVectAddr1 = (unsigned int)EXT_INT1_ISR;
}
