#include "..\internal.h"

// Draw an outlined rectangle.
// I did not write a full-blown routine to save design time for other
// functions. This routine is much faster than DrawClipRect nevertheless.
void __attribute__((__stkparm__)) GrayFastOutlineRect_R(register void* dest1 asm("%a0"),register void* dest2 asm("%a1"), register short x1 asm("%d0"),register short y1 asm("%d1"),register short x2 asm("%d2"),register short y2 asm("%d3"),short color) {
    if (color & (COLOR_WHITE | COLOR_LIGHTGRAY)) {
        FastDrawHLine_R(dest1,x1,x2,y1,A_NORMAL);
        FastDrawHLine_R(dest1,x1,x2,y2,A_NORMAL);
        FastDrawVLine_R(dest1,x1,y1,y2,A_NORMAL);
        FastDrawVLine_R(dest1,x2,y1,y2,A_NORMAL);
    }
    else {
        FastDrawHLine_R(dest1,x1,x2,y1,A_REVERSE);
        FastDrawHLine_R(dest1,x1,x2,y2,A_REVERSE);
        FastDrawVLine_R(dest1,x1,y1,y2,A_REVERSE);
        FastDrawVLine_R(dest1,x2,y1,y2,A_REVERSE);
    }

    if (color & (COLOR_WHITE | COLOR_DARKGRAY)) {
        FastDrawHLine_R(dest2,x1,x2,y1,A_NORMAL);
        FastDrawHLine_R(dest2,x1,x2,y2,A_NORMAL);
        FastDrawVLine_R(dest2,x1,y1,y2,A_NORMAL);
        FastDrawVLine_R(dest2,x2,y1,y2,A_NORMAL);
    }
    else {
        FastDrawHLine_R(dest2,x1,x2,y1,A_REVERSE);
        FastDrawHLine_R(dest2,x1,x2,y2,A_REVERSE);
        FastDrawVLine_R(dest2,x1,y1,y2,A_REVERSE);
        FastDrawVLine_R(dest2,x2,y1,y2,A_REVERSE);
    }

}
