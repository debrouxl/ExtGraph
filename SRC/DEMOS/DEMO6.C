/******************************************************************************
*
* project name:    ExtGraph
* initial date:    16/05/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for SpriteX8 routines
*
* $Id: demo6.c,v 1.6 2002/02/22 16:35:39 tnussb Exp $
*
*******************************************************************************/

#define MIN_AMS 100
#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS
#define NO_AMS_CHECK

#ifdef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define C89_92V200(x,y) (x)
#else
#undef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define USE_TI92P
#define USE_V200
#define C89_92V200(x,y) (y)
#endif

#include <tigcclib.h>
#include "../../lib/extgraph.h"  // NOTE: this path is just for this demo !!
                                 //       if the extgraph library is correctly
                                 //       installed you should use:
                                 //
                                 //       #include <extgraph.h>
//#include "extgraph.h"

unsigned long long s64x64[64] = {
0xffffffffffffffffULL,0xffffffff00000001ULL,0xffffffff00000001ULL,0xf0000007007fff01ULL,
0xf0f80f870007f801ULL,0xf1f80fc70007f001ULL,0xf3f80fe70007f001ULL,0xf7f80ff70007f001ULL,
0xf7f80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f801ULL,0xfff007ff000ff801ULL,
0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,
0xc0000000ffffffffULL,0xc0000000ffffffffULL,0xc000fc04ffffffffULL,0xc00fff84f0000007ULL,
0xc07f00fcf0f80f87ULL,0xc0fe007cf1f80fc7ULL,0xc0fc001cf3f80fe7ULL,0xc1f8001cf7f80ff7ULL,
0xc7f0000cf7f80fffULL,0xc7f00004fff80fffULL,0xcfe00004fff80fffULL,0xcfe00000fff80fffULL,
0xdfe00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,
0xdfc00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,
0xcfe00000fff80fffULL,0xcfe00000fff80fffULL,0xc7f00000fff80fffULL,0xc7f00004fff80fffULL,
0xc1f8001cfff80fffULL,0xc0fc0038fff80fffULL,0xc0ff00e0fff80fffULL,0xc07fc7c0fff007ffULL,
0xc001fc00ffffffffULL,0xc0000000ffffffffULL,0xffffffffffffffffULL,0xffffffffffffffffULL};

/*unsigned long long s64x64_mask[64] = {
~0xffffffffffffffffULL,~0xffffffff00000001ULL,~0xffffffff00000001ULL,~0xf0000007007fff01ULL,
~0xf0f80f870007f801ULL,~0xf1f80fc70007f001ULL,~0xf3f80fe70007f001ULL,~0xf7f80ff70007f001ULL,
~0xf7f80fff0007f001ULL,~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,
~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,
~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,
~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,
~0xfff80fff0007f001ULL,~0xfff80fff0007f001ULL,~0xfff80fff0007f801ULL,~0xfff007ff000ff801ULL,
~0xffffffff00000001ULL,~0xffffffff00000001ULL,~0xffffffff00000001ULL,~0xffffffff00000001ULL,
~0xc0000000ffffffffULL,~0xc0000000ffffffffULL,~0xc000fc04ffffffffULL,~0xc00fff84f0000007ULL,
~0xc07f00fcf0f80f87ULL,~0xc0fe007cf1f80fc7ULL,~0xc0fc001cf3f80fe7ULL,~0xc1f8001cf7f80ff7ULL,
~0xc7f0000cf7f80fffULL,~0xc7f00004fff80fffULL,~0xcfe00004fff80fffULL,~0xcfe00000fff80fffULL,
~0xdfe00000fff80fffULL,~0xdfc00000fff80fffULL,~0xdfc00000fff80fffULL,~0xdfc00000fff80fffULL,
~0xdfc00000fff80fffULL,~0xdfe00000fff80fffULL,~0xdfe00000fff80fffULL,~0xdfe00000fff80fffULL,
~0xcfe00000fff80fffULL,~0xcfe00000fff80fffULL,~0xc7f00000fff80fffULL,~0xc7f00004fff80fffULL,
~0xc1f8001cfff80fffULL,~0xc0fc0038fff80fffULL,~0xc0ff00e0fff80fffULL,~0xc07fc7c0fff007ffULL,
~0xc001fc00ffffffffULL,~0xc0000000ffffffffULL,~0xffffffffffffffffULL,~0xffffffffffffffffULL};
*/
unsigned long long sprt1p[2]={0x5555555555555555ULL,0xAAAAAAAAAAAAAAAAULL};

