#include "types.h"

#ifndef VIDEO_H
#define VIDEO_H

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
#define vid_mem ((vu16 (*)[SCREEN_WIDTH])MEM_VRAM) 

#define REG_VCOUNT (*(vu16*)0x04000006)

// blocks until the start of the next VBlank
// inefficent busy loop
// will be better handled with interrupts later
void vsync() {
    while(REG_VCOUNT >=160); // we are currently in VBlank, wait until the next one
    while(REG_VCOUNT < 160); // we are currently in VDraw, wait until VBlank
}

#endif