#include <kernel.h>

uint64_t* paging_directory;

void init_memory() {
    // Initialize paging
    paging_directory = (uint64_t*)0x1000; //TODO get the right address

    for(int i = 0; i < 512; i++) {
        paging_directory[i] = (i * 0x1000) | 0x83; // Present, Read/Write, Page Size
    }

    // Load CR3 with the paging directory
    asm volatile("mov %0, %%cr3" : : "r"(paging_directory));

    // Enable paging
    uint64_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; // Set the PG bit (Paging)
    asm volatile("mov %0, %%cr0" : : "r"(cr0));
} 