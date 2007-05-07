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


unsigned char s8x8[8] = {0x1,0x3,0x7,0xF,0x1F,0x3F,0x7F,0xFF};
/*unsigned char s8x8[8]    = {0xaa,0x55,0x55,0xaa,0xaa,0x55,0x55,0xaa};*/

/*unsigned short s16x16[16] = {0xaaaa,0x5555,0xaaaa,0x5555,
                             0xaaaa,0x5555,0xaaaa,0x5555,
                             0xaaaa,0x5555,0xaaaa,0x5555,
                             0xaaaa,0x5555,0xaaaa,0x5555};*/
unsigned short s16x16[16] = {0b0000011111100000,
0b0001111111111000,
0b0011111111111100,
0b0111111111111110,
0b0111101111011110,
0b1111010110101111,
0b1111111111111111,
0b1111111111111111,
0b1111111001111111,
0b1110011111100111,
0b1110101111010111,
0b0111010000101110,
0b0111101111011110,
0b0011110000111100,
0b0001111111111000,
0b0000011111100000};

unsigned long s32x32[32] = {
0x00000000,0x11111111,0x22222222,0x33333333,
0x44444444,0x55555555,0x66666666,0x77777777,
0x88888888,0x99999999,0xAAAAAAAA,0xBBBBBBBB,
0xCCCCCCCC,0xDDDDDDDD,0xEEEEEEEE,0xFFFFFFFF,
0xFFFFFFFF,0xEEEEEEEE,0xDDDDDDDD,0xCCCCCCCC,
0xBBBBBBBB,0xAAAAAAAA,0x99999999,0x88888888,
0x77777777,0x66666666,0x55555555,0x44444444,
0x33333333,0x22222222,0x11111111,0x00000000};
/*unsigned long s32x32[32] =  {0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
                             0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555};*/

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
