global isr13
isr13:
    push eax
    mov al, 0xA0
    out 0x20, al
    mov al, 0x20
    out 0x20, al
    pop eax
    iret
