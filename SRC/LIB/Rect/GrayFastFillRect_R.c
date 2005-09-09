#include "../internal.h"

// Draw an filled rectangle.
// I did not write a full-blown routine to save design time for other
// functions. This routine is much faster than DrawClipRect nevertheless.
void __attribute__((__stkparm__)) GrayFastFillRect_R(register void* dest1 asm("%a0"),register void* dest2 asm("%a1"), register short x1 asm("%d0"),register short y1 asm("%d1"),register short x2 asm("%d2"),register short y2 asm("%d3"),short color) {
    if (color & (COLOR_WHITE | COLOR_LIGHTGRAY)) {
        FastFillRect_R(dest1,x1,y1,x2,y2,A_NORMAL);
    }
    else {
        FastFillRect_R(dest1,x1,y1,x2,y2,A_REVERSE);
    }

    if (color & (COLOR_WHITE | COLOR_DARKGRAY)) {
        FastFillRect_R(dest2,x1,y1,x2,y2,A_NORMAL);
    }
    else {
        FastFillRect_R(dest2,x1,y1,x2,y2,A_REVERSE);
    }

}
