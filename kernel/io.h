#ifndef io_h
#define io_h

#include <stdint.h>

#define VGA_ADDRESS 0xb8000
#define VGA_WIDTH   80
#define VGA_HEIGHT  25

#define VGA_COLOUR_PRIMARY VGA_BRIGHT_WHITE

enum {
    VGA_BLACK = 0x0,
    VGA_BLUE = 0x1,
    VGA_GREEN = 0x2,
    VGA_CYAN = 0x3,
    VGA_RED = 0x4,
    VGA_MAGENTA = 0x5,
    VGA_BROWN = 0x6,
    VGA_WHITE = 0x7,
    VGA_GRAY = 0x8,
    VGA_LIGHT_BLUE = 0x9,
    VGA_LIGHT_GREEN = 0xa,
    VGA_LIGHT_CYAN = 0xb,
    VGA_LIGHT_RED = 0xc,
    VGA_LIGHT_MAGENTA = 0xd,
    VGA_YELLOW = 0xe,
    VGA_BRIGHT_WHITE = 0xf,
};

void cls(void);
void vga_put_char(int row, int col, char c, char color);
void puts(char *s);
void putc(char c);

#endif