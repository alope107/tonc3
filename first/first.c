// include using quotes because it's not a system library
#include "toolbox.h"

int main() {

    // Setting up the GBA modes
    // Mode 3 (bitmap mode) and background 2 active
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    // plot 3 dots!
    m3_plot(120, 80, CLR_RED);
    m3_plot(136, 80, CLR_LIME);
    m3_plot(120, 96, CLR_BLUE);

    

    // RAW 
    //  *(unsigned int*)0x04000000 = 0x0403;

    // ((unsigned short*)0x06000000)[120+80*240] = 0x001F;
    // ((unsigned short*)0x06000000)[136+80*240] = 0x03E0;
    // ((unsigned short*)0x06000000)[120+96*240] = 0x7C00;

    while(1);

    return 0;
}