void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);

void UART0_STR(unsigned char *);

#define THRE (1<<5) // Transmit Holding Register Empty
#define MULVAL 15
#define DIVADDVAL 1
#define NEW_LINE 0xA // Character for new line .. analogous to '\n'

void UART0_CONFIG(void)
{
  PINSEL0 = 0x5;  /* Select TxD for P0.0 and RxD for P0.1 */
	U0LCR = 3 | (1<<7) ; /* 8 bits, no Parity, 1 Stop bit | DLAB set to 1  */
	U0DLL = 110;
	U0DLM = 1;   
	U0FDR = (MULVAL<<4) | DIVADDVAL; /* MULVAL=15(bits - 7:4) , DIVADDVAL=0(bits - 3:0)  */
	U0LCR &= 0x0F; // Set DLAB=0 to lock MULVAL and DIVADDVAL
	//BaudRate is now ~9600 and we are ready for UART communication!
}

void UART0_TX(unsigned char dat)
{
 while(((U0LSR>>5)&1)==0);
 U0THR = dat;	
}

unsigned char UART0_RX(void)
{
  while((U0LSR&1)==0);
 	return U0RBR;
}

void UART0_STR(unsigned char *s)

{

  while(*s)

   UART0_TX(*s++);		

}

