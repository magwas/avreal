extern char UBRR1H ;
extern char UBRR1L ;
extern char UCSR1A;
extern char UCSR1B;
extern char UCSR1C;
extern char UDR1;
#define bit_is_clear(sfr, bit) (!(sfr & _BV(bit)))
#define bit_is_set(sfr, bit) (!bit_is_clear(sfr,bit))
#define loop_until_bit_is_clear(sfr, bit) do { } while (bit_is_set(sfr, bit))
#define loop_until_bit_is_set(sfr, bit) do { } while (bit_is_clear(sfr, bit))
#define UBRRH_VALUE 0
#define UBRRL_VALUE 42
#define U2X0 1
#define UCSZ11 2
#define UCSZ10 3
#define RXEN1 4
#define TXEN1 5
#define UDRE1 6
#define RXC1 4
#define TXC1 6
#define _BV(i) (1<<i)

