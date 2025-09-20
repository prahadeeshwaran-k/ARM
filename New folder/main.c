/*Write an ECP to receive and re-transmit serially through UART0 
  of LPC2129 using interrupt method 
	Note:Pclk=15MHZ ,Baud rate=9600*/
	
#include<LPC21XX.H>
#define LED 1<<17
#define SW 14

void UART0_CONFIG(void);
void UART0_Interrupt_config(void);

void UART0_ISR(void) __irq
{
	int temp;
	temp = U0IIR;
	if(temp == 0x04)//if RDA interrupt occured
	{
		U0THR = U0RBR;
  }
	
	VICVectAddr = 0;
}

int main()
{
	IODIR0 = LED;//P0.17 as OUTPUT pin
	UART0_CONFIG();
	UART0_Interrupt_config();
	VICIntEnable = 1<<6;//Enable UART0 interrupt
	
	while(1)
	{
		if(((IOPIN0>>SW)&1)==0)
			IOCLR0 = LED;
		else
			IOSET0 = LED;
  }
}

void UART0_CONFIG(void)
{
  PINSEL0 = 0X5;//P0.0 as TXD0 and P0.1 as RXD0
  U0LCR = 0X83;
  U0DLL = 97;
  U0DLM = 0;
  U0LCR = 0X03;	
}

void UART0_Interrupt_config(void)
{
  VICIntSelect = 0;
  VICVectCntl0 = (0x20)|6;
  VICVectAddr0 = (int)UART0_ISR;
  U0IER	= (1<<1)|(1<<0);//Enable THRE & RDA  interupt
}
