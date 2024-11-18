#include <kernel.h>

void kernel_main() {
    init_gdt(); // Initialize the Global Descriptor Table
    init_idt(); // Initialize the Interrupt Descriptor Table
    init_memory(); // Initializes the memory managment

    const char *message = "Welcome to ScooterOS!!!";
    vga_print(message);

    while(1) {
        // Kernel infinite loop
        // TODO: Implement the kernel's main loop
    }
}