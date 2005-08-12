#include "..\internal.h"

/*===========================================================================*/
/* draw a line with given color from (x0,y0) to (x1,y1)                      */
/*===========================================================================*/
void GrayDrawLine2B(short x0,short y0,short x1, short y1, short color,void* lightplane,void* darkplane) {
    PortSet(lightplane,(239L << 16) + 127);
    if (color & (COLOR_WHITE | COLOR_LIGHTGRAY)) {
        TIOSDrawLine(x0, y0, x1, y1, A_NORMAL);
    }
    else {
        TIOSDrawLine(x0, y0, x1, y1, A_REVERSE);
    }
    PortSet(darkplane,(239L << 16) + 127);
    if (color & (COLOR_WHITE | COLOR_DARKGRAY)) {
        TIOSDrawLine(x0, y0, x1, y1, A_NORMAL);
    }
    else {
        TIOSDrawLine(x0, y0, x1, y1, A_REVERSE);
    }
}
