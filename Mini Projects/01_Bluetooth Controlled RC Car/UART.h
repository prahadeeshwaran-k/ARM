void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);

void UART0_STR(unsigned char *);

void UART0_CONFIG(void)
{
  PINSEL0 |= 0X5;//P0.0 as TXD0 and P0.1 as RXD0
  U0LCR = 0X83;
  U0DLL = 97;
  U0DLM = 0;
  U0LCR = 0X03;	
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

