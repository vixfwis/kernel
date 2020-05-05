global isr0
isr0:
    push eax
    mov al, 0x20
    out 0x20, al
    pop eax
    iret