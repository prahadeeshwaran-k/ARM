/* ================== Motor Input Control Table ==================
| IN1 | IN2 | IN3 | IN4 | Spinning Direction | Char |
|-----|-----|-----|-----|---------------------|------|
|  0  |  0  |  0  |  0  | Motor OFF           |  0   |
|  1  |  0  |  1  |  0  | Forward             |  1   |
|  0  |  1  |  0  |  1  | Backward            |  2   |
|  1  |  1  |  1  |  1  | Motor OFF           |  -   |
================================================================ */

/* ================== Motor Direction Operation ==================
| Direction | Operation | Motor1 | Motor2 |
|-----------|------------|--------|--------|
| Forward   | F          |   1    |   1    |
| Backward  | B          |   2    |   2    |
| Stop      | S          |   0    |   0    |
| Left      | L          |   0    |   1    |
| Right     | R          |   1    |   0    |
================================================================ */

#include<LPC21XX.H>
#include "UART.h"

#define IN1 1<<4
#define IN2	1<<5
#define IN3 1<<6
#define IN4	1<<7

#define STOP     0
#define FORWARD  1
#define BACKWARD 2

void State(unsigned char direction,int Terminal1,int Terminal2){
	switch(direction){
		//Stop Condition
		case STOP:
			IOCLR0 = Terminal1|Terminal2;
			break;
		//Forward Condition
		case FORWARD:
			IOSET0 = Terminal1;
			IOCLR0 = Terminal2;
			break;
		//Backward Condition
		case BACKWARD:
			IOSET0 = Terminal2;
			IOCLR0 = Terminal1;
			break;
	}
}

int main()
{
	unsigned char op;
	
	State(STOP,IN1,IN2); //Motor 1 -> Stop
	State(STOP,IN3,IN4); //Motor 2 -> Stop
	IODIR0 |= (IN1 | IN2 | IN3 | IN4);  // set motor pins as output
	
	UART0_CONFIG();
	
	while(1)
	{	
		op = UART0_RX();
    switch(op){

				case 'F'://Forward
					State(FORWARD, IN1, IN2); //Motor 1 -> Forward
					State(FORWARD, IN3, IN4); //Motor 2 -> Forward
					break;
				
				case 'B'://Backward
					State(BACKWARD, IN1, IN2); //Motor 1 -> Backward
					State(BACKWARD, IN3, IN4); //Motor 2 -> Backward
					break;
				
				case 'S'://Stop
					State(STOP, IN1, IN2); //Motor 1 -> Stop
					State(STOP, IN3, IN4); //Motor 2 -> Stop
					break;
				
				case 'L'://Left
					State(STOP, IN1, IN2); //Motor 1 -> Stop
					State(FORWARD, IN3, IN4); //Motor 2 -> Forward
					break;
				
				case 'R'://Right
					State(FORWARD, IN1, IN2); //Motor 1 -> Forward
					State(STOP, IN3, IN4); //Motor 2 -> Stop
					break;
				
				default: //Stop
					State(STOP, IN1, IN2); //Motor 1 -> Stop
					State(STOP, IN3, IN4); //Motor 2 -> Stop
					break;
				
		}//Switch End

	}//SuperLoop

}

