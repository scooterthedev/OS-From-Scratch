#include <kernel.h>
#include <vga.h>
#include <keyboard.h>
#include <timer.h>
#include <fat32.h>
#include <window_manager.h>
#include <explorer.h>

void kernel_main() {
    // Initialize kernel subsystems
    init_gdt(); // Initialize the Global Descriptor Table
    init_idt(); // Initialize the Interrupt Descriptor Table
    init_memory(); // Initializing the memory management ie. your memory manager so memory.c dosen't use the pagefile to access all the memory for no reason.

    // Initializing drivers
    vga_print("Welcome to ScooterOS!!!\n");
    keyboard_init();
    timer_init();
    fat32_init();

    // Initialize GUI components
    window_manager_init();
    render_window("Main Window");
    explorer_init();
    display_directory("/");

    while(1) {
        // Kernel infinite loop
        // Can implement sleep or low-power state
    }
}