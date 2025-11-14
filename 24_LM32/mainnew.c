#include <LPC21xx.h>

typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned short u16;
typedef signed short   s16;
typedef unsigned int   u32;
typedef signed int     s32;
typedef float          f32;
typedef double         f64;

// ================= TIMER DELAYS ==================
void delay(u32 sec)
{
    T0TCR = 0x02;       // Reset timer
    T0PR  = 60000000 - 1; // 1 tick per second @60MHz
    T0TC  = 0;
    T0TCR = 0x01;       // Enable timer
    while (T0TC < sec);
    T0TCR = 0x00;       // Stop timer
}

void delay_ms(u32 ms)
{
    T0TCR = 0x02;       // Reset timer
    T0PR  = 60000 - 1;  // 1 tick per ms @60MHz
    T0TC  = 0;
    T0TCR = 0x01;
    while (T0TC < ms);
    T0TCR = 0x00;
}

void delay_micro(u32 micro)
{
    T0TCR = 0x02;       // Reset timer
    T0PR  = 60 - 1;     // 1 tick per µs @60MHz
    T0TC  = 0;
    T0TCR = 0x01;
    while (T0TC < micro);
    T0TCR = 0x00;
}

// ============ SPI MACROS ============
#define CS        (1 << 7)
#define MSTR_BIT  5
#define CPOL_BIT  4
#define CPHA_BIT  3
#define SPIF_BIT  7
#define Mode_3    ((1 << CPOL_BIT) | (1 << CPHA_BIT))
#define READBIT(REG,BIT) ((REG >> BIT) & 1)

// ============ UART FUNCTIONS ============
void uart0_init(unsigned int baud)
{
    PINSEL0 |= 0x00000005; // P0.0=TXD0, P0.1=RXD0
    U0LCR = 0x83;
    switch (baud) {
        case 115200: U0DLL = 32; break;
        default:     U0DLL = 32; break;
    }
    U0LCR = 0x03;
}

void uart0_tx(unsigned char data)
{
    while (!(U0LSR & (1 << 5)));
    U0THR = data;
}

void uart0_tx_string(char *ptr)
{
    while (*ptr)
        uart0_tx(*ptr++);
}

void uart0_tx_integer(int num)
{
    char buf[10];
    int i = 0;
    int j;

    if (num == 0) {
        uart0_tx('0');
        return;
    }

    if (num < 0) {
        uart0_tx('-');
        num = -num;
    }

    while (num > 0 && i < 10) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    for (j = i - 1; j >= 0; j--)
        uart0_tx(buf[j]);
}

void uart0_tx_hex(unsigned int num)
{	
	int j;
    char hex[] = "0123456789ABCDEF";
    char buf[8];
    int i = 0;

    if (num == 0) {
        uart0_tx('0');
        return;
    }

    while (num > 0 && i < 8) {
        buf[i++] = hex[num & 0xF];
        num >>= 4;
    }

    for (j = i - 1; j >= 0; j--)
        uart0_tx(buf[j]);
}

void uart0_tx_float(float num)
{
    int ipart = (int)num;
    int fpart = (int)((num - ipart) * 100); // 2 decimal places

    uart0_tx_integer(ipart);
    uart0_tx('.');
    if (fpart < 10) uart0_tx('0');
    uart0_tx_integer(fpart);
}

// ============ SPI FUNCTIONS ============
void Init_SPI0(void)
{
    PINSEL0 |= 0x00001500;   // P0.4=SCK0, P0.5=MISO0, P0.6=MOSI0
    IODIR0  |= CS;           // P0.7 as CS output
    IOSET0  = CS;            // Deselect device (CS high)
    S0SPCCR = 150;  // 60MHz / 150 = 400kHz (valid 8-bit value)
    S0SPCR  = (1 << MSTR_BIT) | Mode_3;
}

u8 SPI0(u8 data)
{
    S0SPDR = data;
    while (!(S0SPSR & (1 << SPIF_BIT)));
    return S0SPDR;
}

// ============ MCP3204 READ ============
f32 Read_ADC_MCP3204(u8 channelNo)
{
    u8 hByte, lByte;
    u16 adcVal = 0;

    IOCLR0 = CS;              // CS low
    SPI0(0x06);               // Start + single-ended
    hByte = SPI0(channelNo << 6);
    lByte = SPI0(0x00);
    IOSET0 = CS;              // CS high

    adcVal = ((hByte & 0x0F) << 8) | lByte;
    return ((adcVal * 3.3) / 4096.0);
}

// ============ MAIN ============
int main(void)
{
    f32 voltage;
    VPBDIV = 0x01;           // PCLK = 60MHz

    uart0_init(115200);
    Init_SPI0();

    uart0_tx_string("\r\nMCP3204 ADC Test @100kbps\r\n");

    while (1)
    {
        voltage = Read_ADC_MCP3204(0);   // Channel 0
        uart0_tx_string("CH0 = ");
        uart0_tx_float(voltage);
        uart0_tx_string(" V\r\n");
        delay_ms(500);
    }
}
