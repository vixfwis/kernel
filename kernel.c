#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include "inline.h"
#include "interrupts.h"

extern void* sunrise;

static uint16_t* vga = (uint16_t*)0xb8000;
static uint16_t* wptr = (uint16_t*)0xb8000;

void clrscr(){
    for (int i = 0; i<80*25;++i)
        vga[i] = 0x0F00 | 0x20;
    wptr = vga;
}

void write(const char* msg){
    for (int i = 0; msg[i] != 0; ++i){
        if(msg[i] == '\n'){
            int row = (((uint32_t)wptr - (uint32_t)vga)/160)+1;
            wptr = (uint16_t*)((uint32_t)vga+160*row);
        }else{
            *wptr = 0x0F00 | msg[i];
            wptr++;
        }
    }
}

char* int2str(int32_t num, char* str, uint32_t base){
    bool sign = false;
    if (num < 0) {
        sign = true;
        num *= -1;
    }
    uint64_t baseofs = base;
    uint32_t mod;
    uint64_t tmp;
    uint8_t len = 0;
    do {
        len++;
        tmp = 1;
        for (uint8_t i = 0; i < len; ++i)
            tmp *= baseofs;
    } while(num >= tmp);
    if (sign)
        len++;
    str[len] = 0;
    do {
        mod = num % baseofs;
        uint8_t c = (uint8_t)((mod)/(baseofs/base)+48);
        if (c > '9')
            c += 7;
        str[--len] = c;
        num -= mod;
        baseofs *= base;
    } while(len != 0);
    str[0] = '-';
    return str;
}

char* uint2str(uint32_t num, char* str, uint32_t base){
    uint64_t baseofs = base;
    uint32_t mod;
    uint64_t tmp;
    uint8_t len = 0;
    do {
        len++;
        tmp = 1;
        for (uint8_t i = 0; i < len; ++i)
            tmp *= baseofs;
    } while(num >= tmp);
    str[len] = 0;
    do {
        mod = num % baseofs;
        uint8_t c = (uint8_t)((mod)/(baseofs/base)+48);
        if (c > '9')
            c += 7;
        str[--len] = c;
        num -= mod;
        baseofs *= base;
    } while(len != 0);
    return str;
}

int memcmp(const void* ptr1, const void* ptr2, size_t num){
    const uint8_t* p1 = (const uint8_t*)ptr1;
    const uint8_t* p2 = (const uint8_t*)ptr2;
    while(*p1 == *p2 && --num){
        p1++;p2++;
    }
    return *p1 - *p2;
}

void printk(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    while (*fmt != 0) {
        // memcmp stuff do %d %u
        fmt++;
    }
    va_end(args);
}
 
void kmain(void* mb_info, uint32_t magic){
    // disable cursor
    outb(0x3D4, 0xA);
    outb(0x3D5, 0x20);
    // init
    initIDT();
    clrscr();

    write("It just works\n");
    char buf[10];
    write(int2str(-2548, buf, 16));
    write("\n^^^");

    for(;;)
        hlt();
}
