#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void init_gdt();
void init_idt();
void init_memory();

void kernel_main();

void set_idt_gate(uint8_t num, uint64_t handler, uint8_t ist, uint8_t flags);
void idt_flush(uint64_t);

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

void enable_interrupts();

#endif