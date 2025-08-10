#include<LPC21XX.H>

#define LED1 1<<1
#define LED2 1<<0

#define EXT_INT0 14
#define EXT_INT1 15

void config_interrupt(void);

void Non_Vectored_Isr(void) __irq{ //If "__irq was not mentioned it leds to problem "
	/*
	VICIRQStatus IRQ Status Register. 
	This register reads out the state of those interrupt requests that are enabled and classified as IRQ.
	*/
	if((VICIRQStatus >> EXT_INT0) & 1){
		EXTINT = 0x01;
		IOSET0 = LED1;
		IOCLR0 = LED1;
	}
	if((VICIRQStatus >> EXT_INT1) & 1){
		EXTINT = 0x02;
		IOSET0 = LED2;
		IOCLR0 = LED2;
	}
	VICVectAddr = 0;
}

unsigned int count;

int main(){
	PINSEL0 = 0X20000000;
	PINSEL1 = 0X01;
	IODIR0 = LED1 | LED2;
	
	config_interrupt();
	
	EXTMODE = 0x03;
	EXTPOLAR = 0x00;
	VICIntEnable = (1<<EXT_INT0) | (1<<EXT_INT1) ;
	while(1){
		count++;
	}
	
	
}

void config_interrupt(void){
	VICIntSelect = 0;
	VICDefVectAddr = (int)Non_Vectored_Isr;
	
	//VICDefVectAddr Default Vector Address Register. 
	//This register holds the address of the Interrupt Service routine (ISR) for non-vectored IRQs
	
	
}
