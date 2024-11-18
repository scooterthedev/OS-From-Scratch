#include <kernel.h>
#include <vga.h>
#include <keyboard.h>
#include <timer.h>
#include <fat32.h>
#include <window_manager.h>
#include <explorer.h>

void kernel_main() {
    init_gdt(); // Initialize the Global Descriptor Table
    vga_print("GDT Initialized\n");
    
    init_idt(); // Initialize the Interrupt Descriptor Table
    vga_print("IDT Initialized\n");
    
    init_memory(); // Initializing the memory management ie. your memory manager so memory.c dosen't use the pagefile to access all the memory for no reason.

    vga_print("Memory Initialized\n");

    vga_print("Welcome to ScooterOS!!!\n");
    keyboard_init();
    vga_print("Keyboard Initialized\n");
    
    timer_init();
    vga_print("Timer Initialized\n");
    
    fat32_init();
    vga_print("FAT32 Initialized\n");

    window_manager_init();
    vga_print("Window Manager Initialized\n");
    
    render_window("Main Window");
    vga_print("Main Window Rendered\n");
    
    explorer_init();
    vga_print("Explorer Initialized\n");
    
    display_directory("/");
    vga_print("Directory Displayed\n");

    while(1) {
        // Infinite loop
    }
}