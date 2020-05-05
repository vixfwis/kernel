global isr1
isr1:
    push eax
    mov al, 0x20
    out 0x20, al
    pop eax
    iret