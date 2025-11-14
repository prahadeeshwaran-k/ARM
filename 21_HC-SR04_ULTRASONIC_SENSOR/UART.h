#include<stdio.h>
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);
void UART0_STR(unsigned char *);
void UART0_Integer(int num);
void UART0_Float(float num);

void UART0_CONFIG(void)
{
  PINSEL0 |= 0X5;//P0.0 as TXD0 and P0.1 as RXD0
  U0LCR = 0X83;
  U0DLL = 97;//135;
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

// Send an integer (handles negatives)
void UART0_Integer(int num)
{
    char buf[10];
    int i = 0;

    if (num == 0)
    {
        UART0_TX('0');
        return;
    }

    if (num < 0)
    {
        UART0_TX('-');
        num = -num;
    }

    while (num > 0)
    {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i--)
        UART0_TX(buf[i]);
}

// Send a float number (2 decimal places)
void UART0_Float(float num)
{
    int intPart, fracPart;

    if (num < 0)
    {
        UART0_TX('-');
        num = -num;
    }

    intPart = (int)num;
    fracPart = (int)((num - intPart) * 100);  // 2 decimal precision

    UART0_Integer(intPart);
    UART0_TX('.');
    UART0_Integer(fracPart);
}
