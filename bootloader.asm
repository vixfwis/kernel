bits 16
org 0x7c00

    mov ax, 0x2401
    int 0x15 ; enable A20

    mov ax, 3
    int 0x10 ; set vga text mode 3

    cli
    lgdt [gdt_ptr]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp cseg:boot32

gdt_start:
    dq 0x0
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
gdt_end:

gdt_ptr:
    dw gdt_end - gdt_start
    dd gdt_start
cseg equ gdt_code - gdt_start
dseg equ gdt_data - gdt_start

bits 32
boot32:
    mov ax, dseg
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    xor ax,ax
    mov al, 50
    mov [0xb8000], al
    jmp $

times 510 - ($-$$) db 0
dw 0xaa55
