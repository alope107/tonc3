// include using quotes because it's not a system library
#include "types.h"
#include "video.h"
#include "colors.h"
#include "smol.h"
#include "keys.h"

int main() {

    // Setting up the GBA modes
    // Mode 3 (bitmap mode) and background 2 active
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    u32 xoffset = 0;
    u32 yoffset = 0;

    while(1) {
        m3_plot(120 + xoffset, 80 + yoffset, YAH);
        m3_plot(136 + xoffset, 80 + yoffset, CLR_LIME);
        m3_plot(120 + xoffset, 96 + yoffset, CLR_BLUE);
        vsync();
        key_poll();
        xoffset += key_tri_horiz();
        yoffset += key_tri_vert();
    }
    // plot 3 dots!
    

    

    // RAW 
    //  *(unsigned int*)0x04000000 = 0x0403;

    // ((unsigned short*)0x06000000)[120+80*240] = 0x001F;
    // ((unsigned short*)0x06000000)[136+80*240] = 0x03E0;
    // ((unsigned short*)0x06000000)[120+96*240] = 0x7C00;

    while(1);

    return 0;
}