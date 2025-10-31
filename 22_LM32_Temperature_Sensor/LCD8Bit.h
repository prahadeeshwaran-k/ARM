#include <stdio.h>

#define LCD_DATA_PIN 0XFF<<8
#define LCD_ENABLE 1<<17
#define LCD_REGISTER 1<<16

void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCDPrintString(unsigned char*);
void LCDPrintInt(int);
void LCDPrintFloat(float);
void LCDPrintFloat3(float);

void LCD_INIT(void){
	IODIR0  |= LCD_DATA_PIN|LCD_ENABLE|LCD_REGISTER;
	LCD_COMMAND(0X0C);
	LCD_COMMAND(0X38);
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X02);
}

void LCD_COMMAND(unsigned char CMD){
	IOCLR0 = LCD_DATA_PIN;
	IOSET0 = CMD<<8;
	IOCLR0 = LCD_REGISTER;
	IOSET0 = LCD_ENABLE;
	delay_ms(2);
	IOCLR0 = LCD_ENABLE;
}

void LCD_DATA(unsigned char DATA){
	IOCLR0 = LCD_DATA_PIN;
	IOSET0 = DATA<<8;
	IOSET0 = LCD_REGISTER;
	IOSET0 = LCD_ENABLE;
	delay_ms(2);
	IOCLR0 = LCD_ENABLE;
}

void LCDPrintString(unsigned char * str){
	unsigned char count =0;
	while(*str){
		LCD_DATA(*str++);
		count++;
		if(count == (unsigned char)16)
			LCD_COMMAND(0xC0);
	}
}

void LCDPrintInt(int num){
	char buffer[20];
	sprintf(buffer,"%d",num);
	LCDPrintString((unsigned char*)buffer);
}

void LCDPrintFloat(float num){
	char buffer[20];
	sprintf(buffer,"%.5f",num);
	LCDPrintString((unsigned char*)buffer);
}

void LCDPrintFloat3(float x){          // 3 decimal places
    char buf[24];
	int whole = (int)x;
    int frac  = (int)((x - (float)whole) * 1000.0f + (x>=0 ? 0.5f : -0.5f));
    if(frac < 0) frac = -frac;

    
    sprintf(buf, "%d.%03d", whole, frac);  // only %d, no %f
    LCDPrintString((unsigned char*)buf);
}

