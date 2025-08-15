void PinWrite(unsigned char PORTNUM, unsigned char PINNUM, unsigned char PINVAL) {
    // PINNUM must be 0–31, PINVAL must be 0 or 1
    if (PINNUM > 31 || ( (PINVAL != 0) && (PINVAL != 1) )) {
        return 0;
    }

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

        default:
            break; // Invalid port
    }
}

unsigned char PinRead(unsigned char PORTNUM, unsigned char PINNUM){
	// PINNUM must be 0–31
    if (PINNUM > 31) {
        return 0;
    }
		
		switch (PORTNUM) {
        case 0:
            return (IOPIN0 >> PINNUM) & 1;
        case 1:
            return (IOPIN1 >> PINNUM) & 1;
        default:
            break; // Invalid port
    }
		
}

void PortWrite(unsigned char PORTNUM, unsigned char PORTPOS, unsigned char PORTVAL) {
	if (PORTPOS > 3 || (PORTNUM == 1 && PORTPOS > 1)) {
					return; // invalid position
			}
    unsigned int shift = PORTPOS * 8; // each block = 8 bits
    unsigned int mask  = 0xFF << shift; // mask for the block

	switch (PORTNUM) {
        case 0:
            IOCLR0 = mask;                  // clear block
            IOSET0 = (PORTVAL & 0xFF) << shift; // set new value
            break;
        case 1:
            IOCLR1 = mask;
            IOSET1 = (PORTVAL & 0xFF) << shift;
            break;

        default:
            break; // Invalid port
    }
}

unsigned char PortRead(unsigned char PORTNUM, unsigned char PORTPOS) {
    if (PORTPOS > 3 || (PORTNUM == 1 && PORTPOS > 1)) {
        return 0;
    }
    unsigned int shift = PORTPOS * 8;
    unsigned int mask  = 0xFF << shift;

    switch (PORTNUM) {
        case 0: return (IOPIN0 & mask) >> shift;
        case 1: return (IOPIN1 & mask) >> shift;
        default: return 0;
    }
}


