#include "vga.h"

static char* video_memory = (char*)0xB8000;
static int cursor_x = 0;
static int cursor_y = 0;

void vga_print(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        vga_print_char(str[i]);
        i++;
    }
}

void vga_print_char(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    video_memory[(cursor_y * 80 + cursor_x) * 2] = c;
    video_memory[(cursor_y * 80 + cursor_x) * 2 + 1] = 0x07; // Light Grey on Black
    cursor_x++;

    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    // Simple scrolling logic
    if (cursor_y >= 25) {
        cursor_y = 24;
    }
}