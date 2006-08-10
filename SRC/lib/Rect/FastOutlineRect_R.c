#include "../internal.h"

// Draw an outlined rectangle.
// I did not write a full-blown routine to save design time for other
// functions. This routine is much faster than DrawClipRect nevertheless.
void __attribute__((__stkparm__)) FastOutlineRect_R(register void* plane asm("%a0"),register short x1 asm("%d0"),register short y1 asm("%d1"),register short x2 asm("%d2"),register short y2 asm("%d3"),short mode) {
    FastDrawHLine_R(plane,x1,x2,y1,mode);
    FastDrawHLine_R(plane,x1,x2,y2,mode);
    FastDrawVLine_R(plane,x1,y1,y2,mode);
    FastDrawVLine_R(plane,x2,y1,y2,mode);
}
