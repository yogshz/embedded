#!/bin/sh

#Compiler specific variables
CC       := avr-gcc
OBJCONV  := avr-objcopy
UPLOADER := avrdude

#Device specific variables
MCU_DEVICE  = atmega8a
PROG_DEVICE = atmega8
PORT        = /dev/ttyUSB0
PROGRAMMER  = avrisp
BAUD        = 19200
MEMORY      = flash
OPERATION   = w
CPU_FREQ    = 1000000UL

#Build specific variables
PROG_NAME  = test_interrupt
FILEFORMAT = i
CFLAGS     = -mmcu=$(MCU_DEVICE) -DF_CPU=$(CPU_FREQ) -Os -Wall -v
SRC_FILES  = $(PROG_NAME).c


.PHONY: all build upload clean

all: build

build :
	@$(MAKE) $(PROG_NAME).hex

$(PROG_NAME).hex : $(PROG_NAME).out
	@$(OBJCONV) -j .text -j .data -O ihex $< $@

$(PROG_NAME).out : $(PROG_NAME).o
	@$(CC) $(CFLAGS) -o $@ $<

$(PROG_NAME).o : $(SRC_FILES)
	@$(CC) $(CFLAGS) -c $<


upload :
	@$(UPLOADER)  -p $(PROG_DEVICE) -b $(BAUD) -P $(PORT) -c $(PROGRAMMER) -U $(MEMORY):$(OPERATION):$(PROG_NAME).hex:$(FILEFORMAT)

clean:
	@rm $(PROG_NAME).hex
	@rm $(PROG_NAME).out
	@rm $(PROG_NAME).o

