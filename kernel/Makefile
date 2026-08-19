OUTPUT = 
BIN = ../bin
CC = x86_64-elf-gcc
AS = nasm
LD = x86_64-elf-ld

# Flags for compiling
C_FLAGS = \
	-Wall \
	-Wextra \
	-std=gnu11 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-lto \
	-fno-PIC \
	-ffunction-sections \
	-fdata-sections \
	-m64 \
	-march=x86-64 \
	-mabi=sysv \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-mcmodel=kernel \
	-Iinclude

# Linking Flags
LD_FLAGS = \
	-m elf_x86_64 \
	-nostdlib \
	-static \
	-z max-page-size=0x1000 \
	--gc-sections \
	-T arch/x86_64/boot/linker.ld

# Get Sources
C_SRCS = $(shell find . -iname "*.c" -printf "%P\n")
ASM_SRCS = $(shell find . -iname "*.asm" -printf "%P\n")

# Make them into Objs
C_OBJS = $(patsubst %.c, $(BIN)/%.o, $(C_SRCS))
ASM_OBJS = $(patsubst %.asm, $(BIN)/%.o, $(ASM_SRCS))

# Link those objs so we can make the kernel
OBJS = $(C_OBJS) $(ASM_OBJS)

all: kernel

$(BIN)/%.o: %.c
	@printf "CC\t%s\n" $(patsubst ../%, %, $@)
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@

$(BIN)/%.o: %.asm
	@printf "ASM\t%s\n" $(patsubst ../%, %, $@)
	@mkdir -p $(dir $@)
	@$(NASM) -Wall -felf64 $< -o $@

.PHONY: kernel

kernel: $(BIN)/$(OUTPUT)-kernel.elf
$(BIN)/$(OUTPUT)-kernel.elf: $(OBJS)
	@printf "LD\t%s\n" $(patsubst ../%, %, $@)
	@mkdir -p $(dir $@)
	@$(LD) $(LD_FLAGS) $^ -o $@