unsigned char *buffer;
unsigned char *buffer2;
unsigned char *buffer3;

unsigned char *sprite1;
unsigned char *sprite2;

#define ARROWS_ROW       ~(1<<0)
#define ESC_ROW          ~C89_92V200(1<<6,1<<8)
#define MODE_ROW         ~C89_92V200(1<<4,1<<8)
#define ZERO_ROW         ~C89_92V200(1<<4,1<<9)
#define ONE_ROW          ~C89_92V200(1<<4,1<<1)
#define TWO_ROW          ~C89_92V200(1<<3,1<<1)

#define UP_KEY           C89_92V200(1<<0,1<<5)
#define DOWN_KEY         C89_92V200(1<<2,1<<7)
#define LEFT_KEY         C89_92V200(1<<1,1<<4)
#define RIGHT_KEY        C89_92V200(1<<3,1<<6)
#define ESC_KEY          C89_92V200(1<<0,1<<6)
#define MODE_KEY         C89_92V200(1<<6,1<<5)
#define ZERO_KEY         C89_92V200(1<<0,1<<5)
#define ONE_KEY          C89_92V200(1<<1,1<<5)
#define TWO_KEY          C89_92V200(1<<1,1<<6)

#define HEIGHT           C89_92V200(100,128)
#define WIDTH            C89_92V200(160,240)

static short mode=1;
static unsigned char *sprite=(unsigned char *)s64x64;


void __attribute__((__always_inline__)) draw(short x, short y) {
    // fetch background from LCD memory
    SpriteX8Get_R(x,y,64,LCD_MEM,buffer,8);
    if (mode==1) {
        // draw masked sprite
        SpriteX8_OR_R(x,y,64,sprite,8,LCD_MEM);
    }
    else if (mode==2) {
        // draw h_mirrored sprite
        SpriteX8_MIRROR_H_R(64,buffer,8,buffer2);
        SpriteX8_MASK_R(x,y,64,buffer2,buffer2,8,LCD_MEM);
    }
    else if (mode==3) {
        // draw v_mirrored sprite
        SpriteX8_MIRROR_V_R(64,buffer,8,buffer2);
        SpriteX8_MASK_R(x,y,64,buffer2,buffer2,8,LCD_MEM);
    }
    else if (mode==4) {
        SpriteX8X8_ROTATE_LEFT_R(64,buffer,8,buffer2);
        SpriteX8_MASK_R(x,y,64,buffer2,buffer2,8,LCD_MEM);
    }
    else if (mode==5) {
        SpriteX8X8_ROTATE_RIGHT_R(64,buffer,8,buffer2);
        SpriteX8_MASK_R(x,y,64,buffer2,buffer2,8,LCD_MEM);
    }
    else {
        // draw sprite, h_mirrored and v_mirrored
        SpriteX8_MIRROR_H_R(64,buffer,8,buffer2);
        SpriteX8_MIRROR_V_R(64,buffer2,8,buffer3);
        SpriteX8_MASK_R(x,y,64,buffer3,buffer3,8,LCD_MEM);
    }
}

void __attribute__((__always_inline__)) restore(short x, short y) {
    // restore background
    SpriteX8_MASK_R(x,y,64,buffer,buffer,8,LCD_MEM);
}


