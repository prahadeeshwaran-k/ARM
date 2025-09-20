#include <LPC21XX.H>
#include "Delay.h"
#include "I2C.h"
#include "AT24C08.h" //EEPROM
#include <string.h>


#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr
#define gLED 1<<16 //P1.16
#define rLED 1<<17 //P1.17

//u8 p[9] __attribute__((at(0x40000040)))="";
	
int main(){
	 unsigned char ch;
	 I2C_Init();
	 IODIR1=gLED|rLED;
	 I2C_eeprom_write(I2C_EEPROM_SA,0X00,'A');
	 ch = I2C_eeprom_read(I2C_EEPROM_SA,0X00);
	 //I2C_eeprom_page_write(I2C_EEPROM_SA,0x00,"ABCDEFGH",8);
	 //I2C_eeprom_seq_read(I2C_EEPROM_SA,0x00,p,8);
	 delay_ms(100);
	 //if(strcmp(p,"ABCDEFGH")==0)
	 if(ch=='A')
	 {
		 IOPIN1=gLED;
	 }		
	 else
	 {
		 IOPIN1=rLED;
     }
	 while(1);
}
