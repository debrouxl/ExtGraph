#include "..\internal.h"

/*===========================================================================*/
/* utility function to draw a string to both planes                          */
/* NOTE: there exists to new styles which are handled as flags               */
/*       A_CENTERED ... the given font will be used and the string will be   */
/*                      drawn centered on the screen                         */
/*       A_SHADOWED ... if this flag is set in the attributes a lightgray    */
/*                      shadow will be drawn with +1 pixel offset in all     */
/*                      two directions                                       */
/*===========================================================================*/
void GrayDrawStrExt2B(short x,short y,char* s,short attr,short font,void* lightplane,void* darkplane) {
    short do_shadow = attr & A_SHADOWED;

    short oldfont = FontGetSys();
    FontSetSys(font);

    if (attr & A_CENTERED) {
        x = (LCD_WIDTH-DrawStrWidth(s,font))/2;
        attr &= ~A_CENTERED;
    }

    attr &= ~A_SHADOWED;

    PortSet(darkplane,(239L << 16) + 127);
    DrawStr(x,y,s,attr);
    PortSet(lightplane,(239L << 16) + 127);
    DrawStr(x,y,s,attr);

    if (do_shadow) DrawStr(x+1,y+1,s,A_NORMAL);
    FontSetSys(oldfont);
}
