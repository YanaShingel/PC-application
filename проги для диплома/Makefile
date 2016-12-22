TARG=main
 
CC = avr-gcc
OBJCOPY = avr-objcopy
CLOCK = 16000000
AVRDUDE = avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 57600 
# Задаем из каких файлов собирать проект, можно указать несколько файлов
SRCS= main.c
 
OBJS = $(SRCS:.c=.o)
 
# Задаем для какого микроконтроллера будем компилировать (atmega8)
MCU=atmega328p

COMPILE = -mmcu=$(MCU) -Wall -g -Os -Werror
 
# Флаги компилятора, при помощи F_CPU определяем частоту на которой будет работать контроллер,
CFLAGS =  $(COMPILE) -DF_CPU=$(CLOCK)
LDFLAGS = $(COMPILE) 
 
all: $(TARG)
 
$(TARG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@.elf  $(OBJS) -lm
	$(OBJCOPY) -O binary -R .eeprom -R .nwram  $@.elf $@.bin
	$(OBJCOPY) -O ihex -R .eeprom -R .nwram  $@.elf $@.hex
 
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

clean:
	rm -f *.elf *.bin *.hex  $(OBJS) *.map
