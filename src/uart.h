
#define uartBufLen 63
extern unsigned char uartrxbuf[uartBufLen+3];
extern unsigned char uarttxbuf[uartBufLen+3];
#define uartRxBuf ((RingBuffer) uartrxbuf)
#define uartTxBuf ((RingBuffer) uarttxbuf)


void uartInit(void) ;
void uartDo(void);
//async
void uartPutChar(char c) ;
unsigned char uartGetChar(void) ;
//sync
void uartTransmit(char c);
unsigned char uartReceive(void);

void uartPuts(char *str);
void uartPrintHex(unsigned char c);

