#include "../internal.h"

void GrayInvertRect2B(short x0,short y0,short x1, short y1,void* lightplane,void* darkplane) {
    SCR_RECT sr = {{x0,y0,x1,y1}};

    PortSet(lightplane,(239L << 16) + 127);
    ScrRectFill(&sr,FULLSCREEN,A_XOR);
    PortSet(darkplane,(239L << 16) + 127);
    ScrRectFill(&sr,FULLSCREEN,A_XOR);
}
