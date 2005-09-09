#include "../internal.h"

/*===========================================================================*/
/* utility function to draw a string to both planes                          */
/*===========================================================================*/
void GrayDrawStr2B(short x,short y,char* s,short attr,void* lightplane,void* darkplane) {
    PortSet(lightplane,(239L << 16) + 127);
    DrawStr(x,y,s,attr);
    PortSet(darkplane,(239L << 16) + 127);
    DrawStr(x,y,s,attr);
}
