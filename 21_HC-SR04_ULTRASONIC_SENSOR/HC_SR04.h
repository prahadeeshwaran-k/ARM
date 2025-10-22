#ifndef __HCSR04_H__
#define __HCSR04_H__

#include <LPC21xx.h>

#define TRIG_PIN   (1 << 8)
#define ECHO_PIN   (IO0PIN & (1 << 9))

void HCSR04_INIT(void);
void Pulse(void);
unsigned int Range(void);

#endif // __HCSR04_H__
