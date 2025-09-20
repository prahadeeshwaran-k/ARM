#include<LPC21XX.H>
#define LED 1<<17
#define SW 14

void UART0_CONFIG(){
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

void SeiralPuts(const char *str){
	int i = 0;
	while(str[i] != '\0')
		UART0_TX_DATA(str[i++]);
}

void SeiralGets(char *buffer){
    int i = 0;
    while(i < 256){
        buffer[i] = UART0_RX_DATA();   // ? read from UART
        UART0_TX_DATA(buffer[i]);      // echo back
        if(buffer[i] == '\n'){
            buffer[i] = '\0';          // terminate string
            break;
        }
        i++;
    }
}

void UART0_ISR(void)__irq{
		U0THR = 'A';
		VICVectAddr = 0;
}

void UART_Interrupt_Config(void){
	VICIntSelect = 0;
	VICVectCntl0 = 0x20|16;
	VICVectAddr0 = (int)UART0_ISR;
	U0IER = 0x01;
}


int main(){
   
    PINSEL0 = 0X05;
    UART0_CONFIG();
    while(1);
}

