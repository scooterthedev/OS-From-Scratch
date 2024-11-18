#include <kernel.h>
#include "../drivers/vga/vga.h"
#include "../drivers/keyboard/keyboard.h"
#include "../fs/fat32/fat32.h"
#include "../gui/src/window_manager.h"
#include "../file_explorer/src/explorer.h"

void kernel_main() {
    init_gdt(); // Initializing the Global Descriptor Table ie. GDP
    init_idt(); // Initializing the Interrupt Descriptor Table ie. IDT
    init_memory(); // Initializing the memory management ie. your memory manager so memory.c dosen't use the pagefile to access all the memory for no reason.

    // Initializing drivers
    vga_print("Welcome to ScooterOS!!!\n");
    keyboard_init();
    fat32_init();

    // Initializing the GUI components
    window_manager_init();
    render_window("Main Window");
    explorer_init();
    display_directory("/");

    while(1) {
        // Make the kernel to an infinite loop
    }
}