void _main(void) {
    short      key;
    short      x=0,y=0;
    LCD_BUFFER lcd;
    INT_HANDLER int5;

    if (!(buffer=(unsigned char *)malloc(5*8*64))) {
        ST_helpMsg("Not enough memory.");
        return;
    }

    buffer2=buffer+8*64;
    buffer3=buffer2+8*64;
    sprite1=buffer3+8*64;
    sprite2=sprite1+8*64;

    // for (i=0;i<32;i++) memcpy(sprite1+(i<<4),(void *)sprt1p,2*8);
    asm("
    moveq #32-1,%%d0
    move.l sprite1(%%pc),%%a0
    lea sprt1p(%%pc),%%a1

    0:
    move.l (%%a1)+,(%%a0)+
    move.l (%%a1)+,(%%a0)+
    move.l (%%a1)+,(%%a0)+
    move.l (%%a1),(%%a0)+
    lea -12(%%a1),%%a1
    dbf %%d0,0b
    " : : : "d0","a0","a1");

    // Using an assembly block is not more efficient speed-wise (if the
    // assembly block has exactly the same size as the call to memset, it is
    // a bit slower).
    memset(sprite2,0xFF,8*64);

    LCD_save(lcd);

    ST_busy(ST_CLEAR);
    ST_helpMsg("ESC/UP/DOWN/LEFT/RIGHT/0/1/2/MODE");
    OSSetSR(0x0200);
    int5 = GetIntVec(AUTO_INT_5);
    SetIntVec(AUTO_INT_5,DUMMY_HANDLER);

    draw(x,y);

    for(;;) {
        // This could be rewritten to use _keytest(_optimized), but it is not
        // worth the trouble of doing it...
        if (_keytest(RR_ESC)) break;
        key=_rowread(ARROWS_ROW);
        if ((key&LEFT_KEY)&&(x>0)) {
            restore(x,y);
            x--;
            if ((key&UP_KEY)&&(y>0))             y--;
            else if ((key&DOWN_KEY)&&(y<HEIGHT-64)) y++;
            draw(x,y);
        }
        else if ((key&RIGHT_KEY)&&(x<WIDTH-64)) {
            restore(x,y);
            x++;
            if ((key&UP_KEY)&&(y>0))             y--;
            else if ((key&DOWN_KEY)&&(y<HEIGHT-64)) y++;
            draw(x,y);
        }
        else if ((key&UP_KEY)&&(y>0)) {
            restore(x,y);
            y--;
            if ((key&LEFT_KEY)&&(x>0))            x--;
            else if ((key&RIGHT_KEY)&&(x<WIDTH-64)) x++;
            draw(x,y);
        }
        else if ((key&DOWN_KEY)&&(y<HEIGHT-64)) {
            restore(x,y);
            y++;
            if ((key&LEFT_KEY)&&(x>0))            x--;
            else if ((key&RIGHT_KEY)&&(x<WIDTH-64)) x++;
            draw(x,y);
        }
        else if (_rowread(MODE_ROW)&MODE_KEY) {     // MODE
            (++mode==7)?mode=1:mode;
            // Waiting loop so as to cut rebounds on key. It replaces a
            // bigger block of code that uses AMS timer functions.
            asm("move.l #0x27FFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");
            restore(x,y);
            draw(x,y);
        }
        else if (_rowread(ZERO_ROW)&ZERO_KEY && sprite!=(unsigned char *)s64x64) {      // 0
            restore(x,y);
            sprite=(unsigned char *)s64x64;
            draw(x,y);
        }
        else if (_rowread(ONE_ROW)&ONE_KEY && sprite!=(unsigned char *)sprite1) {      // 1
            restore(x,y);
            sprite=(unsigned char *)sprite1;
            draw(x,y);
        }
        else if (_rowread(TWO_ROW)&TWO_KEY && sprite!=(unsigned char *)sprite2) {      // 2
            restore(x,y);
            sprite=(unsigned char *)sprite2;
            draw(x,y);
        }
    }

    if (buffer) free(buffer);
    OSSetSR(0);
    SetIntVec(AUTO_INT_5,int5);
    LCD_restore(lcd);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo6.c,v $
// Revision 1.6  2002/02/22 16:35:39  tnussb
// checking for desired calculator type added ...
//
// Revision 1.5  2002/02/22 15:06:14  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.4  2002/02/22 13:10:59  tnussb
// (1) TI92+ support fixed (Lionel Debroux)
// (2) replaced trap 12 usage by save OSSetSR
//
// Revision 1.3  2002/02/11 11:29:31  tnussb
// (1) complete new demo done by Lionel Debroux
// (2) size optimizations and sourcecode reformatted to fit
//     TICT-style by tnussb
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
