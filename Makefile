#
# gcc Makefile for LPC8XX
# Tyler Hoeflicker <tyler.hoeflicker@gmail.com>
#
# License: Public Domain
#

TARGET				= lpc812
CROSS				 = arm-none-eabi-


FILENAME			 = firmware
LINKERSCRIPT	 = ./ld/$(TARGET).ld


CC						 = ${CROSS}gcc
LD						 = ${CROSS}ld
OBJCOPY				= ${CROSS}objcopy
SIZE					 = ${CROSS}size


# use these on the $(LD) line, as needed:
LIBM					 = $(shell $(CC) $(CFLAGS) --print-file-name=libm.a)
LIBC					 = $(shell $(CC) $(CFLAGS) --print-file-name=libc.a)
LIBGCC				 = $(shell $(CC) $(CFLAGS) --print-libgcc-file-name)


SOURCES				= $(wildcard src/*.c src/**/*.c)
OBJECTS				= $(patsubst %.c,%.o,$(SOURCES))
# cr_startup_lpc8xx should not be compiled
OBJECTS			 := $(filter-out src/cr_startup_lpc8xx.o, $(OBJECTS))
DIRS					 = $(shell find src -type d -print)
# compiler library paths
INC						= -I./cmsis $(patsubst %,-I./%,$(DIRS))
# linker library paths
LIBRARY_PATH	 = -L./cmsis $(patsubst $,-L./%,$(DIRS))


## Compiler Flags
CFLAGS				 = -mthumb -mcpu=cortex-m0plus
# generate dependencies and compile
CFLAGS				+= -MD
CFLAGS				+= -Os --specs=nano.specs
CFLAGS				+= -ffunction-sections -fdata-sections
# -fno-builtin is required for putchar overriding
CFLAGS				+= -fno-builtin
CFLAGS				+= -D__USE_CMSIS $(INC)


## Linker Flags
LDFLAGS			 += --gc-sections


## Rules
all: $(FILENAME).bin

$(FILENAME).axf: $(OBJECTS)
	@$(LD) -o $@ $(LDFLAGS) -T $(LINKERSCRIPT) $^ $(LIBGCC)
	-@echo ""
	@$(SIZE) $(FILENAME).axf

%.bin:%.axf
	-@echo "\r\n	 Generating binary"
	@$(OBJCOPY) --strip-unneeded -O ihex $(FILENAME).axf $(FILENAME).hex
	@$(OBJCOPY) --strip-unneeded -O binary $(FILENAME).axf $(FILENAME).bin
	-@echo "	 Cleaning up"
	@rm -f src/*.o src/*.d
	@rm -f src/*/*.o src/*/*.d

clean:
	@rm -f src/*.o src/*.d
	@rm -f src/*/*.o src/*/*.d
	@rm -f $(FILENAME).axf $(FILENAME).hex $(FILENAME).bin
