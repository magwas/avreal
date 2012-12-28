#include <usbdrv.h>
#include "ringbuffer.h"
#include "uart.h"
#include "cmd.h"
#include <oddebug.h>


unsigned char cmdBuf[16];
unsigned char cmdBufP;

void cmdInit() {
	cmdBufP = 0;
}

int p;

void cmdIn(unsigned char c) {
	if (c != '\r') {
		if (cmdBufP<16) {
			cmdBuf[cmdBufP++]=c;
		}else{
			cmdInit();
		}
		return;
	}
	uartPutChar('\n');
	unsigned char * i;
	int j;
	if(cmdBufP>1) {
		p=0;
		for(j=1;j<cmdBufP;j++) {
			p = p <<4;
			p += cmdBuf[j]-'0';
		}
	}
	switch(cmdBuf[0]) {
		case 'X':
			UDEBUG("sending zero");
			usbSetInterrupt((unsigned char *)"",0);
			UDEBUG("zero sent");
			break;
		case 'x':
			UDEBUG("sending hi");
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
			for(i=(unsigned char *)p;i<(unsigned char *)p+16;i++) {
				uartPrintHex(*i);
			}
			break;
	}
	cmdInit();
	uartPutChar('\n');
	uartPutChar('\r');
}
