#include <LPC21XX.H>
#include "Delay.h"
#include "can2.h"
#include "uart.h"
#include "LCD8Bit.h"

int main()

{	

    CAN2_MSG m1;
    can2_init();
    LCD_INIT();            // Initialize LCD
    LCD_COMMAND(0x01);     // Clear LCD

    // --- LINE 1: Dashboard ---

    LCD_COMMAND(0x80);     // 1st line
    LCDPrintString("Dashboard");

    // --- Fixed Labels on LCD ---

    LCD_COMMAND(0xC0);     // 2nd line
    LCDPrintString("Ultrasonic: ");   
    LCD_COMMAND(0x94);     // 3rd line
    LCDPrintString("Temp      : ");
    LCD_COMMAND(0xD4);     // 4th line
    LCDPrintString("HeadLight : ");

    while(1)
    {					       
        can2_rx(&m1);		
        if(m1.rtr == 0)
        {
            if(m1.id == 1)   // Ultrasonic value
            {	
			LCD_COMMAND(0xC0);
			LCDPrintString("Ultrasonic:     "); 
                LCD_COMMAND(0xC0 + 12);  
                LCDPrintInt(m1.byteA);
            }
            else if(m1.id == 2)   // Speed
            {
				LCD_COMMAND(0x94);     // 3rd line
    			LCDPrintString("Temp      :     ");
                LCD_COMMAND(0x94 + 12);
                LCDPrintInt(m1.byteA);
            }
            else if(m1.id == 3)   // HeadLight ON/OFF
            {
				LCD_COMMAND(0xD4);     // 4th line
    			LCDPrintString("HeadLight :     ");
                LCD_COMMAND(0xD4 + 12);
                if(m1.byteA == 0)
                   LCDPrintString("Off ");
               	else if(m1.byteA == 1)
                   LCDPrintString("on");
            }
          }	
     }

}

