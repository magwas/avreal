#include "ringbuffer.h"
#include "uart.h"
#include <stdio.h>
#include <assert.h>

#define testbuflen 63
unsigned char testbuffer[testbuflen+3];
#define testBuffer ((RingBuffer)testbuffer)

int main(void) {
	ringbufferInit(testBuffer,testbuflen);
	assert(testBuffer[0] == 63);
	assert(testBuffer[1] == 0);
	assert(testBuffer[2] == 0);

	ringbufferIncPtr(testBuffer,_ringbufferWr);
	assert(testBuffer[1] == 1);
	testBuffer[1] = 0;
	assert(testBuffer[1] == 0);
	ringbufferPutChar(testBuffer,'a');
	unsigned char t;
	assert(!ringbufferEmpty(testBuffer));
	assert(testBuffer[0] == 63);
	assert(testBuffer[1] == 1);
	assert(testBuffer[2] == 0);
	assert('a' == ringbufferGetChar(testBuffer));

	int i;
	for(i=0;i<250;i++) {
		ringbufferPutChar(testBuffer,i);
		assert(!ringbufferEmpty(testBuffer));
		assert((i) == ringbufferGetChar(testBuffer));
		assert(ringbufferEmpty(testBuffer));
	}
	for(i=0;i<62;i++) {
		ringbufferPutChar(testBuffer,'0'+i);
	}
	assert(!ringbufferFull(testBuffer));
	ringbufferPutChar(testBuffer,'0'+i);
	assert(ringbufferFull(testBuffer));
	for(i=0;i<63;i++) {
		assert(('0'+i) == ringbufferGetChar(testBuffer));
	}
	return 0;
}
