#include "HCSR04.h"

void HCSR04_INIT(void)
{
    IO0DIR |= TRIG_PIN;   
    T1PR = 60-1;           
}

void Pulse(void)
{
    
    IO0SET = TRIG_PIN;
	
    T0TCR = 0x02; //Reset Timer
	T0TCR = 0x01; //Enable timer
	while(T0TC < 10); //wait until timer counter reaches the desired delay
	T0TCR = 0x00; //Disable timer
	
    IO0CLR = TRIG_PIN;
}

unsigned int Range(void)
{
    unsigned int get = 0;

    HCSR04_Pulse();
    while (!ECHO_PIN);

    T0TCR = 0x02;  // Reset timer
    T0TCR = 0x01;  // Start timer

    while (ECHO_PIN);

    T0TCR = 0x00;
    get = T0TC; 

    // Convert pulse duration to cm
    if (get < 38000) // 1 cm 58 ~ 59 s so max is 6.5 meter.
        get = (0.0343 * get)/2;  
    else
        get = 0;         // Out of range or timeout

    return get;
}
