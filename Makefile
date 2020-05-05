INTR_DIR := ./interrupts
INTR_SRC := $(wildcard $(INTR_DIR)/*.asm)
INTR_OBJ := $(patsubst %.asm,%.o,$(INTR_SRC))

all: kernel.bin

qemu-gdb: kernel.bin
	gdb -ex 'target remote localhost:1234' -ex 'file kernel.bin'

qemu: kernel.bin
	qemu-system-i386 -kernel kernel.bin -s

qemu-paused: kernel.bin
	qemu-system-i386 -kernel kernel.bin -s -S

kernel.bin: kernel.o boot.o linker.ld inline.h interrupts.h $(INTR_OBJ)
	gcc -m32 -T linker.ld -o kernel.bin -ffreestanding -nostdlib -O2 kernel.o boot.o inline.h interrupts.h $(INTR_OBJ) -lgcc

kernel.o: kernel.c
	gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: boot.asm
	nasm -f elf32 boot.asm -o boot.o

$(INTR_DIR)/%.o: $(INTR_DIR)/%.asm
	nasm -f elf32 $< -o $@
