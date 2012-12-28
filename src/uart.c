/* as of http://www.appelsiini.net/2011/simple-usart-with-avr-libc */

#include <util/setbaud.h>
#include <avr/io.h>
#include "oddebug.h"
#include "ringbuffer.h"
#include "uart.h"


unsigned char uartrxbuf[uartBufLen+4];
unsigned char uarttxbuf[uartBufLen+4];

void uartInit(void) {
	ringbufferInit(uartRxBuf,uartBufLen);
	ringbufferInit(uartTxBuf,uartBufLen);
	UBRR1H = UBRRH_VALUE;
	UBRR1L = UBRRL_VALUE;

#if USE_2X
	UCSR1A |= _BV(U2X0);
#else
	UCSR1A &= ~(_BV(U2X0));
#endif

	UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); /* 8-bit data */ 
	UCSR1B = _BV(RXEN1) | _BV(TXEN1);   /* Enable RX and TX */
}

/* FIXME blocking */
void uartPutChar(char c) {
	return ringbufferPutChar(uartTxBuf,c);
}

unsigned char uartGetChar() {
	return ringbufferGetChar(uartRxBuf);
}

void uartTransmit(char c) {
	loop_until_bit_is_set(UCSR1A, UDRE1); /* Wait until data register empty. */
	UDR1 = c;
}

unsigned char uartReceive(void) {
	loop_until_bit_is_set(UCSR1A, RXC1);
	return UDR1;
}

void uartDo(void) {
	/*transmit*/
	if ((! ringbufferEmpty(uartTxBuf)) && bit_is_set(UCSR1A,UDRE1)) {
		UDR1 = ringbufferGetChar(uartTxBuf);
	}
	/*receive*/
	if ((! ringbufferFull(uartRxBuf)) && bit_is_set(UCSR1A,RXC1)) {
		unsigned char c;
		c = UDR1;
		ringbufferPutChar(uartRxBuf,c);
	}
}

void uartPuts(char *str){
	char * p;
	for(p=str;*p!=0;p++) {
		uartPutChar(*p);
	}
	uartPutChar('\n');
	uartPutChar('\r');
}


unsigned char hexAscii(unsigned char h)
{
    h &= 0xf;
    if(h >= 10)
        return  ('a' - 10 + h) ;
    h += '0';
    return h;
}

void uartPrintHex(unsigned char c)
{
    uartPutChar(hexAscii(c >> 4));
    uartPutChar(hexAscii(c));
}

#if DEBUG_LEVEL > 0

#warning "Never compile production devices with debugging enabled"

void    odDebug(unsigned char prefix, unsigned char *data, unsigned char len)
{
    uartPrintHex(prefix);
    uartPutChar(':');
    while(len--){
        uartPutChar(' ');
        uartPrintHex(*data++);
    }
    uartPutChar('\r');
    uartPutChar('\n');
}

#endif
