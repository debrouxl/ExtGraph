// Modified from FilledTriangle_R.

#include <tigcclib.h>

#define ASM_EXCHANGE(val1,val2) asm volatile ("exg %0,%1" : "=da" (val1),"=da" (val2) : "0" (val1),"1" (val2) : "cc")

//#define debug_printf _rom_call(short,(const char*,...),479)
//#define debug_printf_enabled (*((unsigned char *)(_rom_call_addr(47A))))

#define SHIFTCOUNT 5

//=============================================================================
// draws a filled triangle, using callback
//=============================================================================
void ClipFilledTriangle_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short x3 asm("%d4"),short y3 asm("%a1"),void *plane asm("%a0"), void(*drawfunc)(unsigned short x1 asm("%d0"), unsigned short x2 asm("%d1"), unsigned char * addr asm("%a0")) asm("%a2")) {
    short m1,m2,m3,y,xa,xb;
//    short d1,d2;
    unsigned char* addr;

    // check for a degenerated triangle
    // (y coordinates or x coordinates collapsed)
    if ((y1==y2 && y2==y3) || (x1==x2 && x2==x3)) return;

    // sort points by their y coordinate ...
    // point with highest y will be afterwards in (x1/y1),
    // point with lowest y will be in (x3/y3)
    if (y2>=y1) {
        ASM_EXCHANGE(x1,x2);
        ASM_EXCHANGE(y1,y2);
    }

    if (y3>=y1) {
        ASM_EXCHANGE(x1,x3);
        ASM_EXCHANGE(y1,y3);
    }

    if (y3>=y2) {
        ASM_EXCHANGE(x2,x3);
        ASM_EXCHANGE(y2,y3);
    }

//    debug_printf_enabled = 1;

//    debug_printf("x1:%hd x2:%hd x3:%hd y1:%hd y2:%hd y3:%hd\n",x1,x2,x3,y1,y2,y3);

    x1 <<= SHIFTCOUNT;
    x2 <<= SHIFTCOUNT;
    x3 <<= SHIFTCOUNT;

    //calculate dx/dy for highest-to-middle point
    if ((y=y1-y2)) m3 = (x1-x2)/y;
    else           m3 = 999;

    //calculate dx/dy for highest-to-lowest point
    if ((y=y1-y3)) m1 = (x1-x3)/y;
    else           m1 = 999;

    //calculate dx/dy for middle-to-lowest point
    if ((y=y2-y3)) m2 = (x2-x3)/y;
    else           m2 = 999;

    // start point is the lowest one point (xcoordinates shifted up by 7 bits)
    xa=x3;

    // if highest-and-middle lowest point share their xcoordinate xb is the xcoord of middle point
    if (m2==999) xb=x2;
    else         xb=xa;

    addr = (unsigned char *)plane+((((y3)+(y3))<<4)-((y3)+(y3)));

    if (x2<(x3+(y2-y3)*m1)) {
//        d1=1,d2=0;

        // now draw the spans
        for (y=y3;y<=y2;y++,xa+=m1,xb+=m2,(unsigned char *)addr+=30) {
//            debug_printf("y:%hd y3:%hd y2:%hd xa:%hd m1:%hd xb:%hd m2:%hd\n",y,y3,y2,xa,m1,xb,m2);
            (*drawfunc)(1+(xa>>SHIFTCOUNT),0+(xb>>SHIFTCOUNT),addr);
        }
        for (;y<=y1;y++,xa+=m1,xb+=m3,(unsigned char *)addr+=30) {
//            debug_printf("y:%hd y1:%hd xa:%hd m1:%hd xb:%hd m3:%hd\n",y,y1,xa,m1,xb,m3);
            (*drawfunc)(1+(xa>>SHIFTCOUNT),0+(xb>>SHIFTCOUNT),addr);
        }
    }
    else {
//        d1=0,d2=1;

        // now draw the spans
        for (y=y3;y<=y2;y++,xa+=m1,xb+=m2,(unsigned char *)addr+=30) {
//            debug_printf("y:%hd y3:%hd y2:%hd xa:%hd m1:%hd xb:%hd m2:%hd\n",y,y3,y2,xa,m1,xb,m2);
            (*drawfunc)(0+(xa>>SHIFTCOUNT),1+(xb>>SHIFTCOUNT),addr);
        }
        for (;y<=y1;y++,xa+=m1,xb+=m3,(unsigned char *)addr+=30) {
//            debug_printf("y:%hd y1:%hd xa:%hd m1:%hd xb:%hd m3:%hd\n",y,y1,xa,m1,xb,m3);
            (*drawfunc)(0+(xa>>SHIFTCOUNT),1+(xb>>SHIFTCOUNT),addr);
        }
    }
}
