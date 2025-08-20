#include "common.h"

volatile char *vga_buffer = (volatile char *)VGA_ADDRESS;
static struct {
    int x;
    int y;
} cursor;

static inline void moveCursorLeft() {
    cursor.x--;
}

static inline void moveCursorRight() {
    cursor.x++;
}

static inline void moveCursorUp() {
    cursor.y--;
}

static inline void moveCursorDown() {
    cursor.y++;
}

void cls() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i * 2] = ' ';
        vga_buffer[i * 2 + 1] = VGA_COLOUR_PRIMARY;
    }

    cursor.x = 0;
    cursor.y = 0;
}

void vga_put_char(int row, int col, char c, char color) {
    unsigned int index = (row * VGA_WIDTH + col) * 2;

    vga_buffer[index] = c;
    vga_buffer[index + 1] = color;
}

void puts(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        putc(s[i]);
    }
}

void putc(char c) {
    if (c == '\n') {
        cursor.x = 0;
        moveCursorDown();
    } else if (c == '\b') {
        if (cursor.x > 0) {
            moveCursorLeft();
            vga_put_char(cursor.y, cursor.x, ' ', VGA_COLOUR_PRIMARY);
        }
    } 
    else {
        vga_put_char(cursor.y, cursor.x, c, VGA_COLOUR_PRIMARY);
        moveCursorRight();
    }   
}