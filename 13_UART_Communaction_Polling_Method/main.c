#include<LPC21XX.H>
#include<stdarg.h>
#include<stdio.h>

void UART0_CONFIG(){
	//|DLAB |SetBreak|stickparity|eventparselect|parityenable|noofstopbit|wordlenght|select |
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

void SerialPrint(const char *p,...){
	int i,val;
	float f;
	char ch,buffer[20];
	va_list ap;
	va_start(ap,p);
	for(i = 0 ;p[i];i++){
		if(p[i]=='%'){
			i++;
			if(p[i]=='d'){
				val = va_arg(ap,int);
				sprintf(buffer,"%d",val);
				SeiralPuts(buffer);
			}
			if(p[i]=='c'){
				ch = va_arg(ap,int);
				UART0_TX_DATA(ch);
			}
			if(p[i]=='f'){
				f = va_arg(ap,double);
				sprintf(buffer,"%f",f);
				SeiralPuts(buffer);
			}
			if(p[i]=='s'){
				char*cp = va_arg(ap,char*);
				SeiralPuts(cp);
			} 	
		}
		else
			UART0_TX_DATA(p[i]);
	}
}

int main(){
    char ch;
    char buffer[256];
    PINSEL0 = 0X05;
    UART0_CONFIG();

    UART0_TX_DATA('A');
    SerialPrint("%d %f Hello World",13,5.645);

    ch = UART0_RX_DATA();
    ch = ch ^ 32;
    SerialPrint("%c SerialGet: \n", ch);

    SeiralGets(buffer);
    SerialPrint("%s", buffer);

    while(1);
}

