#include "types.h"

extern u16 key_prev, key_current;

#ifndef KEY_H
#define KEY_H

// Bitmasks for each key location
#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

// Bitmask for all key locations
#define KEY_MASK     0x03FF

// Register that holds instant key status
// Keys that are DOWN have their bit set to 1
// UP keys have bit set to 0
#define REG_KEYINPUT *((vu16*) 0x04000130)

// Updates the current and previous key, masking and flipping to 
// get a more natural representation
// should be called once per frame
INLINE void key_poll() {
    key_prev = key_current;
    key_current = ~REG_KEYINPUT & KEY_MASK;
}

// Gets the state of they keys for this frame
// DOWN keys have a bit value of 1
// NOT DOWN keys haveva bit value of 0
// Note that this is the opposite to how it is natively stored
INLINE u32 key_current_state() {return key_current;}
// Gets the state of the keys for the previous frame
INLINE u32 key_prev_state() {return key_prev;}

// Returns a positive value if the given key is down on this frame, 0 otherwise
INLINE u32 key_down(u32 key) {return key_current & key;}

// Returns a 0 value if the given key was pressed on the previous frame, 0 otherwise
INLINE u32 key_was_down(u32 key) {return key_prev & key;}

// Returns if a key started to be pressed this frame (was up last frame, now is down)
INLINE u32 key_hit(u32 key) { return key_current & ~key_prev & key;}

// Returns if a key was just released this frame (was down last frame, now is up)
INLINE u32 key_released(u32 key) {return ~key_current & key_prev & key;}


// Bit index of each key
enum keyIndex {
    KI_A=0,
    KI_B,
    KI_SELECT,
    KI_START, 
    KI_RIGHT,
    KI_LEFT,
    KI_UP,
    KI_DOWN,
    KI_R,
    KI_L
};

// Returns 0 if the bits at plusI and minusI are equal (both/neither set), else
// 1 if the bit at plusI is set, else
// -1 if minusI is set
INLINE int bit_tribool(u32 pressed, int plusI, int minusI){
    return ((pressed >> plusI) & 1) - ((pressed >> minusI) & 1);
}

INLINE int key_tri_horiz() {
    return bit_tribool(key_current, KI_RIGHT, KI_LEFT);
}

INLINE int key_tri_vert() {
    return bit_tribool(key_current, KI_DOWN, KI_UP);
}
#endif