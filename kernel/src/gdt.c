#include <kernel.h>

struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
}___attribute___((packed));

struct gdt_ptr {
    uint16_t limit;
    uint16_t base;
}___attribute___((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern void gdt_flush(uinit64_t);

void init_gdt() {
    gp.limit = (sizeof(struct gdt_entry) * 3) -1;
    gp.base = (uint64_t)&gdt;

    // Null Time
    gdt[0].limit_low = 0;
    gdt[0].base_low = 0;
    gdt[0].base_middle = 0;
    gdt[0].access = 0;
    gdt[0].granularity =0;
    gdt[0].base_high = 0;

    // Code segment
    gdt[1].limit_low = 0xFFFF;
    gdt[1].base_low = 0;
    gdt[1].base_middle = 0;
    gdt[1].access = 0x9A;
    gdt[1].granularity = 0xCF;
    gdt[1].base_high = 0;

    // Data segment
    gdt[2].limit_low = 0xFFFF;
    gdt[2].base_low = 0;
    gdt[2].base_middle = 0;
    gdt[2].access = 0x92;
    gdt[2].granularity = 0xCF;
    gdt[2].base_high = 0;

    gdt_flush((uint64_t)&gp)
}