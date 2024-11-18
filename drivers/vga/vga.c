include "vga.h"

static char& video_memory = (char*)0xB8000;

void vga_print(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07; // Light Grey
        i++;
    }
}