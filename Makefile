CFLAGS = -m32 -std=gnu99 -ffreestanding -nostdlib -O2 -Wall -Wextra

all: kernel.bin

qemu-gdb: kernel.bin
	gdb -ex 'target remote localhost:1234' -ex 'file kernel.bin'

qemu: kernel.bin
	qemu-system-i386 -kernel kernel.bin -s

qemu-paused: kernel.bin
	qemu-system-i386 -kernel kernel.bin -s -S

kernel.bin: kernel.o boot.o isr.o inline.o interrupts.o linker.ld inline.h interrupts.h
	gcc -T linker.ld $(CFLAGS) -o kernel.bin kernel.o boot.o isr.o inline.o interrupts.o -lgcc

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm -f elf32 $< -o $@
