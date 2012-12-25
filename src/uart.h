/* as of http://www.appelsiini.net/2011/simple-usart-with-avr-libc */

void uart_init(void) ;
void uart_putchar(char c) ;
#define uartPutc uart_putchar
char uart_getchar(void) ;
void uart_puts(char *str);

#define UDEBUG(s)       uart_puts(s);

