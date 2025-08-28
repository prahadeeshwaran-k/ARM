// Pin connections to LCD
#define LCD_D 0xf<<20   // Data lines D4-D7 connected to P1.20 - P1.23
#define RS    1<<17     // Register Select pin (P1.17)
#define RW    1<<18     // Read/Write pin (P1.18)
#define E     1<<19     // Enable pin (P1.19)

// Function prototypes
void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCDPrintString(unsigned char*);
void LCDPrintInt(int);
void LCDPrintFloat(float);

// Send a command to the LCD
void LCD_COMMAND(unsigned char cmd)
{
    // Send upper nibble (D4-D7)
    IOCLR1 = LCD_D;              // Clear data bits
    IOSET1 = (cmd & 0xF0) << 16; // Mask upper nibble and send to P1.20-P1.23

    IOCLR1 = RS;  // RS = 0 → Command register
    IOSET1 = E;   // Enable high
    delay_ms(2);  // Wait for LCD to latch data
    IOCLR1 = E;   // Enable low

    // Send lower nibble (D0-D3)
    IOCLR1 = LCD_D;              // Clear data bits
    IOSET1 = (cmd & 0x0F) << 20; // Mask lower nibble and send

    IOCLR1 = RS;  // RS = 0 → Command register
    IOSET1 = E;   // Enable high
    delay_ms(2);  // Wait for LCD to latch data
    IOCLR1 = E;   // Enable low
}

// Send a data character to the LCD
void LCD_DATA(unsigned char d)
{
    // Send upper nibble
    IOCLR1 = LCD_D;              // Clear data bits
    IOSET1 = (d & 0xF0) << 16;   // Mask upper nibble
    IOSET1 = RS;                 // RS = 1 → Data register
    IOSET1 = E;                  // Enable high
    delay_ms(2);
    IOCLR1 = E;                  // Enable low

    // Send lower nibble
    IOCLR1 = LCD_D;              // Clear data bits
    IOSET1 = (d & 0x0F) << 20;   // Mask lower nibble
    IOSET1 = RS;                 // RS = 1 → Data register
    IOSET1 = E;                  // Enable high
    delay_ms(2);
    IOCLR1 = E;                  // Enable low
}

// Initialize LCD in 4-bit mode
void LCD_INIT()
{
    IODIR1 = LCD_D | RS | RW | E; // Set data and control pins as output
    IOCLR1 = RW;                  // RW = 0 → Always write mode

    LCD_COMMAND(0x01); // Clear display
    LCD_COMMAND(0x02); // Return home
    LCD_COMMAND(0x0C); // Display ON, Cursor OFF
    LCD_COMMAND(0x28); // 4-bit mode, 2 lines, 5x8 dots
}

// Print a string on LCD
void LCDPrintString(unsigned char *str) {
    unsigned char count = 0;
    while (*str) {
        LCD_DATA(*str++); // Send each character
        count++;
        if (count == 16)  // If we reach end of first line
            LCD_COMMAND(0xC0); // Move to second line
    }
}

// Print an integer on LCD
void LCDPrintInt(int num) {
    char buffer[20];
    sprintf(buffer, "%d", num); // Convert integer to string
    LCDPrintString((unsigned char*)buffer);
}

// Print a floating-point number on LCD
void LCDPrintFloat(float num) {
    char buffer[20];
    sprintf(buffer, "%.5f", num); // Convert float to string (5 decimal places)
    LCDPrintString((unsigned char*)buffer);
}
