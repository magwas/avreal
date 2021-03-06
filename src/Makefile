###############################################################################
# Makefile for the project avreal
###############################################################################

DEBUG=2

## General Flags
PROJECT = avreal
#MCU = atmega8
#MCU = atmega16
MCU = at90can32
#MCU = atmega88
#MCU = atmega168
TARGET = avreal.elf
CC = avr-gcc

USBDRV = ../v-usb/usbdrv/

## Include Directories
INCLUDES = -I"." -I$(USBDRV)
## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -DF_CPU=16000000UL -Os -fsigned-char
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 
CFLAGS += -DBAUD=115200 -DDEBUG_LEVEL=$(DEBUG) $(INCLUDES)

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -lc


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = main.o led.o uart.o cmd.o usbdrvasm.o usbdrv.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) avreal.hex avreal.eep avreal.lss## Compile
usbdrvasm.o: $(USBDRV)/usbdrvasm.S
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

main.o: main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

oddebug.o: $(USBDRV)/oddebug.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usbdrv.o: $(USBDRV)/usbdrv.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S --prefix-addresses $< > $@

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) avreal.elf dep/* avreal.hex avreal.eep avreal.lss

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

prog: avreal.hex
	avrdude -p c32 -c gpio -v -U flash:w:avreal.hex

debug: avreal.elf
	simulavr -d at90can32 --file avreal.elf -g & ddd --debugger avr-gdb&

fuses:
	avrdude -p c32 -c gpio -U lfuse:w:0xde:m -U hfuse:w:0x99:m -U efuse:w:0xff:m

reset:
	avrdude -p c32 -c gpio -U lfuse:r:-:h 

