#include <LPC21XX.H>
#include "i2c.h"
#include "eeprom.h" //EEPROM
#include "Delay.h"
#include <string.h>
#include "uart.h"

#define gLED 19
#define rLED 16
#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr
	
int main(){
	 unsigned char ch;
	 i2c_init();
	 UART0_CONFIG();
	 UART0_STR("I2C Demo With EEPROM\r\n");
	 IODIR1 |=gLED|rLED;
	 i2c_eeprom_write(I2C_EEPROM_SA,0X00,'A');
	 ch = i2c_eeprom_read(I2C_EEPROM_SA,0X00);
	 //I2C_eeprom_page_write(I2C_EEPROM_SA,0x00,"ABCDEFGH",8);
	 //I2C_eeprom_seq_read(I2C_EEPROM_SA,0x00,p,8);
	 delay_ms(100);
	 //if(strcmp(p,"ABCDEFGH")==0)
	 if(ch=='A')
	 {
		 IOSET1 = gLED;;
		 UART0_STR("Data Present");
	 }		
	 else
	 {
		 IOSET1 = rLED;
		 UART0_STR("Data Not Present");
     }
	 while(1);
}
