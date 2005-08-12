#include "..\internal.h"

void GrayDrawRect2B(short x0,short y0,short x1, short y1, short color,short fill,void* lightplane,void* darkplane) {
    WIN_RECT wrect;
    SCR_RECT rect;
    void     (__ATTR_TIOS__ *df)(void*,void*,short);
    void*    parea;

    if (fill) {
        rect.xy.x0 = x0;
        rect.xy.y0 = y0;
        rect.xy.x1 = x1;
        rect.xy.y1 = y1;
        parea      = &rect;
        df         = (void __ATTR_TIOS__(*)(void*,void*,short))ScrRectFill;
    }
    else {
        wrect.x0 = x0;
        wrect.y0 = y0;
        wrect.x1 = x1;
        wrect.y1 = y1;
        parea    = &wrect;
        df       = (void __ATTR_TIOS__(*)(void*,void*,short))DrawClipRect;
    }

    PortSet(lightplane,(239L << 16) + 127);
    if (color & (COLOR_WHITE | COLOR_LIGHTGRAY)) {
        (*df)(parea,FULLSCREEN, A_NORMAL);
    }
    else {
        (*df)(parea,FULLSCREEN, A_REVERSE);
    }
    PortSet(darkplane,(239L << 16) + 127);
    if (color & (COLOR_WHITE | COLOR_DARKGRAY)) {
        (*df)(parea,FULLSCREEN, A_NORMAL);
    }
    else {
        (*df)(parea,FULLSCREEN, A_REVERSE);
    }
}
