#!/bin/sh

#Compiler specific variables
CC       := avr-gcc
OBJCONV  := avr-objcopy
UPLOADER := avrdude

#Device specific variables
DEVICE      = atmega328p
PORT        = /dev/ttyUSB0
PROGRAMMER  = arduino
BAUD        = 57600
MEMORY      = flash
OPERATION   = w
CPU_FREQ    = 16000000L

#Build specific variables
PROG_NAME  = test_uart
FILEFORMAT = i
CFLAGS     = -mmcu=$(DEVICE) -DF_CPU=$(CPU_FREQ) -Os -Wall
SRC_FILES  = $(PROG_NAME).c


.PHONY: all build upload clean

all: build upload

build :
	@$(MAKE) $(PROG_NAME).hex

$(PROG_NAME).hex : $(PROG_NAME).out
	@$(OBJCONV) -j .text -j .data -O ihex $< $@

$(PROG_NAME).out : $(PROG_NAME).o
	@$(CC) $(CFLAGS) -o $@ $<

$(PROG_NAME).o : $(SRC_FILES)
	@$(CC) $(CFLAGS) -c $<


upload :
	@$(UPLOADER)  -p $(DEVICE) -b $(BAUD) -P $(PORT) -c $(PROGRAMMER) -U $(MEMORY):$(OPERATION):$(PROG_NAME).hex:$(FILEFORMAT)

clean:
	@rm $(PROG_NAME).hex
	@rm $(PROG_NAME).out
	@rm $(PROG_NAME).o

