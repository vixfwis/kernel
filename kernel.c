#include <stdint.h>
#include <stdarg.h>
#include "inline.h"
#include "interrupts.h"

extern void* sunset;

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

void printk(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);

}
 
void kmain(void* mb_info, uint32_t magic){
    // disable cursor
    outb(0x3D4, 0xA);
    outb(0x3D5, 0x20);
    // init
    initIDT();
    clrscr();

    const char* hello = "Hello world!\n";
    for(int i = 0; i < 10; ++i)
        write(hello);

    for(;;);
}
