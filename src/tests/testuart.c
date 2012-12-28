#include "ringbuffer.h"
#include "uart.h"
#include <stdio.h>
#include <assert.h>
#include <avr/io.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

unsigned char alarmed = 0;
void (*fptr)(void) = NULL;

void  ALARMhandler(int sig)
{
	signal(SIGALRM, SIG_IGN);          /* ignore this signal       */
	printf("alarmed\n");
	alarmed = 1;
	assert(NULL != fptr);
	(*fptr)();
	printf("UCSR1A = %02x UDR1 = %02x\n",UCSR1A,UDR1);
	signal(SIGALRM, ALARMhandler);     /* reinstall the handler    */
}

void canxmit(void) {
	UCSR1A =  UCSR1A | (1<<UDRE1);
}

void canrcv(void) {
	UCSR1A =  UCSR1A | (1<<RXC1);
}


int main(void) {
	signal(SIGALRM, ALARMhandler); 
	unsigned int i;
	uartInit();
	assert (UBRR1H == UBRRH_VALUE);
	assert(uartRxBuf[0] == 63);
	assert(uartRxBuf[1] == 0);
	assert(uartRxBuf[2] == 0);
	assert(uartTxBuf[0] == 63);
	assert(uartTxBuf[1] == 0);
	assert(uartTxBuf[2] == 0);
	assert((uartRxBuf - uartTxBuf) == 68 );

	char * str="h012345678\n\r";
	uartPutChar('h');
	uartPuts("012345678");
	for (i=0;i<strlen(str);i++) {
		assert(str[i] == ringbufferGetChar(uartTxBuf));
	}
	assert(ringbufferEmpty(uartTxBuf));

	uartPrintHex(0x1A);
	assert('1' == ringbufferGetChar(uartTxBuf));
	assert('a' == ringbufferGetChar(uartTxBuf));

	assert(ringbufferEmpty(uartRxBuf));
	for(i=0;i<strlen(str);i++) {
		ringbufferPutChar(uartRxBuf,str[i]);
	}
	assert(!ringbufferEmpty(uartRxBuf));
	
	for(i=0;i<strlen(str);i++) {
		assert(!ringbufferEmpty(uartRxBuf));
		unsigned char c;
		c = uartGetChar();
		//c = ringbufferGetChar(uartRxBuf);
		//printf("%02x %02x %u\n",str[i], c, i);
		assert(str[i] == c );
	}
	assert(ringbufferEmpty(uartRxBuf));

	alarm(1);
	canxmit();
	uartTransmit('a');
	assert(UDR1 == 'a');

	canrcv();
	UDR1 = 'b';
	assert('b' == uartReceive());

	assert(ringbufferEmpty(uartTxBuf));
	UCSR1A = 0;
	uartPutChar('b');
	alarmed=0;fptr = canxmit;
	UDR1 = 0;
	while(!UDR1) {
		uartDo();
	}
	assert(ringbufferEmpty(uartTxBuf));
	assert(UDR1 == 'b');

	UDR1 = 'c';
	assert(ringbufferEmpty(uartRxBuf));
	alarmed=0;fptr = canrcv;
	alarm(1);
	//printf("wr=%u rd=%u c=%02x\n",uartRxBuf[1],uartRxBuf[2], uartRxBuf[uartRxBuf[2]]);
	while(ringbufferEmpty(uartRxBuf)) {
		//usleep(300000);
		//printf("wr=%u rd=%u c=%02x\n",uartRxBuf[1],uartRxBuf[2], uartRxBuf[uartRxBuf[2]]);
		uartDo();
	}
	//printf("Wr=%u rd=%u c=%02x l=%u\n",uartRxBuf[1],uartRxBuf[2], uartRxBuf[uartRxBuf[2]],uartRxBuf[0]);
	assert('c' == uartGetChar());
	//printf("Wr=%u rd=%u c=%02x\n",uartRxBuf[1],uartRxBuf[2], uartRxBuf[uartRxBuf[2]]);
	assert(ringbufferEmpty(uartRxBuf));

	
	return 0;
}
