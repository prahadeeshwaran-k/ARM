#include<LPC21XX.H>   // LPC21xx microcontroller register definitions
#include<stdarg.h>    // For variable argument functions (va_list, va_arg, etc.)
#include<stdio.h>     // For sprintf()

// ================= UART0 Initialization =================
void UART0_CONFIG(){
	U0LCR= 	0X83;    // Line Control Register: (11)8-bit word length, DLAB=1 (to access divisor latches)
	U0DLL = 0X97;    // Divisor Latch Low (for baud rate generation)
	U0DLM = 0;       // Divisor Latch High
	U0LCR = 0X03;    // Clear DLAB, keep 8-bit word length
}

// ================= Transmit one byte =================
void UART0_TX_DATA(unsigned char data)
{
		while(((U0LSR>>5)&1) == 0);  // Wait until THR (Transmit Holding Register) is empty
		U0THR = data;                // Load data into THR for transmission
}

// ================= Receive one byte =================
unsigned char UART0_RX_DATA(void)
{
		while((U0LSR&1) == 0);  // Wait until data is received (RDR = 1)
		return U0RBR;           // Read received byte from Receiver Buffer Register
}

// ================= Transmit string =================
void SeiralPuts(const char *str){
	int i = 0;
	while(str[i] != '\0')        // Loop until NULL terminator
		UART0_TX_DATA(str[i++]); // Send each character
}

// ================= Receive string (with echo) =================
void SeiralGets(char *buffer){
    int i = 0;
    while(i < 256){                      // Limit to 256 chars
        buffer[i] = UART0_RX_DATA();     // Read a char from UART
        UART0_TX_DATA(buffer[i]);        // Echo back the received char
        if(buffer[i] == '\n'){           // If Enter (newline) is pressed
            buffer[i] = '\0';            // Replace newline with string terminator
            break;                       // Exit loop
        }
        i++;
    }
}

// ================= Custom printf-like function =================
// Supports %d, %c, %f, %s for serial output
void SerialPrint(const char *p,...){
	
	int i,val;
	float f;
	char ch,buffer[20];
	
	va_list ap;
	va_start(ap,p);                 // Start variable arguments processing
	for(i = 0 ;p[i];i++){           // Loop through format string
		if(p[i]=='%'){             // Format specifier found
			i++;
			if(p[i]=='d'){         // Integer
				val = va_arg(ap,int);
				sprintf(buffer,"%d",val);
				SeiralPuts(buffer);
			}
			if(p[i]=='c'){         // Character
				ch = va_arg(ap,int);
				UART0_TX_DATA(ch);
			}
			if(p[i]=='f'){         // Floating-point number
				f = va_arg(ap,double);
				sprintf(buffer,"%f",f);
				SeiralPuts(buffer);
			}
			if(p[i]=='s'){         // String
				char*cp = va_arg(ap,char*);
				SeiralPuts(cp);
			} 	
		}
		else
			UART0_TX_DATA(p[i]);   // Print normal characters
	}
}

// ================= Main Function =================
int main(){
    char ch;
    char buffer[256];

    PINSEL0 = 0X05;          // Select UART0 TXD0 (P0.0) and RXD0 (P0.1) pins
    UART0_CONFIG();          // Initialize UART0

    UART0_TX_DATA('A');      // Send single character 'A'
    SerialPrint("%d %f Hello World",13,5.645); // Send formatted string with int & float

    ch = UART0_RX_DATA();    // Wait for a character from UART
    ch = ch ^ 32;            // Toggle case (flip 6th bit: converts lowercase <-> uppercase)
    SerialPrint("%c SerialGet: \n", ch);  // Print modified character

    SeiralGets(buffer);      // Get a string from UART (with echo)
    SerialPrint("%s", buffer); // Print back the received string

    while(1);                // Infinite loop (program runs forever)
}
