#include <stdint.h>

#ifndef INLINE_H
#define INLINE_H

void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
void outl(uint16_t port, uint32_t val);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);
void loadIDT(void* idt);
void sti(void);
void cli(void);
void hlt(void);

#endif