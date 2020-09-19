global outb
outb:
    push ebp
    mov ebp, esp
    mov dx, word [ebp+8]
    mov al, byte [ebp+12]
    out dx, al
    leave
    ret

global outw
outw:
    push ebp
    mov ebp, esp
    mov dx, word [ebp+8]
    mov ax, word [ebp+12]
    out dx, ax
    leave
    ret

global outl
outl:
    push ebp
    mov ebp, esp
    mov dx, word [ebp+8]
    mov eax, dword [ebp+12]
    out dx, eax
    leave
    ret

global inb
inb:
    push ebp
    mov ebp, esp
    mov dx, word [ebp+8]
    mov al, byte [ebp+12]
    in al, dx
    leave
    ret

global inw
inw:
    push ebp
    mov ebp, esp
    mov dx, word [ebp+8]
    mov ax, word [ebp+12]
    in ax, dx
    leave
    ret

global inl
inl:
    push ebp
    mov ebp, esp
    mov dx, word [ebp+8]
    mov eax, dword [ebp+12]
    in eax, dx
    leave
    ret

global loadIDT
loadIDT:
    push ebp
    mov ebp, esp
    mov edi, dword [ebp+8]
    lidt [edi]
    leave
    ret

global sti
sti:
    sti
    ret

global cli
cli:
    cli
    ret

global hlt
hlt:
    hlt
    ret
