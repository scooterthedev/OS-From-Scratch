#include <kernel.h>
#include <vga.h>

void kernel_main(void)    // Print boot message
 {
    // Initialize hardware
    vga_init();
    
    // Printing the boot message
    vga_print("ScooterOS Kernel Loaded!\n");
    vga_print("Initializing system...\n");
    
    // Enter halt loop
    while(1) {
        __asm__ volatile("hlt");
    }
}