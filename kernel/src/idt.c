#include <kernel.h>

struct idt_entry {
    uint16_t base_low;
    uint16_t sel; // This is the kernel segment selector
    uint8_t ist; // This is the interrupt stack table
    uint8_t flags;
    uint16_t base_middle;
    uint32_t base_high;
    uint32_t reserved;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct idt_entry idt [256];
struct idt_ptr idtp;

void set_idt_gate(uint8_t num, uint64_t handler, uint8_t ist, uint8_t flags) {
    idt[num].base_low = handler & 0xFFFF;
    idt[num].sel = 0x08; // Kernel code segment
    idt[num].ist = ist;
    idt[num].flags = flags;
    idt[num].base_middle = (handler >> 16) & 0xFFFF;
    idt[num].base_high = (handler >> 32) & 0xFFFFFFFF;
    idt[num].reserved = 0;
}

void init_idt() {
    idtp.limit = sizeof(struct idt_entry) * 256 -1;
    idtp.base = (uint64_t)&idt;

    // Now we are going to be clearing the IDT
    for(int i = 0; i < 256; i++) {
        set_idt_gate(i, 0, 0, 0);
    }
    // Now we are going to set the keyboard interupt
    extern void keyboard_interrupt_handler();
    set_idt_gate(33, (uint64_t)keyboard_interrupt_handler, 0, 0x8E);

    idt_flush((uint64_t)&idtp);
}