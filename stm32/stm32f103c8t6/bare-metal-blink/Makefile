# Makefile for building STM32F103C8T6 code using blue-pill board

CC       :=  arm-none-eabi-gcc
CP       :=  arm-none-eabi-objcopy
CPU      :=  cortex-m3
LDSCRIPT :=  stm32f103c8t6.ld
PROGNAME :=  blink
CFLAGS    =  -mcpu=$(CPU) -O0 -mthumb -Wall
LDFLAGS   =  -nostdlib -T $(LDSCRIPT) -Wl,-Map=$(PROGNAME).map
OUTFORMAT:=  binary
OBJECTS   =  $(PROGNAME).o startup_stm32f103c8t6.o
FLASHADDR:=  0x08000000
UPLOADCMD:=  st-flash write $(PROGNAME).bin $(FLASHADDR) 

.PHONY: all clean
all : $(OBJECTS) $(PROGNAME).elf $(PROGNAME).bin

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(PROGNAME).elf : $(OBJECTS)
	@$(CC) $(LDFLAGS) $^ -o $@

$(PROGNAME).bin : $(PROGNAME).elf
	@$(CP) -O $(OUTFORMAT) $< $@

clean :
	@rm -f $(OBJECTS) $(PROGNAME).elf $(PROGNAME).map $(PROGNAME).bin

upload : $(PROGNAME).bin
	@$(UPLOADCMD)
