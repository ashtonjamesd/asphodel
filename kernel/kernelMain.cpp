#include "common.h"

#define forever for(;;)

void initScreen() {
    cls();
    puts(OS_NAME);
}

extern "C" void kernelMain() {
    initScreen();
    forever;
}