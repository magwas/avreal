#include <util/delay.h>

#include <avr/io.h>


#define OUTPORT     PORTF
#define OUTDDR      DDRF


void ledder( void )
{
    OUTDDR  = 0xff;             // set bit 0 of output port to output 

    while (1)
    {
	OUTPORT = 0xff;
	_delay_ms(500);
	OUTPORT = 0x0;
	_delay_ms(500);
    }
}
