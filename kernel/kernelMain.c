#include "io.h"

void kernelMain(void) {
    cls();
    vga_put_str(0, 0, "Hello, World!", VGA_WHITE);

    for (;;);
}
