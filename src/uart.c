/* as of http://www.appelsiini.net/2011/simple-usart-with-avr-libc */

#include <util/setbaud.h>
#include <avr/io.h>

void uart_init(void) {
	UBRR1H = UBRRH_VALUE;
	UBRR1L = UBRRL_VALUE;

#if USE_2X
	UCSR1A |= _BV(U2X0);
#else
	UCSR1A &= ~(_BV(U2X0));
#endif

	UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); /* 8-bit data */ 
	UCSR1B = _BV(RXEN1) | _BV(TXEN1);   /* Enable RX and TX */
}

/* FIXME blocking */
void uart_putchar(char c) {
	loop_until_bit_is_set(UCSR1A, UDRE1); /* Wait until data register empty. */
	UDR1 = c;
}

char uart_getchar(void) {
	if (! (UCSR1A&(1<<RXC1))) {
		return(0); 
	}
	return UDR1;
}

void uart_puts(char *str){
	char * p;
	for(p=str;*p!=0;p++) {
		uart_putchar(*p);
	}
	uart_putchar('\n');
	uart_putchar('\r');
}

