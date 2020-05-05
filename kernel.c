#include <stdint.h>
#include "inline.h"
#include "interrupts.h"
 
void kmain(void) {
    initIDT();
    const uint16_t color = 0x0F00;
    const char* hello = "Hello world!";
    uint16_t* vga = (uint16_t*)0xb8000;
    // clear
    for (int i = 0; i<80*25;++i)
        vga[i] = color | 0x20;
    // write
    for (int i = 0; i<13;++i)
        vga[i] = color | hello[i];

    for(;;);
}
