#include "HC_SR04.h"

void HCSR04_INIT(void)
{
    IO0DIR |= TRIG_PIN; 
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

float Range(void)
{
    float distance;
    unsigned int timer_value = 0;

    Pulse(); 
	
    while (!ECHO_PIN);

    T0TCR = 0x02; // Reset timer
    T0TCR = 0x01; // Start timer

    while (ECHO_PIN);

    T0TCR = 0x00; 
    timer_value = T0TC;

    // 1 cm 58 ~ 59 s so max is 6.5 meter
    // Check for timeout (38ms = ~max range)
    if (timer_value < 38000) 
        distance = (timer_value * 0.0343) / 2.0;
    else
        distance = -1.0; // Return -1 or 0 to indicate "Out of Range"

    return distance;
}
