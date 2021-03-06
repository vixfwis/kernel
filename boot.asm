MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .data
gdt_start: ; pointer to self instead of null descriptor
    dw gdt_end - gdt_start
    dd gdt_start
    dw 0x0
gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

    times 8*8 - ($-gdt_start) db 0
gdt_end:

section .text
global _start
_start:
    ; save multiboot header
    mov edx, ebx
    ; load gdt
    cli
    lgdt [gdt_start]
    jmp 8:reload_cs
reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov gs, ax
    mov fs, ax
    ; load stack
    mov esp, stack_top
    ; run kmain
    push edx
    extern kmain
    call kmain
    cli
the_end:
    hlt
    jmp the_end
