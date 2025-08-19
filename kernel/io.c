#include <stdint.h>
#include "io.h"

volatile uint8_t *vga_buffer = (volatile uint8_t *)VGA_ADDRESS;

void cls() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i * 2]     = ' ';
        vga_buffer[i * 2 + 1] = 0x07;
    }
}

void vga_put_char(int row, int col, char c, char color) {
    unsigned int index = (row * VGA_WIDTH + col) * 2;

    vga_buffer[index]     = c;
    vga_buffer[index + 1] = color;
}

void vga_put_str(int row, int col, char *s, char color) {
    for (int i = 0; s[i] != '\0'; i++) {
        vga_put_char(row, col + i, s[i], color);
    }
}