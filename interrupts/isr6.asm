global isr6
isr6:
    push eax
    mov al, 0x20
    out 0x20, al
    pop eax
    iret
