CFLAGS = -I ./mock -I ..
COMPILE = gcc $(CFLAGS) -c 

OBJECTS= io.o  testrb.o  uart.o testuart.o

all: testrb testuart

clean:
	rm -f  $(OBJECTS)


testrb:  testrb.o 
	gcc -o testrb testrb.o ; ./testrb

testuart: io.o  testuart.o  uart.o
	gcc -o testuart io.o  testuart.o  uart.o; ./testuart

io.o: mock/io.c
	$(COMPILE) $<

testrb.o: testrb.c
	$(COMPILE) $<

uart.o: ../uart.c
	$(COMPILE) $<

