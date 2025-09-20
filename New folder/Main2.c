/* Program: UART0 String Transmit & Receive using Interrupts
   Controller: LPC2129
   Pclk = 15 MHz, Baud rate = 9600
*/

#include <LPC21xx.h>
#define LED (1<<17)
#define SW  14

void UART0_CONFIG(void);
void UART0_Interrupt_config(void);
void UART0_SendString(char *str);

volatile char rx_buffer[100];   // buffer for received string
volatile int rx_index = 0;
volatile int string_ready = 0;

void UART0_ISR(void) __irq
{
    int temp;
    temp = U0IIR;  // Read interrupt ID register

    if ((temp & 0x0E) == 0x04)  // RDA: Receive Data Available
    {
        char ch = U0RBR;  // Read received character

        if (ch == '\r')   // End of string (Enter key)
        {
            rx_buffer[rx_index] = '\0'; // Null terminate string
            rx_index = 0;               // Reset buffer index
            string_ready = 1;           // Indicate string is ready
        }
        else
        {
            if (rx_index < sizeof(rx_buffer)-1)
            {
                rx_buffer[rx_index++] = ch;
            }
        }
    }

    if ((temp & 0x0E) == 0x02) // THRE: Transmit Holding Register Empty
    {
        // Not used here, string sending is done in polling
    }

    VICVectAddr = 0; // End of interrupt
}

int main()
{
    IODIR0 = LED; // P0.17 as OUTPUT pin

    UART0_CONFIG();
    UART0_Interrupt_config();
    VICIntEnable = 1 << 6; // Enable UART0 interrupt

    // Send a welcome string
    UART0_SendString("UART0 String Tx/Rx Demo\r\n");
    UART0_SendString("Type something and press Enter:\r\n");

    while (1)
    {
        if (((IOPIN0 >> SW) & 1) == 0)
            IOCLR0 = LED;
        else
            IOSET0 = LED;

        if (string_ready)  // If a full string is received
        {
            string_ready = 0;
            UART0_SendString("Received: ");
            UART0_SendString((char *)rx_buffer);
            UART0_SendString("\r\n");
        }
    }
}

void UART0_CONFIG(void)
{
    PINSEL0 = 0x00000005; // P0.0 as TXD0 and P0.1 as RXD0
    U0LCR = 0x83;         // 8-bit, 1 stop bit, no parity, DLAB=1
    U0DLL = 97;           // Baud rate = 9600 for PCLK=15MHz
    U0DLM = 0;
    U0LCR = 0x03;         // Clear DLAB
}

void UART0_Interrupt_config(void)
{
    VICIntSelect = 0;                 // All IRQ
    VICVectCntl0 = (1 << 5) | 6;      // Enable slot0 for UART0
    VICVectAddr0 = (unsigned)UART0_ISR;
    U0IER = (1 << 0) | (1 << 1);      // Enable RDA & THRE interrupts
}

void UART0_SendString(char *str)
{
    while (*str)
    {
        while (!(U0LSR & (1 << 5))); // Wait for THR empty
        U0THR = *str++;
    }
}
