/* as of http://www.appelsiini.net/2011/simple-usart-with-avr-libc */

void uart_init(void) ;
void uart_putchar(char c) ;
#define uartPutc uart_putchar
void printHex(uchar c);
char uart_getchar(void) ;
void uart_puts(char *str);
void uart_printhex(unsigned char c);

register unsigned char fastCounter asm ("r13");
register unsigned char fastCounter2 asm ("r12");


#define UDEBUG(s)       uart_puts(s);

