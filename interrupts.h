#include <stdint.h>
#include "inline.h"

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#pragma pack(1)
typedef struct _IDTEntry {
    uint16_t ofsLow;
    uint16_t selector;
    uint8_t zero;
    uint8_t typeAttr;
    uint16_t ofsHigh;
} IDTEntry;

IDTEntry IDT[256];

void regIntr(void* handler, uint8_t pos) {
    uint32_t addr = (uint32_t)handler; 
    IDT[pos].ofsLow = addr & 0xffff;
    IDT[pos].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[pos].zero = 0;
    IDT[pos].typeAttr = 0x8e; /* INTERRUPT_GATE */
    IDT[pos].ofsHigh = (addr & 0xffff0000) >> 16;
}

void initIDT(void) {
    extern void isr0();
    extern void isr1();
    extern void isr2();
    extern void isr3();
    extern void isr4();
    extern void isr5();
    extern void isr6();
    extern void isr7();
    extern void isr8();
    extern void isr9();
    extern void isr10();
    extern void isr11();
    extern void isr12();
    extern void isr13();
    extern void isr14();
    extern void isr15();

    /* remapping the PIC */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 40);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    regIntr(isr0, 32);
    regIntr(isr1, 33);
    regIntr(isr2, 34);
    regIntr(isr3, 35);
    regIntr(isr4, 36);
    regIntr(isr5, 37);
    regIntr(isr6, 38);
    regIntr(isr7, 39);
    regIntr(isr8, 40);
    regIntr(isr9, 41);
    regIntr(isr10, 42);
    regIntr(isr11, 43);
    regIntr(isr12, 44);
    regIntr(isr13, 45);
    regIntr(isr14, 46);
    regIntr(isr15, 47);

    loadIDT(IDT, 256 * sizeof(IDTEntry));
    sti();
}

#endif
