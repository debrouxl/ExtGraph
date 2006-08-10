/******************************************************************************
*
* project name:    ExtGraph
* initial date:    30/04/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for scale sprite functions
*
* $Id: demo5.c,v 1.4 2002/02/22 15:06:14 tnussb Exp $
*
*******************************************************************************/

#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS
#define MIN_AMS 100
#define NO_AMS_CHECK

#define NO_CALC_DETECT

#include <tigcclib.h>
#include "../../lib/extgraph.h"  // NOTE: this path is just for this demo !!
                                 //       if the extgraph library is correctly
                                 //       installed you should use:
                                 //
                                 //       #include <extgraph.h>


unsigned char s8x8[8]    = {0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55};

unsigned short s16x16[16] = {0xaaaa,0x5555,0xaaaa,0x5555,
                             0xaaaa,0x5555,0xaaaa,0x5555,
                             0xaaaa,0x5555,0xaaaa,0x5555,
                             0xaaaa,0x5555,0xaaaa,0x5555};

unsigned long s32x32[32] =  {0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555};

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


void _main(void) {
    short      i;
    LCD_BUFFER screen;

    LCD_save(screen);

    ClrScr();
    ST_helpMsg("ScaleSprite (8x8) [press a key]");
    ngetchx();
    ClrScr();

    for (i=1;i<80;i++) {
        ScaleSprite8_OR(s8x8,LCD_MEM,0,0,i,i);
        ScaleSprite8_AND(s8x8,LCD_MEM,0,0,i,i);
    }

    ST_helpMsg("ScaleSprite (16x16) [press a key]");
    ngetchx();
    ClrScr();

    for (i=1;i<80;i++) {
        ScaleSprite16_OR(s16x16,LCD_MEM,0,0,i,i);
        ScaleSprite16_AND(s16x16,LCD_MEM,0,0,i,i);
    }

    ST_helpMsg("ScaleSprite (32x32) [press a key]");
    ngetchx();
    ClrScr();

    for (i=1;i<80;i++) {
        ScaleSprite32_OR(s32x32,LCD_MEM,0,0,i,i);
        ScaleSprite32_AND(s32x32,LCD_MEM,0,0,i,i);
    }

    ST_helpMsg("ScaleSprite (64x64) [press a key]");
    ngetchx();
    clrscr();

    for (i=1;i<80;i++) {
        ScaleSprite64_OR(s64x64,LCD_MEM,0,0,i,i);
        ScaleSprite64_AND(s64x64,LCD_MEM,0,0,i,i);
    }

    ST_helpMsg("[press a key to quit]");
    ngetchx();
    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo5.c,v $
// Revision 1.4  2002/02/22 15:06:14  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.3  2002/02/11 11:05:39  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) minor code beautifying
// (3) missing history added to end of file
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
