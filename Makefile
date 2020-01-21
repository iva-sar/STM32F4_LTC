MODULE_NAME = STM32F407

#STLINK path
STLINK=~/stlink

#Toolchain
TOOLCHAIN_ROOT = 
PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
AS = $(PREFIX)gcc
LD = $(PREFIX)gcc
AR = $(PREFIX)ar
BIN = $(PREFIX)objcopy

LIB_C = 
LIB_GCC = 

SPL = Libraries/STM32F4xx_StdPeriph_Driver
CMSIS = Libraries/CMSIS

STARTUP = $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_ride7
# C source flags
CFLAGS = -Wall \
         -mcpu=cortex-m4 \
         -mthumb \
         -mfloat-abi=hard \
	 -mfpu=fpv4-sp-d16
#         -fomit-frame-pointer \
#         -fno-strict-aliasing \
#         -specs=nosys.specs \
#         -specs=nano.specs 

# Assembler flags
AFLAGS = -x assembler-with-cpp
# Linker flags
LDFLAGS = -specs=nosys.specs -specs=nano.specs -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard 
CPU = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16

INC =  -I $(SPL)/inc
INC += -I $(CMSIS)/Include
INC += -I $(CMSIS)/Device/ST/STM32F4xx/Include
INC += -I Project/Headers
#INC += -I .

CFLAGS += $(INC)
CFLAGS += -g -std=c99
CFLAGS += -D USE_STDPERIPH_DRIVER -D STM32F40xx -D USE_STM32F07_DISCO
#CFLAGS += -D USE_STDPERIPH_DRIVER -D USE_STM32F07_DISCO
#CFLAGS += $(EXTRA)

BLACKLIST = $(SPL)/src/stm32f4xx_fmc.c

#_SRC = $(wildcard *.c)
_SRC  = $(wildcard Project/Source/*.c)
_SRC += $(wildcard $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/*.c)
_SRC += $(wildcard $(SPL)/src/*.c)
SRC  = $(filter-out $(BLACKLIST), $(_SRC))

ASRC = $(STARTUP)/startup_stm32f40xx.s

OBJ = $(patsubst %.c,%.o,$(SRC))
AOBJ = $(patsubst %.s,%.o,$(ASRC))

LINKER_SCRIPT = Project/STM32F407VGTx_FLASH.ld

# ObjCopy flags
BINFLAGS = -O binary

.PRECIOUS: %.c %.o

all: app.bin

client: 
	make EXTRA=-DCLIENT
server:
	make

%.o: %.c Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(MODULE_NAME): Compiled $< successfully!"

%.o : %.s Makefile
	@$(AS) $(CFLAGS) $(AFLAGS) -c $< -o $@
	@echo "$(MODULE_NAME): Compiled "$<" successfully!"

app.bin : app.elf
	@$(BIN) $< $(BINFLAGS) $@
	@echo "$(MODULE_NAME): Generated binary successfully!"

app.elf : $(AOBJ) $(OBJ)
	@$(LD) $(AOBJ) $(OBJ) \
	$(LDFLAGS) -o $@ \
	-lc  \
	-T$(LINKER_SCRIPT)
	@echo "$(MODULE_NAME): Linked app successfully!"

clean :
	rm -f app.elf app.bin
	rm $(OBJ)

burn: app.bin
	$(STLINK)/st-flash write app.bin 0x8000000
	#st-flash write app.bin 0x8000000

