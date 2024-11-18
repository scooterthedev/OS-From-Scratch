#include <kernel.h>
#include "../drivers/vga/vga.h"
#include "../drivers/keyboard/keyboard.h"

void kernel_main() {
    init_gdt(); // Initialize the Global Descriptor Table
    init_idt(); // Initialize the Interrupt Descriptor Table
    init_memory(); // Initializes the memory managment

    vga_print("Welcome to ScooterOS!!!\n");
    keyboard_init();

    while(1) {
        // Kernel infinite loop
    }
}