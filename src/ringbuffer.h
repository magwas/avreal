
#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

typedef char * RingBuffer;
/*
conceptually:
struct RingBuffer {
	unsigned char len;
	unsigned char wrp;
	unsigned char rdp;
	unsigned char buf[]
}
*/

static inline void ringbufferInit(RingBuffer rb, unsigned char len) {
	/* len must be 2^n -1 */
	rb[0]=len;
	rb[1]=0;
	rb[2]=0;
}

#define _ringbufferLen 0
#define _ringbufferWr 1
#define _ringbufferRd 2

static inline void ringbufferIncPtr(RingBuffer rb, unsigned char pos) {
 	rb[pos] = ((rb[pos]+1)&rb[_ringbufferLen]);
}

static inline char ringbufferEmpty(RingBuffer rb) {
	return (rb[1] == rb[2]);
}

static inline char ringbufferFull(RingBuffer rb) {
	return (rb[_ringbufferRd] == ((rb[_ringbufferWr]+1)&rb[_ringbufferLen]));
}

static inline void ringbufferPutChar(RingBuffer rb, unsigned char c) {
	if (ringbufferFull(rb))
		/* the caller should have used ringbufferFull */
		return;
	rb[3+rb[_ringbufferWr]]=c;
	ringbufferIncPtr(rb,_ringbufferWr);
	return;
}

static inline unsigned char ringbufferGetChar(RingBuffer rb) {
	if ( ringbufferEmpty(rb))
		/* the caller should have used ringbufferEmpty */
		return 0; 
	
	unsigned char r = rb[3+rb[_ringbufferRd]];
	ringbufferIncPtr(rb,_ringbufferRd);
	return r;
}

#endif /* _RINGBUFFER_H */

