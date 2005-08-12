#include "..\internal.h"

/*===========================================================================*/
/* draw a line with given color from (x0,y0) to (x1,y1)                      */
/* using FastDrawLine()                                                      */
/*===========================================================================*/
void GrayFastDrawLine2B(short x0,short y0,short x1, short y1, short color,void* lightplane,void* darkplane) {
    if (color & (COLOR_WHITE | COLOR_LIGHTGRAY)) {
        FastDrawLine_R(lightplane,x0, y0, x1, y1, A_NORMAL);
    }
    else {
        FastDrawLine_R(lightplane,x0, y0, x1, y1, A_REVERSE);
    }
    if (color & (COLOR_WHITE | COLOR_DARKGRAY)) {
        FastDrawLine_R(darkplane,x0, y0, x1, y1, A_NORMAL);
    }
    else {
        FastDrawLine_R(darkplane,x0, y0, x1, y1, A_REVERSE);
    }
}
