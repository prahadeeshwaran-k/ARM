#include<LPC21XX.H>
#include"Delay.h"
#define C0 (IOPIN1&(1<<20))
#define C1 (IOPIN1&(1<<21))
#define C2 (IOPIN1&(1<<22))
#define C3 (IOPIN1&(1<<23))

#define R0 1<<16
#define R1 1<<17
#define R2 1<<18
#define R3 1<<19

unsigned int keypad_lut[4][4]={
	{ 1, 2, 3, 4},
	{ 5, 6, 7, 8},
	{ 9,10,11,12},
	{13,14,15,16}
};

unsigned int keyScan(void){
	unsigned char row,col;
	PINSEL2 = 0;
	IODIR1 = R0 | R1 | R2 | R3 ;//SET Direction Rows as Output.

	while(1){
		IOCLR1 = R0 | R1 | R2 | R3 ;
		IOSET1 = C0 | C1 |C2 | C3 ;

		while((C0 && C1 && C2 && C3) == 1);

		//For ROW 0
		IOCLR1 = R0;
		IOSET1 = R1 | R2 | R3 ;
		if(((C0 && C1 && C2 && C3) == 0)){
			row = 0;
			break;
		}
		//For ROW 1
		IOCLR1 = R1;
		IOSET1 = R0 | R2 | R3 ;
		if(((C0 && C1 && C2 && C3) == 0)){
			row = 1;
			break;
		}
		//For ROW 2
		IOCLR1 = R2;
		IOSET1 = R0 | R1 | R3 ;
		if(((C0 && C1 && C2 && C3) == 0)){
			row = 2;
			break;
		}
		//For ROW 3
		IOCLR1 = R3;
		IOSET1 = R0 | R1 | R2 ;
		if(((C0 && C1 && C2 && C3) == 0)){
			row = 3;
			break;
		}
	}  // END OF INNER LOOP

	if(C0 == 0)
		col =0;
	else if(C1 ==0)
		col =1;
	else if(C2 ==0)
		col =2;
	else if(C3 ==0)
		col =3;

	delay_ms(20);
	while((C0 && C1 && C2 && C3) == 0);//WAIT FOR KEY RELEASE

	return keypad_lut[row][col];
}