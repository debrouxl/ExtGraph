#include "../internal.h"

/*===========================================================================*/
/* draw a horizontal line with given color from (x0,y) to (x1,y)             */
/* using FastDrawLine()                                                      */
/*===========================================================================*/
void GrayFastDrawHLine2B(short x0,short x1, short y, short color,void* lightplane,void* darkplane) {
    if (color & (COLOR_WHITE | COLOR_LIGHTGRAY)) {
        FastDrawHLine_R(lightplane,x0, x1, y, A_NORMAL);
    }
    else {
        FastDrawHLine_R(lightplane,x0, x1, y, A_REVERSE);
    }
    if (color & (COLOR_WHITE | COLOR_DARKGRAY)) {
        FastDrawHLine_R(darkplane,x0, x1, y, A_NORMAL);
    }
    else {
        FastDrawHLine_R(darkplane,x0, x1, y, A_REVERSE);
    }
}
