#include<LPC21XX.H>
#include"Delay.h"
#include"LCD.h"
#include<stdio.h>

#define SW1 1<<2
#define SW2 1<<3
#define SW3 1<<4
#define SW4 1<<5

void UART0_CONFIG(){
	PINSEL0 = 0X05;
	U0LCR= 1<<7 | 3<<0; //0x83 to turn on the 7bit
	U0DLL = 0X97;
	U0DLM = 0;
	U0LCR = 0X03;
}

void UART0_TX_DATA(unsigned char data)
{
		while(((U0LSR>>5)&1) == 0);
		U0THR = data;
}

unsigned char UART0_RX_DATA(void)
{
		while((U0LSR&1) == 0);
		return U0RBR;
}

void SerialPuts(const char *str){
	int i = 0;
	while(str[i] != '\0')
		UART0_TX_DATA(str[i++]);
}

void SerialGets(char *buffer){
    int i = 0;
    while(i < 256){
        buffer[i] = UART0_RX_DATA();   
        UART0_TX_DATA(buffer[i]);      // echo back
        if(buffer[i] == '\n'){
            buffer[i] = '\0';          // terminate string
            break;
        }
        i++;
    }
}


int main(){
	 UART0_CONFIG();
   while(1){
        if(((IOPIN0 & SW1) == 0)){   // Button 1 pressed (active low)
            delay_ms(150);           // Debounce
            while((IOPIN0 & SW1) == 0); // Wait for release
            SerialPuts("Button 1 is Pressed\r\n");
        }
        if(((IOPIN0 & SW2) == 0)){
            delay_ms(150);
            while((IOPIN0 & SW2) == 0);
            SerialPuts("Button 2 is Pressed\r\n");
        }
        if(((IOPIN0 & SW3) == 0)){
            delay_ms(150);
            while((IOPIN0 & SW3) == 0);
            SerialPuts("Button 3 is Pressed\r\n");
        }
        if(((IOPIN0 & SW4) == 0)){
            delay_ms(150);
            while((IOPIN0 & SW4) == 0);
            SerialPuts("Button 4 is Pressed\r\n");
        }
    }
}

