#include "timer.h"
#include "../vga/vga.h"

// PIT setup
void timer_init() {
    uint32_t freq = 1193182 / 50; // 50HZ
    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(freq & 0xFF));
    outb(0x40, (uint8_t)(freq >> 8) & 0xFF);
}

void timer_handler() {
    outb(0x20, 0x20);
}