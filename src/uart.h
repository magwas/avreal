
#define uartBufLen 15
extern unsigned char uartrxbuf[uartBufLen+4];
extern unsigned char uarttxbuf[uartBufLen+4];
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

unsigned char hexAscii(unsigned char h);
void uartPrintHex(unsigned char c);

