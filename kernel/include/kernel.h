#ifndef KERNEL_H
#define KERNEL_H

void init_gdt();
void init_idt();
void init_memory();

void kernel_main();

#endif