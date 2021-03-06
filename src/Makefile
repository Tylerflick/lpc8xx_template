#
# gcc Makefile for LPC810
# Kamal Mostafa <kamal@whence.com>
#
# License: Public Domain
#

TARGET				= lpc812
CROSS 				= arm-none-eabi-

FILENAME 			= firmware
LINKERSCRIPT 	= ../ld/$(TARGET).ld

CFLAGS	 			= -mthumb -mcpu=cortex-m0plus -MD #-mfloat-abi=soft
CFLAGS			 += -Os --specs=nano.specs -ffunction-sections -fdata-sections
CFLAGS			 += -fno-builtin

CC 						= ${CROSS}gcc
LD 						= ${CROSS}ld
OBJCOPY 			= ${CROSS}objcopy
SIZE 					= ${CROSS}size

# use these on the $(LD) line, as needed:
LIBM 					= ${shell ${CC} ${CFLAGS} --print-file-name=libm.a}
LIBC 					= ${shell ${CC} ${CFLAGS} --print-file-name=libc.a}
LIBGCC 				= ${shell ${CC} ${CFLAGS} --print-libgcc-file-name}

LDFLAGS 		 += --gc-sections


INC 			 	 += -I../cmsis
CFLAGS 			 += $(INC) -D__USE_CMSIS # -DCLOCK_SETUP=1

OBJS   				= main.o \
	       				gpio.o \
				        uart.o \
				        mrt.o \
				        printf.o \
								one_wire.o \
								delay.o \
								ds18b20.o \
				        printf-retarget.o \
				        system_LPC8xx.o \
				        gcc_startup_lpc8xx.o

all: $(FILENAME).bin

$(FILENAME).axf: $(OBJS)
	@$(LD) -o $@ $(LDFLAGS) -T $(LINKERSCRIPT) $^ $(LIBGCC)
	-@echo ""
	@$(SIZE) $(FILENAME).axf

clean:
	@rm -f *.o *.d
	@rm -f $(FILENAME).axf $(FILENAME).hex $(FILENAME).bin

%.bin:%.axf
	-@echo ""
	-@echo "Generating $(FILENAME).hex (FlashMagic, etc.)"
	@$(OBJCOPY) --strip-unneeded -O ihex $(FILENAME).axf $(FILENAME).hex
	-@echo "Generating $(FILENAME).bin"
	@$(OBJCOPY) --strip-unneeded -O binary $(FILENAME).axf $(FILENAME).bin
	-@echo "Removing build files."
	@rm -f *.o *.d
