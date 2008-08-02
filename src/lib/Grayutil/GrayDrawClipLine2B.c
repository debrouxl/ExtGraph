#include "../internal.h"

/*===========================================================================*/
/* draw a line with given color from (x0,y0) to (x1,y1), clipped version     */
/*===========================================================================*/
void GrayDrawClipLine2B(short x0,short y0,short x1, short y1, short color,void* lightplane,void* darkplane) {
    WIN_RECT rect = {x0, y0, x1, y1};
    
    PortSet(lightplane,(239L << 16) + 127);
    if (color & (COLOR_WHITE | COLOR_LIGHTGRAY)) {
        TIOSDrawClipLine(&rect, FULLSCREEN, A_NORMAL);
    }
    else {
        TIOSDrawClipLine(&rect, FULLSCREEN, A_REVERSE);
    }

    PortSet(darkplane,(239L << 16) + 127);
    if (color & (COLOR_WHITE | COLOR_DARKGRAY)) {
        TIOSDrawClipLine(&rect, FULLSCREEN, A_NORMAL);
    }
    else {
        TIOSDrawClipLine(&rect, FULLSCREEN, A_REVERSE);
    }
}
