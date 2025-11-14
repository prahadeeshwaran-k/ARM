#include <LPC21XX.H>
#include "can2.h"
#include "uart.h"
#include "LCD8Bit.h"
#include "Delay.h"

int main()
{	
    CAN2_MSG m1;
    
    can2_init();
    uart0_init(115200);
    
    LCD_INIT();            // Initialize LCD
    LCD_COMMAND(0x01);     // Clear LCD
    
    // --- LINE 1: Dashboard ---
    LCD_COMMAND(0x80);     // 1st line
    LCDPrintString("Dashboard");
    
    // --- Fixed Labels on LCD ---
    LCD_COMMAND(0xC0);     // 2nd line
    LCDPrintString("Ultrasonic: ");
    
    LCD_COMMAND(0x94);     // 3rd line
    LCDPrintString("Speed     : ");
    
    LCD_COMMAND(0xD4);     // 4th line
    LCDPrintString("HeadLight : ");
    
    uart0_tx_string("Dashboard\r\n");

    while(1)
    {					       
        can2_rx(&m1);
		
        if(m1.rtr == 0)
        {
            if(m1.id == 1)   // Ultrasonic value
            {
                // UART printing
                uart0_tx_string("ultrasonic: ");
                uart0_tx_integer(m1.byteA);
                uart0_tx_string("\r\n");

                // LCD update (line 2, position after label)
                LCD_COMMAND(0xC0 + 12);  
                LCDPrintInt(m1.byteA);
            }
            else if(m1.id == 2)   // Speed
            {
                uart0_tx_string("Speed: ");
                uart0_tx_integer(m1.byteA);
                uart0_tx_string("\r\n");

                // LCD update (line 3, position after label)
                LCD_COMMAND(0x94 + 12);
                LCDPrintInt(m1.byteA);
            }
            else if(m1.id == 3)   // HeadLight ON/OFF
            {
                uart0_tx_string("HeadLights: ");
                uart0_tx_integer(m1.byteA);
                uart0_tx_string("\r\n");

                // LCD update (line 4, position after label)
                LCD_COMMAND(0xD4 + 12);
                if(m1.byteA == 1)
                    LCDPrintString("ON ");
                else
                    LCDPrintString("OFF");
            }
            
          
        }	
    }
}

