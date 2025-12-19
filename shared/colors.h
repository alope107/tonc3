#include "video.h"

#ifndef COLORS_H
#define COLORS_H

// Colors are short halfwords
// Extra typedef for conceptual clarity
typedef u16 COLOR;

// Some colors!
// GBA colors are 15 bit BGR
// The subpixels are laid out bgr on the physical screen, and that's why it's not rgb
// Wacky!
#define CLR_BLACK   0x0000
#define CLR_RED     0x001F
#define CLR_LIME    0x03E0
#define CLR_YELLOW  0x03FF
#define CLR_BLUE    0x7C00
#define CLR_MAG     0x7C1F
#define CLR_CYAN    0x7FE0
#define CLR_WHITE   0x7FFF

// u32 means things will be automatically scaled up
// also cpu is 32 bit anyway, so shorts aren't needed
INLINE COLOR RGB15(u32 red, u32 green, u32 blue) {
    return red | (green << 5) | (blue <<10);
}

// plot a single pixel in the given color in mode 3
// could conceivably be moved to a different plotting file
INLINE void m3_plot(int x, int y, COLOR clr) {
    vid_mem[y][x] = clr;
}

#endif