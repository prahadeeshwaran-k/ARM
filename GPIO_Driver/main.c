#include <LPC21xx.h>
#include "Delay.h"
void delay(uint32_t sec);
void PinWrite(unsigned char PORTNUM, unsigned char PINNUM, unsigned char PINVAL);
int main() {
    // Set P0.16 as output once
    IODIR0 |= (1 << 16);

    while (1) {
        PinWrite(0, 16, 1);  // LED ON
        delay(1);            // 1 second
        PinWrite(0, 16, 0);  // LED OFF
        delay(1);            // 1 second
    }
}

void PinWrite(unsigned char PORTNUM, unsigned char PINNUM, unsigned char PINVAL) {
    if (PINNUM > 31 || (PINVAL != 0 && PINVAL != 1))
        return;

    switch (PORTNUM) {
        case 0:
            if (PINVAL)
                IOSET0 = (1 << PINNUM);
            else
                IOCLR0 = (1 << PINNUM);
            break;

        case 1:
            if (PINVAL)
                IOSET1 = (1 << PINNUM);
            else
                IOCLR1 = (1 << PINNUM);
            break;
    }
}
