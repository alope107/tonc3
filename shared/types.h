#ifndef TYPES_H
#define TYPES_H

// Short names for unsigned datatypes
// Emphasizes sizes
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// volatile types - used to indeicate to compiler that seemingly useless writes shouldn't be optimized away
// commonly used for registers / mmap
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

// static - internal to the file, not global
// inline - compiler hint that maybe don't actually make a whole function?
#define INLINE static inline

#endif