#include <util/delay.h>

#include <avr/io.h>


#define OUTPORT     PORTF
#define OUTDDR      DDRF

void delay(void) {
	int i;
	for(i=0; i<10;i++){
		_delay_ms(10);
	}
}
void ledder( void )
{
    OUTDDR  = 0xff;             // set bit 0 of output port to output 

    while (1)
    {
		OUTPORT = 0xff;
		delay();
		OUTPORT = 0x0;
		delay();
    }
}
