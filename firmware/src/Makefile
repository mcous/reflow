# simple AVR Makefile
#
# written by michael cousins (github.com/mcous)
# released to the public domain

# Makefile
#
# targets:
#   all:    compiles the source code
#   test:   tests the isp connection to the mcu
#   flash:  writes compiled hex file to the mcu's flash memory
#   fuse:   writes the fuse bytes to the MCU
#   disasm: disassembles the code for debugging
#   clean:  removes all .elf, and .o files in the obj and exe directories

# parameters (change this stuff accordingly)
# project name
PRJ = reflow
# avr mcu
MCU = atmega328p
# mcu clock frequency
CLK = 8000000
# avr programmer (and port if necessary)
#PRG = avrispmkii -P usb -b 115200 -B 4
PRG = avrisp -P /dev/tty.usbmodem411 -b 19200
# fuse bit values for v0.1 pcb
# use internal 8 MHz RC oscillator with no clock division and slowest available startup
# enable SPI programming
# brownout detection at 2.7 V
LFU = 0xE2
HFU = 0xDF
EFU = 0x05
# program source files
SRC = $(PRJ).cpp display.cpp buttons.cpp encoder.cpp
# where to look for included libraries (consisting of .c/.cpp files and .h files)
# e.g. INC = ../../EyeToSee ../../YouSART
INC = 
# any defines to send the compiler
DEF = 
# directories
OBJDIR = ../bin/obj
EXEDIR = ../bin/exe

#################################################################################################
# \/ stuff nobody needs to worry about until such time that worrying about it is appropriate \/ #
#################################################################################################

# include path
INCLUDES := $(addprefix -I,$(INC))
# defines
DEFINES  := $(addprefix -D,$(DEF))
# c flags
CFLAGS    = -Wall -Os -DF_CPU=$(CLK) $(DEFINES) -mmcu=$(MCU) $(INCLUDES)
# any aditional flags for c++
CPPFLAGS  =

# executables
AVRDUDE = avrdude -c $(PRG) -p $(MCU)
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE    = avr-size --format=avr --mcu=$(MCU)
CC      = avr-gcc

# generate list of objects
CFILES   := $(filter %.c, $(SRC)) $(foreach dir, $(INC), $(wildcard $(dir)/*.c))
CPPFILES := $(filter %.cpp, $(SRC)) $(foreach dir, $(INC), $(wildcard $(dir)/*.cpp))
OBJDEPS  := $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
OBJ      := $(addprefix $(OBJDIR)/,$(notdir $(OBJDEPS)))

# user targets
# compile all files
all: $(EXEDIR)/$(PRJ).hex

# test programmer connectivity
test:
	$(AVRDUDE) -v

# flash program to mcu
flash: all
	$(AVRDUDE) -U flash:w:$(EXEDIR)/$(PRJ).hex:i

# write fuses to mcu
fuse:
	$(AVRDUDE) -U lfuse:w:$(LFU):m -U hfuse:w:$(HFU):m -U efuse:w:$(EFU):m

# generate disassembly files for debugging
disasm: $(EXEDIR)/$(PRJ).elf
	$(OBJDUMP) -d $(EXEDIR)/$(PRJ).elf

# remove compiled files
clean:
	rm -f $(EXEDIR)/$(PRJ).elf $(OBJ)

# elf file
$(EXEDIR)/$(PRJ).elf: $(OBJDEPS)
	$(CC) $(CFLAGS) -o $(EXEDIR)/$(PRJ).elf $(OBJ)

# hex file
$(EXEDIR)/$(PRJ).hex: $(EXEDIR)/$(PRJ).elf
	rm -f $(EXEDIR)/$(PRJ).hex
	$(OBJCOPY) -j .text -j .data -O ihex $(EXEDIR)/$(PRJ).elf $(EXEDIR)/$(PRJ).hex
	$(SIZE) $(EXEDIR)/$(PRJ).elf

$(OBJDEPS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(EXEDIR)

# pattern matching for object files
# objects from c files
%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)

# objects from c++ files
%.o : %.cpp 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)
