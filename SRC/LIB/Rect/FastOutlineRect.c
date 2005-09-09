#include "../internal.h"

// Draw an outlined rectangle.
// I did not write a full-blown routine to save design time for other
// functions. This routine is much faster than DrawClipRect nevertheless.
void __attribute__((__stkparm__)) FastOutlineRect(void* plane,short x1,short y1,short x2,short y2,short mode) {
    FastDrawHLine_R(plane,x1,x2,y1,mode);
    FastDrawHLine_R(plane,x1,x2,y2,mode);
    FastDrawVLine_R(plane,x1,y1,y2,mode);
    FastDrawVLine_R(plane,x2,y1,y2,mode);
}
