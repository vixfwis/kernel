#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include "inline.h"
#include "interrupts.h"
#include <limits.h>

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


char* int2str(int32_t num, char * str, uint32_t base) {
	uint32_t min_based_over_num = base; 
	uint8_t j = 0;

	if (num < 0) { 
		str[j++] = '-'; 
		num = -num; 
	}

	while (min_based_over_num <= (uint32_t) num && 
		INT32_MAX / base > min_based_over_num) 
		min_based_over_num *= base;
	if ((uint32_t) num <= min_based_over_num)
		min_based_over_num /= base;	

	while (min_based_over_num > 0) { 
		int32_t tmp = num / min_based_over_num;
		num = num % min_based_over_num; 
		str[j++] = tmp > 9 ? tmp + '0' + 7 : tmp + '0'; 
		min_based_over_num /= base; 
	}
	str[j] = 0;
	
	return str;
}

char* uint2str(uint32_t num, char* str, uint32_t base){
	uint32_t min_based_over_num = base; 
	uint8_t j = 0;

	while (min_based_over_num <= num && 
		UINT_MAX / base > min_based_over_num) 
		min_based_over_num *= base;
	if (num <= min_based_over_num)
		min_based_over_num /= base;	

	while (min_based_over_num > 0) { 
		int32_t tmp = num / min_based_over_num;
		num = num % min_based_over_num; 
		str[j++] = tmp > 9 ? tmp + '0' + 7 : tmp + '0'; 
		min_based_over_num /= base; 
	}
	str[j] = 0;
	
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
 
void kmain(void* mb_info){
    (void) mb_info;

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
