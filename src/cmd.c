#include <usbdrv.h>
#include "uart.h"
#include "cmd.h"


enum {
        CMD_STATE_BEGIN = 0,
};

char cmd_state;

void cmd_init() {
	cmd_state = CMD_STATE_BEGIN;
}

void cmd_in(unsigned char c) {
	switch(c) {
		case 'x':
			usbSetInterrupt((unsigned char *)"hi!\n\r",5);
			UDEBUG("hi sent");
			// no break
		case 'l':
			printHex(usbTxStatus1.len);
			break;
		case 'r':
			printHex(usbRxLen);
			break;
		case 'c':
			printHex(fastCounter);
			break;
		case 'C':
			printHex(fastCounter2);
			break;
		default:
			cmd_init();
	}
}
