all: kernel.bin bootloader.bin

qemu-gdb: kernel.bin
	gdb -ex 'target remote localhost:1234' -ex 'file kernel.bin'

qemu: kernel.bin
	qemu-system-i386 -kernel kernel.bin -s

qemu-paused: kernel.bin
	qemu-system-i386 -kernel kernel.bin -s -S

kernel.bin: kernel.o boot.o linker.ld
	gcc -m32 -T linker.ld -o kernel.bin -ffreestanding -nostdlib -O2 kernel.o boot.o -lgcc

kernel.o: kernel.c
	gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: boot.asm
	nasm -f elf32 boot.asm -o boot.o

bootloader.bin: bootloader.asm
	nasm -f bin bootloader.asm -o bootloader.bin

qemu-bl: bootloader.bin
	qemu-system-i386 -drive file=bootloader.bin,format=raw -s

qemu-bl-paused: bootloader.bin
	qemu-system-i386 -drive file=bootloader.bin,format=raw -s -S

qemu-bl-gdb: bootloader.bin
	gdb -ex 'target remote localhost:1234' -ex 'file bootloader.bin'
