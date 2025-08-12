#include<LPC21XX.H>
#include"delay.h"

#define seg_d 0xff //P0.0 to P0.7
unsigned char Seg_Lut[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,};

int main(){
	unsigned char Digit = 0;
	int i;
	IODIR0 = seg_d;
	IOSET0 = seg_d;
	while(1){
		for(i = 0 ; i<10 ; i++){
			IOCLR0 = seg_d;
			IOSET0 = Seg_Lut[Digit++];
			delay(1);
		}
	}
}
