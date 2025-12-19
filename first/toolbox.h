#ifndef TOOLBOX_H
#define TOOLBOX

// Short names for unsigned datatypes
// Reingforces sizes
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// Colors are short halfwords
// Extra typedef for conceptual clarity
typedef u16 COLOR;

// static - internal to the file, not global
// inline - compiler hint that maybe don't actually make a whole function?
#define INLINE static inline

// Where the memory registers for I/O are located
#define MEM_IO      0x04000000

// Bitmap VRAM start
#define MEM_VRAM    0x06000000

// Location of the display mode bits
// A dereferenced pointer so we can write to it
// volatile is so the compiler knows that other parts might read it, and not to discard seemingly useless writes
#define REG_DISPCNT *((volatile u32*)MEM_IO)

// video modes
// only one can be active at a time, so sequential values work
#define DCNT_MODE0     0x0000
#define DCNT_MODE1      0x0001
#define DCNT_MODE2      0x0002
#define DCNT_MODE3      0x0003
#define DCNT_MODE4      0x0004
#define DCNT_MODE5      0x0005

// layers for backgrounds and sprites
// multiple can be active at a time, so they each need their own bit
#define DCNT_BG0        0x0100
#define DCNT_BG1        0x0200
#define DCNT_BG2        0x0400
#define DCNT_BG3        0x0800
#define DCNT_OBJ        0x1000

// GBA screen dimensions
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

// doing this differently than tonc!
// I want vid_mem to be addressable as a 2d array
// So, I need to cast MEM_VRAM as a pointer to an array of 240 u16s
// Asterisk needs to be paren so it's a pointer to an array instead of an array of pointers
#define vid_mem ((volatile u16 (*)[SCREEN_WIDTH])MEM_VRAM) 

INLINE void m3_plot(int x, int y, COLOR clr) {
    vid_mem[y][x] = clr;
}

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

#endif