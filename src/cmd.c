#include <usbdrv.h>
#include "ringbuffer.h"
#include "uart.h"
#include "cmd.h"
#include <oddebug.h>


void cmd_init() {
}


void do_stats() {
}

void cmd_in(unsigned char c) {
	unsigned char * i;
/*
	unsigned int j;
	for(j=0;j<64;j++) {
		uartTransmit(hexAscii((uartTxBuf[j])>>4));
		uartTransmit(hexAscii((uartTxBuf[j])));
	}
	uartTransmit('\n');
	uartTransmit('\r');
*/
	switch(c) {
		case 'X':
			UDEBUG("sending zero");
			usbSetInterrupt((unsigned char *)"",0);
			break;
		case 'x':
			usbSetInterrupt((unsigned char *)"hi!\n\r",5);
			UDEBUG("hi sent");
			// no break
		case 'l':
			uartPrintHex(usbTxStatus1.len);
			DBG1(0xfa,usbTxStatus1.buffer,usbTxStatus1.len);
			break;
		case 'r':
			uartPrintHex(usbRxLen);
			break;
		case 'd':
			for(i=(unsigned char *)4;i<(unsigned char *)14;i++) {
				uartPrintHex(*i);
			}
			uartPutChar('\n');
			uartPutChar('\r');
			break;
		default:
			cmd_init();
	}
}
